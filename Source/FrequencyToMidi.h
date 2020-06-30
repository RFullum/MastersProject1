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
    int getMidiFromFreq(float freq)
    {
        frequency = freq;
        convertFreqToMidi();
        
        return midiNoteNumber;
    }
private:
    void convertFreqToMidi()
    {
        float conversionNum = log( frequency / 440.0f ) / log( 2 ) * 12 + 69;
        midiNoteNumber = roundToInt(conversionNum);
        //std::cout << "numFloat " << conversionNum << " num " << midiNoteNumber << "\n";
    }
    int midiNoteNumber;
    float frequency;
};
