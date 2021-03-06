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
                       // REMOVED AUDIO OUTPUTS:
                       //.withOutput ("Output", AudioChannelSet::stereo(), false)
                     #endif
                       ),
#endif

//
// ParameterFloats:
// id, description, min, max, default
// ~OR~
// id, description, normalisableRange(min, max, increment, skew, symmetric),
//                 default, param label, param category, string from value, string to value
//
// ParameterChoices:
// id, description, StringArray( {"choice1", "choice2", ... } ), default index of StringArray
//
parameters(*this, nullptr, "ParameterTree", {
    std::make_unique<AudioParameterFloat> ( "input_gain", "Input Gain",
                                            NormalisableRange<float>(0.1f, 10.0f, 0.01f, 1.0f, false), 4.25, "gain" ),
    std::make_unique<AudioParameterFloat> ( "gate_threshold", "Gate Threshold",
                                            NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f, false), 0.01f, "gate" ),
    
    std::make_unique<AudioParameterChoice> ( "accelXOnOff", "Accel X", StringArray( { "Off", "On" } ), 0 ),
    std::make_unique<AudioParameterChoice> ( "accelYOnOff", "Accel Y", StringArray( { "Off", "On" } ), 0 ),
    std::make_unique<AudioParameterChoice> ( "accelZOnOff", "Accel Z", StringArray( { "Off", "On" } ), 0 ),
    
    std::make_unique<AudioParameterChoice> ( "gyroXOnOff", "Gyro X", StringArray( { "Off", "On" } ), 0 ),
    std::make_unique<AudioParameterChoice> ( "gyroYOnOff", "Gyro Y", StringArray( { "Off", "On" } ), 0 ),
    std::make_unique<AudioParameterChoice> ( "gyroZOnOff", "Gyro Z", StringArray( { "Off", "On" } ), 0 ),
    
    std::make_unique<AudioParameterChoice> ( "midiLearnFocus", "Midi Learn Focus",
                                             StringArray( { "none",
                                                            "Accel X", "Accel Y", "Accel Z",
                                                            "Gyro X",  "Gyro Y",  "Gyro Z" } ),
                                             0 ),
    std::make_unique<AudioParameterChoice> ( "accelMapShape", "Accelerometer Shape",
                                             StringArray( { "Linear",  "Logarithmic", "Exponential",
                                                            "Exp-log", "Log-exp" } ),
                                             0 ),
    std::make_unique<AudioParameterChoice> ( "gyroMapShape", "Gyro Shape",
                                             StringArray( { "Linear",  "Logarithmic", "Exponential",
                                                            "Exp-log", "Log-exp" } ),
                                             0 ),
    
    std::make_unique<AudioParameterChoice> ( "zeroAccelXOrientation", "Zero X Orientation",
                                             StringArray( { "Active", "Set Orientation", "Reset" } ),
                                             0),
    std::make_unique<AudioParameterChoice> ( "zeroAccelYOrientation", "Zero Y Orientation",
                                             StringArray( { "Active", "Set Orientation", "Reset" } ),
                                             0 ),
    std::make_unique<AudioParameterChoice> ( "zeroAccelZOrientation", "Zero Z Orientation",
                                             StringArray( { "Active", "Set Orientation", "Reset" } ),
                                             0 ),
    // Invisible Params
    std::make_unique<AudioParameterFloat> ( "accelXCC", "Accel X CC",
                                            NormalisableRange<float>(0.0f, 127.0f, 1.0f, 1.0f, false), 64.0f, "Accel X CC" ),
    std::make_unique<AudioParameterFloat> ( "accelYCC", "Accel Y CC",
                                            NormalisableRange<float>(0.0f, 127.0f, 1.0f, 1.0f, false), 64.0f, "Accel Y CC" ),
    std::make_unique<AudioParameterFloat> ( "accelZCC", "Accel Z CC",
                                            NormalisableRange<float>(0.0f, 127.0f, 1.0f, 1.0f, false), 64.0f, "Accel Z CC" ),
    std::make_unique<AudioParameterFloat> ( "gyroXCC", "Gyro X CC",
                                            NormalisableRange<float>(0.0f, 127.0f, 1.0f, 1.0f, false), 64.0f, "Gyro X CC" ),
    std::make_unique<AudioParameterFloat> ( "gyroYCC", "Gyro Y CC",
                                            NormalisableRange<float>(0.0f, 127.0f, 1.0f, 1.0f, false), 64.0f, "Gyro Y CC" ),
    std::make_unique<AudioParameterFloat> ( "gyroZCC", "Gyro Z CC",
                                            NormalisableRange<float>(0.0f, 127.0f, 1.0f, 1.0f, false), 64.0f, "Gyro Z CC" ),
    
    
    
}),

freq(0.0f),
currentLevel(0.0f),
noteVelocity(0.0f),

currentMidiNoteNumber(0),
previousMidiNoteNumber(0),
midiChannel(1),

triggerNewNote(false),

prevAccelXCC(0.0f),
prevAccelYCC(0.0f),
prevAccelZCC(0.0f),
prevGyroXCC(0.0f),
prevGyroYCC(0.0f),
prevGyroZCC(0.0f)

{
    // Param Construct
    inputGainParam     = parameters.getRawParameterValue ( "input_gain"     );
    gateThresholdParam = parameters.getRawParameterValue ( "gate_threshold" );
    
    accelXOnOffParameter = parameters.getRawParameterValue ( "accelXOnOff" );
    accelYOnOffParameter = parameters.getRawParameterValue ( "accelYOnOff" );
    accelZOnOffParameter = parameters.getRawParameterValue ( "accelZOnOff" );
    
    gyroXOnOffParameter = parameters.getRawParameterValue ( "gyroXOnOff" );
    gyroYOnOffParameter = parameters.getRawParameterValue ( "gyroYOnOff" );
    gyroZOnOffParameter = parameters.getRawParameterValue ( "gyroZOnOff" );
    
    midiLearnFocusParameter    = parameters.getRawParameterValue ( "midiLearnFocus" );
    accelMappingShapeParameter = parameters.getRawParameterValue ( "accelMapShape"  );
    gyroMappingShapeParameter  = parameters.getRawParameterValue ( "gyroMapShape"   );
    
    zeroAccelXValuesParameter = parameters.getRawParameterValue ( "zeroAccelXOrientation" );
    zeroAccelYValuesParameter = parameters.getRawParameterValue ( "zeroAccelYOrientation" );
    zeroAccelZValuesParameter = parameters.getRawParameterValue ( "zeroAccelZOrientation" );
    
    // Invisible Params
    accelXCCValParameter = parameters.getRawParameterValue ( "accelXCC" );
    accelYCCValParameter = parameters.getRawParameterValue ( "accelYCC" );
    accelZCCValParameter = parameters.getRawParameterValue ( "accelZCC" );
    gyroXCCValParameter  = parameters.getRawParameterValue ( "gyroXCC"  );
    gyroYCCValParameter  = parameters.getRawParameterValue ( "gyroYCC"  );
    gyroZCCValParameter  = parameters.getRawParameterValue ( "gyroZCC"  );
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
    bandLimiter.setSampleRate ( sampleRate );
    freqCalc.setSampleRate    ( sampleRate );
    
    // Sets frequency detection classes buffer size
    zeroXing.setBuffer ( sampleRate );

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
    int numSamples    = buffer.getNumSamples();
    auto* leftChannel = buffer.getWritePointer(0);
    // auto* rightChannel = buffer.getWritePointer(1);
    
    // Audio Gain
    buffer.applyGain ( *inputGainParam );
    
    currentLevel = buffer.getRMSLevel(0, 0, numSamples);
    
    // Noise Gate Values
    noiseGate.setThreshold ( *gateThresholdParam );
    noiseGate.levelIn      ( currentLevel        );
    
    // Level to Midi Velocity
    midiInfo.setVelocity ( currentLevel );
    
    
    // DSP!
    for (int i=0; i<numSamples; i++)
    {
        float gatedSample    = noiseGate.processGate  ( leftChannel[i] );
        float filteredSample = bandLimiter.process    ( gatedSample    );
        float clippedSample  = waveClipper.clipSignal ( filteredSample );

        if (noiseGate.currentGateState() == true)
        {
            freq = 0.0f;
        }
        else
        {
            float cycleLenght = zeroXing.process  ( clippedSample );
            freq              = freqCalc.freqCalc ( cycleLenght   );
        }

    }   // END DSP LOOP
    
    
    // MIDI Note Values
    currentMidiNoteNumber  = frequencyToMidi.getMidiFromFreq ( freq );
    triggerNewNote         = midiInfo.setNoteTrigger         ( currentMidiNoteNumber );
    previousMidiNoteNumber = midiInfo.getPreviousNoteNumber  ();
    noteVelocity           = midiInfo.getVelocity            ();
    
    // MIDI Note On/Off Logic
    if (triggerNewNote)
    {
        if (currentMidiNoteNumber == 0)
        {
            midiMessages.addEvent( MidiMessage::allNotesOff( midiChannel ), midiMessages.getLastEventTime() + 1 );
        }
        else if (previousMidiNoteNumber == 0 && currentMidiNoteNumber != 0)
        {
            midiMessages.addEvent ( MidiMessage::allNotesOff( midiChannel ), midiMessages.getLastEventTime() + 1 );
            midiMessages.addEvent ( MidiMessage::noteOn( midiChannel, currentMidiNoteNumber, noteVelocity ),
                                    midiMessages.getLastEventTime() + 1 );
        }
        else if (previousMidiNoteNumber != 0 && currentMidiNoteNumber != 0)
        {
            midiMessages.addEvent ( MidiMessage::allNotesOff( midiChannel ), midiMessages.getLastEventTime() + 1 );
            midiMessages.addEvent ( MidiMessage::noteOn( midiChannel, currentMidiNoteNumber, noteVelocity ),
                                    midiMessages.getLastEventTime() + 1 );
        }
        else
        {
            midiMessages.addEvent ( MidiMessage::allNotesOff( midiChannel ), midiMessages.getLastEventTime() + 1 );
        }
        
    }   // END MIDI NOTE ON/OFF LOGIC
    
    
    //
    // MIDI CC Value
    //
    
    if (prevAccelXCC != *accelXCCValParameter)
    {
        midiMessages.addEvent( MidiMessage::controllerEvent( 1, 80, *accelXCCValParameter ), midiMessages.getLastEventTime() + 1 );
        
        prevAccelXCC = *accelXCCValParameter;
    }
        
    
    if (prevAccelYCC != *accelYCCValParameter)
    {
        midiMessages.addEvent( MidiMessage::controllerEvent( 1, 81, *accelYCCValParameter ), midiMessages.getLastEventTime() + 1 );
        
        prevAccelYCC = *accelYCCValParameter;
    }
        
    
    if (prevAccelZCC != *accelZCCValParameter)
    {
        midiMessages.addEvent( MidiMessage::controllerEvent( 1, 82, *accelZCCValParameter ), midiMessages.getLastEventTime() + 1 );
        
        prevAccelZCC = *accelZCCValParameter;
    }
        
    
    if (prevGyroXCC != *gyroXCCValParameter)
    {
        midiMessages.addEvent( MidiMessage::controllerEvent( 1, 16, *gyroXCCValParameter ), midiMessages.getLastEventTime() + 1 );
        
        prevGyroXCC= *gyroXCCValParameter;
    }
        
    
    if (prevGyroYCC != *gyroYCCValParameter)
    {
        midiMessages.addEvent( MidiMessage::controllerEvent( 1, 17, *gyroYCCValParameter ), midiMessages.getLastEventTime() + 1 );
        
        prevGyroYCC = *gyroYCCValParameter;
    }
        
    
    if (prevGyroZCC != *gyroZCCValParameter)
    {
        midiMessages.addEvent( MidiMessage::controllerEvent( 1, 18, *gyroZCCValParameter ), midiMessages.getLastEventTime() + 1 );
        
        prevGyroZCC = *gyroZCCValParameter;
    }
        
    
    //DBG(*accelXCCValParameter);
    //DBG(*accelYCCValParameter);
    //DBG(*accelZCCValParameter);
    //DBG(*gyroXCCValParameter);
    //DBG(*gyroYCCValParameter);
    //DBG(*gyroZCCValParameter);
    //DBG("");
     
    // END MIDI CC VALUE PROCESSING
    
    
}   // END PROCESS BLOCK

//==============================================================================
bool MasterExp1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MasterExp1AudioProcessor::createEditor()
{
    return new MasterExp1AudioProcessorEditor (*this);
    //return new GenericAudioProcessorEditor (*this);
}

//==============================================================================
void MasterExp1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // getStateInformation
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void MasterExp1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // setStateInformation
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName (parameters.state.getType()))
        {
            parameters.replaceState (ValueTree::fromXml (*xmlState));
        }
    }

}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MasterExp1AudioProcessor();
}


