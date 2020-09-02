# ESP8266 With ECC608

### Author: Bryan Pearson

Download or clone this repository into your ESP8266_RTOS_SDK workspace in connect your ESP8266 to an external ECC608 crypto chip.

This sample project will establish an I<sup>2</sup>C connection with the ECC608 at address 0x20 and pins 14 (SDA) and 2 (SCL). Check the main.c for how to configure the project to your particular needs. The project will attempt to read the serial number from the ECC608 and generate a 32-byte random number.

Once the hardware has been appropriately configured, simply run "make flash monitor" to build and upload the project to your ESP8266.

This project was built using [ESP8266_RTOS_SDK release/v3.3](https://github.com/espressif/ESP8266_RTOS_SDK/tree/release/v3.3).