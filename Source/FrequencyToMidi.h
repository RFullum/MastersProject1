/*
  ==============================================================================

    FrequencyToMidi.h
    Created: 29 Jun 2020 3:18:49pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FrequencyToMidi
{
public:
    FrequencyToMidi();
    ~FrequencyToMidi();
    
    /**
     Takes (float) frequency as an argument and returns the Midi Note Number as an int
     */
    int getMidiFromFreq(float freq);
    
private:
    /**
     Formula to convert frequency to midi.
     */
    void convertFreqToMidi();
    
    
    // Member Variables
    int midiNoteNumber;
    float frequency;
};
