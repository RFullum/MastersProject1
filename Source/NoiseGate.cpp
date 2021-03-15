/*
  ==============================================================================

    NoiseGate.cpp
    Created: 15 Mar 2021 11:14:52pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "NoiseGate.h"


NoiseGate::NoiseGate() : silenceCounter(0), silenceThresholdLength(1024),
                         thresholdLevel(0.0f), currentLevel(0.0f),
                         gateActive(true)
{}

NoiseGate::~NoiseGate()
{}

/// sets gate threshold 0.0f - 1.0f;
void NoiseGate::setThreshold(float thresh)
{
    thresholdLevel = thresh;
}

/**
Recieves buffer.getRMSLevel( ) from process block and sets it to currentLevel.
*/
void NoiseGate::levelIn(float level)
{
    currentLevel = level;
}

/**
Takes sample in. If signal is above the threshold, the gate passes sampleIn through and returns it, and sets
gateActive to false. If the signal is below the threshold for silenceThresholdLength, the gate returns a 0.0f value and
sets gateActive to True
*/
float NoiseGate::processGate(float sampleIn)
{
    return gate(sampleIn);
}

/**
Returns state of gate as bool: True = Gate is active and no audio is output. False = Gate is off and audio
is thruput.
*/
bool NoiseGate::currentGateState()
{
    return gateActive;
}


/**
Takes sample in. If signal is above the threshold, the gate passes sampleIn through and returns it, and sets
gateActive to false. If the signal is below the threshold for silenceThresholdLength, the gate returns a 0.0f value and
sets gateActive to True
*/
float NoiseGate::gate(float sampleIn)
{
    float sampleOut;
    
    if (currentLevel > thresholdLevel)
    {
        gateActive = false;
        sampleOut  = sampleIn;
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
            gateActive     = true;
            silenceCounter = 0;
            sampleOut      = 0.0f;
        }
    }

    return sampleOut;
}
