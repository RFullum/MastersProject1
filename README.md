# MastersProject1
Masters Final Project: Takes audio, Arudino Gyroscope and accelerometer values in. 
Determines frequency real time and outputs as MIDI notes. Converts Arduino IMU values to mappable MIDI CC values. 

Companion Arduino code available here:  https://gist.github.com/RFullum/b47bb54a7f3cfb170573cea4a893f727

Example videos:

https://youtu.be/EqeRRt8cee4

https://youtu.be/OJ8HTu78fEk

https://youtu.be/OzbzVEB7xBU


- C++/Juce application. 
- Mac only. 
- Needs to run as a standalone app to work. Will not work as a VST or AU.

- Analyzes the frequency on input 1 without FFT analysis and outputs MIDI notes via the IAC Bus to your DAW.
- Receives UDP over wifi from Arduino Nano 33 IOT, converts gyroscope and accelerometer values to MIDI CC values,
  which can be MIDI mapped inside your DAW.

