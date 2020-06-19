/*
  ==============================================================================

    FrequencyCalculation.h
    Created: 16 Jun 2020 6:04:07pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once


class FrequencyCalculation
{
public:
    /// Sets sampleRate
    void setSampleRate(float SR)
    {
        sampleRate = SR;
    }
    
    float freqCalc(float zeroXings)
    {
        return ( zeroXings * (sampleRate / bufferSize) * 0.5f );
    }
private:
    float sampleRate;
    float bufferSize = 1024;
};
