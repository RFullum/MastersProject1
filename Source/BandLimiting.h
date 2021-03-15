/*
  ==============================================================================

    BandLimiting.h
    Created: 16 Jun 2020 3:13:04pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class BandLimiter
{
public:
    BandLimiter();
    ~BandLimiter();
    
    
    /// Sets sampleRate
    void setSampleRate(float SR);
    
    /// takes sample in and cleans it through HPF and then LPF
    float process(float sampleIn);

private:
    /**
     Four stage cascading high pass filter to filter out extremely low frequencies and unwanted subharmonics
     */
    float processHPF(float sampleIn);
    
    /**
     One pole lowpass filter to gently roll off higher harmonics to ensure focus to fundamental frequencies.
     */
    float processLPF(float sampleIn);
    
    
    // Member Variables
    IIRFilter hpStage1;
    IIRFilter hpStage2;
    IIRFilter hpStage3;
    IIRFilter hpStage4;
    IIRFilter lpOnePole;
    
    float hpfCutoff;
    float lpfCutoff;
    
    float sampleRate;
};





