/*
  ==============================================================================

    TransientTracker.h
    Created: 17 Jun 2020 4:41:05pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

class TransientTracker
{
public:
    /// Constructor, initializes all values in levelBuffer to 0.0f
    TransientTracker()
    {
        for (int i=0; i<levelBufferSize; i++)
            levelBuffer[i] = 0.0f;
    }
    
    ~TransientTracker()
    {
        delete[] levelBuffer;
    }
    
    /**
     Takes in current sample as argument and returns bool reporting if it detects a transient or not
     */
    bool transientDetect(float sampleIn)
    {
        bool isTransient = false;
        
        float fastLevel = getCurrentLevel(sampleIn);
        float slowLevel = slowEnvelope(fastLevel);
        float attackRatio = envelopeDifference(fastLevel, slowLevel);
        
        if (attackRatio > attackDifferenceThreshold)
        {
            isTransient = true;
        }
        
        return isTransient;
    }

    
private:
    /**
     Takes current sample in, writes its absolute value to a buffer, and returns the level averaged across buffer
     */
    float getCurrentLevel(float sampleIn)
    {
        writeToBuffer(sampleIn);
        
        return averageBufferValue();
    }
    
    /// Writes absolute value of input sample to buffer, wrapped to buffer size
    void writeToBuffer(float sampleIn)
    {
        levelBuffer[writeHeadPos] = std::abs(sampleIn);
        writeHeadPos++;
        writeHeadPos %= levelBufferSize;
    }
    
    /// Returns the averave value of samples in buffer
    float averageBufferValue()
    {
        float samplesSum = 0.0f;
        
        for (int i=0; i<levelBufferSize; i++)
        {
            samplesSum += levelBuffer[i];
        }
        
        return samplesSum / (float)levelBufferSize;
    }
    
    /**
     Takes in the currentLevel and tracks the envelope. When the level increases, it's followed by a factor
     less than 1.0. When the level decreases it's followed directly. This creates a slower attack.
     */
    float slowEnvelope(float currentLevel)
    {
        if (currentLevel > previousLevel)
        {
            previousLevel += (currentLevel - previousLevel) * attackFactor;
        }
        else
        {
            previousLevel = currentLevel;
        }
        
        return previousLevel;
    }
    
    /**
     Finds the difference between the current level slowEnvelope level. Arguments: fastEnv is the currentLevel value.
     slowEnv is the level of the slowEnvelope method.
     */
    float envelopeDifference(float fastEnv, float slowEnv)
    {
        return fastEnv - slowEnv;
    }
    
    
    
    //
    // Member Variables
    //
    
    // Level Buffer Variables
    int levelBufferSize = 1024;
    float* levelBuffer = new float[levelBufferSize];
    int writeHeadPos = 0;
    
    // slowEnvelope variables
    float previousLevel = 0.0f;
    float attackFactor = 0.5f;
    
    // transientDetect variables
    float attackDifferenceThreshold = 0.5f;
};


