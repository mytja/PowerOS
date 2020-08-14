// Adafruit SSD1306 - Version: Latest 
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include "PowerOS.h"
#include <SPI.h>
#include <RTClib.h>

RTC_DS1307 rtc;

int protection = 1;
int returnprot = 1;
int gameChosen = 0;
const int left_button = 2;
const int right_button = 3;
const int ok_button = 4;
const int cancel_button = 5;
const int down_button = 6;
const int up_button = 7;
const int WCharge = 8;

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
  sensors.begin();
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
  else if (gameChosen == 2){
    if (game_state == 0) {
      // in game
      display.clearDisplay();

    // If the flap button is currently pressed, reduce the downward force on the bird a bit.
    // Once this foce goes negative the bird goes up, otherwise it falls towards the ground
    // gaining speed
      if (digitalRead(FLAP_BUTTON) == HIGH) {
        momentum = -4;
      }

    // increase the downward force on the bird
      momentum += 1;

    // add the downward force to the bird position to determine it's new position
      bird_y += momentum;

    // make sure the bird doesn't fly off the top of the screen
      if (bird_y < 0 ) {
        bird_y = 0;
      }

    // make sure the bird doesn't fall off the bottom of the screen
    // give it a slight positive lift so it 'waddles' along the ground.
      if (bird_y > display.height() - SPRITE_HEIGHT) {
        bird_y = display.height() - SPRITE_HEIGHT;
        momentum = -2;
      }

      // display the bird
      // if the momentum on the bird is negative the bird is going up!
      if (momentum < 0) {

        // display the bird using a randomly picked flap animation frame
        if (random(2) == 0) {
          display.drawBitmap(bird_x, bird_y, wing_down_bmp, 16, 16, WHITE);
        }
        else {
          display.drawBitmap(bird_x, bird_y, wing_up_bmp, 16, 16, WHITE);
        }

      }
      else {

        // bird is currently falling, use wing up frame
        display.drawBitmap(bird_x, bird_y, wing_up_bmp, 16, 16, WHITE);

      }

      // now we draw the walls and see if the player has hit anything
      for (int i = 0 ; i < 2; i++) {

        // draw the top half of the wall
        display.fillRect(wall_x[i], 0, wall_width, wall_y[i], WHITE);

        // draw the bottom half of the wall
        display.fillRect(wall_x[i], wall_y[i] + wall_gap, wall_width, display.height() - wall_y[i] + wall_gap, WHITE);

        // if the wall has hit the edge of the screen
        // reset it back to the other side with a new gap position
        if (wall_x[i] < 0) {
          wall_y[i] = random(0, display.height() - wall_gap);
          wall_x[i] = display.width();
        }

        // if the bird has passed the wall, update the score
        if (wall_x[i] == bird_x) {
          score++;

          // highscore is whichever is bigger, the current high score or the current score
          high_score = max(score, high_score);
        }

        // if the bird is level with the wall and not level with the gap - game over!
        if (
          (bird_x + SPRITE_WIDTH > wall_x[i] && bird_x < wall_x[i] + wall_width) // level with wall
          &&
          (bird_y < wall_y[i] || bird_y + SPRITE_HEIGHT > wall_y[i] + wall_gap) // not level with the gap
        ) {
        
          // display the crash and pause 1/2 a second
          display.display();
          delay(500);

          // switch to game over state
          game_state = 1; 

        }

        // move the wall left 4 pixels
        wall_x[i] -= 4;
      }

      // display the current score
      boldTextAtCenter(0, (String)score);

      // now display everything to the user and wait a bit to keep things playable
      display.display();
      delay(GAME_SPEED);

    }
    else {

      // game over screen

      screenWipe(10);

      outlineTextAtCenter(1, "NANO BIRD");
    
      textAtCenter(display.height() / 2 - 8, "GAME OVER");
      textAtCenter(display.height() / 2, String(score));
    
      boldTextAtCenter(display.height() - 16, "HIGH SCORE");
      boldTextAtCenter(display.height()  - 8, String(high_score));

      display.display();

      // wait while the user stops pressing the button
      while (digitalRead(FLAP_BUTTON) == LOW);

      // setup a new game
      bird_y = display.height() / 2;
      momentum = -4;
      wall_x[0] = display.width() ;
      wall_y[0] = display.height() / 2 - wall_gap / 2;
      wall_x[1] = display.width() + display.width() / 2;
      wall_y[1] = display.height() / 2 - wall_gap / 1;
      score = 0;

      // wait until the user presses the button
      while (digitalRead(FLAP_BUTTON) == HIGH);

      // start a new game
      screenWipe(10);
      game_state = 0;
      
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
    protection = returnprot;
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
      main6();
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
    else if (currentState==6){
      main4();
      delay(delayint);
    }
  }
  else if (digitalRead(ok_button) == HIGH){
    protection = returnprot;
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
        startup_nanoBird();
        currentState = 99;
        delay(delayint);
        gameChosen = 2;
      }
      else if (game==3){
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
    protection = returnprot;
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
    else if (currentState==6){
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
    else if (currentState==4){
      sensors.requestTemperatures();
      main6();
      delay(delayint);
    }
  }
  else if (digitalRead(cancel_button) == HIGH){
    protection = returnprot;
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
    else if (gameChosen==1 || gameChosen==2){
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
    protection = returnprot;
    if (currentState==12){
      state = state + 1;
      delay(delayint);
    }
    else if (currentState==10){
      state = state + 1;
      delay(delayint);
    }
    else if (currentState==7){
      game = game + 1;
      delay(delayint);
    }
  }
  else if (digitalRead(up_button) == HIGH){
    protection = returnprot;
    if (currentState==12){
      state = state - 1;
      delay(delayint);
    }
    else if (currentState==10){
      state = state - 1;
      delay(delayint);
    }
    else if (currentState==7){
      game = game - 1;
      delay(delayint);
    }
  }
}
