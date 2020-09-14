#include "MenuFunctions.h"
#include "featherwing_setup.h"
//#include "icons.h"

//Adafruit_ILI9341 tft(TFT_CS, TFT_DC);
Adafruit_ILI9341 tft(15, 33);

MenuFunctions::MenuFunctions()
{
}

// Function to check menu input
void MenuFunctions::main(uint32_t currentTime)
{
  boolean pressed = false;
  /*if (!ts.bufferEmpty()) {
    TS_Point p = ts.getPoint();
    p.x = map(p.x, TS_MINY, TS_MAXY, menu_function_obj.tft.height(), 0);
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, menu_function_obj.tft.width());

    Serial.println("x: " + (String)p.x + " y: " + (String)p.y);
  }*/

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

      if ((char)key.key == 0x01) { // Up

        // Clear arrow
        tft.setCursor(0, current_menu->selected * 22);
        //tft.print("  ");
        tft.fillRect(0, current_menu->selected * 22, 5, 7, ILI9341_BLACK);

        // Adjust selected
        if (current_menu->selected > 0)
          current_menu->selected--;

        // Create arrow
        tft.setCursor(0, current_menu->selected * 22);
        tft.print("> ");
      }
      else if ((char)key.key == 0x02) { // Down

        // Clear arrow
        tft.setCursor(0, current_menu->selected * 22);
        //tft.print("  ");
        tft.fillRect(0, current_menu->selected * 22, 5, 7, ILI9341_BLACK);

        // Adjust selected
        if (current_menu->selected < current_menu->list->size() - 1)
          current_menu->selected++;

        // Create arrow
        tft.setCursor(0, current_menu->selected * 22);
        tft.print("> ");
      }
      else if ((char)key.key == 0x05) { // Select
        current_menu->list->get(current_menu->selected).callable();
      }
      
    }
  }
  
}


// Function to build the menus
void MenuFunctions::RunSetup()
{    

  tft.begin();
  tft.setRotation(1);
  this->clearScreen();
  
  // root menu stuff
  mainMenu.list = new LinkedList<MenuNode>(); // Get list in first menu ready

  // Main menu stuff
  wifiMenu.list = new LinkedList<MenuNode>(); // Get list in second menu ready
  bluetoothMenu.list = new LinkedList<MenuNode>(); // Get list in third menu ready
  generalMenu.list = new LinkedList<MenuNode>();
  deviceMenu.list = new LinkedList<MenuNode>();

  // Device menu stuff
  failedUpdateMenu.list = new LinkedList<MenuNode>();
  whichUpdateMenu.list = new LinkedList<MenuNode>();
  confirmMenu.list = new LinkedList<MenuNode>();
  updateMenu.list = new LinkedList<MenuNode>();
  infoMenu.list = new LinkedList<MenuNode>();

  // WiFi menu stuff
  wifiSnifferMenu.list = new LinkedList<MenuNode>();
  wifiScannerMenu.list = new LinkedList<MenuNode>();
  wifiAttackMenu.list = new LinkedList<MenuNode>();
  wifiGeneralMenu.list = new LinkedList<MenuNode>();

  // Bluetooth menu stuff
  bluetoothSnifferMenu.list = new LinkedList<MenuNode>();
  bluetoothScannerMenu.list = new LinkedList<MenuNode>();
  bluetoothGeneralMenu.list = new LinkedList<MenuNode>();

  // Settings stuff
  shutdownWiFiMenu.list = new LinkedList<MenuNode>();
  shutdownBLEMenu.list = new LinkedList<MenuNode>();
  generateSSIDsMenu.list = new LinkedList<MenuNode>();
  clearSSIDsMenu.list = new LinkedList<MenuNode>();

  // Work menu names
  mainMenu.name = " ESP32 Marauder ";
  wifiMenu.name = " WiFi ";
  deviceMenu.name = " Device ";
  generalMenu.name = " General Apps ";
  failedUpdateMenu.name = " Updating... ";
  whichUpdateMenu.name = "Select Method ";
  confirmMenu.name = " Confirm Update ";
  updateMenu.name = " Update Firmware ";
  infoMenu.name = " Device Info ";
  bluetoothMenu.name = " Bluetooth ";
  wifiSnifferMenu.name = " WiFi Sniffers ";
  wifiScannerMenu.name = " WiFi Scanners";
  wifiAttackMenu.name = " WiFi Attacks ";
  wifiGeneralMenu.name = " WiFi General ";
  bluetoothSnifferMenu.name = " Bluetooth Sniffers ";
  bluetoothScannerMenu.name = " Bluetooth Scanners ";
  bluetoothGeneralMenu.name = " Bluetooth General ";
  shutdownWiFiMenu.name = " Shutdown WiFi ";
  shutdownBLEMenu.name = " Shutdown BLE ";
  generateSSIDsMenu.name = " Generate SSIDs ";
  clearSSIDsMenu.name = " Clear SSIDs ";
  

  // Build Main Menu
  mainMenu.parentMenu = NULL;
  addNodes(&mainMenu, "WiFi", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&wifiMenu);
  });
  addNodes(&mainMenu, "Bluetooth", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&bluetoothMenu);
  });
  addNodes(&mainMenu, "General Apps", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&generalMenu);
  });
  addNodes(&mainMenu, "Device", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&deviceMenu);
  });
  addNodes(&mainMenu, "Reboot", ILI9341_WHITE, NULL, 0, []() {
    ESP.restart();
  });

  // Build WiFi Menu
  wifiMenu.parentMenu = &mainMenu; // Main Menu is second menu parent
  addNodes(&wifiMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(wifiMenu.parentMenu);
  });
  addNodes(&wifiMenu, "Sniffers", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&wifiSnifferMenu);
  });
  addNodes(&wifiMenu, "Scanners", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&wifiScannerMenu);
  });
  addNodes(&wifiMenu, "Attacks", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&wifiAttackMenu);
  });
  addNodes(&wifiMenu, "General", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&wifiGeneralMenu);
  });

  // Build WiFi sniffer Menu
  wifiSnifferMenu.parentMenu = &wifiMenu; // Main Menu is second menu parent
  addNodes(&wifiSnifferMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(wifiSnifferMenu.parentMenu);
  });
  //addNodes(&wifiSnifferMenu, "Probe Request Sniff", ILI9341_CYAN, NULL, PROBE_SNIFF, [this]() {
  //  display_obj.clearScreen();
  //  this->drawStatusBar();
  //  wifi_scan_obj.StartScan(WIFI_SCAN_PROBE, ILI9341_CYAN);
  //});
  //addNodes(&wifiSnifferMenu, "Beacon Sniff", ILI9341_MAGENTA, NULL, BEACON_SNIFF, [this]() {
  //  display_obj.clearScreen();
  //  this->drawStatusBar();
  //  wifi_scan_obj.StartScan(WIFI_SCAN_AP, ILI9341_MAGENTA);
  //});
  //addNodes(&wifiSnifferMenu, "Deauth Sniff", ILI9341_RED, NULL, DEAUTH_SNIFF, [this]() {
  //  display_obj.clearScreen();
  //  this->drawStatusBar();
  //  wifi_scan_obj.StartScan(WIFI_SCAN_DEAUTH, ILI9341_RED);
  //});

  // Build WiFi scanner Menu
  wifiScannerMenu.parentMenu = &wifiMenu; // Main Menu is second menu parent
  addNodes(&wifiScannerMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(wifiScannerMenu.parentMenu);
  });
  //addNodes(&wifiScannerMenu, "Packet Monitor", ILI9341_BLUE, NULL, PACKET_MONITOR, [this]() {
  //  wifi_scan_obj.StartScan(WIFI_PACKET_MONITOR, ILI9341_BLUE);
  //});
  //addNodes(&wifiScannerMenu, "EAPOL/PMKID Scan", ILI9341_VIOLET, NULL, EAPOL, [this]() {
  //  wifi_scan_obj.StartScan(WIFI_SCAN_EAPOL, ILI9341_VIOLET);
  //});
  //addNodes(&wifiScannerMenu, "Detect Pwnagotchi", ILI9341_RED, NULL, PWNAGOTCHI, [this]() {
  //  display_obj.clearScreen();
  //  this->drawStatusBar();
  //  wifi_scan_obj.StartScan(WIFI_SCAN_PWN, ILI9341_RED);
  //});
  //addNodes(&wifiScannerMenu, "Detect Espressif", ILI9341_ORANGE, NULL, ESPRESSIF, [this]() {
  //  display_obj.clearScreen();
  //  this->drawStatusBar();
  //  wifi_scan_obj.StartScan(WIFI_SCAN_ESPRESSIF, ILI9341_ORANGE);
  //});

  // Build WiFi attack menu
  wifiAttackMenu.parentMenu = &wifiMenu; // Main Menu is second menu parent
  addNodes(&wifiAttackMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(wifiAttackMenu.parentMenu);
  });
  //addNodes(&wifiAttackMenu, "Beacon Spam List", ILI9341_RED, NULL, BEACON_LIST, [this]() {
  //  display_obj.clearScreen();
  //  this->drawStatusBar();
  //  wifi_scan_obj.StartScan(WIFI_ATTACK_BEACON_LIST, ILI9341_RED);
  //});
  //addNodes(&wifiAttackMenu, "Beacon Spam Random", ILI9341_ORANGE, NULL, BEACON_SPAM, [this]() {
  //  display_obj.clearScreen();
  //  this->drawStatusBar();
  //  wifi_scan_obj.StartScan(WIFI_ATTACK_BEACON_SPAM, ILI9341_ORANGE);
  //});
  //addNodes(&wifiAttackMenu, "Rick Roll Beacon", ILI9341_YELLOW, NULL, RICK_ROLL, [this]() {
  //  display_obj.clearScreen();
  //  this->drawStatusBar();
  //  wifi_scan_obj.StartScan(WIFI_ATTACK_RICK_ROLL, ILI9341_YELLOW);
  //});

  // Build WiFi General menu
  wifiGeneralMenu.parentMenu = &wifiMenu;
  addNodes(&wifiGeneralMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(wifiGeneralMenu.parentMenu);
  });
  //addNodes(&wifiGeneralMenu, "Join WiFi", ILI9341_DARKCYAN, NULL, JOIN_WIFI, [this](){
  //  display_obj.clearScreen(); 
  //  wifi_scan_obj.currentScanMode = LV_JOIN_WIFI; 
  //  wifi_scan_obj.StartScan(LV_JOIN_WIFI, ILI9341_YELLOW); 
  //  joinWiFiGFX();
  //});
  addNodes(&wifiGeneralMenu, "Shutdown WiFi", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&shutdownWiFiMenu);
    //wifi_scan_obj.RunShutdownWiFi();
  });
  addNodes(&wifiGeneralMenu, "Generate SSIDs", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&generateSSIDsMenu);
    //wifi_scan_obj.RunGenerateSSIDs();
  });
  //addNodes(&wifiGeneralMenu, "Add SSID", ILI9341_NAVY, NULL, KEYBOARD_ICO, [this](){
  //  display_obj.clearScreen(); 
    //wifi_scan_obj.currentScanMode = LV_ADD_SSID; 
  //  wifi_scan_obj.StartScan(LV_ADD_SSID, ILI9341_YELLOW); 
  //  addSSIDGFX();
  //});
  addNodes(&wifiGeneralMenu, "Clear SSIDs", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&clearSSIDsMenu);
    //wifi_scan_obj.RunClearSSIDs();
  });

  // Build shutdown wifi menu
  shutdownWiFiMenu.parentMenu = &wifiGeneralMenu;
  addNodes(&shutdownWiFiMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(shutdownWiFiMenu.parentMenu);
  });

  // Build generate ssids menu
  generateSSIDsMenu.parentMenu = &wifiGeneralMenu;
  addNodes(&generateSSIDsMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(generateSSIDsMenu.parentMenu);
  });

  // Build clear ssids menu
  clearSSIDsMenu.parentMenu = &wifiGeneralMenu;
  addNodes(&clearSSIDsMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(clearSSIDsMenu.parentMenu);
  });


  // Build Bluetooth Menu
  bluetoothMenu.parentMenu = &mainMenu; // Second Menu is third menu parent
  addNodes(&bluetoothMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(bluetoothMenu.parentMenu);
  });
  addNodes(&bluetoothMenu, "Sniffers", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&bluetoothSnifferMenu);
  });
  addNodes(&bluetoothMenu, "Scanners", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&bluetoothScannerMenu);
  });
  addNodes(&bluetoothMenu, "General", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&bluetoothGeneralMenu);
  });

  // Build bluetooth sniffer Menu
  bluetoothSnifferMenu.parentMenu = &bluetoothMenu; // Second Menu is third menu parent
  addNodes(&bluetoothSnifferMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(bluetoothSnifferMenu.parentMenu);
  });
  //addNodes(&bluetoothSnifferMenu, "Bluetooth Sniffer", ILI9341_GREEN, NULL, BLUETOOTH_SNIFF, [this]() {
  //  display_obj.clearScreen();
  //  this->drawStatusBar();
  //  wifi_scan_obj.StartScan(BT_SCAN_ALL, ILI9341_GREEN);
  //});

  // Build bluetooth scanner Menu
  bluetoothScannerMenu.parentMenu = &bluetoothMenu; // Second Menu is third menu parent
  addNodes(&bluetoothScannerMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(bluetoothScannerMenu.parentMenu);
  });
  //addNodes(&bluetoothScannerMenu, "Detect Card Skimmers", ILI9341_MAGENTA, NULL, CC_SKIMMERS, [this]() {
  //  display_obj.clearScreen();
  //  this->drawStatusBar();
  //  wifi_scan_obj.StartScan(BT_SCAN_SKIMMERS, ILI9341_MAGENTA);
  //});

  // Build bluetooth general menu
  bluetoothGeneralMenu.parentMenu = &bluetoothMenu;
  addNodes(&bluetoothGeneralMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(bluetoothGeneralMenu.parentMenu);
  });
  addNodes(&bluetoothGeneralMenu, "Shutdown BLE", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(&shutdownBLEMenu);
    //wifi_scan_obj.RunShutdownBLE();
  });

  // Build shutdown BLE menu
  shutdownBLEMenu.parentMenu = &bluetoothGeneralMenu;
  addNodes(&shutdownBLEMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(shutdownBLEMenu.parentMenu);
  });

  // General apps menu
  generalMenu.parentMenu = &mainMenu;
  addNodes(&generalMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    //display_obj.draw_tft = false;
    changeMenu(generalMenu.parentMenu);
  });
  //addNodes(&generalMenu, "Draw", ILI9341_WHITE, NULL, DRAW, [this]() {
  //  display_obj.clearScreen();
  //  display_obj.setupDraw();
  //  display_obj.draw_tft = true;
  //});

  // Device menu
  deviceMenu.parentMenu = &mainMenu;
  addNodes(&deviceMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(deviceMenu.parentMenu);
  });
  //addNodes(&deviceMenu, "Update Firmware", ILI9341_ORANGE, NULL, UPDATE, [this](){wifi_scan_obj.currentScanMode = OTA_UPDATE; changeMenu(&updateMenu); web_obj.setupOTAupdate();});
  addNodes(&deviceMenu, "Update Firmware", ILI9341_WHITE, NULL, 0, [this]() {
    //wifi_scan_obj.currentScanMode = OTA_UPDATE;
    changeMenu(&whichUpdateMenu);
  });
  addNodes(&deviceMenu, "Device Info", ILI9341_WHITE, NULL, 0, [this]() {
    //wifi_scan_obj.currentScanMode = SHOW_INFO;
    changeMenu(&infoMenu);
    //wifi_scan_obj.RunInfo();
  });
 
  // Select update
  whichUpdateMenu.parentMenu = &deviceMenu;
  addNodes(&whichUpdateMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(whichUpdateMenu.parentMenu);
  });
  addNodes(&whichUpdateMenu, "Web Update", ILI9341_WHITE, NULL, 0, [this]() {
    //wifi_scan_obj.currentScanMode = OTA_UPDATE;
    changeMenu(&updateMenu);
    //web_obj.setupOTAupdate();
  });
  //if (sd_obj.supported) addNodes(&whichUpdateMenu, "SD Update", ILI9341_MAGENTA, NULL, SD_UPDATE, [this]() {
    //wifi_scan_obj.currentScanMode = OTA_UPDATE;
  //  changeMenu(&confirmMenu);
  //});

  // Confirm SD update menu
  confirmMenu.parentMenu = &whichUpdateMenu;
  addNodes(&confirmMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    changeMenu(confirmMenu.parentMenu);
  });
  //addNodes(&confirmMenu, "Yes", ILI9341_ORANGE, NULL, UPDATE, [this](){wifi_scan_obj.currentScanMode = OTA_UPDATE; changeMenu(&updateMenu); sd_obj.runUpdate();});
  addNodes(&confirmMenu, "Yes", ILI9341_WHITE, NULL, 0, [this]() {
    //wifi_scan_obj.currentScanMode = OTA_UPDATE;
    changeMenu(&failedUpdateMenu);
    //sd_obj.runUpdate();
  });

  // Web Update
  //updateMenu.parentMenu = &deviceMenu;
  //addNodes(&updateMenu, "Back", ILI9341_LIGHTGREY, NULL, 0, [this]() {
  //  wifi_scan_obj.currentScanMode = WIFI_SCAN_OFF;
  //  changeMenu(updateMenu.parentMenu);
  //  WiFi.softAPdisconnect(true);
  //  web_obj.shutdownServer();
  //});
  //addNodes(&updateMenu, "Back", ILI9341_LIGHTGREY, NULL, 0, [this](){wifi_scan_obj.currentScanMode = WIFI_SCAN_OFF; changeMenu(updateMenu.parentMenu);});

  // Failed update menu
  failedUpdateMenu.parentMenu = &whichUpdateMenu;
  addNodes(&failedUpdateMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    //wifi_scan_obj.currentScanMode = WIFI_SCAN_OFF;
    changeMenu(failedUpdateMenu.parentMenu);
  });

  // Device info menu
  infoMenu.parentMenu = &deviceMenu;
  addNodes(&infoMenu, "Back", ILI9341_WHITE, NULL, 0, [this]() {
    //wifi_scan_obj.currentScanMode = WIFI_SCAN_OFF;
    changeMenu(infoMenu.parentMenu);
  });

  // Set the current menu to the mainMenu
  changeMenu(&mainMenu);

  this->initTime = millis();
}

// Function to change menu
void MenuFunctions::changeMenu(Menu * menu)
{
  //display_obj.initScrollValues();
  //display_obj.setupScrollArea(TOP_FIXED_AREA, BOT_FIXED_AREA);
  //tft.init();
  current_menu = menu;

  buildButtons(menu);

  //current_menu->selected = 0;

  tft.setCursor(0, 0);

  displayCurrentMenu();
}

// Function to show all MenuNodes in a Menu
void MenuFunctions::showMenuList(Menu * menu, int layer)
{
  // Iterate through all of the menu nodes in the menu
  for (uint8_t i = 0; i < menu->list->size(); i++)
  {
    // Depending on layer, indent
    for (uint8_t x = 0; x < layer * 4; x++)
      Serial.print(" ");
    Serial.print("Node: ");
    Serial.println(menu->list->get(i).name);
  }
  Serial.println();
}


// Function to add MenuNodes to a menu
void MenuFunctions::addNodes(Menu * menu, String name, uint16_t color, Menu * child, int place, std::function<void()> callable)
{
  //TFT_eSPI_Button new_button;
  menu->list->add(MenuNode{name, color, place, 0, callable});
}

void MenuFunctions::buildButtons(Menu * menu)
{
  Serial.println("Bulding buttons...");
  /*if (menu->list != NULL)
  {
    //for (int i = 0; i < sizeof(key); i++)
    //  key[i] = NULL;
    for (uint8_t i = 0; i < menu->list->size(); i++)
    {
      TFT_eSPI_Button new_button;
      char buf[menu->list->get(i).name.length() + 1] = {};
      menu->list->get(i).name.toCharArray(buf, menu->list->get(i).name.length() + 1);
      key[i].initButton(tft,
                                    KEY_X + 0 * (KEY_W + KEY_SPACING_X),
                                    KEY_Y + i * (KEY_H + KEY_SPACING_Y), // x, y, w, h, outline, fill, text
                                    KEY_W,
                                    KEY_H,
                                    ILI9341_BLACK, // Outline
                                    ILI9341_BLACK, // Fill
                                    menu->list->get(i).color, // Text
                                    buf,
                                    KEY_TEXTSIZE);

      key[i].setLabelDatum(BUTTON_PADDING - (KEY_W / 2), 2, ML_DATUM);
    }
  }*/
}


void MenuFunctions::displayCurrentMenu()
{
  Serial.println(F("Displaying current menu..."));
  clearScreen();
  //tft.setTextColor(ILI9341_LIGHTGREY, ILI9341_DARKGREY);
  //this->drawStatusBar();
  if (current_menu->list != NULL)
  {
    //tft.setFreeFont(MENU_FONT);
    for (uint8_t i = 0; i < current_menu->list->size(); i++)
    {
      //display_obj.key[i].drawButton2(current_menu->list->get(i).name);
      //display_obj.key[i].drawButton(ML_DATUM, BUTTON_PADDING, current_menu->list->get(i).name);
      //display_obj.key[i].drawButton(true);
      //key[i].drawButton(false, current_menu->list->get(i).name);

      tft.setCursor(0, i * KEY_H);

      if (current_menu->selected == i)
        tft.print("> " + current_menu->list->get(i).name);
      else
        tft.print("  " + current_menu->list->get(i).name);

      //if (current_menu->list->get(i).name != "Back")
      //  tft.drawXBitmap(0,
      //                              KEY_Y + i * (KEY_H + KEY_SPACING_Y) - (ICON_H / 2),
      //                              menu_icons[current_menu->list->get(i).icon],
      //                              ICON_W,
      //                              ICON_H,
      //                              ILI9341_BLACK,
      //                              current_menu->list->get(i).color);
    }
    //tft.setFreeFont(NULL);
  }
}

void MenuFunctions::clearScreen() {
  tft.fillScreen(ILI9341_BLACK);
}
