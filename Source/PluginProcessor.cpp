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
                       //.withOutput ("Output", AudioChannelSet::stereo(), false)
                     #endif
                       ),
#endif

parameters(*this, nullptr, "ParameterTree", {
// ParameterFloats:
// id, description, min, max, default
//
// ParameterChoices:
// id, descript, choices (StringArray), default index of StringArray
//
    std::make_unique<AudioParameterFloat>("input_gain", "Input Gain", 0.1f, 10.0f, 4.25f),
    std::make_unique<AudioParameterFloat>("gate_threshold", "Gate Threshold", 0.0f, 1.0f, 0.01f),
    
    //std::make_unique<AudioParameterChoice>("ccGyroX", "Gyro X CC Number", StringArray({}), 1)
    
    std::make_unique<AudioParameterChoice>("accelXOnOff", "Accel X", StringArray({ "Off", "On" }), 0),
    std::make_unique<AudioParameterChoice>("accelYOnOff", "Accel Y", StringArray({ "Off", "On" }), 0),
    std::make_unique<AudioParameterChoice>("accelZOnOff", "Accel Z", StringArray({ "Off", "On" }), 0),
    
    std::make_unique<AudioParameterChoice>("gyroXOnOff", "Gyro X", StringArray({ "Off", "On" }), 0),
    std::make_unique<AudioParameterChoice>("gyroYOnOff", "Gyro Y", StringArray({ "Off", "On" }), 0),
    std::make_unique<AudioParameterChoice>("gyroZOnOff", "Gyro Z", StringArray({ "Off", "On" }), 0),
    
    std::make_unique<AudioParameterChoice>("midiLearnFocus", "Midi Learn Focus", StringArray({ "none", "Accel X", "Accel Y", "Accel Z", "Gyro X", "Gyro Y", "Gyro Z"}), 0)
    
    
})


{
    // Param Construct
    inputGainParam = parameters.getRawParameterValue("input_gain");
    gateThresholdParam = parameters.getRawParameterValue("gate_threshold");
    
    accelXOnOffParameter = parameters.getRawParameterValue("accelXOnOff");
    accelYOnOffParameter = parameters.getRawParameterValue("accelYOnOff");
    accelZOnOffParameter = parameters.getRawParameterValue("accelZOnOff");
    
    gyroXOnOffParameter = parameters.getRawParameterValue("gyroXOnOff");
    gyroYOnOffParameter = parameters.getRawParameterValue("gyroYOnOff");
    gyroZOnOffParameter = parameters.getRawParameterValue("gyroZOnOff");
    
    midiLearnFocusParameter = parameters.getRawParameterValue("midiLearnFocus");
    
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
    
    // Sets frequency detection classes buffer size
    zeroXing.setBuffer(sampleRate);
    
    // UDP Setup: connects to UDP Ports for each instance
    udpConnectionGyroX.udpPortConnect(udpPortGyroX);
    udpConnectionGyroY.udpPortConnect(udpPortGyroY);
    udpConnectionGyroZ.udpPortConnect(udpPortGyroZ);
    udpConnectionAccelX.udpPortConnect(udpPortAccelX);
    udpConnectionAccelY.udpPortConnect(udpPortAccelY);
    udpConnectionAccelZ.udpPortConnect(udpPortAccelZ);

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
    
    // Clears midi buffer
    midiMessages.clear();
    
    // Audio input to buffer
    int numSamples = buffer.getNumSamples();
    auto* leftChannel = buffer.getWritePointer(0);
    // auto* rightChannel = buffer.getWritePointer(1);
    
    // Audio Gain
    buffer.applyGain(*inputGainParam);
    currentLevel = buffer.getRMSLevel(0, 0, numSamples);
    
    // Noise Gate Values
    noiseGate.setThreshold(*gateThresholdParam);
    noiseGate.levelIn(currentLevel);
    
    // Level to Midi Velocity
    midiInfo.setVelocity(currentLevel);
    
    // Read XYZ values from Arduio via UDP
    udpConnectionGyroX.readArduinoStream();
    udpConnectionGyroY.readArduinoStream();
    udpConnectionGyroZ.readArduinoStream();
    udpConnectionAccelX.readArduinoStream();
    udpConnectionAccelY.readArduinoStream();
    udpConnectionAccelZ.readArduinoStream();
    
    // DSP!
    for (int i=0; i<numSamples; i++)
    {
        float gatedSample = noiseGate.processGate(leftChannel[i]);
        float filteredSample = bandLimiter.process(gatedSample);
        float clippedSample = waveClipper.clipSignal(filteredSample);

        if (noiseGate.currentGateState() == true)
        {
            freq = 0.0f;
        }
        else
        {
            float cycleLenght = zeroXing.process(clippedSample);
            freq = freqCalc.freqCalc(cycleLenght);
        }

    }   // END DSP LOOP
    
    
    // MIDI Note Values
    currentMidiNoteNumber = frequencyToMidi.getMidiFromFreq(freq);
    triggerNewNote = midiInfo.setNoteTrigger(currentMidiNoteNumber);
    previousMidiNoteNumber = midiInfo.getPreviousNoteNumber();
    noteVelocity = midiInfo.getVelocity();
    
    // MIDI Note On/Off Logic
    if (triggerNewNote)
    {
        if (currentMidiNoteNumber == 0)
        {
            /*
            for (int j=0; j<128; j++)
            {
                midiMessages.addEvent(MidiMessage::noteOff(midiChannel, j), midiMessages.getLastEventTime() + 1);
            }
            */
            //std::cout << "crnt 0 addEvent: noteOff " << midiChannel << " " << previousMidiNoteNumber << " " << midiMessages.getLastEventTime() + 1 << "\n";
            midiMessages.addEvent(MidiMessage::allNotesOff(midiChannel), midiMessages.getLastEventTime() + 1);
        }
        else if (previousMidiNoteNumber == 0 && currentMidiNoteNumber != 0)
        {
            midiMessages.addEvent(MidiMessage::allNotesOff(midiChannel), midiMessages.getLastEventTime() + 1);
            
            midiMessages.addEvent(MidiMessage::noteOn(midiChannel, currentMidiNoteNumber, noteVelocity), midiMessages.getLastEventTime() + 1);
            //std::cout << "prv 0 crnt X addEvent: noteOn " << midiChannel << " " << currentMidiNoteNumber << " " << noteVelocity << " " << midiMessages.getLastEventTime() + 1 << "\n";
        }
        else if (previousMidiNoteNumber != 0 && currentMidiNoteNumber != 0)
        {
            
            //midiMessages.addEvent(MidiMessage::noteOff(midiChannel, previousMidiNoteNumber), midiMessages.getLastEventTime() + 1);
            //std::cout << "prv X crnt Y addEvent: noteOff " << midiChannel << " " << previousMidiNoteNumber << " " << midiMessages.getLastEventTime() + 1 << "\n";
            midiMessages.addEvent(MidiMessage::allNotesOff(midiChannel), midiMessages.getLastEventTime() + 1);
            
            midiMessages.addEvent(MidiMessage::noteOn(midiChannel, currentMidiNoteNumber, noteVelocity), midiMessages.getLastEventTime() + 1);
            //std::cout << "prv X crnt Y addEvent: noteOn " << midiChannel << " " << currentMidiNoteNumber << " " << noteVelocity << " " << midiMessages.getLastEventTime() + 1 << "\n";
        }
        else
        {
            midiMessages.addEvent(MidiMessage::allNotesOff(midiChannel), midiMessages.getLastEventTime() + 1);
            //midiMessages.addEvent(MidiMessage::noteOff(midiChannel, currentMidiNoteNumber), midiMessages.getLastEventTime() + 1);
            //std::cout << "other addEvent: noteOff " << midiChannel << " " << previousMidiNoteNumber << " " << midiMessages.getLastEventTime() + 1 << "\n";
        }
        
    }   // END MIDI NOTE ON/OFF LOGIC
    
    //
    // MIDI CC Value
    //
    
    // Get global on off value from parameter tree
    accelXOnOff = *accelXOnOffParameter;
    accelYOnOff = *accelYOnOffParameter;
    accelZOnOff = *accelZOnOffParameter;
    
    gyroXOnOff = *gyroXOnOffParameter;
    gyroYOnOff = *gyroYOnOffParameter;
    gyroZOnOff = *gyroZOnOffParameter;
    
    // Use Midi Learn Focus Parameter to solo individual values
    // allowing Midi Learn to receive one value at a time
    if (*midiLearnFocusParameter != 0)
    {
        if (*midiLearnFocusParameter == 1)
        {
            accelXOnOff = 1;
            accelYOnOff = accelZOnOff = gyroXOnOff = gyroYOnOff = gyroZOnOff = 0;
        }
        else if (*midiLearnFocusParameter == 2)
        {
            accelYOnOff = 1;
            accelXOnOff = accelZOnOff = gyroXOnOff = gyroYOnOff = gyroZOnOff = 0;
        }
        else if (*midiLearnFocusParameter == 3)
        {
            accelZOnOff = 1;
            accelXOnOff = accelYOnOff = gyroXOnOff = gyroYOnOff = gyroZOnOff = 0;
        }
        else if (*midiLearnFocusParameter == 4)
        {
            gyroXOnOff = 1;
            accelXOnOff = accelYOnOff = accelZOnOff = gyroYOnOff = gyroZOnOff = 0;
        }
        else if (*midiLearnFocusParameter == 5)
        {
            gyroYOnOff = 1;
            accelXOnOff = accelYOnOff = accelZOnOff = gyroXOnOff = gyroZOnOff = 0;
        }
        else if (*midiLearnFocusParameter == 6)
        {
            gyroZOnOff = 1;
            accelXOnOff = accelYOnOff = accelZOnOff = gyroXOnOff = gyroYOnOff = 0;
        }
    }
    
    // Sends Midi CC Value according to On/Off parameter and midiLearnFocusParameter logic
    if (accelXOnOff == 1)
    {
        midiMessages.addEvent(MidiMessage::controllerEvent(1, 80, udpConnectionAccelX.getCCValue()), midiMessages.getLastEventTime() + 1);
    }
    
    if (accelYOnOff == 1)
    {
        midiMessages.addEvent(MidiMessage::controllerEvent(1, 81, udpConnectionAccelY.getCCValue()), midiMessages.getLastEventTime() + 1);
    }
    
    if (accelZOnOff == 1)
    {
        midiMessages.addEvent(MidiMessage::controllerEvent(1, 82, udpConnectionAccelZ.getCCValue()), midiMessages.getLastEventTime() + 1);
    }
    
    if (gyroXOnOff == 1)
    {
        midiMessages.addEvent(MidiMessage::controllerEvent(1, 16, udpConnectionGyroZ.getCCValue()), midiMessages.getLastEventTime() + 1);
    }
    
    if (gyroYOnOff == 1)
    {
        midiMessages.addEvent(MidiMessage::controllerEvent(1, 17, udpConnectionGyroY.getCCValue()), midiMessages.getLastEventTime() + 1);
    }
    
    if (gyroZOnOff == 1)
    {
        midiMessages.addEvent(MidiMessage::controllerEvent(1, 18, udpConnectionGyroZ.getCCValue()), midiMessages.getLastEventTime() + 1);
    }
    
    
    
    
}   // END PROCESS BLOCK

//==============================================================================
bool MasterExp1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MasterExp1AudioProcessor::createEditor()
{
    return new GenericAudioProcessorEditor (*this);
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
