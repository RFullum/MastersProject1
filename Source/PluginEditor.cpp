/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MasterExp1AudioProcessorEditor::MasterExp1AudioProcessorEditor (MasterExp1AudioProcessor& p)
    : AudioProcessorEditor (&p),

      accelXOnOff(false),
      accelYOnOff(false),
      accelZOnOff(false),
      
      gyroXOnOff(false),
      gyroYOnOff(false),
      gyroZOnOff(false),

      onyx                   ( Colour( (uint8)53,  (uint8)59,  (uint8)60  ) ),
      lightSlateGray         ( Colour( (uint8)130, (uint8)146, (uint8)152 ) ),
      magicMint              ( Colour( (uint8)174, (uint8)255, (uint8)216 ) ),
      fieryRose              ( Colour( (uint8)255, (uint8)104, (uint8)114 ) ),
      orangePeel             ( Colour( (uint8)252, (uint8)152, (uint8)0   ) ),

      processor (p)
{
    setSize (1000, 500);
    
    // Timer
    Timer::startTimerHz(60);
    
    // Slider Setup
    Slider::SliderStyle vertSlider = Slider::SliderStyle::LinearVertical;
    
    sliderSetup ( inGainSlider,        vertSlider, true );
    sliderSetup ( gateThresholdSlider, vertSlider, true );
    
    // Invisible Slider Setup
    // (Backend to get IMU Midi Values to the MidiMessage Buffer)
    sliderSetup ( accelXCCSlider, vertSlider, false );
    sliderSetup ( accelYCCSlider, vertSlider, false );
    sliderSetup ( accelZCCSlider, vertSlider, false );
    sliderSetup ( gyroXCCSlider,  vertSlider, false );
    sliderSetup ( gyroYCCSlider,  vertSlider, false );
    sliderSetup ( gyroZCCSlider,  vertSlider, false );
    
    // Combo Box Setup
    onOffBoxSetup ( accelXBox );
    onOffBoxSetup ( accelYBox );
    onOffBoxSetup ( accelZBox );
    onOffBoxSetup ( gyroXBox  );
    onOffBoxSetup ( gyroYBox  );
    onOffBoxSetup ( gyroZBox  );
    
    StringArray midiLearnItems  = { "none", "Accel X", "Accel Y", "Accel Z", "Gyro X",  "Gyro Y",  "Gyro Z" };
    StringArray accelShapeItems = { "Linear",  "Logarithmic", "Exponential", "Exp-log", "Log-exp" };
    StringArray gyroShapeItems  = { "Linear",  "Logarithmic", "Exponential", "Exp-log", "Log-exp" };
    StringArray zeroXItems      = { "Active", "Set Orientation", "Reset" };
    StringArray zeroYItems      = { "Active", "Set Orientation", "Reset" };
    StringArray zeroZItems      = { "Active", "Set Orientation", "Reset" };
    
    comboBoxSetup ( midiLearnBox,  midiLearnItems  );
    comboBoxSetup ( accelShapeBox, accelShapeItems );
    comboBoxSetup ( gyroShapeBox,  gyroShapeItems  );
    comboBoxSetup ( zeroXBox,      zeroXItems      );
    comboBoxSetup ( zeroYBox,      zeroYItems      );
    comboBoxSetup ( zeroZBox,      zeroZItems      );
    
    // Label Setup
    float labelFontSize = 16.0f;
    
    labelSetup ( inGainLabel,        "Input Gain",           labelFontSize );
    labelSetup ( gateThresholdLabel, "Gate Threshold",       labelFontSize );
    labelSetup ( accelXLabel,        "Accel X",              labelFontSize );
    labelSetup ( accelYLabel,        "Accel Y",              labelFontSize );
    labelSetup ( accelZLabel,        "Accel Z",              labelFontSize );
    labelSetup ( gyroXLabel,         "Gyro X",               labelFontSize );
    labelSetup ( gyroYLabel,         "Gyro Y",               labelFontSize );
    labelSetup ( gyroZLabel,         "Gyro Z",               labelFontSize );
    labelSetup ( midiLearnLabel,     "MIDI Learn Focus",     labelFontSize );
    labelSetup ( accelShapeLabel,    "Accel Response Shape", labelFontSize );
    labelSetup ( gyroShapeLabel,     "Gyro Response Shape",  labelFontSize );
    labelSetup ( zeroXLabel,         "Zero X Orientation",   labelFontSize );
    labelSetup ( zeroYLabel,         "Zero Y Orientation",   labelFontSize );
    labelSetup ( zeroZLabel,         "Zero Z Orientation",   labelFontSize );
    
    // Attachements
    inGainAttach        = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> ( processor.parameters, "input_gain",     inGainSlider        );
    gateThresholdAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> ( processor.parameters, "gate_threshold", gateThresholdSlider );
    
    accelXAttach = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( processor.parameters, "accelXOnOff", accelXBox );
    accelYAttach = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( processor.parameters, "accelYOnOff", accelYBox );
    accelZAttach = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( processor.parameters, "accelZOnOff", accelZBox );
    
    gyroXAttach = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( processor.parameters, "gyroXOnOff", gyroXBox );
    gyroYAttach = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( processor.parameters, "gyroYOnOff", gyroYBox );
    gyroZAttach = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( processor.parameters, "gyroZOnOff", gyroZBox );
    
    midiLearnAttach  = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( processor.parameters, "midiLearnFocus", midiLearnBox  );
    accelShapeAttach = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( processor.parameters, "accelMapShape",  accelShapeBox );
    gyroShapeAttach  = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( processor.parameters, "gyroMapShape",   gyroShapeBox  );
    
    zeroXAttach = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( processor.parameters, "zeroAccelXOrientation", zeroXBox );
    zeroYAttach = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( processor.parameters, "zeroAccelYOrientation", zeroYBox );
    zeroZAttach = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> ( processor.parameters, "zeroAccelZOrientation", zeroZBox );
    
    // Invisible Attachments (Backend to get IMU Midi Values to the MidiMessage Buffer)
    accelXCCAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> ( processor.parameters, "accelXCC", accelXCCSlider );
    accelYCCAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> ( processor.parameters, "accelYCC", accelYCCSlider );
    accelZCCAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> ( processor.parameters, "accelZCC", accelZCCSlider );
    gyroXCCAttach  = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> ( processor.parameters, "gyroXCC",  gyroXCCSlider  );
    gyroYCCAttach  = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> ( processor.parameters, "gyroYCC",  gyroYCCSlider  );
    gyroZCCAttach  = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> ( processor.parameters, "gyroZCC",  gyroZCCSlider  );
    
    
    // OSC
    ardAccelX.setIMUType ( ArduinoToMidiCC::ImuType::Accel );
    ardAccelY.setIMUType ( ArduinoToMidiCC::ImuType::Accel );
    ardAccelZ.setIMUType ( ArduinoToMidiCC::ImuType::Accel );
    ardGyroX.setIMUType  ( ArduinoToMidiCC::ImuType::Gyro  );
    ardGyroY.setIMUType  ( ArduinoToMidiCC::ImuType::Gyro  );
    ardGyroZ.setIMUType  ( ArduinoToMidiCC::ImuType::Gyro  );
}

MasterExp1AudioProcessorEditor::~MasterExp1AudioProcessorEditor()
{
    Timer::stopTimer();
}

//==============================================================================
void MasterExp1AudioProcessorEditor::paint (Graphics& g)
{
    float rounding = 2.0f;
    
    g.fillAll ( lightSlateGray );
    
    g.setColour( onyx );
    g.fillRoundedRectangle ( sliderAreaInner,  rounding );
    g.fillRoundedRectangle ( onOffAreaInner,   rounding );
    g.fillRoundedRectangle ( utilityAreaInner, rounding );
}

void MasterExp1AudioProcessorEditor::resized()
{
    // Main GUI Structure
    float padding     = 2.0f;
    float labelHeight = 50.0f;
    
    Rectangle<int> totalArea = getLocalBounds();
    
    Rectangle<int> sliderArea  = totalArea.removeFromLeft( totalArea.getWidth() * 0.25f ).reduced( padding );
    Rectangle<int> onOffArea   = totalArea.removeFromLeft( totalArea.getWidth() * 0.5f  ).reduced( padding );
    Rectangle<int> utilityArea = totalArea.reduced( padding );
    
    sliderAreaInner.setBounds  ( sliderArea.getX(),  sliderArea.getY(),  sliderArea.getWidth(),  sliderArea.getHeight()  );
    onOffAreaInner.setBounds   ( onOffArea.getX(),   onOffArea.getY(),   onOffArea.getWidth(),   onOffArea.getHeight()   );
    utilityAreaInner.setBounds ( utilityArea.getX(), utilityArea.getY(), utilityArea.getWidth(), utilityArea.getHeight() );
    
    // Sliders
    Rectangle<int> inGainArea = sliderArea.removeFromLeft( sliderArea.getWidth() * 0.5f );
    Rectangle<int> inGainLabelArea  = inGainArea.removeFromTop( labelHeight );
    Rectangle<int> inGainSliderArea = inGainArea;
    
    inGainLabel.setBounds  ( inGainLabelArea );
    inGainSlider.setBounds ( inGainSliderArea );
    
    Rectangle<int> gateThreshArea       = sliderArea;
    Rectangle<int> gateThreshLabelArea  = gateThreshArea.removeFromTop( labelHeight );
    Rectangle<int> gateThreshSliderArea = gateThreshArea;
    
    gateThresholdLabel.setBounds  ( gateThreshLabelArea );
    gateThresholdSlider.setBounds ( gateThreshSliderArea );
    
    // On/Off CombBoxes
    float boxXPadding = 25.0f;
    float boxYPadding = 20.0f;
    float onOffBoxHeight  = onOffArea.getHeight() / 6.0f;
    float onOffLabelWidth = onOffArea.getWidth() * 0.33f;
    
    Rectangle<int> accelXArea      = onOffArea.removeFromTop   ( onOffBoxHeight  );
    Rectangle<int> accelXLabelArea = accelXArea.removeFromLeft ( onOffLabelWidth );
    Rectangle<int> accelXBoxArea   = accelXArea.reduced        ( boxXPadding, boxYPadding );
    
    accelXLabel.setBounds ( accelXLabelArea );
    accelXBox.setBounds   ( accelXBoxArea   );
    
    Rectangle<int> accelYArea      = onOffArea.removeFromTop   ( onOffBoxHeight  );
    Rectangle<int> accelYLabelArea = accelYArea.removeFromLeft ( onOffLabelWidth );
    Rectangle<int> accelYBoxArea   = accelYArea.reduced        ( boxXPadding, boxYPadding );;
    
    accelYLabel.setBounds ( accelYLabelArea );
    accelYBox.setBounds   ( accelYBoxArea   );
    
    Rectangle<int> accelZArea      = onOffArea.removeFromTop   ( onOffBoxHeight  );
    Rectangle<int> accelZLabelArea = accelZArea.removeFromLeft ( onOffLabelWidth );
    Rectangle<int> accelZBoxArea   = accelZArea.reduced        ( boxXPadding, boxYPadding );;
    
    accelZLabel.setBounds ( accelZLabelArea );
    accelZBox.setBounds   ( accelZBoxArea   );
    
    Rectangle<int> gyroXArea      = onOffArea.removeFromTop  ( onOffBoxHeight  );
    Rectangle<int> gyroXLabelArea = gyroXArea.removeFromLeft ( onOffLabelWidth );
    Rectangle<int> gyroXBoxArea   = gyroXArea.reduced        ( boxXPadding, boxYPadding );;
    
    gyroXLabel.setBounds ( gyroXLabelArea );
    gyroXBox.setBounds   ( gyroXBoxArea   );
    
    Rectangle<int> gyroYArea      = onOffArea.removeFromTop  ( onOffBoxHeight  );
    Rectangle<int> gyroYLabelArea = gyroYArea.removeFromLeft ( onOffLabelWidth );
    Rectangle<int> gyroYBoxArea   = gyroYArea.reduced        ( boxXPadding, boxYPadding );;
    
    gyroYLabel.setBounds ( gyroYLabelArea );
    gyroYBox.setBounds   ( gyroYBoxArea   );
    
    Rectangle<int> gyroZArea      = onOffArea;
    Rectangle<int> gyroZLabelArea = gyroZArea.removeFromLeft ( onOffLabelWidth );
    Rectangle<int> gyroZBoxArea   = gyroZArea.reduced        ( boxXPadding, boxYPadding );;
    
    gyroZLabel.setBounds ( gyroZLabelArea );
    gyroZBox.setBounds   ( gyroZBoxArea );
    
    // Utility ComboBoxes
    float uteBoxHeight  = utilityArea.getHeight() / 6.0f;
    float uteLabelWidth = utilityArea.getWidth() * 0.33f;
    
    Rectangle<int> midiLearnArea      = utilityArea.removeFromTop    ( uteBoxHeight  );
    Rectangle<int> midiLearnLabelArea = midiLearnArea.removeFromLeft ( uteLabelWidth );
    Rectangle<int> midiLearnBoxArea   = midiLearnArea.reduced        ( boxXPadding, boxYPadding );;
    
    midiLearnLabel.setBounds ( midiLearnLabelArea );
    midiLearnBox.setBounds   ( midiLearnBoxArea   );
    
    Rectangle<int> accelShapeArea      = utilityArea.removeFromTop     ( uteBoxHeight  );
    Rectangle<int> accelShapeLabelArea = accelShapeArea.removeFromLeft ( uteLabelWidth );
    Rectangle<int> accelShapeBoxArea   = accelShapeArea.reduced        ( boxXPadding, boxYPadding );;
    
    accelShapeLabel.setBounds ( accelShapeLabelArea );
    accelShapeBox.setBounds   ( accelShapeBoxArea   );
    
    Rectangle<int> gyroShapeArea      = utilityArea.removeFromTop    ( uteBoxHeight  );
    Rectangle<int> gyroShapeLabelArea = gyroShapeArea.removeFromLeft ( uteLabelWidth );
    Rectangle<int> gyroShapeBoxArea   = gyroShapeArea.reduced        ( boxXPadding, boxYPadding );;
    
    gyroShapeLabel.setBounds ( gyroShapeLabelArea );
    gyroShapeBox.setBounds   ( gyroShapeBoxArea   );
    
    Rectangle<int> zeroXArea      = utilityArea.removeFromTop ( uteBoxHeight  );
    Rectangle<int> zeroXLabelArea = zeroXArea.removeFromLeft  ( uteLabelWidth );
    Rectangle<int> zeroXBoxArea   = zeroXArea.reduced        ( boxXPadding, boxYPadding );;
    
    zeroXLabel.setBounds ( zeroXLabelArea );
    zeroXBox.setBounds   ( zeroXBoxArea   );
    
    Rectangle<int> zeroYArea      = utilityArea.removeFromTop ( uteBoxHeight  );
    Rectangle<int> zeroYLabelArea = zeroYArea.removeFromLeft  ( uteLabelWidth );
    Rectangle<int> zeroYBoxArea   = zeroYArea.reduced        ( boxXPadding, boxYPadding );;
    
    zeroYLabel.setBounds ( zeroYLabelArea );
    zeroYBox.setBounds   ( zeroYBoxArea   );
    
    Rectangle<int> zeroZArea      = utilityArea;
    Rectangle<int> zeroZLabelArea = zeroZArea.removeFromLeft  ( uteLabelWidth );
    Rectangle<int> zeroZBoxArea   = zeroZArea.reduced        ( boxXPadding, boxYPadding );;
    
    zeroZLabel.setBounds ( zeroZLabelArea );
    zeroZBox.setBounds   ( zeroZBoxArea   );
    
}

void MasterExp1AudioProcessorEditor::timerCallback()
{
    // Response Map
    ardAccelX.setValueMapShape ( accelShapeBox.getSelectedItemIndex() );
    ardAccelY.setValueMapShape ( accelShapeBox.getSelectedItemIndex() );
    ardAccelZ.setValueMapShape ( accelShapeBox.getSelectedItemIndex() );
    ardGyroX.setValueMapShape  ( gyroShapeBox.getSelectedItemIndex() );
    ardGyroY.setValueMapShape  ( gyroShapeBox.getSelectedItemIndex() );
    ardGyroZ.setValueMapShape  ( gyroShapeBox.getSelectedItemIndex() );
    
    
    // Zero or Reset axis orientation
    orientationZeroing ( zeroXBox, ardAccelX, ardOSC.getAccelX() );
    orientationZeroing ( zeroYBox, ardAccelY, ardOSC.getAccelY() );
    orientationZeroing ( zeroZBox, ardAccelZ, ardOSC.getAccelZ() );
    
    // Get global on/off value from parameter tree
    // Use Midi Learn Focus Parameter to solo individual values
    // allowing Midi Learn to receive one value at a time
    switch (midiLearnBox.getSelectedItemIndex())
    {
        case 0:
            accelXOnOff = ( accelXBox.getSelectedItemIndex() == 0 ) ? false : true;
            accelYOnOff = ( accelYBox.getSelectedItemIndex() == 0 ) ? false : true;
            accelZOnOff = ( accelZBox.getSelectedItemIndex() == 0 ) ? false : true;
            
            gyroXOnOff = ( gyroXBox.getSelectedItemIndex() == 0 ) ? false : true;
            gyroYOnOff = ( gyroYBox.getSelectedItemIndex() == 0 ) ? false : true;
            gyroZOnOff = ( gyroZBox.getSelectedItemIndex() == 0 ) ? false : true;
            break;
        // Midi Learn Accel X
        case 1:
            accelXOnOff = true;
            accelYOnOff = accelZOnOff = gyroXOnOff = gyroYOnOff = gyroZOnOff = false;
            break;
        // Midi Learn Accel Y
        case 2:
            accelYOnOff = true;
            accelXOnOff = accelZOnOff = gyroXOnOff = gyroYOnOff = gyroZOnOff = false;
            break;
        // Midi Learn Accel Z
        case 3:
            accelZOnOff = true;
            accelXOnOff = accelYOnOff = gyroXOnOff = gyroYOnOff = gyroZOnOff = false;
            break;
        // Midi Learn Gyro X
        case 4:
            gyroXOnOff = true;
            accelXOnOff = accelYOnOff = accelZOnOff = gyroYOnOff = gyroZOnOff = false;
            break;
        // Midi Learn Gyro Y
        case 5:
            gyroYOnOff = true;
            accelXOnOff = accelYOnOff = accelZOnOff = gyroXOnOff = gyroZOnOff = false;
            break;
        // Midi Learn Gyro Z
        case 6:
            gyroZOnOff = true;
            accelXOnOff = accelYOnOff = accelZOnOff = gyroXOnOff = gyroYOnOff = false;
            break;
        default:
            accelXOnOff = ( accelXBox.getSelectedItemIndex() == 0 ) ? false : true;
            accelYOnOff = ( accelYBox.getSelectedItemIndex() == 0 ) ? false : true;
            accelZOnOff = ( accelZBox.getSelectedItemIndex() == 0 ) ? false : true;
            
            gyroXOnOff = ( gyroXBox.getSelectedItemIndex() == 0 ) ? false : true;
            gyroYOnOff = ( gyroYBox.getSelectedItemIndex() == 0 ) ? false : true;
            gyroZOnOff = ( gyroZBox.getSelectedItemIndex() == 0 ) ? false : true;
            break;
    }
    
    
    if (accelXOnOff)
        accelXCCSlider.setValue ( ardAccelX.getCCValue( ardOSC.getAccelX() ) );
    
    if (accelYOnOff)
        accelYCCSlider.setValue ( ardAccelY.getCCValue( ardOSC.getAccelY() ) );
    
    if (accelZOnOff)
        accelZCCSlider.setValue ( ardAccelZ.getCCValue( ardOSC.getAccelZ() ) );
    
    if (gyroXOnOff)
        gyroXCCSlider.setValue ( ardGyroX.getCCValue( ardOSC.getGyroX() ) );
    
    if (gyroYOnOff)
        gyroYCCSlider.setValue ( ardGyroY.getCCValue( ardOSC.getGyroY() ) );
    
    if (gyroZOnOff)
        gyroZCCSlider.setValue ( ardGyroZ.getCCValue( ardOSC.getGyroZ() ) );
}

/// Zeros the orientation to the current position of sensors
void MasterExp1AudioProcessorEditor::orientationZeroing(ComboBox& box,  ArduinoToMidiCC& imuAxis, float imuVal)
{
    switch (box.getSelectedItemIndex())
    {
        case 0:
            break;
        case 1:
            imuAxis.zeroOrientation( imuVal );
            break;
        case 2:
            imuAxis.resetOrientation();
            break;
        default:
            break;
    }
}


/// Sets up Slider object instances in constructor. sliderInstance is the slider to set up, suffix is textValueSuffix, sliderFillColor is the slider color below the thumb
void MasterExp1AudioProcessorEditor::sliderSetup(Slider &sliderInstance, Slider::SliderStyle style, bool showTextBox)
{
    sliderInstance.setSliderStyle(style);
        
    // If slider has a textbox, draw it, otherwise, don't
    if (showTextBox)
    {
        sliderInstance.setTextBoxStyle ( Slider::TextBoxBelow, false, 50, 20 );
        sliderInstance.setColour       ( Slider::textBoxOutlineColourId, Colour( (uint8)0, (uint8)0, (uint8)0, (uint8)0 ) );
        sliderInstance.setColour       ( Slider::textBoxTextColourId, magicMint );
    }
    else
    {
        sliderInstance.setTextBoxStyle( Slider::NoTextBox, false, 0, 0 );
    }
    
    sliderInstance.setColour( Slider::trackColourId, fieryRose );
    sliderInstance.setColour( Slider::thumbColourId, magicMint );
    
    addAndMakeVisible(sliderInstance);
}


/// Sets up Label for the Slider instances. Takes the labelInstance and the text for setText
void MasterExp1AudioProcessorEditor::labelSetup(Label &labelInstance, String labelText, float fontSize)
{
    labelInstance.setText              ( labelText, dontSendNotification );
    labelInstance.setJustificationType ( Justification::centred          );
    labelInstance.setColour            ( Label::textColourId, orangePeel );
    labelInstance.setFont              ( Font("helvetica", fontSize, 1)  );
    addAndMakeVisible                  ( labelInstance                   );
}


/// Sets up an On/Off combo box
void MasterExp1AudioProcessorEditor::onOffBoxSetup(ComboBox &boxInstance)
{
    boxInstance.addItem              ( "Off", 1 );
    boxInstance.addItem              ( "On",  2 );
    boxInstance.setJustificationType ( Justification::centred );
    boxInstance.setSelectedItemIndex ( 0 );
    
    boxInstance.setColour ( ComboBox::backgroundColourId, onyx           );
    boxInstance.setColour ( ComboBox::outlineColourId,    lightSlateGray );
    boxInstance.setColour ( ComboBox::textColourId,       magicMint      );
    boxInstance.setColour ( ComboBox::arrowColourId,      magicMint      );
    
    addAndMakeVisible ( boxInstance );
}


void MasterExp1AudioProcessorEditor::comboBoxSetup(ComboBox& boxInstance, StringArray& itemArray)
{
    boxInstance.addItemList          ( itemArray, 1           );
    boxInstance.setJustificationType ( Justification::centred );
    boxInstance.setSelectedId        ( 0                      );
    
    boxInstance.setColour ( ComboBox::backgroundColourId, onyx           );
    boxInstance.setColour ( ComboBox::outlineColourId,    lightSlateGray );
    boxInstance.setColour ( ComboBox::textColourId,       magicMint      );
    boxInstance.setColour ( ComboBox::arrowColourId,      magicMint      );
    
    addAndMakeVisible ( boxInstance );
}


