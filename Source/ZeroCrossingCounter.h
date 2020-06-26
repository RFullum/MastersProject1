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
     Takes argument of current sample in from WaveClipper. Writes to buffer,
     and returns number of zero crossings in said buffer.
     */
    float process(float sampleIn)
    {
        writeToBuffer(sampleIn);
        return countZeroXings();
    }
    
    float processAlt(float sampleIn)
    {
        writeToBufferAlt(sampleIn);
        return averageCycleLength();
    }
    
private:
    /// Writes incomming samples to buffer, wrapped to buffer size
    void writeToBuffer(float sampleIn)
    {
        crossingBuffer[writeHeadPos] = sampleIn;
        writeHeadPos++;
        writeHeadPos %= crossingBufferSize;
    }
    
    /**
     Writes samples to buffer from writeHeadPos 0. One full cycle is three zero crossings. When crossingCount
     reaches 3, it finds the length of the cycle by subtracting the first crossing position from the third crossing
     position. Then it stores that cycle length into the pointer of cycle lengths. Then resets writeHeadPos and
     crossingCount to 0.
     */
    void writeToBufferAlt(float sampleIn)
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
    
    /**
     */
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
    int crossingCount = 0;
    int cycleLengthsSize = 10;
    int cycleLengthsCount = 0;
    float* cycleLengths = new float[cycleLengthsSize];
    
    int firstCrossing = 0;
    int thirdCrossing = 0;
    
};
