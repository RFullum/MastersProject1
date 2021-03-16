/*
  ==============================================================================

    ArduinoToMidiCC.h
    Created: 16 Mar 2021 5:17:11pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ArduinoToMidiCC
{
public:
    ArduinoToMidiCC();
    ~ArduinoToMidiCC();
    
    /**
     Takes shape parameter argument to define the shape of the gyro or accelerometer mapping to midi: Linear, logarithmic,
     exponential, exp to log, and log to exp.
     */
    void setValueMapShape(float shapeParameter);
    
    /// Enum defining which type the IMU sensor is: Accelerometer (Accel) or Gyroscope (Gyro)
    enum class ImuType
    {
        Accel,
        Gyro
    };
    
    /// Sets ImuType: ImuType::Accel or ImuType::Gyro
    void setIMUType(ImuType type);
    
    /**
     Returns Midi CC Value from 0 - 127
     Knows and maps gyro or accelerometer values accordingly
     */
    int getCCValue(float sensorValue);
    
    /**
     After Arduino is physically mounted to instrument or device, this method will set Accelerometer values to 0 so its mounted position
     is the center point. The values are then wrapped so there is full
     */
    void zeroOrientation(float currentVal);
    
    /// Resets Accelerometer offset to 0.0f
    void resetOrientation();
    
private:
    /**
     Maps accelerometer values -4.0f -- 4.0f, to mid values 0 -- 127. Shapes: Linear, Logarithmic, Exponential,
     Log to exp, or Exp to log. Note: Accelerometer gives orientation of Arduino. Rotating around the given axis will give values from
     -1 to 1, and back down to -1 again. 1 is the pull of earth's gravity and -1 is the same, but upside down. Values greater than 1 or
     less than -1 are caused by accelerations beyond gravity: A sudden movement up increases value without orientation change; A sudden movement
     down decreases the value without orientation change.
     */
    int getAccelCC(float sensorValue);
    
    /**
     Maps gyro values -2000.0f -- 2000.0f, to midi values 0 -- 127. Shapes: Linear, Logarithmic, Exponential,
     Log to exp, or Exp to log.
     */
    int getGyroCC(float sensorValue);
    
    /**
     Remaps the values based on offset: Between offset and 1 to 0 and 1; Between offset and -1 to 0 and -1.
     Note: Only the zeros offset. 1 and -1 remain in the same position.
     */
    void zeroOrientationRemap(float sensorVal);
    
    // Member Variables
    float mappingShape;          // Gets shape of value mapping from parameter (linear, log, exp, exp-log, log-exp)
    float accelOffsetValue;      // The Accel value for zeroing the orientation
    float accelOffsetRemap;      // Remapped Accel values after zeroing orientation
    
    ImuType imuType;
};



