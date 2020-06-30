/*
  ==============================================================================

    MidiDataCalculations.h
    Created: 29 Jun 2020 6:00:40pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once


class MidiDataCalculations
{
public:
    /**
     Takes in current level as argument. Clips current level from 0.0 to 1.0. Maps to MIDI values (int)0-127
     */
    void setVelocity(float levelIn)
    {
        float level = std::max(0.0f, std::min(levelIn, 1.0f));  // clamps from 0.0 to 1.0
        
        velocity = jmap(level, 0.0f, 1.0f, 0.0f, 127.0f);
    }
    
    /// Returns velocity as a float from 0.0 to 127.0
    float getVelocity()
    {
        return velocity;
    }
    
    bool setNoteTrigger(int noteNumber)
    {
        currentNote = noteNumber;
        
        if (currentNote == previousNote)
        {
            newNote = false;
        }
        else
        {
            newNote = true;
        }
        
        return newNote;
    }
    
private:

    // Member Variables
    
    // Note On/Off variables
    bool newNote = false;
    int currentNote;
    int previousNote = 0;
    
    // velocity variables
    float velocity;
    
};
