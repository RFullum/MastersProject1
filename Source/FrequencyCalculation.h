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
    
    /// Set bufferSize to frequencyBufferSize, same as used in ZeroXingCounter or you'll have problems
    void setBufferSize(int bufSize)
    {
        bufferSize = bufSize;
    }
    
    float freqCalc(float zeroXings)
    {
        return ( zeroXings * (sampleRate / (float)bufferSize) * 0.5f );
    }
private:
    float sampleRate;
    int bufferSize;
};
