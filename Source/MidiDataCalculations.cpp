/*
  ==============================================================================

    MidiDataCalculations.cpp
    Created: 15 Mar 2021 11:09:49pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "MidiDataCalculations.h"


MidiDataCalculations::MidiDataCalculations() : newNote(false), currentNote(0), previousNote(0), velocity(0.0f)
{}

MidiDataCalculations::~MidiDataCalculations()
{}

/**
Takes in current level as argument. Clips current level from 0.0 to 1.0. Maps to MIDI values (int)0-127
*/
void MidiDataCalculations::setVelocity(float levelIn)
{
    velocity = std::max(0.0f, std::min(levelIn, 1.0f));  // clamps from 0.0 to 1.0
}

/// Returns velocity as a float from 0.0 to 127.0
float MidiDataCalculations::getVelocity()
{
    return velocity;
}

/// Determins if a new note should be triggered
bool MidiDataCalculations::setNoteTrigger(int noteNumber)
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
    
    previousNote = currentNote;

    return newNote;
}

/// Returns the note number of the previously played Midi note
int MidiDataCalculations::getPreviousNoteNumber()
{
    return previousNote;
}

