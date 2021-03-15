/*
  ==============================================================================

    ZeroCrossingCounter.h
    Created: 16 Jun 2020 3:41:22pm
    Author:  Robert Fullum
 
    This class writes incoming values to a buffer and counts zero crossings.
    It determines the wavelength of the incoming waves by comparing writehead
    positions of the first and third zero crossing. These wavelengths are stored
    to a wrapped pointer array and averaged, replacing the oldest with the newest
    wavelength. 

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ZeroXing
{
public:
    ZeroXing();
    
    /// Destructor
    ~ZeroXing();
    
    /**
     Takes sampleRate as argument. Creates a buffer based on lowest frequency to be detected and sampleRate
     Initializes buffer values to 0.0f
     */
    void setBuffer(float SR);
    
    
    /**
     Takes argument of current sample in from WaveClipper. returns the average wavelength being played
     */
    float process(float sampleIn);
    
    
private:
    /**
     Determines minimum number of samples needed for buffer size based on sample rate and
     frequency floor. Buffer must be large enough to accomodate one full cycle plus another half cycle.
     */
    float frequencyFloorLength();
    
    
    /**
     Sets buffer size to be least great power of 2 that is greater than the minimum length for the buffer in samples
     */
    float setBufferSize(float minLength);
    
    /**
     Writes samples to buffer from writeHeadPos 0. Two zero crossings is half a cycle. When crossingCount
     reaches 2, it finds the length of the cycle by subtracting the first crossing position from the second crossing
     position and multiplying by 2. Then it stores that cycle length into the pointer of cycle lengths. Then resets writeHeadPos and
     crossingCount to 0.
     */
    void writeToBuffer(float sampleIn);
    
    
    /**
     Finds and returns the average cycle length of cycle lengths stored in cycleLengths
     */
    float averageCycleLength();
    
    // Member Variables
    int crossingBufferSize;
    float* crossingBuffer;
    
    int writeHeadPos;
    int crossingCount;
    
    int cycleLengthsSize;
    int cycleLengthsCount;
    float* cycleLengths = new float[cycleLengthsSize];
    
    int firstCrossing;
    int secondCrossing;
    
    float sampleRate;
    float frequencyFloor;
};
