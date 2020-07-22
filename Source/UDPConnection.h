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
    void udpPortConnect(int udpPortNumber)
    {
        currentPort = udpPortNumber;
        udpSocket.bindToPort(udpPortNumber);
        std::cout << "Port: " << udpSocket.getBoundPort() << "\n";
    }
    
    void readArduinoStream()
    {
        String sensorName;
        
        if (currentPort == 65013)
            sensorName = "gyroX ";
        else if (currentPort == 65014)
            sensorName = "gyroY ";
        else if (currentPort == 65015)
            sensorName = "gyroZ ";
        else if (currentPort == 65016)
            sensorName = "accelX ";
        else if (currentPort == 65017)
            sensorName = "accelY ";
        else if (currentPort == 65018)
            sensorName = "accelZ ";
        else
            sensorName = "whaa? ";
        
        udpSocket.read(udpInBuffer, 4, false);
        recastValueFloat = (float*)(udpInBuffer);
        std::cout << sensorName << *recastValueFloat << "\n";
    }
private:
    
    // Member Variables
    /*
    int udpPort = 65012;        // That's a fun number!
    int udpPortX = 65013;
    int udpPortY = 65014;
    int udpPortZ = 65015;
     */
    int currentPort;
    float *recastValueFloat;
    Byte* udpInBuffer = new Byte[4];    // Buffer for incoming byte arrays
    
    DatagramSocket udpSocket;
};
