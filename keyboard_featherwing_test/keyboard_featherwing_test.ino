#define HUZZAH_32

#include "featherwing_setup.h"
//#include "TFT_eSPI.h"
//#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
//#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
#include <Adafruit_NeoPixel.h>
//#include <BBQ10Keyboard.h>
#include <SD.h>

#include "MenuFunctions.h";

#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

//int count = 0;

Adafruit_STMPE610 ts(STMPE_CS);
//Adafruit_ILI9341 tft(TFT_CS, TFT_DC);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
BBQ10Keyboard keyboard;
File root;

MenuFunctions menu_function_obj;

void setup()
{    
  Serial.begin(115200);

  delay(100);

  Serial.println("Setting pixel color...");

  pixels.setBrightness(0);
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  delay(100);
  pixels.setBrightness(50);
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();

  //delay(2000);

  #ifdef HUZZAH_ESP8266
    Serial.println("HUZZAH_ESP8266");
  #elif defined(FEATHER_MZERO)
    Serial.println("HUZZAH_MZERO");
  #elif defined(HUZZAH_32)
    Serial.println("HUZZAH_32");
  #endif
  
  Wire.begin();
  const bool sd = SD.begin(SD_CS);

  delay(10);

  //menu_function_obj.tft.begin();
  menu_function_obj.RunSetup();
  ts.begin();

  //Serial.println("\nOK");

  //pixels.begin();
  //pixels.setBrightness(30);

  //pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  //pixels.show();

  keyboard.begin();
  keyboard.setBacklight(0.5f);
  
  //menu_function_obj.tft.setRotation(1);
  //menu_function_obj.tft.fillScreen(ILI9341_BLACK);
  //menu_function_obj.tft.println("Hello World");
  Serial.println("Hello, World!");


  //if (sd) {
    //menu_function_obj.tft.println("SD Connected");
    /*tft.print("SD Card contents:\n");
    root = SD.open("/");
    
    while (true) {
      File entry =  root.openNextFile();
      if (!entry)
        break;

      tft.println(entry.name());
      entry.close();
    }*/
  //}
  //else
    //menu_function_obj.tft.println("SD NOT connected");
}

void loop() {
  /*if (!ts.bufferEmpty()) {
    TS_Point p = ts.getPoint();
    p.x = map(p.x, TS_MINY, TS_MAXY, menu_function_obj.tft.height(), 0);
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, menu_function_obj.tft.width());

    Serial.println("x: " + (String)p.x + " y: " + (String)p.y);
  }*/

  // Print keys to screen
  /*
  if (keyboard.keyCount()) {
    const BBQ10Keyboard::KeyEvent key = keyboard.keyEvent();
    if (key.state == BBQ10Keyboard::StateRelease) {
      //pixels.setPixelColor(0, pixels.Color(0, 255, 0));
      //pixels.show(); 
    
      if ((char)key.key == 0x01)
        Serial.println("UP");
      else if ((char)key.key == 0x02)
        Serial.println("DOWN");
      else if ((char)key.key == 0x03)
        Serial.println("LEFT");
      else if ((char)key.key == 0x04)
        Serial.println("RIGHT");
      else if ((char)key.key == 0x05)
        Serial.println("SELECT");
      else if ((char)key.key == 0x06)
        Serial.println("MACRO 1");
      else if ((char)key.key == 0x11)
        Serial.println("MACRO 2");
      else if ((char)key.key == 0x07)
        Serial.println("MACRO 3");
      else if ((char)key.key == 0x12)
        Serial.println("MACRO 4");
      else {
        Serial.print((char)key.key);
        //menu_function_obj.tft.print(key.key);
      }
      
    }
  }*/

  menu_function_obj.main(millis());

  //pixels.clear();
  //pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  //pixels.show(); 

}
