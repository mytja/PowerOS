// Adafruit SSD1306 - Version: Latest #include <Adafruit_SSD1306.h>#include <splash.h>#include "PowerOS.h"int left_button = 1;int right_button = 2;int ok_button = 3;int cancel_button = 4;void setup() {  startup();}void loop() {  if (digitalRead(left_button) == HIGH){    if (currentState==3){      main2();      delay(500);    }    else if (currentState==2){      main1();      delay(500);    }    else if (currentState==4){      main3();      delay(500);    }    else if (currentState==5){      main4();      delay(500);    }    else if (currentState==7){      game = game-1;    }  }  if (digitalRead(ok_button) == HIGH){    if (currentState==2){      pgames();      delay(500);    }    else if (currentState==3){      about();      delay(500);    }    else if (currentState==5){      psettings();      delay(500);    }    else if (currentState==7){      if (game==1){        //game-mytja.game1();      }      else if (game==2){        //game-mytja.TestGame();      }    }  }  if (digitalRead(right_button) == HIGH){    if (currentState==1){      main2();      delay(500);    }    else if (currentState==2){      main3();      delay(500);    }    else if (currentState==3){      main4();      delay(500);    }    else if (currentState==4){      main5();      delay(500);    }    else if (currentState==7){      game = game+1;    }  }  if (digitalRead(cancel_button) == HIGH){    if (currentState==7){      main2();      delay(500);    }    else if (currentState==8){      main3();      delay(500);    }    else if (currentState==10){      main5();      delay(500);    }  }}