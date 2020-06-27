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
    
    /// Takes the cycleLength in and returns the current frequency
    float freqCalc(float cycleLength)
    {
        return sampleRate / cycleLength;
    }
    
private:
    float sampleRate;
};
