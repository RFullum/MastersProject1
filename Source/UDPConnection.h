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
        //std::cout << "Port: " << udpSocket.getBoundPort() << "\n";
    }
    
    /**
     Reads byte buffer coming from Arduino over UDP and recasts back to float value
     */
    void readArduinoStream()
    {
        udpSocket.read(udpInBuffer, 4, false);      // Puts incoming value into udpInBuffer
        recastValueFloat = (float*)(udpInBuffer);   // recasts buffer back to float
        // std::cout << sensorName << *recastValueFloat << "\n";
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
    
    
private:
    /**
     Maps gyro values -2000.0f -- 2000.0f, to midi values 0 -- 127 (linear)
     */
    int getGyroCC()
    {
        int ccGyro = jmap(*recastValueFloat, -2000.0f, 2000.0f, 0.0f, 127.0f);
        
        return ccGyro;
    }
    
    /**
     Maps accelerometer values -4.0f -- 4.0f, to mid values 0 -- 127 (linear)
     */
    int getAccelCC()
    {
        int ccAccel = jmap(*recastValueFloat, -4.0f, 4.0f, 0.0f, 127.0f);
        
        return ccAccel;
    }
    
    // Member Variables
    int currentPort;
    float *recastValueFloat;            // Recast byte buffer into float
    Byte* udpInBuffer = new Byte[4];    // Buffer for incoming byte arrays
    bool isGyroOrAccel;                 // True = Gyro; False = Accelerometer
    
    DatagramSocket udpSocket;           // JUCE's UDP wrapper instance
};
