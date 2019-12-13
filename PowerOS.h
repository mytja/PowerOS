#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "PowerLib.h"
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);
#include <Wire.h>
#define BATTERY_MODE_SOLID 1
#define CHARGE_AREA_START_X     20
#define CHARGE_AREA_START_Y     18
#define CHARGE_AREA_WIDTH       83
#define CHARGE_AREA_HEIGHT      28
#define YELLOW 0xFFE0
#define BLUE 0x001F


int game = 1;
int cursor = 1;
int led = 6;


void showBatteryLevel(uint8_t percent)
{
    uint8_t width;

    if (percent > 100)
        percent = 100;

    display.clearDisplay();
    display.drawBitmap(0, 0, battery_bitmap, 128, 64, WHITE);

    if (BATTERY_MODE_SOLID)
    {
        width = (percent * CHARGE_AREA_WIDTH) / 100;
        display.drawRect(CHARGE_AREA_START_X, CHARGE_AREA_START_Y, width, CHARGE_AREA_HEIGHT, WHITE);
    } else {
        uint8_t bars;
        
        if (percent >= 66)
        {
            // Show three bars
            bars = 3;
        } else if (percent >= 33)
        {
            // Show two bars
            bars = 2;
        } else if (percent > 0)
        {
            // Show one bar
            bars = 1;
        } else {
            // Show nothing
            bars = 0;
        }

        uint8_t offset = CHARGE_AREA_START_X;
        for (uint8_t i = 0; i < bars; i++)
        {
            display.drawRect(offset, CHARGE_AREA_START_Y, 27, CHARGE_AREA_HEIGHT, WHITE);
            offset += 28;
        }
    }

    display.display();
}
int percent = 100;
int currentState = 0;

void main1(){
  display.clearDisplay();
  showBatteryLevel(percent);
    
  if (percent){
    percent--;
  }
  else{
    percent = 100;
  }
  delay(50);
  display.display();
  currentState = 1;
}

void startup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D); //or 0x3C
  display.clearDisplay(); //for Clearing the display
  display.drawBitmap(0, 0, poweros_logo, 32, 64, BLUE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.setTextSize(3);
  display.setTextColor(YELLOW);
  display.setCursor(40, 32);
  display.print("PowerOS");
  display.setTextSize(1);
  
  display.setCursor(40, 50);
  display.print("Loading");
  display.display();
  currentState = 0;
  delay(3000);
  main1();
  
}

void main2(){
  display.clearDisplay();
  display.drawBitmap(0, 0, poweros_logo, 32, 64, BLUE);
  display.setTextSize(3);
  display.setTextColor(YELLOW);
  display.setCursor(40, 32);
  display.print("PGames");
  display.display();
  currentState = 2;
}

void main3(){
  display.clearDisplay();
  display.drawBitmap(0, 0, poweros_logo, 32, 64, BLUE);
  display.setTextSize(3);
  display.setTextColor(YELLOW);
  display.setCursor(40, 32);
  display.print("ABOUT");
  display.display();
  currentState = 3;
}

void main4(){
  display.clearDisplay();
  display.drawBitmap(0, 0, poweros_logo, 64, 32, BLUE);
  display.setTextSize(1);
  display.setTextColor(YELLOW);
  display.setCursor(64, 32);
  display.print("FLASHLIGHT");
  display.display();
  display.setCursor(110, 46);
  if (digitalRead(led)==HIGH){
    display.print("ON");
  }
  else{
    display.print("OFF");
  }
  currentState = 4;
}

void main5(){
  display.clearDisplay();
  display.drawBitmap(0, 0, poweros_logo, 96, 32, BLUE);
  display.setTextSize(1);
  display.setTextColor(YELLOW);
  display.setCursor(64, 46);
  display.print("SETTINGS");
  display.display();
  currentState = 5;
}

void pgames(){
  display.setTextSize(3);
  display.setTextColor(BLUE);
  display.setCursor(64, 10);
  display.print("Welcome to PGames Game Selector!");
  display.setTextColor(YELLOW);
  display.setTextSize(1);
  display.setCursor(64, 20);
  display.print("Game1");
  display.display();
  currentState = 7;
}

void about(){
  display.clearDisplay();
  display.drawBitmap(0, 0, poweros_logo, 64, 32, BLUE);
  display.setTextSize(1);
  display.setTextColor(YELLOW);
  display.setCursor(64, 0);
  display.print("copyright MyTja");
  display.setCursor(0, 35);
  display.print("Language: C");
  display.setCursor(0, 43);
  display.print("version Alpha 0.1");
  display.setCursor(0, 50);
  display.print("www.mytja.tk");
  display.display();
  currentState = 8;
}

void psettings(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLUE);
  display.setCursor(0, 0);
  display.print("PSettings");
  display.setTextColor(YELLOW);
  display.setCursor(0, 10);
  display.print("Language: English (UK)");
  display.setCursor(0, 20);
  display.print("License: Advanced");
  display.setCursor(0, 30);
  display.print("Wireless charging: OFF");
  currentState = 10;
}