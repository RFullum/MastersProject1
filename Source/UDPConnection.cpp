/*
  ==============================================================================

    UDPConnection.cpp
    Created: 15 Mar 2021 11:21:35pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include "UDPConnection.h"


UDPConnection::UDPConnection() : currentPort(9001), isGyroOrAccel(true),
                                 mappingShape(0.0f), accelOffsetValue(0.0f),
                                 accelOffsetRemap(0.0f)
{}

UDPConnection::~UDPConnection()
{
    delete[] udpInBuffer;
}

/**
Sets current port and binds socket to port passed in arugment
Port value determines if it's bound to a Gyroscopic or Accelerometer value
*/
void UDPConnection::udpPortConnect(int udpPortNumber)
{
    currentPort = udpPortNumber;
    
    udpSocket.bindToPort(udpPortNumber);
    
    if (currentPort == 65013 || currentPort == 65014 || currentPort == 65015)
        isGyroOrAccel = true;
    else
        isGyroOrAccel = false;
}

/**
Reads byte buffer coming from Arduino over UDP and recasts back to float value
*/
void UDPConnection::readArduinoStream()
{
    udpSocket.read(udpInBuffer, 4, false);      // Puts incoming value into udpInBuffer
    
    recastValueFloat = (float*)(udpInBuffer);   // recasts buffer back to float
}

/**
Takes shape parameter argument to define the shape of the gyro or accelerometer mapping to midi: Linear, logarithmic,
exponential, exp to log, and log to exp.
*/
void UDPConnection::setValueMapShape(float shapeParameter)
{
    mappingShape = shapeParameter;
}

/**
Returns Midi CC Value from 0 - 127
Knows and maps gyro or accelerometer values accordingly
*/
int UDPConnection::getCCValue()
{
    int ccValue;
    
    if (isGyroOrAccel)
    {
        ccValue = getGyroCC();
    }
    else
    {
        ccValue = getAccelCC();
    }

    return ccValue;
}

/**
After Arduino is physically mounted to instrument or device, this method will set Accelerometer values to 0 so its mounted position
is the center point. The values are then wrapped so there is full
*/
void UDPConnection::zeroOrientation()
{
    if (!isGyroOrAccel)
    {
        accelOffsetValue = *recastValueFloat;
    }
}

/**
Resets Accelerometer offset to 0.0f
*/
void UDPConnection::resetOrientation()
{
    accelOffsetValue = 0.0f;
}

/**
Maps gyro values -2000.0f -- 2000.0f, to midi values 0 -- 127. Shapes: Linear, Logarithmic, Exponential,
Log to exp, or Exp to log.
*/
int UDPConnection::getGyroCC()
{
    int ccGyro = 0;
    
    float gyroMapLog = 0.0f;
    float gyroMapExp = 0.0f;
    
    switch ((int)mappingShape)
    {
        // Linear Map
        case 0:
            ccGyro = jmap( *recastValueFloat, -2000.0f, 2000.0f, 0.0f, 127.0f );
            break;
        // Log map
        case 1:
            gyroMapLog = log  ( jmap( *recastValueFloat, -2000.0f, 2000.0f, 1.0f, MathConstants<float>::euler ) );
            ccGyro     = jmap ( gyroMapLog, 0.0f, 1.0f, 0.0f, 127.0f );
            break;
        // Exponential map
        case 2:
            gyroMapExp = pow  ( jmap( *recastValueFloat, -2000.0f, 2000.0f, 0.0f, 1.0f ), 2 );
            ccGyro     = jmap ( gyroMapExp, 0.0f, 1.0f, 0.0f, 127.0f );
            break;
        // Log 0-64, exp 64-127
        case 3:
            if (*recastValueFloat < 0.0f)
            {
                gyroMapLog = log  ( jmap(*recastValueFloat, -2000.0f, 0.0f, 1.0f, MathConstants<float>::euler ) );
                ccGyro     = jmap ( gyroMapLog, 0.0f, 1.0f, 0.0f, 64.0f );
            }
            else
            {
                gyroMapExp = pow  ( jmap( *recastValueFloat, 0.0f, 2000.0f, 0.0f, 1.0f ), 2 );
                ccGyro     = jmap ( gyroMapExp, 0.0f, 1.0f, 64.0f, 127.0f );
            }
            break;
        // Exp 0-64, log 64-127
        case 4:
            if (*recastValueFloat < 0.0f)
            {
                gyroMapExp = pow  ( jmap( *recastValueFloat, -2000.0f, 0.0f, 0.0f, 1.0f ), 2 );
                ccGyro     = jmap ( gyroMapExp, 0.0f, 1.0f, 0.0f, 64.0f );
            }
            else
            {
                gyroMapLog = log  ( jmap( *recastValueFloat, 0.0f, 2000.0f, 1.0f, MathConstants<float>::euler ) );
                ccGyro     = jmap ( gyroMapLog, 0.0f, 1.0f, 64.0f, 127.0f );
            }
            break;
        // Catch any erroneous values and set to linear as a safety net
        default:
            ccGyro = jmap( *recastValueFloat, -2000.0f, 2000.0f, 0.0f, 127.0f );
            break;
    }
    
    return ccGyro;
}

/**
Maps accelerometer values -4.0f -- 4.0f, to mid values 0 -- 127. Shapes: Linear, Logarithmic, Exponential,
Log to exp, or Exp to log. Note: Accelerometer gives orientation of Arduino. Rotating around the given axis will give values from
-1 to 1, and back down to -1 again. 1 is the pull of earth's gravity and -1 is the same, but upside down. Values greater than 1 or
less than -1 are caused by accelerations beyond gravity: A sudden movement up increases value without orientation change; A sudden movement
down decreases the value without orientation change.
*/
int UDPConnection::getAccelCC()
{
    int ccAccel = 0;
    
    float accelMapLog = 0.0f;
    float accelMapExp = 0.0f;
    
    zeroOrientationRemap();
    
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
Remaps the values based on offset: Between offset and 1 to 0 and 1; Between offset and -1 to 0 and -1.
Note: Only the zeros offset. 1 and -1 remain in the same position.
*/
void UDPConnection::zeroOrientationRemap()
{
    if (*recastValueFloat >= accelOffsetValue)
    {
        accelOffsetRemap = jmap( *recastValueFloat, accelOffsetValue, 1.0f, 0.0f, 1.0f );
    }
    else
    {
        accelOffsetRemap = jmap( *recastValueFloat, accelOffsetValue, -1.0f, 0.0f, -1.0f );
    }
}
