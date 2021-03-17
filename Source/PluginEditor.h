/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OSCHandler.h"
#include "ArduinoToMidiCC.h"
#include "TitleHeader.h"

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
    
    /// Zeros the orientation to the current position of sensors
    void orientationZeroing(ComboBox& box, ArduinoToMidiCC& imuAxis, float imuVal);
    
    
    // Title Areas
    TitleHeader titleHeader;
    TitleFooter titleFooter;

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
    
    // Invisible Slider (Backend to get IMU Midi Values to the MidiMessage Buffer)
    Slider accelXCCSlider;
    Slider accelYCCSlider;
    Slider accelZCCSlider;
    
    Slider gyroXCCSlider;
    Slider gyroYCCSlider;
    Slider gyroZCCSlider;
    
    // Attachments
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>  inGainAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>  gateThresholdAttach;
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> accelXAttach;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> accelYAttach;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> accelZAttach;
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> gyroXAttach;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> gyroYAttach;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> gyroZAttach;
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> midiLearnAttach;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> accelShapeAttach;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> gyroShapeAttach;
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> zeroXAttach;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> zeroYAttach;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> zeroZAttach;
    
    // Invisible Attachments (Backend to get IMU Midi Values to the MidiMessage Buffer)
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> accelXCCAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> accelYCCAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> accelZCCAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gyroXCCAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gyroYCCAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gyroZCCAttach;
    
    // OSC
    ArduinoReceiverOSC ardOSC;
    ArduinoToMidiCC ardAccelX;
    ArduinoToMidiCC ardAccelY;
    ArduinoToMidiCC ardAccelZ;
    ArduinoToMidiCC ardGyroX;
    ArduinoToMidiCC ardGyroY;
    ArduinoToMidiCC ardGyroZ;
    
    
    // IMU   
    bool accelXOnOff;
    bool accelYOnOff;
    bool accelZOnOff;
    
    bool gyroXOnOff;
    bool gyroYOnOff;
    bool gyroZOnOff;
    
    // Colors
    Colour onyx;
    Colour lightSlateGray;
    Colour magicMint;
    Colour fieryRose;
    Colour orangePeel;
    
    // Background Rectangles
    Rectangle<float> sliderAreaInner;
    Rectangle<float> onOffAreaInner;
    Rectangle<float> utilityAreaInner;
    
    MasterExp1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterExp1AudioProcessorEditor)
};
