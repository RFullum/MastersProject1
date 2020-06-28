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
    
    void setBuffer(float SR)
    {
        sampleRate = SR;
        
        float minSamples = frequencyFloorLength();
        crossingBufferSize = (int)setBufferSize(minSamples);
        crossingBuffer = new float[crossingBufferSize];
        std::cout << "\n\nSR " << sampleRate << "\nbufSiz " << crossingBufferSize << "\n\n";
        
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
    // STILL NOT ACCURATE BELOW C-ish ~65Hz
    //
    //
    /**
     Determines minimum number of samples needed for buffer size based on sample rate and
     frequency floor. Buffer must be large enough to accomodate one full cycle plus another half cycle.
     */
    float frequencyFloorLength()
    {
        float cycleLength = sampleRate / frequencyFloor;
        
        return cycleLength + ( cycleLength * 0.5f );
    }
    
    /**
     Sets buffer size to be least great power of 2 that is greater than the minimum length for the buffer in samples
     */
    float setBufferSize(float minLength)
    {
        int power = 1;
        
        while ( pow(2.0, power) < minLength)
        {
            power++;
        }
        
        return pow(2.0, power);
    }

    
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
                else if (crossingCount == 2)
                    secondCrossing = writeHeadPos;
            }
        }
        //std::cout << "first " << firstCrossing << " third " << thirdCrossing << "\n";
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
    
    int cycleLengthsSize = 5;
    int cycleLengthsCount = 0;
    float* cycleLengths = new float[cycleLengthsSize];
    
    int firstCrossing = 0;
    int secondCrossing = 0;
    
    float sampleRate;
    float frequencyFloor = 20.0f;
};
