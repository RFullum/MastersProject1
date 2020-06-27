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

class ZeroXing
{
public:
    /**
     Constructor
     */
    ZeroXing()
    {
    
    }
    
    /// Destructor
    ~ZeroXing()
    {
        delete[] crossingBuffer;
    }
    
    //
    // CHANGE THE WAY BUFFER SIZE IS SET UP PER YOUR NOTES
    //
    
    /// Sets crossingBufferSize and creates crossingBuffer pointer of said size, initializing values to 0.0f
    void setBuffer(int bufferSize)
    {
        crossingBufferSize = bufferSize;
        crossingBuffer = new float[crossingBufferSize];
        
        for (int i=0; i<crossingBufferSize; i++)
        {
            crossingBuffer[i] = 0.0f;
        }
    }
    
    /**
     Takes argument of current sample in from WaveClipper. returns the average wavelength being played
     */
    float process(float sampleIn)
    {
        writeToBuffer(sampleIn);
        return averageCycleLength();
    }
    
private:

    
//
//
// CONSIDER WRITING 0.0F TO REMAINING BUFFER INDEXES WHEN 3 ZERO CROSSINGS DETECTED
//
//
    
    /**
     Writes samples to buffer from writeHeadPos 0. One full cycle is three zero crossings. When crossingCount
     reaches 3, it finds the length of the cycle by subtracting the first crossing position from the third crossing
     position. Then it stores that cycle length into the pointer of cycle lengths. Then resets writeHeadPos and
     crossingCount to 0.
     */
    void writeToBuffer(float sampleIn)
    {
        float currentSample;
        float previousSample;
        
        int previousSamplePos = writeHeadPos - 1;
        
        while (previousSamplePos < 0)
            previousSamplePos += crossingBufferSize;
        
        crossingBuffer[writeHeadPos] = sampleIn;
        
        if (writeHeadPos > 0)
        {
            currentSample = crossingBuffer[writeHeadPos];
            previousSample = crossingBuffer[previousSamplePos];
            
            if (currentSample != previousSample)
            {
                crossingCount++;
                if (crossingCount == 1)
                    firstCrossing = writeHeadPos;
                else if (crossingCount == 3)
                    thirdCrossing = writeHeadPos;
            }
        }
        //std::cout << "first " << firstCrossing << " third " << thirdCrossing << "\n";
        if (crossingCount < 3)
        {
            writeHeadPos++;
            writeHeadPos %= crossingBufferSize;
        }
        else
        {
            cycleLengths[cycleLengthsCount] = thirdCrossing - firstCrossing;
            
            cycleLengthsCount++;
            cycleLengthsCount %= cycleLengthsSize;
            
            writeHeadPos = 0;
            crossingCount = 0;
        }
        
        //std::cout << "wHP " << writeHeadPos << "\n";
    }
    
    /**
     Finds and returns the average cycle length of cycle lengths stored in cycleLengths
     */
    float averageCycleLength()
    {
        float sumCycleLength = 0.0f;
        
        for (int i=0; i<cycleLengthsSize; i++)
        {
            //std::cout << "length " << i << " " << cycleLengths[i] << "\n";
            sumCycleLength += cycleLengths[i];
        }
        
        return sumCycleLength / (float)cycleLengthsSize;
    }
    
    // Member Variables
    int crossingBufferSize;
    float* crossingBuffer;
    
    int writeHeadPos = 0;
    int crossingCount = 0;
    int cycleLengthsSize = 10;
    int cycleLengthsCount = 0;
    float* cycleLengths = new float[cycleLengthsSize];
    
    int firstCrossing = 0;
    int thirdCrossing = 0;
    
};
