# IoT computer button

This is a simple project to remotely turn on/off a computer using Amazon Alexa and an ESP3. I used [fauxmoESP](https://github.com/vintlabs/fauxmoESP).

I connected the ESP32's GPIO to the computer's power button. When the ESP32 receives a message from Alexa, it sends a signal to the computer to turn on/off.
The device is powered by a USB and is always listening for Alexa commands. It is in a 3D printed case I modeled in Blender.

## Image

![20230419_191157](https://user-images.githubusercontent.com/90425800/233219727-29441e39-dc80-4606-b4ab-f31ceffd0e18.jpg)
