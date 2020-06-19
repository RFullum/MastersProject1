/*
  ==============================================================================

    WaveClipper.h
    Created: 1 Jun 2020 3:32:09pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

class WaveClipper
{
public:
    /** INEFFICIENT: Use hardClip method
     Multiplies incoming signal by clipAmount and hard clips between -1.0f and 1.0f to create square wave
    */
    float clipValue(float inputSample)
    {
        float multSampleVal = multSample(inputSample);
        
        return clipSample(multSampleVal);
    }
    
    /**
     More efficient clipper: If the incoming value is zero or greater, output 1.0f
     If the invoming value is less than zero, output -1.0f
     */
    float hardClip(float inputSample)
    {
        float outVal;
        
        if (inputSample >= 0.0f)
        {
            outVal = 1.0f;
        }
        else 
        {
            outVal = -1.0f;
        }

        
        return outVal;
    }
    
private:
    /// (DEPRICATED) )Returns inputSample * clipAmount
    float multSample(float inputSample)
    {
        return inputSample * clipAmount;
    }
    
    /// (DEPRICATED) )Hard clips amplified sample values between -1.0f and 1.0f
    float clipSample(float ampedSample)
    {
        float outSample;
        
        if (ampedSample > 1.0f)
        {
            outSample = 1.0f;
        }
        else if (ampedSample < -1.0f)
        {
            outSample = -1.0f;
        }
        else
        {
            outSample = ampedSample;
        }
        
        return outSample;
    }
    
    // Member Variables
    float clipAmount = 1000.0f; // NO LONGER NEEDED
};
