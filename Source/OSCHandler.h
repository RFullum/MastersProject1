/*
  ==============================================================================

    OSCHandler.h
    Created: 13 Mar 2021 4:06:23pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class ArduinoReceiverOSC : private OSCReceiver,
                           private OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>,
                           private OSCReceiver::Listener<juce::OSCReceiver::MessageLoopCallback>
{
public:
    ArduinoReceiverOSC();
    ~ArduinoReceiverOSC();
    
    /// Returns smoothed float of the raw Accelerometer X axis value
    float getAccelX();
    
    /// Returns smoothed float of the raw Accelerometer Y axis value
    float getAccelY();
    
    /// Returns smoothed float of the raw Accelerometer Z axis value
    float getAccelZ();
    
    /// Returns smoothed float of the raw Gyroscope X axis value
    float getGyroX();
    
    /// Returns smoothed float of the raw Gyroscope Y axis value
    float getGyroY();
    
    /// Returns smoothed float of the raw Gyroscope Z axis value
    float getGyroZ();
    
private:
    /// Automatically called when an OSC Message comes in. Checks the address, and sets appropriate variable with incoming float
    void oscMessageReceived (const OSCMessage& message) override;

    /**
    Automatically called when OSC Bundle comes in, splits bundle into its elements, and calls either
    oscMessageReceived or oscBundleReceived depending on which type the element of the bundle is
    */
    void oscBundleReceived (const OSCBundle& bundle) override;
    
    float accelXVal;
    float accelYVal;
    float accelZVal;
    float gyroXVal;
    float gyroYVal;
    float gyroZVal;
    
    float accelXSmooth;
    float accelYSmooth;
    float accelZSmooth;
    float gyroXSmooth;
    float gyroYSmooth;
    float gyroZSmooth;
    
    float smoothingFactor;
    
    OSCAddress accelXAddress;
    OSCAddress accelYAddress;
    OSCAddress accelZAddress;
    OSCAddress gyroXAddress;
    OSCAddress gyroYAddress;
    OSCAddress gyroZAddress;
};
