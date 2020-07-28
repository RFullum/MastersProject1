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
#include "TransientTracker.h"
#include "FrequencyToMidi.h"
#include "MidiDataCalculations.h"
#include "UDPConnection.h"


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

private:
    // class Instances
    AudioProcessorValueTreeState parameters;
    WaveClipper waveClipper;
    NoiseGate noiseGate;
    BandLimiter bandLimiter;
    ZeroXing zeroXing;
    FrequencyCalculation freqCalc;
    FrequencyToMidi frequencyToMidi;
    MidiDataCalculations midiInfo;
    
    
    float freq; // Frequency derived by zero crossing calculation
    float currentLevel;
    int currentMidiNoteNumber = 0;
    int previousMidiNoteNumber = 0;
    int midiChannel = 1;
    float noteVelocity;
    bool triggerNewNote = false;
    
    bool gateState;
    
    // Noise Gate
    std::atomic<float>* gateThreshold;
    
    // UDP
    UDPConnection udpConnectionGyroX;
    UDPConnection udpConnectionGyroY;
    UDPConnection udpConnectionGyroZ;
    UDPConnection udpConnectionAccelX;
    UDPConnection udpConnectionAccelY;
    UDPConnection udpConnectionAccelZ;
    int udpPortGyroX = 65013;
    int udpPortGyroY = 65014;
    int udpPortGyroZ = 65015;
    int udpPortAccelX = 65016;
    int udpPortAccelY = 65017;
    int udpPortAccelZ = 65018;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterExp1AudioProcessor)
};
