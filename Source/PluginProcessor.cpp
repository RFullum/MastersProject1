/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MasterExp1AudioProcessor::MasterExp1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
parameters(*this, nullptr, "ParameterTree", {
// id, description, min, max, default
// Main Osc Params
    std::make_unique<AudioParameterFloat>("gate_threshold", "Gate Threshold", 0.0f, 1.0f, 0.0f)
})


{
    // Gate Param Construct
    gateThreshold = parameters.getRawParameterValue("gate_threshold");
    
}

MasterExp1AudioProcessor::~MasterExp1AudioProcessor()
{
}

//==============================================================================
const String MasterExp1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MasterExp1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MasterExp1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MasterExp1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MasterExp1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MasterExp1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MasterExp1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void MasterExp1AudioProcessor::setCurrentProgram (int index)
{
}

const String MasterExp1AudioProcessor::getProgramName (int index)
{
    return {};
}

void MasterExp1AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MasterExp1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Sets sampleRate for classes
    bandLimiter.setSampleRate(sampleRate);
    freqCalc.setSampleRate(sampleRate);
    
    // Sets threshold for noiseGate
    noiseGate.setThreshold(0.3f);
    
    // Sets frequency detection classes buffer size
    zeroXing.setBufferAlt(sampleRate);
    
    

}

void MasterExp1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MasterExp1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MasterExp1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    int numSamples = buffer.getNumSamples();
    auto* leftChannel = buffer.getWritePointer(0);
    auto* rightChannel = buffer.getWritePointer(1);
    
    
    
    // DSP!
    for (int i=0; i<numSamples; i++)
    {
        float sampleL = 0.0f;
        float sampleR = 0.0f;
        
        float gatedSample = noiseGate.processGate(leftChannel[i]);
        float filteredSample = bandLimiter.process(gatedSample);
        float clippedSample = waveClipper.hardClip(filteredSample);

        float cycleLenght = zeroXing.process(clippedSample);
        freq = freqCalc.freqCalc(cycleLenght);
        
        transientTracker.transientDetect(filteredSample);
        
        
        sampleL = filteredSample;
        sampleR = filteredSample;
        
        // Stereo out
        leftChannel[i] = sampleL;
        rightChannel[i] = sampleR;
        
    }
    
    std::cout << "freq " << freq << "\n";
    //std::cout << "transient? " << transientTracker.transientDetect(filteredSample) << "\n";
}

//==============================================================================
bool MasterExp1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MasterExp1AudioProcessor::createEditor()
{
    return new MasterExp1AudioProcessorEditor (*this);
}

//==============================================================================
void MasterExp1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MasterExp1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MasterExp1AudioProcessor();
}
