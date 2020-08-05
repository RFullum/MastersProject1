/*
  ==============================================================================

    BandLimiting.h
    Created: 16 Jun 2020 3:13:04pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once


class BandLimiter
{
public:
    /// Sets sampleRate
    void setSampleRate(float SR)
    {
        sampleRate = SR;
    }
    
    /// takes sample in and cleans it through HPF and then LPF
    float process(float sampleIn)
    {
        return processLPF(processHPF(sampleIn));
    }

private:
    /**
     Four stage cascading high pass filter to filter out extremely low frequencies and unwanted subharmonics
     */
    float processHPF(float sampleIn)
    {
        hpStage1.setCoefficients( IIRCoefficients::makeHighPass(sampleRate, hpfCutoff) );
        hpStage2.setCoefficients( IIRCoefficients::makeHighPass(sampleRate, hpfCutoff) );
        hpStage3.setCoefficients( IIRCoefficients::makeHighPass(sampleRate, hpfCutoff) );
        hpStage4.setCoefficients( IIRCoefficients::makeHighPass(sampleRate, hpfCutoff) );
        
        float stage1 = hpStage1.processSingleSampleRaw(sampleIn);
        float stage2 = hpStage2.processSingleSampleRaw(stage1);
        float stage3 = hpStage3.processSingleSampleRaw(stage2);
        float stage4 = hpStage4.processSingleSampleRaw(stage3);
        
        return stage4;
    }
    
    /**
     One pole lowpass filter to gently roll off higher harmonics to ensure focus to fundamental frequencies.
     */
    float processLPF(float sampleIn)
    {
        lpOnePole.setCoefficients( IIRCoefficients::makeLowPass(sampleRate, lpfCutoff) );
        
        return lpOnePole.processSingleSampleRaw(sampleIn);
    }
    
    // Member Variables
    IIRFilter hpStage1;
    IIRFilter hpStage2;
    IIRFilter hpStage3;
    IIRFilter hpStage4;
    IIRFilter lpOnePole;
    
    float hpfCutoff = 15.0f;
    float lpfCutoff = 150.0f;
    
    float sampleRate;
};





