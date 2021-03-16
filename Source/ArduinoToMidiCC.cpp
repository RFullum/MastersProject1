/*
  ==============================================================================

    ArduinoToMidiCC.cpp
    Created: 16 Mar 2021 5:17:11pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "ArduinoToMidiCC.h"


ArduinoToMidiCC::ArduinoToMidiCC() :
    mappingShape(0.0f),
    accelOffsetValue(0.0f),
    accelOffsetRemap(0.0f),
    imuType( ImuType::Accel )
{}

ArduinoToMidiCC::~ArduinoToMidiCC()
{}

/**
 Takes shape parameter argument to define the shape of the gyro or accelerometer mapping to midi: Linear, logarithmic,
 exponential, exp to log, and log to exp.
 */
void ArduinoToMidiCC::setValueMapShape(float shapeParameter)
{
    mappingShape = shapeParameter;
}

/// Sets ImuType: ImuType::Accel or ImuType::Gyro
void ArduinoToMidiCC::setIMUType(ImuType type)
{
    imuType = type;
}

/**
 Returns Midi CC Value from 0 - 127
 Knows and maps gyro or accelerometer values accordingly
 */
int ArduinoToMidiCC::getCCValue(float sensorValue)
{
    int ccValue;
    
    if (imuType == ImuType::Accel)
        ccValue = getAccelCC( sensorValue );
    else if (imuType == ImuType::Gyro)
        ccValue = getGyroCC( sensorValue );
    else
        ccValue = getAccelCC( sensorValue );
    
    return ccValue;
}

/**
 Maps accelerometer values -4.0f -- 4.0f, to mid values 0 -- 127. Shapes: Linear, Logarithmic, Exponential,
 Log to exp, or Exp to log. Note: Accelerometer gives orientation of Arduino. Rotating around the given axis will give values from
 -1 to 1, and back down to -1 again. 1 is the pull of earth's gravity and -1 is the same, but upside down. Values greater than 1 or
 less than -1 are caused by accelerations beyond gravity: A sudden movement up increases value without orientation change; A sudden movement
 down decreases the value without orientation change.
 */
int ArduinoToMidiCC::getAccelCC(float sensorValue)
{
    int ccAccel = 0;
    
    float accelMapLog = 0.0f;
    float accelMapExp = 0.0f;
    
    zeroOrientationRemap( sensorValue );
    
    switch ((int)mappingShape)
    {
        // Linear map
        case 0:
            ccAccel = jmap( accelOffsetRemap, -4.0f, 4.0f, 0.0f, 127.0f );
            break;
        // Logarithmic map
        case 1:
            accelMapLog = log  ( jmap( accelOffsetRemap, -4.0f, 4.0f, 1.0f, MathConstants<float>::euler ) );
            ccAccel     = jmap ( accelMapLog, 0.0f, 1.0f, 0.0f, 127.0f );
            break;
        // Exponential map
        case 2:
            accelMapExp = pow  ( jmap( accelOffsetRemap, -4.0f, 4.0f, 0.0f, 1.0f ), 2 );
            ccAccel     = jmap ( accelMapExp, 0.0f, 1.0f, 0.0f, 127.0f );
            break;
        // Log 0-64, exp 64-127
        case 3:
            if (accelOffsetRemap < 0.0f)
            {
                accelMapLog = log  ( jmap( accelOffsetRemap, -4.0f, 0.0f, 1.0f, MathConstants<float>::euler ) );
                ccAccel     = jmap (accelMapLog, 0.0f, 1.0f, 0.0f, 64.0f );
            }
            else
            {
                accelMapExp = pow  ( jmap( accelOffsetRemap, 0.0f, 4.0f, 0.0f, 1.0f ), 2 );
                ccAccel     = jmap ( accelMapExp, 0.0f, 1.0f, 64.0f, 127.0f );
            }
            break;
        // Exp 0-64, log 64-127
        case 4:
            if (accelOffsetRemap < 0.0f)
            {
                accelMapExp = pow  ( jmap( accelOffsetRemap, -4.0f, 0.0f, 0.0f, 1.0f ), 2 );
                ccAccel     = jmap ( accelMapExp, 0.0f, 1.0f, 0.0f, 64.0f );
            }
            else
            {
                accelMapLog = log  ( jmap( accelOffsetRemap, 0.0f, 4.0f, 1.0f, MathConstants<float>::euler ) );
                ccAccel     = jmap ( accelMapLog, 0.0f, 1.0f, 64.0f, 127.0f );
            }
            break;
        // Catch any erroneous values and set to linear as a safety net
        default:
            ccAccel = jmap( accelOffsetRemap, -4.0f, 4.0f, 0.0f, 127.0f );
            break;
    }
    
    return ccAccel;
}

/**
 Maps gyro values -2000.0f -- 2000.0f, to midi values 0 -- 127. Shapes: Linear, Logarithmic, Exponential,
 Log to exp, or Exp to log.
 */
int ArduinoToMidiCC::getGyroCC(float sensorValue)
{
    int ccGyro = 0;
    
    float gyroMapLog = 0.0f;
    float gyroMapExp = 0.0f;
    
    switch ((int)mappingShape)
    {
        // Linear Map
        case 0:
            ccGyro = jmap( sensorValue, -2000.0f, 2000.0f, 0.0f, 127.0f );
            break;
        // Log map
        case 1:
            gyroMapLog = log  ( jmap( sensorValue, -2000.0f, 2000.0f, 1.0f, MathConstants<float>::euler ) );
            ccGyro     = jmap ( gyroMapLog, 0.0f, 1.0f, 0.0f, 127.0f );
            break;
        // Exponential map
        case 2:
            gyroMapExp = pow  ( jmap( sensorValue, -2000.0f, 2000.0f, 0.0f, 1.0f ), 2 );
            ccGyro     = jmap ( gyroMapExp, 0.0f, 1.0f, 0.0f, 127.0f );
            break;
        // Log 0-64, exp 64-127
        case 3:
            if (sensorValue < 0.0f)
            {
                gyroMapLog = log  ( jmap( sensorValue, -2000.0f, 0.0f, 1.0f, MathConstants<float>::euler ) );
                ccGyro     = jmap ( gyroMapLog, 0.0f, 1.0f, 0.0f, 64.0f );
            }
            else
            {
                gyroMapExp = pow  ( jmap( sensorValue, 0.0f, 2000.0f, 0.0f, 1.0f ), 2 );
                ccGyro     = jmap ( gyroMapExp, 0.0f, 1.0f, 64.0f, 127.0f );
            }
            break;
        // Exp 0-64, log 64-127
        case 4:
            if (sensorValue < 0.0f)
            {
                gyroMapExp = pow  ( jmap( sensorValue, -2000.0f, 0.0f, 0.0f, 1.0f ), 2 );
                ccGyro     = jmap ( gyroMapExp, 0.0f, 1.0f, 0.0f, 64.0f );
            }
            else
            {
                gyroMapLog = log  ( jmap( sensorValue, 0.0f, 2000.0f, 1.0f, MathConstants<float>::euler ) );
                ccGyro     = jmap ( gyroMapLog, 0.0f, 1.0f, 64.0f, 127.0f );
            }
            break;
        // Catch any erroneous values and set to linear as a safety net
        default:
            ccGyro = jmap( sensorValue, -2000.0f, 2000.0f, 0.0f, 127.0f );
            break;
    }
    
    return ccGyro;
}

/**
 Remaps the values based on offset: Between offset and 1 to 0 and 1; Between offset and -1 to 0 and -1.
 Note: Only the zeros offset. 1 and -1 remain in the same position.
 */
void ArduinoToMidiCC::zeroOrientationRemap(float sensorVal)
{
    if (sensorVal >= accelOffsetValue)
    {
        accelOffsetRemap = jmap( sensorVal, accelOffsetValue, 1.0f, 0.0f, 1.0f );
    }
    else
    {
        accelOffsetRemap = jmap( sensorVal, accelOffsetValue, -1.0f, 0.0f, -1.0f );
    }
}

/**
 After Arduino is physically mounted to instrument or device, this method will set Accelerometer values to 0 so its mounted position
 is the center point. The values are then wrapped so there is full
 */
void ArduinoToMidiCC::zeroOrientation(float currentVal)
{
    if (imuType == ImuType::Accel)
        accelOffsetValue = currentVal;
}

/// Resets Accelerometer offset to 0.0f
void ArduinoToMidiCC::resetOrientation()
{
    accelOffsetValue = 0.0f;
}
