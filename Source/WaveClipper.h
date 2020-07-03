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
    
    /**
     Takes input sample. If the incoming value is zero or greater, returns 1.0f
     If the invoming value is less than zero, returns -1.0f
     */
    float clipSignal(float inputSample)
    {
        return valueClipper(inputSample);
    }
    
private:
    float valueClipper(float inVal)
    {
        float outVal;
        
        if (inVal >= 0.0f)
        {
            outVal = 1.0f;
        }
        else
        {
            outVal = -1.0f;
        }

        
        return outVal;
    }
};
