/*
  ==============================================================================

    UDPConnection.h
    Created: 20 Jul 2020 5:57:11pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once


class UDPConnection
{
public:
    /**
     Sets current port and binds socket to port passed in arugment
     Port value determines if it's bound to a Gyroscopic or Accelerometer value
     */
    void udpPortConnect(int udpPortNumber)
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
    void readArduinoStream()
    {
        udpSocket.read(udpInBuffer, 4, false);      // Puts incoming value into udpInBuffer
        recastValueFloat = (float*)(udpInBuffer);   // recasts buffer back to float
    }
    
    /**
     Takes shape parameter argument to define the shape of the gyro or accelerometer mapping to midi: Linear, logarithmic,
     exponential, exp to log, and log to exp.
     */
    void setValueMapShape(float shapeParameter)
    {
        mappingShape = shapeParameter;
    }
    
    /**
     Returns Midi CC Value from 0 - 127
     Knows maps gyro or accelerometer values accordingly
     */
    int getCCValue()
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
    void zeroOrientation()
    {
        if (!isGyroOrAccel)
        {
            accelOffsetValue = *recastValueFloat;
        }
    }
    
    /**
     Resets Accelerometer offset to 0.0f
     */
    void resetOrientation()
    {
        accelOffsetValue = 0.0f;
    }
    
    
private:
    /**
     Maps gyro values -2000.0f -- 2000.0f, to midi values 0 -- 127. Shapes: Linear, Logarithmic, Exponential,
     Log to exp, or Exp to log.
     */
    int getGyroCC()
    {
        int ccGyro = 0;
        
        // Linear Map
        if (mappingShape == 0)
        {
            ccGyro = jmap(*recastValueFloat, -2000.0f, 2000.0f, 0.0f, 127.0f);
        }
        // Log map
        else if (mappingShape == 1)
        {
            float gyroMapLog = log( jmap(*recastValueFloat, -2000.0f, 2000.0f, 1.0f, MathConstants<float>::euler) );
            ccGyro = jmap(gyroMapLog, 0.0f, 1.0f, 0.0f, 127.0f);
        }
        // Exponential map
        else if (mappingShape == 2)
        {
            float gyroMapExp = pow( jmap(*recastValueFloat, -2000.0f, 2000.0f, 0.0f, 1.0f), 2 );
            ccGyro = jmap(gyroMapExp, 0.0f, 1.0f, 0.0f, 127.0f);
        }
        // Log 0-64, exp 64-127
        else if (mappingShape == 3)
        {
            if (*recastValueFloat < 0.0f)
            {
                float gyroMapLog = log( jmap(*recastValueFloat, -2000.0f, 0.0f, 1.0f, MathConstants<float>::euler) );
                ccGyro = jmap(gyroMapLog, 0.0f, 1.0f, 0.0f, 64.0f);
            }
            else
            {
                float gyroMapExp = pow( jmap(*recastValueFloat, 0.0f, 2000.0f, 0.0f, 1.0f), 2 );
                ccGyro = jmap(gyroMapExp, 0.0f, 1.0f, 64.0f, 127.0f);
            }
        }
        // Exp 0-64, log 64-127
        else if (mappingShape == 4)
        {
            if (*recastValueFloat < 0.0f)
            {
                float gyroMapExp = pow( jmap(*recastValueFloat, -2000.0f, 0.0f, 0.0f, 1.0f), 2 );
                ccGyro = jmap(gyroMapExp, 0.0f, 1.0f, 0.0f, 64.0f);
            }
            else
            {
                float gyroMapLog = log( jmap(*recastValueFloat, 0.0f, 2000.0f, 1.0f, MathConstants<float>::euler) );
                ccGyro = jmap(gyroMapLog, 0.0f, 1.0f, 64.0f, 127.0f);
            }
        }
        // Catch any erroneous values and set to linear as a safety net
        else
        {
            ccGyro = jmap(*recastValueFloat, -2000.0f, 2000.0f, 0.0f, 127.0f);
        }
        
        return ccGyro;
    }
    
    
    /**
     Maps accelerometer values -4.0f -- 4.0f, to mid values 0 -- 127. Shapes: Linear, Logarithmic, Exponential,
     Log to exp, or Exp to log.
     */
    int getAccelCC()
    {
        int ccAccel = 0;
        zeroOrientationRemap();
        
        // Linear map
        if (mappingShape == 0)
        {
            ccAccel = jmap(accelOffsetRemap, -4.0f, 4.0f, 0.0f, 127.0f);
        }
        // Logarithmic map
        else if (mappingShape == 1)
        {
            float accelMapLog = log( jmap(accelOffsetRemap, -4.0f, 4.0f, 1.0f, MathConstants<float>::euler) );
            ccAccel = jmap(accelMapLog, 0.0f, 1.0f, 0.0f, 127.0f);
        }
        // Exponential map
        else if (mappingShape == 2)
        {
            float accelMapExp = pow( jmap(accelOffsetRemap, -4.0f, 4.0f, 0.0f, 1.0f), 2 );
            ccAccel = jmap(accelMapExp, 0.0f, 1.0f, 0.0f, 127.0f);
        }
        // Log 0-64, exp 64-127
        else if (mappingShape == 3)
        {
            if (accelOffsetRemap < 0.0f)
            {
                float accelMapLog = log( jmap(accelOffsetRemap, -4.0f, 0.0f, 1.0f, MathConstants<float>::euler) );
                ccAccel = jmap(accelMapLog, 0.0f, 1.0f, 0.0f, 64.0f);
            }
            else
            {
                float accelMapExp = pow( jmap(accelOffsetRemap, 0.0f, 4.0f, 0.0f, 1.0f), 2 );
                ccAccel = jmap(accelMapExp, 0.0f, 1.0f, 64.0f, 127.0f);
            }
        }
        // Exp 0-64, log 64-127
        else if (mappingShape == 4)
        {
            if (accelOffsetRemap < 0.0f)
            {
                float accelMapExp = pow( jmap(accelOffsetRemap, -4.0f, 0.0f, 0.0f, 1.0f), 2 );
                ccAccel = jmap(accelMapExp, 0.0f, 1.0f, 0.0f, 64.0f);
            }
            else
            {
                float accelMapLog = log( jmap(accelOffsetRemap, 0.0f, 4.0f, 1.0f, MathConstants<float>::euler) );
                ccAccel = jmap(accelMapLog, 0.0f, 1.0f, 64.0f, 127.0f);
            }
        }
        // Catch any erroneous values and set to linear as a safety net
        else
        {
            ccAccel = jmap(accelOffsetRemap, -4.0f, 4.0f, 0.0f, 127.0f);
        }
            
        return ccAccel;
    }
    
    void zeroOrientationRemap()
    {
        //float accelMax = 1.0f - accelOffsetValue;
        //float accelMin = -1.0f - accelOffsetValue;
        
        if (*recastValueFloat >= accelOffsetValue)
        {
            accelOffsetRemap = jmap(*recastValueFloat, accelOffsetValue, 1.0f, 0.0f, 1.0f);
        }
        else
        {
            accelOffsetRemap = jmap(*recastValueFloat, accelOffsetValue, -1.0f, 0.0f, -1.0f);
        }
       
    }
    
    
    //
    // Member Variables
    //
    
    // UDP Connection
    int currentPort;
    float *recastValueFloat;            // Recast byte buffer into float
    Byte* udpInBuffer = new Byte[4];    // Buffer for incoming byte arrays
    
    DatagramSocket udpSocket;           // JUCE's UDP wrapper instance
    
    // Mapping Values
    bool isGyroOrAccel;                 // True = Gyro; False = Accelerometer
    float mappingShape = 0.0f;          // Gets shape of value mapping from parameter (linear, log, exp, exp-log, log-exp)
    float accelOffsetValue = 0.0f;      // The Accel value for zeroing the orientation
    float accelOffsetRemap = 0.0f;      // Remapped Accel values after zeroing orientation
    
    bool currentXSign;
    bool currentYSign;
    bool currentZSign;
};
