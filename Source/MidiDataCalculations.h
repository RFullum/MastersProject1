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
     Takes in current level as argument. Clips current level from 0.0 to 1.0. Maps to MIDI values 0-127 and
     returns Midi value as int
     */
    int getVelocity(float levelIn)
    {
        float level = std::max(0.0f, std::min(levelIn, 1.0f));  // clamps from 0.0 to 1.0
        
        return (int)jmap(level, 0.0f, 1.0f, 0.0f, 127.0f);
    }
private:

    // Member Variables
    int currentNote;
    int previousNote;
    
};
