#ifndef MenuFunctions_h
#define MenuFunctions_h

#include <LinkedList.h>
#include <BBQ10Keyboard.h>
#include <functional>
//#include <TFT_eSPI.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include "featherwing_setup.h"

// Keypad start position, key sizes and spacing
#define KEY_X 120 // Centre of key
#define KEY_Y 50
#define KEY_W 240 // Width and height
#define KEY_H 22
#define KEY_SPACING_X 0 // X and Y gap
#define KEY_SPACING_Y 1
#define KEY_TEXTSIZE 1   // Font size multiplier
#define ICON_W 22
#define ICON_H 22
#define BUTTON_PADDING 22
//#define BUTTON_ARRAY_LEN 5
#define BUTTON_ARRAY_LEN 7

#define FLASH_BUTTON 0

extern BBQ10Keyboard keyboard;

struct Menu;

// Individual Nodes of a menu

struct MenuNode {
  String name;
  uint16_t color;
  int icon;
  //TFT_eSPI_Button* button;
  int button;
  std::function<void()> callable;
};

// Full Menus
struct Menu {
  String name;
  LinkedList<MenuNode>* list;
  Menu                * parentMenu;
  uint8_t               selected = 0;
};


class MenuFunctions
{
  private:

    String u_result = "";

    uint32_t initTime = 0;

    Menu* current_menu;

    // Main menu stuff
    Menu mainMenu;

    Menu wifiMenu;
    Menu bluetoothMenu;
    Menu generalMenu;
    Menu deviceMenu;

    // Device menu stuff
    Menu whichUpdateMenu;
    Menu failedUpdateMenu;
    Menu confirmMenu;
    Menu updateMenu;
    Menu infoMenu;

    // WiFi menu stuff
    Menu wifiSnifferMenu;
    Menu wifiScannerMenu;
    Menu wifiAttackMenu;
    Menu wifiGeneralMenu;

    // Bluetooth menu stuff
    Menu bluetoothSnifferMenu;
    Menu bluetoothScannerMenu;
    Menu bluetoothGeneralMenu;

    // Settings things menus
    Menu shutdownWiFiMenu;
    Menu shutdownBLEMenu;
    Menu generateSSIDsMenu;
    Menu clearSSIDsMenu;

    void addNodes(Menu* menu, String name, uint16_t color, Menu* child, int place, std::function<void()> callable);
    void showMenuList(Menu* menu, int layer);

  public:
    MenuFunctions();

    uint16_t x = -1, y = -1;
    boolean pressed = false;

    //Adafruit_ILI9341 tft(TFT_CS, TFT_DC);

    //TFT_eSPI_Button key[BUTTON_ARRAY_LEN];

    void buildButtons(Menu* menu);
    void clearScreen();
    void changeMenu(Menu* menu);
    void displayCurrentMenu();
    void main(uint32_t currentTime);
    void RunSetup();
};



#endif
