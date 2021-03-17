/*
  ==============================================================================

    TitleHeader.cpp
    Created: 4 Feb 2021 11:47:30am
    Author:  Robert Fullum

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TitleHeader.h"

//==============================================================================
TitleHeader::TitleHeader() : backgroundColor ( Colour( (uint8)125, (uint8)125,  (uint8)125 ) ),
                             textColor       ( Colour( (uint8)235, (uint8)52,   (uint8)222)  )
{
}

TitleHeader::~TitleHeader()
{
}

void TitleHeader::paint (juce::Graphics& g)
{
    g.fillAll   ( backgroundColor );
    g.setColour ( textColor );
    
    g.setFont   ( Font("technoid", 60.0f, 0) );
    g.drawText  ( "FULLUMMUSIC", fullumMusicArea.reduced( 6, 0 ), Justification::right );
    
    g.setFont   ( Font("technoid", 30.0f, 0) );
    g.drawText  ( "Center",     centerArea.reduced     ( 10, 0 ), Justification::left );
    g.drawText  ( "Duck",       duckArea.reduced       ( 10, 0 ), Justification::left );
    g.drawText  ( "Compressor", compressorArea.reduced ( 12, 0 ), Justification::left );
}

void TitleHeader::resized()
{
    auto totalArea = getLocalBounds();
    
    fullumMusicArea = totalArea.removeFromRight( totalArea.getWidth() * 0.66f );
    
}

void TitleHeader::setBackgroundColor(Colour& bg)
{
    backgroundColor = bg;
}

void TitleHeader::setTextColor(Colour& textC)
{
    textColor = textC;
}



//==============================================================================
//==============================================================================
//==============================================================================



void TitleFooter::paint(juce::Graphics& g)
{
    g.fillAll   (backgroundColor);
    g.setColour ( textColor );
    
    g.setFont  ( Font("Helvetica", 14, 0) );
    g.drawText ( "Version 1.0", versionArea.reduced( 12, 6 ), Justification::left );
    g.drawText ( "www.FullumMusic.com", urlArea.reduced( 12, 6 ), Justification::right );
}


void TitleFooter::resized()
{
    auto totalArea = getLocalBounds();
    
    versionArea = totalArea.removeFromLeft( totalArea.getWidth() * 0.5f );
    urlArea     = totalArea;
}
