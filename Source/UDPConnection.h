/*
  ==============================================================================

    UDPConnection.h
    Created: 20 Jul 2020 5:57:11pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class UDPConnection
{
public:
    UDPConnection();
    ~UDPConnection();
    
    /**
     Sets current port and binds socket to port passed in arugment
     Port value determines if it's bound to a Gyroscopic or Accelerometer value
     */
    void udpPortConnect(int udpPortNumber);
    
    /**
     Reads byte buffer coming from Arduino over UDP and recasts back to float value
     */
    void readArduinoStream();
    
    /**
     Takes shape parameter argument to define the shape of the gyro or accelerometer mapping to midi: Linear, logarithmic,
     exponential, exp to log, and log to exp.
     */
    void setValueMapShape(float shapeParameter);
    
    /**
     Returns Midi CC Value from 0 - 127
     Knows and maps gyro or accelerometer values accordingly
     */
    int getCCValue();
    
    
    /**
     After Arduino is physically mounted to instrument or device, this method will set Accelerometer values to 0 so its mounted position
     is the center point. The values are then wrapped so there is full
     */
    void zeroOrientation();
    
    
    /**
     Resets Accelerometer offset to 0.0f
     */
    void resetOrientation();
    
    
    
private:
    /**
     Maps gyro values -2000.0f -- 2000.0f, to midi values 0 -- 127. Shapes: Linear, Logarithmic, Exponential,
     Log to exp, or Exp to log.
     */
    int getGyroCC();
    
    
    
    /**
     Maps accelerometer values -4.0f -- 4.0f, to mid values 0 -- 127. Shapes: Linear, Logarithmic, Exponential,
     Log to exp, or Exp to log. Note: Accelerometer gives orientation of Arduino. Rotating around the given axis will give values from
     -1 to 1, and back down to -1 again. 1 is the pull of earth's gravity and -1 is the same, but upside down. Values greater than 1 or
     less than -1 are caused by accelerations beyond gravity: A sudden movement up increases value without orientation change; A sudden movement
     down decreases the value without orientation change.
     */
    int getAccelCC();
    
    
    /**
     Remaps the values based on offset: Between offset and 1 to 0 and 1; Between offset and -1 to 0 and -1.
     Note: Only the zeros offset. 1 and -1 remain in the same position.
     */
    void zeroOrientationRemap();
    
    
    
    //
    // Member Variables
    //
    
    // UDP Connection
    int currentPort;
    float *recastValueFloat;            // Recast byte buffer into float
    unsigned char* udpInBuffer = new unsigned char[4];    // Buffer for incoming byte arrays
    
    DatagramSocket udpSocket;           // JUCE's UDP wrapper instance
    
    // Mapping Values
    bool isGyroOrAccel;          // True = Gyro; False = Accelerometer
    float mappingShape;          // Gets shape of value mapping from parameter (linear, log, exp, exp-log, log-exp)
    float accelOffsetValue;      // The Accel value for zeroing the orientation
    float accelOffsetRemap;      // Remapped Accel values after zeroing orientation
    
};
