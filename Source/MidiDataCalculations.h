/*
  ==============================================================================

    MidiDataCalculations.h
    Created: 29 Jun 2020 6:00:40pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MidiDataCalculations
{
public:
    MidiDataCalculations();
    ~MidiDataCalculations();
    
    /**
     Takes in current level as argument. Clips current level from 0.0 to 1.0. Maps to MIDI values (int)0-127
     */
    void setVelocity(float levelIn);
    
    
    /// Returns velocity as a float from 0.0 to 127.0
    float getVelocity();
    
    
    /// Determins if a new note should be triggered
    bool setNoteTrigger(int noteNumber);
    
    /// Returns the note number of the previously played Midi note
    int getPreviousNoteNumber();
    
private:
    // Member Variables
    
    // Note On/Off variables
    bool newNote;
    int currentNote;
    int previousNote;
    
    // velocity variables
    float velocity;
    
};
