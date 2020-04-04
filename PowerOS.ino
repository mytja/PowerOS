// Adafruit SSD1306 - Version: Latest 
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include "PowerOS.h"
#include <SPI.h>
#include <RTClib.h>

RTC_DS1307 rtc;

int protection = 1;
int gameChosen = 0;
int left_button = 2;
int right_button = 3;
int ok_button = 4;
int cancel_button = 5;
int down_button = 6;
int up_button = 7;
int WCharge = 8;

const int delayint = 200;

void setup() {
  startup();
  pinMode(led, OUTPUT);
  pinMode(WCharge, OUTPUT);
  pinMode(left_button, OUTPUT);
  pinMode(right_button, OUTPUT);
  pinMode(ok_button, OUTPUT);
  pinMode(cancel_button, OUTPUT);
  pinMode(up_button, OUTPUT);
  pinMode(down_button, OUTPUT);
}

void loop() {
  analogBattery = analogRead(A1);
  percent = (analogBattery / 255.0) * 100;
  if (gameChosen == 1){
    if (digitalRead(left_button) == HIGH){
      controllerValue1 = controllerValue1 - 15;
    }
    else if (digitalRead(down_button) == HIGH){
      controllerValue1 = controllerValue1 + 15;
    }
    else if (digitalRead(up_button) == HIGH){
      controllerValue2 = controllerValue2 - 15;
    }
    else if (digitalRead(right_button) == HIGH){
      controllerValue2 = controllerValue2 + 15;
    }

    paddlePositionPlayer1 = controllerValue1 * (46.0 / 1023.0);
    paddlePositionPlayer2 = controllerValue2 * (46.0 / 1023.0);

    // Set button state
    buttonState = digitalRead(ok_button);

    if (buttonState == HIGH && gameState == 0) {
      gameState = 1;
      delay(100);
    } else if (buttonState == HIGH && (gameState == 1 || gameState == 2)) {
      gameState = 0;
      scorePlayer1 = 0;
      scorePlayer2 = 0;
      ballX = 128/2;
      ballY = 32/2;
      delay(100);
    }
  
    if (gameState == 0) {
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(40, 18);
      display.println("PONG");
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(32, 38);
      display.println("press start");
      display.display();
      display.clearDisplay();      
    }

    if (gameState == 1) {
    drawField(scorePlayer1, scorePlayer2);
    
    collisionControl();
    drawBall();
    
    display.display();
    display.clearDisplay();
  }

    if (gameState == 2) {
      drawField(scorePlayer1, scorePlayer2);

      display.setTextSize(1);
      display.setTextColor(WHITE);
    
      if (scorePlayer1 == 2) {
        display.setCursor(15, 30);
      } else if (scorePlayer2 == 2) {
        display.setCursor(77, 30);
      }
      display.println("winner!");
      display.display();
      display.clearDisplay();   
    }
  }
  
  DateTime now = rtc.now();
  year = now.year();
  month = now.month();
  day = now.day();
  dayofweek = daysOfTheWeek[now.dayOfTheWeek()];
  hour = now.hour();
  min = now.minute();
  sec = now.second();
  
  if (digitalRead(left_button) == HIGH){
    protection = 1;
    if (currentState==1){
      main0();
      delay(delayint);
    }
    else if (currentState==3){
      main2();
      delay(delayint);
    }
    else if (currentState==2){
      main1();
      delay(delayint);
    }
    else if (currentState==4){
      main3();
      delay(delayint);
    }
    else if (currentState==5){
      main4();
      delay(delayint);
    }
    else if (currentState==7){
      game = game-1;
      delay(delayint);
    }
    else if (currentState==10){
      state = state-1;
      delay(delayint);
    }
    else if (currentState==12){
      state = state-1;
      delay(delayint);
    }
    if (protection == 1){
      if (analogBattery > 215){
        overVoltage();
        Serial.println("Overvoltage protection released!");
        protection = 0;
        delay(delayint);
      }
      else if (analogBattery < 130){
        underVoltage();
        Serial.println("Undervoltage protection released!");
        protection = 0;
        delay(delayint);
      }
    }
  }
  else if (digitalRead(ok_button) == HIGH){
    protection = 1;
    if (currentState==2){
      pgames();
      delay(delayint);
    }
    else if (currentState==3){
      about();
      delay(delayint);
    }
    else if (currentState==5){
      psettings();
      delay(delayint);
    }
    else if (currentState==7){
      if (game==1){
        mytja_pong_startup();
        currentState = 99;
        delay(delayint);
        gameChosen = 1;
      }
      else if (game==2){
        //mytja_TestGame();
        //currentState = 99;
      }
    }
    else if (currentState==10){
      if (state==1){
        planguage();
        delay(delayint);
      }
      else if (state==2){
        plicense();
        delay(delayint);
      }
      else if (state==3){
        wirelessch();
        state = 1;
        delay(delayint);
      }
    }
    else if (currentState==14){
      if (state==1){
        
      }
    }
    else if (currentState==12){
      if (state==1){
        digitalWrite(WCharge, LOW);
        delay(delayint);
      }
      else if (state==2){
        digitalWrite(WCharge, HIGH);
        delay(delayint);
      }
    }
    else if (currentState==1){
      pbattery();
      delay(delayint);
    }
  }
  else if (digitalRead(right_button) == HIGH){
    protection = 1;
    if (currentState==0){
      main1();
      delay(delayint);
    }
    else if (currentState==1){
      main2();
      delay(delayint);
    }
    else if (currentState==2){
      main3();
      delay(delayint);
    }
    else if (currentState==3){
      main4();
      delay(delayint);
    }
    else if (currentState==4){
      main5();
      delay(delayint);
    }
    else if (currentState==7){
      game = game+1;
      delay(delayint);
    }
    else if (currentState==10){
      state = state+1;
      delay(delayint);
    }
    else if (currentState==12){
      state = state+1;
      delay(delayint);
    }
  }
  else if (digitalRead(cancel_button) == HIGH){
    protection = 1;
    if (currentState==7){
      main2();
      delay(delayint);
    }
    else if (currentState==8){
      main3();
      delay(delayint);
    }
    else if (currentState==10){
      main5();
      state = 1;
      delay(delayint);
    }
    else if (currentState==12){
      psettings();
      state = 1;
      delay(delayint);
    }
    else if (currentState==11){
      psettings();
      delay(delayint);
    }
    else if (currentState==13){
      main1();
      delay(delayint);
    }
    else if (currentState==14){
      psettings();
      delay(delayint);
    }
    else if (gameChosen==1){
      pgames();
      gameChosen = 0;
      delay(delayint);
    }
    else if (currentState==15){
      startup();
      delay(delayint);
    }
    else if (currentState==16){
      startup();
      delay(delayint);
    }
  }
  else if (digitalRead(down_button) == HIGH){
    protection = 1;
    if (currentState==12){
      state = state + 1;
      delay(delayint);
    }
    else if (currentState==10){
      state = state + 1;
      delay(delayint);
    }
  }
  else if (digitalRead(up_button) == HIGH){
    protection = 1;
    if (currentState==12){
      state = state - 1;
      delay(delayint);
    }
    else if (currentState==10){
      state = state - 1;
      delay(delayint);
    }
  }
}
