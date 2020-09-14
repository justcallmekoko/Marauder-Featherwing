// Feather specific
#if defined(HUZZAH_ESP8266)
  #define STMPE_CS 16
  #define SD_CS 2
  #define TFT_CS 0
  #define TFT_DC 15
  #define NEOPIXEL_PIN 13
  
#elif defined(FEATHER_MZERO)
  #define STMPE_CS 6
  #define TFT_CS 9
  #define TFT_DC 10
  #define SD_CS 5
  #define NEOPIXEL_PIN 11
  
#elif defined(HUZZAH_32)
  #define STMPE_CS 32
  //#define TFT_MOSI 23
  //#define TFT_MISO 19
  //#define TFT_SCK 18
  #define TFT_CS 15
  #define TFT_DC 33
  #define SD_CS 14
  #define NEOPIXEL_PIN 27
#endif
