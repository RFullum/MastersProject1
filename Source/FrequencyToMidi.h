/*
  ==============================================================================

    FrequencyToMidi.h
    Created: 29 Jun 2020 3:18:49pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

class FrequencyToMidi
{
public:
    /**
     Takes (float) frequency as an argument and returns the Midi Note Number as an int
     */
    int getMidiFromFreq(float freq)
    {
        frequency = freq;
        convertFreqToMidi();
        
        return midiNoteNumber;
    }
private:
    /**
     Formula to convert frequency to midi.
     */
    void convertFreqToMidi()
    {
        float conversionNum = log( frequency / 440.0f ) / log( 2 ) * 12 + 69;
        midiNoteNumber = roundToInt(conversionNum);
    }
    
    // Member Variables
    int midiNoteNumber;
    float frequency;
};
