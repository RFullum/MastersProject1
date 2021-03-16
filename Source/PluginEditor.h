/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UDPConnection.h"

//==============================================================================
/**
*/
class MasterExp1AudioProcessorEditor  : public AudioProcessorEditor, public Timer
{
public:
    MasterExp1AudioProcessorEditor (MasterExp1AudioProcessor&);
    ~MasterExp1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    /// Sets up Slider object instances in constructor. sliderInstance is the slider to set up, suffix is textValueSuffix, sliderFillColor is the slider color below the thumb
    void sliderSetup(Slider& sliderInstance, Slider::SliderStyle style, bool showTextBox);
    
    /// Sets up Label for the Slider instances. Takes the labelInstance and the text for setText
    void labelSetup(Label& labelInstance, String labelText, float fontSize);
    
    /// Sets up an On/Off combo box
    void onOffBoxSetup(ComboBox& boxInstance);
    
    /// Sets up a combo box
    void comboBoxSetup(ComboBox& boxInstance, StringArray& itemArray);
    
    // Sliders
    Slider inGainSlider;
    Slider gateThresholdSlider;
    
    // ComboBoxes
    ComboBox accelXBox;
    ComboBox accelYBox;
    ComboBox accelZBox;
    
    ComboBox gyroXBox;
    ComboBox gyroYBox;
    ComboBox gyroZBox;
    
    ComboBox midiLearnBox;
    ComboBox accelShapeBox;
    ComboBox gyroShapeBox;
    
    ComboBox zeroXBox;
    ComboBox zeroYBox;
    ComboBox zeroZBox;
    
    // Labels
    Label inGainLabel;
    Label gateThresholdLabel;
    
    Label accelXLabel;
    Label accelYLabel;
    Label accelZLabel;
    
    Label gyroXLabel;
    Label gyroYLabel;
    Label gyroZLabel;
    
    Label midiLearnLabel;
    Label accelShapeLabel;
    Label gyroShapeLabel;
    
    Label zeroXLabel;
    Label zeroYLabel;
    Label zeroZLabel;
    
    
    // UDP
    UDPConnection udpConnectionGyroX;
    UDPConnection udpConnectionGyroY;
    UDPConnection udpConnectionGyroZ;
    UDPConnection udpConnectionAccelX;
    UDPConnection udpConnectionAccelY;
    UDPConnection udpConnectionAccelZ;
    
    int udpPortGyroX;
    int udpPortGyroY;
    int udpPortGyroZ;
    int udpPortAccelX;
    int udpPortAccelY;
    int udpPortAccelZ;
    
    // Colors
    Colour onyx;
    Colour lightSlateGray;
    Colour magicMint;
    Colour fieryRose;
    Colour orangePeel;
    
    MasterExp1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterExp1AudioProcessorEditor)
};
