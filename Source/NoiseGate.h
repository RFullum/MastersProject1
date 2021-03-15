/*
  ==============================================================================

    NoiseGate.h
    Created: 16 Jun 2020 10:47:20am
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once


class NoiseGate
{
public:
    NoiseGate();
    ~NoiseGate();
    
    /// sets gate threshold 0.0f - 1.0f;
    void setThreshold(float thresh);
    
    
    /**
     Recieves buffer.getRMSLevel( ) from process block and sets it to currentLevel.
     */
    void levelIn(float level);
    
    
    /**
     Takes sample in. If signal is above the threshold, the gate passes sampleIn through and returns it, and sets
     gateActive to false. If the signal is below the threshold for silenceThresholdLength, the gate returns a 0.0f value and
     sets gateActive to True
     */
    float processGate(float sampleIn);
    

    /**
     Returns state of gate as bool: True = Gate is active and no audio is output. False = Gate is off and audio
     is thruput.
     */
    bool currentGateState();
    
    
private:
    /**
    Takes sample in. If signal is above the threshold, the gate passes sampleIn through and returns it, and sets
    gateActive to false. If the signal is below the threshold for silenceThresholdLength, the gate returns a 0.0f value and
    sets gateActive to True
    */
    float gate(float sampleIn);
    
    // Member Variables
    int silenceCounter;
    int silenceThresholdLength;
    
    float thresholdLevel;
    float currentLevel;
    
    bool gateActive;
    
};
