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
    WaveClipper();
    ~WaveClipper();
    
    /**
     Takes input sample. If the incoming value is zero or greater, returns 1.0f
     If the invoming value is less than zero, returns -1.0f
     */
    float clipSignal(float inputSample);
    
    
private:
    /**
    Takes input sample. If the incoming value is zero or greater, returns 1.0f
    If the invoming value is less than zero, returns -1.0f
    */
    float valueClipper(float inVal);
};
