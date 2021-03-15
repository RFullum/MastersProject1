/*
  ==============================================================================

    FrequencyToMidi.cpp
    Created: 15 Mar 2021 11:05:16pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "FrequencyToMidi.h"


FrequencyToMidi::FrequencyToMidi() : midiNoteNumber(0), frequency(0.0f)
{}

FrequencyToMidi::~FrequencyToMidi()
{}

/**
Takes (float) frequency as an argument and returns the Midi Note Number as an int
*/
int FrequencyToMidi::getMidiFromFreq(float freq)
{
    frequency = freq;
    convertFreqToMidi();
    
    return midiNoteNumber;
}

/**
Formula to convert frequency to midi.
*/
void FrequencyToMidi::convertFreqToMidi()
{
    float conversionNum = log( frequency / 440.0f ) / log( 2 ) * 12 + 69;
    midiNoteNumber      = roundToInt( conversionNum );
}
