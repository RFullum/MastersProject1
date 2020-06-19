/*
  ==============================================================================

    TransientTracker.h
    Created: 17 Jun 2020 4:41:05pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

class CurrentLevel
{
public:
    /// Constructor, initializes all values in levelBuffer to 0.0f
    CurrentLevel()
    {
        for (int i=0; i<levelBufferSize; i++)
            levelBuffer[i] = 0.0f;
    }
    
    float getCurrentLevel(float sampleIn)
    {
        
        return 0.0f;
    }

    
private:
    int levelBufferSize = 1024;
    float* levelBuffer = new float[levelBufferSize];
    
    int writeHeadPos = 0;
    
};
