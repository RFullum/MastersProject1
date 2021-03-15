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
    FrequencyCalculation();
    ~FrequencyCalculation();
    
    
    /// Sets sampleRate
    void setSampleRate(float SR);
    
    /// Takes the cycleLength in and returns the current frequency
    float freqCalc(float cycleLength);
    
    
private:
    float sampleRate;
};
