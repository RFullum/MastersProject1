/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WaveClipper.h"
#include "NoiseGate.h"
#include "BandLimiting.h"
#include "ZeroCrossingCounter.h"
#include "FrequencyCalculation.h"
#include "FrequencyToMidi.h"
#include "MidiDataCalculations.h"


//==============================================================================
/**
*/
class MasterExp1AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MasterExp1AudioProcessor();
    ~MasterExp1AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // APVTS
    AudioProcessorValueTreeState parameters;
    
    
private:
    // Header file class instances
    WaveClipper waveClipper;
    NoiseGate noiseGate;
    BandLimiter bandLimiter;
    ZeroXing zeroXing;
    FrequencyCalculation freqCalc;
    FrequencyToMidi frequencyToMidi;
    MidiDataCalculations midiInfo;
    
    // Variables
    float freq;             // Frequency derived by zero crossing calculation
    float currentLevel;     // Level of audio
    float noteVelocity;
    
    int currentMidiNoteNumber;
    int previousMidiNoteNumber;
    int midiChannel;    // 1 for ease of use. Can make selectable parameter in future versions
    
    bool triggerNewNote;
    
    // Parameter tree variables
    std::atomic<float>* gateThresholdParam;
    std::atomic<float>* inputGainParam;
    
    std::atomic<float>* accelXOnOffParameter;
    std::atomic<float>* accelYOnOffParameter;
    std::atomic<float>* accelZOnOffParameter;
    std::atomic<float>* gyroXOnOffParameter;
    std::atomic<float>* gyroYOnOffParameter;
    std::atomic<float>* gyroZOnOffParameter;
    
    std::atomic<float>* accelXSoloParameter;
    std::atomic<float>* accelYSoloParameter;
    std::atomic<float>* accelZSoloParameter;
    std::atomic<float>* gyroXSoloParameter;
    std::atomic<float>* gyroYSoloParameter;
    std::atomic<float>* gyroZSoloParameter;
    
    std::atomic<float>* midiLearnFocusParameter;
    std::atomic<float>* gyroMappingShapeParameter;
    std::atomic<float>* accelMappingShapeParameter;
    
    std::atomic<float>* zeroAccelXValuesParameter;
    std::atomic<float>* zeroAccelYValuesParameter;
    std::atomic<float>* zeroAccelZValuesParameter;
    
    // Invisible Parameter tree variables
    std::atomic<float>* accelXCCValParameter;
    std::atomic<float>* accelYCCValParameter;
    std::atomic<float>* accelZCCValParameter;
    std::atomic<float>* gyroXCCValParameter;
    std::atomic<float>* gyroYCCValParameter;
    std::atomic<float>* gyroZCCValParameter;
    
    float prevAccelXCC;
    float prevAccelYCC;
    float prevAccelZCC;
    float prevGyroXCC;
    float prevGyroYCC;
    float prevGyroZCC;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterExp1AudioProcessor)
};
