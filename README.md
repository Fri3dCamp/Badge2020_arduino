# Arduino library for the Fri3d Camp 2022 Badge

## Installation

Installation is two-fold, first of all you need to install support for the Fri3d Badge. The badge carries an ESP32, so we need to install support for the ESP32 boards.

The second step is to install the arduino library holding all the utility functions etc for the Fri3d Camp 2022 badge.

### Add ESP32 board to your Arduino IDE

* In your Arduino IDE, open **File>Preferences**
* Enter `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` into the “Additional Board Manager URLs” field 
* Open **Tools>Board>Board Manager**
* Search for the `esp32` boards from Espressif Systems and install the latest version.
* Under **Tools>Board>...** select **..>ESP32 Arduino>ESP32 Dev Module**

### Arduino Library for the Fri3d Camp badge

Download this repo as a .ZIP file and install it, similar to other Arduino libraries: https://www.arduino.cc/en/Guide/Libraries#toc4

### Library dependencies

* In your Arduino IDE, open **Tools>Manage Libraries ...**
* Install the following libraries
  * Adafruit NeoPixel (for the ws2812 LEDs)
  * Adafruit ST7735 and ST7789 Library (for the TFT screen)
  * Adafruit GFX Library (graphics library to draw stuff on the screen)

## Usage

This is a work in progress, the library for now only contains basic examples of (parts of) the hardware.
