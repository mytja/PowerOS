#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "PowerLib.h"
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);
#include <Wire.h>
#include <SPI.h>
#include "Pong.h"
#include "Nano_bird.h"
#include "nanoBird_img.h"
#include <DallasTemperature.h>
#include <OneWire.h>

const int Temp1 = 9;

OneWire temp1(Temp1);
DallasTemperature sensors(&temp1);

byte analogBattery = analogRead(A1);
int percent = (analogBattery/255)*100;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int year;
int month;
int day;
int hour;
int min;
int sec;
char dayofweek;

char versionOfPowerOS = "1.1";  // This string is not in use yet

int state = 1;
int game = 1;
int cursor = 1;
int led = 9;
int currentState = 0;
int timer;

void wakeUp() {
  timer = 0;
}

void main0(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(hour);
  display.setCursor(30, 0);
  display.print(":");
  display.setCursor(40, 0);
  display.print(min);
  display.setTextSize(1);
  display.setCursor(20, 16);
  display.print(dayofweek);
  display.setCursor(20, 24);
  display.print(day);
  display.setCursor(35, 24);
  display.print(month);
  display.setCursor(50, 24);
  display.print(year);
  display.display();
  currentState = 0;
}

void main1(){
  analogBattery = analogRead(A1);
  percent = (analogBattery / 255.0) * 100;
  Serial.println(percent);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print("Battery");
  display.display();
  currentState = 1;
}

void startup(){
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //or 0x3D
  display.clearDisplay(); //for Clearing the display
  display.drawBitmap(0, 0, poweros_logo, 16, 32, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 10);
  display.print("PowerOS");
  display.setTextSize(1);
  
  display.setCursor(40, 50);
  display.print("Loading");
  display.display();
  currentState = -1;
  delay(3000);
  main0();
  
}

void main2(){
  display.clearDisplay();
  display.drawBitmap(0, 0, poweros_logo, 16, 32, WHITE);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20, 5);
  display.print("PGames");
  display.display();
  currentState = 2;
}

void main3(){
  display.clearDisplay();
  display.drawBitmap(0, 0, poweros_logo, 16, 32, WHITE);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20, 5);
  display.print("ABOUT");
  display.display();
  currentState = 3;
}

void main4(){
  display.clearDisplay();
  display.drawBitmap(0, 0, poweros_logo, 16, 32, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 0);
  display.print("FLASHLIGHT");
  display.setCursor(20, 8);
  if (digitalRead(led)==HIGH){
    display.print("ON");
  }
  else{
    display.print("OFF");
  }
  display.display();
  currentState = 4;
}

void main5(){
  display.clearDisplay();
  display.drawBitmap(0, 0, poweros_logo, 16, 32, WHITE);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 8);
  display.print("SETTINGS");
  display.display();
  currentState = 5;
}

void main6(){
  display.clearDisplay();
  display.drawBitmap(0, 0, poweros_logo, 16, 32, WHITE);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 0);
  display.print("PTemp");
  display.setTextSize(1);
  display.setCursor(20, 16);
  display.print("Temp of battery");
  display.setCursor(20, 24);
  display.print(sensors.getTempCByIndex(0));
  display.display();
  currentState = 6;
}

void pgames(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("PGames Game Selector");
  display.setTextSize(1);
  display.setCursor(0, 8);
  display.print("Pong Multiplayer");
  display.setCursor(0, 16);
  display.print("Nano bird");
  display.setCursor(0, 24);
  display.print("Game1");
  display.display();
  currentState = 7;
}

void about(){
  display.clearDisplay();
  display.drawBitmap(0, 0, poweros_logo, 16, 32, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 0);
  display.print("c MyTja");
  display.setCursor(20, 8);
  display.print("Arduino");
  display.setCursor(20, 16);
  display.print("Guinea 1.1.2");
  display.setCursor(20, 24);
  display.print("www.mytja.tk");
  display.display();
  currentState = 8;
}

void psettings(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("PSettings");
  display.setCursor(0, 8);
  display.print("Language:English (UK)");
  display.setCursor(0, 16);
  display.print("License: Open-source");
  display.setCursor(0, 24);
  display.print("Wireless charging:OFF");
  display.display();
  currentState = 10;
}

void planguage(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("English (UK)");
  display.display();
  currentState = 11;
}

void wirelessch(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Wireless charging");
  display.setCursor(0, 16);
  display.print("OFF");
  display.setCursor(0, 24);
  display.print("ON");
  display.display();
  currentState = 12;
}

void pbattery(){
  analogBattery = analogRead(A1);
  percent = (analogBattery / 255.0) * 100;
  Serial.println(percent);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Battery");
  display.setCursor(0, 8);
  display.print("Charged:");
  display.setCursor(55, 8);
  display.print(percent);
  display.setCursor(100, 8);
  display.print("%");
  display.setCursor(0, 16);
  display.print("Battery life: Cannot measure");
  display.display();
  currentState = 13;
}

void plicense(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("License");
  display.setCursor(0, 8);
  display.print("Open-source");
  display.display();
  currentState = 14;
}

void overVoltage(){
  currentState = 15;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Overvoltage!");
  display.setCursor(0, 8);
  display.print("Turn off your device!");
  display.setCursor(0, 24);
  display.print("Thank you!");
  display.display();
}

void underVoltage(){
  currentState = 16;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Undervoltage!");
  display.setCursor(0, 8);
  display.print("Turn your device off!");
  display.setCursor(0, 24);
  display.print("Thank you!");
  display.display();
}
