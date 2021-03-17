/**
 * Sketch for Arduino Nano 33 IoT
 * 
 * Connects to WiFi network and uses UDP to send 
 * onboard sensor data as OSC Bundles.
 * 
 * Sensors: 3D Gyro and 3D accelerometer (6 values)
 * Sensor values are Floats cast to a byte array. 
 *  
 * This is to connect with a JUCE application running on my laptop.
 */

#include <WiFiNINA.h>         // Wifi library
#include <WiFiUdp.h>          // UDP library
#include <Arduino_LSM6DS3.h>  // IMU accelerometer library
#include <OSCBundle.h>        // OSC Bundle Library


// WiFi variables
char ssid[] = "Frasier Crane";    // Wifi SSID (network name)
char pass[] = "1974Ducati750ss";  // Wifi password

int status = WL_IDLE_STATUS;      // Status of WiFi connection

WiFiSSLClient client;             // Instantiate the Wifi client


// UDP Variables
WiFiUDP udp;                          // Instantiate UDP class

unsigned int localPort = 2390;        // local port to listen on
const char* computerIP = "Speed3";

const unsigned int destPort = 9001;

// IMU
float accelX, accelY, accelZ;
float gyroX,  gyroY,  gyroZ;

// OSC Bundle
OSCBundle bndl;

//
// ***********************************************************
//


void setup() 
{
  connectToWiFi();
  connectUDP();
  checkIMU();
}


void loop() 
{
  readSensor();
  sendUDPBundle();
}


//
//  setup() Functions ************************************************
//


void connectToWiFi()
{
  // Check for Wifi Module. If no module, don't continue
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("FAILURE");
    while (true);
  }
  else
  {
    Serial.println("Not Failure");
  }

  // Connect to Wifi Access Point
  while ( status != WL_CONNECTED) 
  {
    status = WiFi.begin(ssid, pass);

    // wait 1 second for connection:
    delay(1000);
  }
}


void connectUDP()
{
  // Start UDP
  udp.begin(localPort);
}


void checkIMU()
{
  // Stop if IMU doesn't begin.
  if (!IMU.begin())
  {
    while(1);
  }
}


//
//  loop() Functions ************************************************
//


void readSensor()
{
  if (IMU.accelerationAvailable())
  {
    IMU.readAcceleration( accelX, accelY, accelZ );
  }

  if (IMU.gyroscopeAvailable())
  {
    IMU.readGyroscope( gyroX, gyroY, gyroZ );
  }
}


void sendUDPBundle()
{
  bndl.add( "/juce/accelX" ).add( accelX );
  bndl.add( "/juce/accelY" ).add( accelY );
  bndl.add( "/juce/accelZ" ).add( accelZ );

  bndl.add( "/juce/gyroX" ).add( gyroX );
  bndl.add( "/juce/gyroY" ).add( gyroY );
  bndl.add( "/juce/gyroZ" ).add( gyroZ );

  udp.beginPacket( computerIP, destPort );
  bndl.send( udp );
  udp.endPacket();
  bndl.empty();
}
