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

      udpPortGyroX(65013),
      udpPortGyroY(65014),
      udpPortGyroZ(65015),

      udpPortAccelX(65016),
      udpPortAccelY(65017),
      udpPortAccelZ(65018),

      onyx                   ( Colour( (uint8)53,  (uint8)59,  (uint8)60  ) ),
      lightSlateGray         ( Colour( (uint8)130, (uint8)146, (uint8)152 ) ),
      magicMint              ( Colour( (uint8)174, (uint8)255, (uint8)216 ) ),
      fieryRose              ( Colour( (uint8)255, (uint8)104, (uint8)114 ) ),
      orangePeel             ( Colour( (uint8)252, (uint8)152, (uint8)0   ) ),

      processor (p)
{
    setSize (1000, 1000);
    
    // Timer
    Timer::startTimerHz(60);
    
    // UDP Setup: connects to UDP Ports for each instance
    udpConnectionGyroX.udpPortConnect  ( udpPortGyroX  );
    udpConnectionGyroY.udpPortConnect  ( udpPortGyroY  );
    udpConnectionGyroZ.udpPortConnect  ( udpPortGyroZ  );
    udpConnectionAccelX.udpPortConnect ( udpPortAccelX );
    udpConnectionAccelY.udpPortConnect ( udpPortAccelY );
    udpConnectionAccelZ.udpPortConnect ( udpPortAccelZ );
    
    // Slider Setup
    Slider::SliderStyle vertSlider = Slider::SliderStyle::LinearVertical;
    
    sliderSetup ( inGainSlider,        vertSlider, true );
    sliderSetup ( gateThresholdSlider, vertSlider, true );
    
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
    
}

MasterExp1AudioProcessorEditor::~MasterExp1AudioProcessorEditor()
{
    Timer::stopTimer();
}

//==============================================================================
void MasterExp1AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MasterExp1AudioProcessorEditor::resized()
{
    
}

void MasterExp1AudioProcessorEditor::timerCallback()
{
    /*
    // Sets shape of value mappings (linear, log, exp, exp-log, log-exp)
    udpConnectionAccelX.setValueMapShape ( *accelMappingShapeParameter );
    udpConnectionAccelY.setValueMapShape ( *accelMappingShapeParameter );
    udpConnectionAccelZ.setValueMapShape ( *accelMappingShapeParameter );
    udpConnectionGyroX.setValueMapShape  ( *gyroMappingShapeParameter  );
    udpConnectionGyroY.setValueMapShape  ( *gyroMappingShapeParameter  );
    udpConnectionGyroZ.setValueMapShape  ( *gyroMappingShapeParameter  );
    
    // Zero or Reset axis orientation
    if (*zeroAccelXValuesParameter != 0.0f)
    {
        if (*zeroAccelXValuesParameter == 1.0f)
        {
            udpConnectionAccelX.zeroOrientation();
        }
        else
        {
            udpConnectionAccelX.resetOrientation();
        }
    }
    
    if (*zeroAccelYValuesParameter != 0.0f)
    {
        if (*zeroAccelYValuesParameter == 1.0f)
        {
            udpConnectionAccelY.zeroOrientation();
        }
        else
        {
            udpConnectionAccelY.resetOrientation();
        }
    }
    
    if (*zeroAccelZValuesParameter != 0.0f)
    {
        if (*zeroAccelZValuesParameter == 1.0f)
        {
            udpConnectionAccelZ.zeroOrientation();
        }
        else
        {
            udpConnectionAccelZ.resetOrientation();
        }
    }
    */
    // Read XYZ values from Arduio via UDP
    udpConnectionGyroX.readArduinoStream();
    udpConnectionGyroY.readArduinoStream();
    udpConnectionGyroZ.readArduinoStream();
    udpConnectionAccelX.readArduinoStream();
    udpConnectionAccelY.readArduinoStream();
    udpConnectionAccelZ.readArduinoStream();
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
    labelInstance.setJustificationType ( Justification::centred );
    labelInstance.setColour            ( Label::textColourId, orangePeel );
    labelInstance.setFont              ( Font("helvetica", fontSize, 1) );
    addAndMakeVisible                  ( labelInstance );
}


/// Sets up an On/Off combo box
void MasterExp1AudioProcessorEditor::onOffBoxSetup(ComboBox &boxInstance)
{
    boxInstance.addItem              ( "Off", 1 );
    boxInstance.addItem              ( "On",  2 );
    boxInstance.setJustificationType ( Justification::centred );
    boxInstance.setSelectedItemIndex ( 0 );
    
    boxInstance.setColour ( ComboBox::backgroundColourId, onyx        );
    boxInstance.setColour ( ComboBox::outlineColourId, lightSlateGray );
    boxInstance.setColour ( ComboBox::textColourId, orangePeel        );
    boxInstance.setColour ( ComboBox::arrowColourId, magicMint        );
    
    addAndMakeVisible ( boxInstance );
}


void MasterExp1AudioProcessorEditor::comboBoxSetup(ComboBox& boxInstance, StringArray& itemArray)
{
    boxInstance.addItemList          ( itemArray, 1           );
    boxInstance.setJustificationType ( Justification::centred );
    boxInstance.setSelectedId        ( 0                      );
    
    boxInstance.setColour ( ComboBox::backgroundColourId, onyx        );
    boxInstance.setColour ( ComboBox::outlineColourId, lightSlateGray );
    boxInstance.setColour ( ComboBox::textColourId, orangePeel        );
    boxInstance.setColour ( ComboBox::arrowColourId, magicMint        );
    
    addAndMakeVisible ( boxInstance );
}

//
//
// PluginProcessor::processBlock() needs to communicate with this
// to replace udpConnection####.getCCValue() in the midiMessages section
//
//


