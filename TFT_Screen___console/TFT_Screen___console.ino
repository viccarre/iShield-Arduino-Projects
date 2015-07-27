#include <Nordic_nRF8001.h>
#include <RBL_nRF8001.h>
#include "iShield.h"
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"


#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// These are the pins used for the UNO
// for Due/Mega/Leonardo use the hardware SPI pins (which are different)
#define _sclk 7
#define _miso 6
#define _mosi 5
#define _cs 4
#define _dc 3
#define _rst 2

// Using software SPI is really not suggested, its incredibly slow
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _mosi, _sclk, _rst, _miso);
// Use hardware SPI
//Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);
iShield myiShield;
String message;

void setup() {
  
  ble_begin();
  Serial.begin(9600);
  Serial.println("Setup BLE ...");
  ble_begin();
  Serial.println("Setup TFT Screen ...");
  tft.begin();
  Serial.println("Finish setup ...");
  //ble_begin();
  tft.fillScreen(ILI9340_BLACK);
  tft.setRotation(3);
  tft.setCursor(0, 0);

}


void loop(void) {

  myiShield.readConsole();
  message = myiShield.incomingData();
  tft.fillRect(0,22,ILI9340_TFTHEIGHT,40,ILI9340_BLACK);
  tft.setTextColor(ILI9340_GREEN);
  tft.setTextSize(3);
  tft.setCursor(0, 0);
  tft.println("iShield data > ");
  tft.println("                     ");
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9340_GREEN);
  tft.setTextSize(3);
  tft.println("iShield data > ");
  tft.println(message);
  Serial.println(message);
  
}

