/*
  ==============================================================================

    ZeroCrossingCounter.cpp
    Created: 15 Mar 2021 11:38:10pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "ZeroCrossingCounter.h"


ZeroXing::ZeroXing() : crossingBufferSize(1024), writeHeadPos(0),
                       crossingCount(0), cycleLengthsSize(5),
                       cycleLengthsCount(0), firstCrossing(0),
                       secondCrossing(0), sampleRate(44100.0f),
                       frequencyFloor(20.0f)
{}

ZeroXing::~ZeroXing()
{
    delete[] crossingBuffer;
}

/**
Takes sampleRate as argument. Creates a buffer based on lowest frequency to be detected and sampleRate
Initializes buffer values to 0.0f
*/
void ZeroXing::setBuffer(float SR)
{
    sampleRate = SR;
    
    float minSamples   = frequencyFloorLength();
    crossingBufferSize = (int)setBufferSize(minSamples);
    crossingBuffer     = new float[crossingBufferSize];
    
    for (int i=0; i<crossingBufferSize; i++)
    {
        crossingBuffer[i] = 0.0f;
    }
}

/**
Takes argument of current sample in from WaveClipper. returns the average wavelength being played
*/
float ZeroXing::process(float sampleIn)
{
    writeToBuffer(sampleIn);
    
    return averageCycleLength();
}

/**
Determines minimum number of samples needed for buffer size based on sample rate and
frequency floor. Buffer must be large enough to accomodate one full cycle plus another half cycle.
*/
float ZeroXing::frequencyFloorLength()
{
    float cycleLength = sampleRate / frequencyFloor;
    
    return cycleLength + ( cycleLength * 0.5f );
}

/**
Sets buffer size to be least great power of 2 that is greater than the minimum length for the buffer in samples
*/
float ZeroXing::setBufferSize(float minLength)
{
    int power = 1;
    
    while ( pow(2.0, power) < minLength)
    {
        power++;
    }
    
    return pow(2.0, power);
}

/**
Writes samples to buffer from writeHeadPos 0. Two zero crossings is half a cycle. When crossingCount
reaches 2, it finds the length of the cycle by subtracting the first crossing position from the second crossing
position and multiplying by 2. Then it stores that cycle length into the pointer of cycle lengths. Then resets writeHeadPos and
crossingCount to 0.
*/
void ZeroXing::writeToBuffer(float sampleIn)
{
    float currentSample;
    float previousSample;
    
    int previousSamplePos = writeHeadPos - 1;
    
    while (previousSamplePos < 0)
        previousSamplePos += crossingBufferSize;
    
    crossingBuffer[writeHeadPos] = sampleIn;
    
    if (writeHeadPos > 0)
    {
        currentSample  = crossingBuffer[writeHeadPos];
        previousSample = crossingBuffer[previousSamplePos];
        
        if (currentSample != previousSample)
        {
            crossingCount++;
            if (crossingCount == 1)
                firstCrossing = writeHeadPos;
            else if (crossingCount == 2)
                secondCrossing = writeHeadPos;
        }
    }
    
    if (crossingCount < 2)
    {
        writeHeadPos++;
        writeHeadPos %= crossingBufferSize;
    }
    else
    {
        cycleLengths[cycleLengthsCount] = ( secondCrossing - firstCrossing ) * 2.0f;
        
        cycleLengthsCount++;
        cycleLengthsCount %= cycleLengthsSize;
        
        writeHeadPos  = 0;
        crossingCount = 0;
    }
}

/**
Finds and returns the average cycle length of cycle lengths stored in cycleLengths
*/
float ZeroXing::averageCycleLength()
{
    float sumCycleLength = 0.0f;
    
    for (int i=0; i<cycleLengthsSize; i++)
    {
        sumCycleLength += cycleLengths[i];
    }
    
    return sumCycleLength / (float)cycleLengthsSize;
}


