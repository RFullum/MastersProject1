/*
  ==============================================================================

    ZeroCrossingCounter.h
    Created: 16 Jun 2020 3:41:22pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

class ZeroXing
{
public:
    /**
     Constructor - Takes in size of buffer. Creates buffer and sets buffer to all 0.0f
     */
    ZeroXing()
    {
    
    }
    
    /// Destructor
    ~ZeroXing()
    {
        delete[] crossingBuffer;
    }
    
    void setBuffer(int bufferSize)
    {
        crossingBufferSize = bufferSize;
        crossingBuffer = new float[crossingBufferSize];
        
        for (int i=0; i<crossingBufferSize; i++)
        {
            crossingBuffer[i] = 0.0f;
        }
    }
    
    float process(float sampleIn)
    {
        writeToBuffer(sampleIn);
        return countZeroXings();
    }
    
private:
    /// Writes incomming samples to buffer, wrapped to buffer size
    void writeToBuffer(float sampleIn)
    {
        crossingBuffer[writeHeadPos] = sampleIn;
        writeHeadPos++;
        writeHeadPos %= crossingBufferSize;
    }
    
    float countZeroXings()
    {
        int crossingCount = 0;
        float currentSample;
        float previousSample;
        
        for (int i=0; i<crossingBufferSize; i++)
        {
            int previousSampleIndex = i - 1;
            
            while (previousSampleIndex < 0)
                previousSampleIndex += crossingBufferSize;
            
            currentSample = crossingBuffer[i];
            previousSample = crossingBuffer[previousSampleIndex];
            
            if (currentSample != previousSample)
            crossingCount++;
        }
        
        return crossingCount;
    }
    
    
    // Member Variables
    int crossingBufferSize;
    float* crossingBuffer;
    
    int writeHeadPos = 0;
};
