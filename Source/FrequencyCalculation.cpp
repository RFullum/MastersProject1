/*
  ==============================================================================

    FrequencyCalculation.cpp
    Created: 15 Mar 2021 11:02:46pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "FrequencyCalculation.h"



FrequencyCalculation::FrequencyCalculation() : sampleRate(44100.0f)
{}

FrequencyCalculation::~FrequencyCalculation()
{}

/// Sets sampleRate
void FrequencyCalculation::setSampleRate(float SR)
{
    sampleRate = SR;
}

/// Takes the cycleLength in and returns the current frequency
float FrequencyCalculation::freqCalc(float cycleLength)
{
    return sampleRate / cycleLength;
}
