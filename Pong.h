int buttonState = 0;               // HIGH = Pressed
int gameState = 0;                 // 0 = Home, 1 = Game, 2 = End

int controllerValue1 = 0;          // variable to store the value coming from the potentiometer
int controllerValue2 = 0;          // variable to store the value coming from the potentiometer

int paddlePositionPlayer1 = 0;
int paddlePositionPlayer2 = 0;  

int scorePlayer1 = 0;    
int scorePlayer2 = 0;

int ballX = 128/2;      
int ballY = 32/2;
int ballSpeedX = 2;
int ballSpeedY = 1;

void mytja_pong_startup() {
  display.clearDisplay();
}

void drawField(int score1, int score2) {
    display.fillRect(0, round(paddlePositionPlayer1), 2, 18, 1);
    display.fillRect(126, round(paddlePositionPlayer2), 2, 18, 1);
  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(55, 0);
    display.print(score1);
    display.print(":");
    display.print(score2);

    display.fillRect(63, 12, 1, 5, 1);
    display.fillRect(63, 22, 1, 5, 1);
    display.fillRect(63, 32, 1, 5, 1);
    display.fillRect(63, 42, 1, 5, 1);
    display.fillRect(63, 52, 1, 5, 1);
    display.fillRect(63, 62, 1, 5, 1);
}

void collisionControl() {
  //bounce from top and bottom
  if (ballY >= 32 - 2 || ballY <= 0) {
    ballSpeedY *= -1;
  } 

  //score points if ball hits wall behind player
  if (ballX >= 128 - 2 || ballX <= 0) {
    if (ballSpeedX > 0) {
      scorePlayer1++;
      ballX = 128 / 4;
    }
    if (ballSpeedX < 0) {
      scorePlayer2++;
      ballX = 128 / 4 * 3;
    }  
    if (scorePlayer1 == 2 || scorePlayer2 == 2) {
      gameState = 2;
    }
  }

  //bounce from player1
  if (ballX >= 0 && ballX <= 2 && ballSpeedX < 0) {
    if (ballY > round(paddlePositionPlayer1) - 2 && ballY < round(paddlePositionPlayer1) + 18) {
      ballSpeedX *= -1;
    }
  }
  //bounce from player2
  if (ballX >= 128-2-2 && ballX <= 128-2 && ballSpeedX > 0) {
    if (ballY > round(paddlePositionPlayer2) - 2 && ballY < round(paddlePositionPlayer2) + 18) {
      ballSpeedX *= -1;
    }

  }
}

void drawBall() {
  display.fillRect(ballX, ballY, 2, 2, 1);
  
  ballX += ballSpeedX;
  ballY += ballSpeedY;
}
