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
    /**
     Constructor
     */
    NoiseGate()
    {
        
    }
    
    /// destructor
    ~NoiseGate()
    {
        
    }
    
    /// sets gate threshold 0.0f - 1.0f;
    void setThreshold(float thresh)
    {
        thresholdLevel = thresh;
    }
    
    /**
     Recieves buffer.getRMSLevel( ) from process block and sets it to currentLevel.
     */
    void levelIn(float level)
    {
        currentLevel = level;
    }
    
    /**
     Takes sample in. If signal is above the threshold, the gate passes sampleIn through and returns it, and sets
     gateActive to false. If the signal is below the threshold for silenceThresholdLength, the gate returns a 0.0f value and
     sets gateActive to True
     */
    float processGate(float sampleIn)
    {
        return gate(sampleIn);
    }

    /**
     Returns state of gate as bool: True = Gate is active and no audio is output. False = Gate is off and audio
     is thruput.
     */
    bool currentGateState()
    {
        return gateActive;
    }
    
private:
    /**
    Takes sample in. If signal is above the threshold, the gate passes sampleIn through and returns it, and sets
    gateActive to false. If the signal is below the threshold for silenceThresholdLength, the gate returns a 0.0f value and
    sets gateActive to True
    */
    float gate(float sampleIn)
    {
        float sampleOut;
        
        if (currentLevel > thresholdLevel)
        {
            gateActive = false;
            sampleOut = sampleIn;
        }
        else
        {
            if (silenceCounter < silenceThresholdLength && gateActive == false)
            {
                gateActive = false;
                silenceCounter++;
                sampleOut = sampleIn;
            }
            else
            {
                gateActive = true;
                silenceCounter = 0;
                sampleOut = 0.0f;
            }
        }

        return sampleOut;
    }
    
    // Member Variables
    int silenceCounter = 0;
    int silenceThresholdLength = 128;
    
    float thresholdLevel;
    float currentLevel;
    
    bool gateActive = true;
    
};
