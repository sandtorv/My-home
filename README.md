# My-home #
A simple website connected to the Particle Photon that utilizes the BME280 temperature, humidity and barometric sensor over I2C. 

Includes a OLED display (SSD1306) for displaying temperature, humidity and barometric pressure from the sensor.


##Shopping list##
* [Particle Photon](https://store.particle.io/collections/photon)
* [OLED SDD1306 display](https://www.adafruit.com/products/938)
* [BME280 sensor](https://www.adafruit.com/products/2652)
* Two 1.5k - 10k Ohm resistors
* A few cables cables


![alt tag](https://github.com/sandtorv/My-home/blob/master/Images/Overview.png "How it looks")

##Setup##
1. [Setup your Particle Photon](https://docs.particle.io/guide/getting-started/intro/)
2. Upload the My-home-firmware.cpp in /Firmware to the Particle Photon
3. Connect both the display and the BME280 sensor to the I2C on the Particle Photon [like this](https://docs.particle.io/reference/firmware/photon/#wire-i2c-)
4. Open the config.js in /Website/js/ and add your Access Token and Device ID from the Particle Website.
5. Open the index.html in /Website and view the magic ;-)