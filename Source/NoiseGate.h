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
        
        writeToBuffer(sampleIn);
        
        for (int i=0; i<gateBufferSize; i++)
        {
            amplitudeValues += abs(gateBuffer[i]);
        }
        
        //std::cout << "ampVal " << amplitudeValues << "\n";
        
        averageAmplitude = amplitudeValues / (float)gateBufferSize;
        //std::cout  << "avgAmp " << averageAmplitude << "\n";
        
        if (averageAmplitude > threshold)
        {
            return sampleIn;
        }
        else
            return 0.0f;
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
    float threshold;
};
