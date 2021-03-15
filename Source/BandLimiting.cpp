/*
  ==============================================================================

    BandLimiting.cpp
    Created: 15 Mar 2021 10:53:11pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "BandLimiting.h"


BandLimiter::BandLimiter() : hpfCutoff(15.0f), lpfCutoff(150.0f), sampleRate(44100.0f)
{}

BandLimiter::~BandLimiter()
{}

/// Sets sampleRate
void BandLimiter::setSampleRate(float SR)
{
    sampleRate = SR;
}


float BandLimiter::process(float sampleIn)
{
    return processLPF( processHPF( sampleIn ) );
}

/**
Four stage cascading high pass filter to filter out extremely low frequencies and unwanted subharmonics
*/
float BandLimiter::processHPF(float sampleIn)
{
    hpStage1.setCoefficients ( IIRCoefficients::makeHighPass ( sampleRate, hpfCutoff ) );
    hpStage2.setCoefficients ( IIRCoefficients::makeHighPass ( sampleRate, hpfCutoff ) );
    hpStage3.setCoefficients ( IIRCoefficients::makeHighPass ( sampleRate, hpfCutoff ) );
    hpStage4.setCoefficients ( IIRCoefficients::makeHighPass ( sampleRate, hpfCutoff ) );
    
    float stage1 = hpStage1.processSingleSampleRaw ( sampleIn );
    float stage2 = hpStage2.processSingleSampleRaw ( stage1   );
    float stage3 = hpStage3.processSingleSampleRaw ( stage2   );
    float stage4 = hpStage4.processSingleSampleRaw ( stage3   );
    
    return stage4;
}


/**
One pole lowpass filter to gently roll off higher harmonics to ensure focus to fundamental frequencies.
*/
float BandLimiter::processLPF(float sampleIn)
{
    lpOnePole.setCoefficients( IIRCoefficients::makeLowPass( sampleRate, lpfCutoff ) );
    
    return lpOnePole.processSingleSampleRaw(sampleIn);
}
