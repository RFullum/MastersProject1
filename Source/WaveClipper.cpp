/*
  ==============================================================================

    WaveClipper.cpp
    Created: 15 Mar 2021 11:35:41pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "WaveClipper.h"

WaveClipper::WaveClipper()
{}

WaveClipper::~WaveClipper()
{}

/**
Takes input sample. If the incoming value is zero or greater, returns 1.0f
If the invoming value is less than zero, returns -1.0f
*/
float WaveClipper::clipSignal(float inputSample)
{
    return valueClipper(inputSample);
}

/**
Takes input sample. If the incoming value is zero or greater, returns 1.0f
If the invoming value is less than zero, returns -1.0f
*/
float WaveClipper::valueClipper(float inVal)
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
