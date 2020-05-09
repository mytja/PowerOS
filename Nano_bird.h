#define FLAP_BUTTON  4
#define GAME_SPEED 50

// Initialise the display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SPRITE_HEIGHT   8
#define SPRITE_WIDTH    8

int game_state = 1; // 0 = game over screen, 1 = in game
int score = 0; // current game score
int high_score = 0; // highest score since the nano was reset
int bird_x = (int)display.width() / 4; // birds x position (along) - initialised to 1/4 the way along the screen
int bird_y; // birds y position (down)
int momentum = 0; // how much force is pulling the bird down
int wall_x[2]; // an array to hold the walls x positions
int wall_y[2]; // an array to hold the walls y positions
int wall_gap = 30; // size of the wall wall_gap in pixels
int wall_width = 10; // width of the wall in pixels

void startup_nanoBird(){
  display.clearDisplay();
  pinMode(FLAP_BUTTON, OUTPUT);
  randomSeed(analogRead(0));
}

void screenWipe(int speed) {

  // progressivly fill screen with white
  for (int i = 0; i < display.height(); i += speed) {
    display.fillRect(0, i, display.width(), speed, WHITE);
    display.display();
  }

  // progressively fill the screen with black
  for (int i = 0; i < display.height(); i += speed) {
    display.fillRect(0, i, display.width(), speed, BLACK);
    display.display();
  }

}

/**
 * displays txt at x,y coordinates
 */
void textAt(int x, int y, String txt) {
  display.setCursor(x, y);
  display.print(txt);
}

/**
 * displays text centered on the line
 */
void textAtCenter(int y, String txt) {
  textAt(display.width() / 2 - txt.length() * 3, y, txt);
}

/**
 * displays outlined text centered on the line
 */
void outlineTextAtCenter(int y, String txt) {
  int x = display.width() / 2 - txt.length() * 3;

  display.setTextColor(WHITE);
  textAt(x - 1, y, txt);
  textAt(x + 1, y, txt);
  textAt(x, y - 1, txt);
  textAt(x, y + 1, txt);

  display.setTextColor(BLACK);
  textAt(x, y, txt);
  display.setTextColor(WHITE);

}

/**
 * displays bold text centered on the line
 */
void boldTextAtCenter(int y, String txt) {
  int x = display.width() / 2 - txt.length() * 3;

  textAt(x, y, txt);
  textAt(x + 1, y, txt);

}
