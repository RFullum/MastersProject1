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
        //std::cout << "Port: " << udpSocket.getBoundPort() << "\n";
    }
    
    void readArduinoStream()
    {
        udpSocket.read(udpInBuffer, 4, false);      // Puts incoming value into udpInBuffer
        recastValueFloat = (float*)(udpInBuffer);   // recasts buffer back to float
        // std::cout << sensorName << *recastValueFloat << "\n";
    }
private:
    
    // Member Variables
    int currentPort;
    float *recastValueFloat;            // Recast byte buffer into float
    Byte* udpInBuffer = new Byte[4];    // Buffer for incoming byte arrays
    
    DatagramSocket udpSocket;           // JUCE's UDP wrapper instance
};
