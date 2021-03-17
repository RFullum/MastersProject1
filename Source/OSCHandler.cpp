/*
  ==============================================================================

    OSCHandler.cpp
    Created: 13 Mar 2021 4:06:23pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "OSCHandler.h"


ArduinoReceiverOSC::ArduinoReceiverOSC() :
    accelXVal(0.0f), accelYVal(0.0f), accelZVal(0.0f),
    gyroXVal(0.0f),  gyroYVal(0.0f),  gyroZVal(0.0f),

    accelXSmooth(0.0f), accelYSmooth(0.0f), accelZSmooth(0.0f),
    gyroXSmooth(0.0f),  gyroYSmooth(0.0f),  gyroZSmooth(0.0f),

    smoothingFactor(0.4f),

    accelXAddress("/juce/accelX"), accelYAddress("/juce/accelY"), accelZAddress("/juce/accelZ"),
    gyroXAddress("/juce/gyroX"),   gyroYAddress("/juce/gyroY"),   gyroZAddress("/juce/gyroZ")

{
    connect     ( 9001 );
    addListener ( this );                    // Bundles
    addListener ( this, accelXAddress );     // Messages
    addListener ( this, accelYAddress );     
    addListener ( this, accelZAddress );
    addListener ( this, gyroXAddress  );
    addListener ( this, gyroYAddress  );
    addListener ( this, gyroZAddress  );
}

ArduinoReceiverOSC::~ArduinoReceiverOSC()
{}


/// Automatically called when an OSC Message comes in. Checks the address, and sets appropriate variable with incoming float
void ArduinoReceiverOSC::oscMessageReceived(const OSCMessage& message)
{
    //DBG(message.getAddressPattern().toString());
    //DBG(message[0].getFloat32());
    //DBG("");
    
    if (message.getAddressPattern().toString() == accelXAddress.toString())
        accelXVal = message[0].getFloat32();
    else if (message.getAddressPattern().toString() == accelYAddress.toString())
        accelYVal = message[0].getFloat32();
    else if (message.getAddressPattern().toString() == accelZAddress.toString())
        accelZVal = message[0].getFloat32();
    else if (message.getAddressPattern().toString() == gyroXAddress.toString())
        gyroXVal = message[0].getFloat32();
    else if (message.getAddressPattern().toString() == gyroYAddress.toString())
        gyroYVal = message[0].getFloat32();
    else if (message.getAddressPattern().toString() == gyroZAddress.toString())
        gyroZVal = message[0].getFloat32();
}

/**
 Automatically called when OSC Bundle comes in, splits bundle into its elements, and calls either
 oscMessageReceived or oscBundleReceived depending on which type the element of the bundle is
 */
void ArduinoReceiverOSC::oscBundleReceived(const juce::OSCBundle& bundle)
{
    if (bundle.size() > 0)
    {
        for (int i = 0; i < bundle.size(); i++)
        {
            auto elem = bundle[i];
            
            if (elem.isMessage())
            {
                oscMessageReceived ( elem.getMessage() );
            }
            else if (elem.isBundle())
            {
                oscBundleReceived ( elem.getBundle() );
            }
        }
    }
}

/// Returns smoothed float of the raw Accelerometer X axis value
float ArduinoReceiverOSC::getAccelX()
{
    accelXSmooth += ( accelXVal - accelXSmooth ) * smoothingFactor;
    
    return accelXSmooth;
}

/// Returns smoothed float of the raw Accelerometer Y axis value
float ArduinoReceiverOSC::getAccelY()
{
    accelYSmooth += ( accelYVal - accelYSmooth ) * smoothingFactor;
    
    return accelYSmooth;
}

/// Returns smoothed float of the raw Accelerometer Z axis value
float ArduinoReceiverOSC::getAccelZ()
{
    accelZSmooth += ( accelZVal - accelZSmooth ) * smoothingFactor;
    
    return accelZSmooth;
}

/// Returns smoothed float of the raw Gyroscope X axis value
float ArduinoReceiverOSC::getGyroX()
{
    gyroXSmooth += ( gyroXVal - gyroXSmooth ) * smoothingFactor;
    
    return gyroXSmooth;
}

/// Returns smoothed float of the raw Gyroscope Y axis value
float ArduinoReceiverOSC::getGyroY()
{
    gyroYSmooth += ( gyroYVal - gyroYSmooth ) * smoothingFactor;
    
    return gyroYSmooth;
}

/// Returns smoothed float of the raw Gyroscope Z axis value
float ArduinoReceiverOSC::getGyroZ()
{
    gyroZSmooth += ( gyroZVal - gyroZSmooth ) * smoothingFactor;
    
    return gyroZVal;
}
