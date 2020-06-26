/*
  ==============================================================================

    NoiseGate.h
    Created: 16 Jun 2020 10:47:20am
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once


class NoiseGate
{
public:
    /**
     Constructor: initializes gateBuffer values to 0.0f
     */
    NoiseGate()
    {
        for (int i=0; i<gateBufferSize; i++)
        {
            gateBuffer[i] = 0.0f;
        }
    }
    
    ~NoiseGate()
    {
        delete[] gateBuffer;
    }
    
    /// sets gate threshold 0.0f - 1.0f;
    void setThreshold(float thresh)
    {
        threshold = thresh;
    }
    
    /**
     Takes sampleIn, writes to buffer, takes the average of values in buffer and compares to the threshold.
     Outputs sampleIn if buffer averages above threshold, otherwise outputs 0.0f
     */
    float processGate(float sampleIn)
    {
        float amplitudeValues = 0.0f;
        float averageAmplitude;
        float sampleOut = 0.0f;
        
        writeToBuffer(sampleIn);
        
        for (int i=0; i<gateBufferSize; i++)
        {
            amplitudeValues += abs(gateBuffer[i]);
        }
        
        averageAmplitude = amplitudeValues / (float)gateBufferSize;
        
        if (averageAmplitude > threshold)
        {
            sampleOut = sampleIn;
        }
        else if (silenceCounter < silenceThreshold)
        {
            silenceCounter++;
            sampleOut = sampleIn;
        }
        else
        {
            silenceCounter = 0;
            sampleOut = 0.0f;
        }
        
        return sampleOut;
    }
    
private:
    /// writes to next sample in gateBuffer, wrapped to gateBufferSize
    void writeToBuffer(float sampleIn)
    {
        gateBuffer[writeHeadPos] = sampleIn;
        writeHeadPos++;
        writeHeadPos %= gateBufferSize;
    }
    
    // Member Variables
    int gateBufferSize = 1024;
    
    float* gateBuffer = new float[gateBufferSize];
    
    int writeHeadPos = 0;
    int silenceCounter = 0;
    int silenceThreshold = 1024;
    float threshold;
};
