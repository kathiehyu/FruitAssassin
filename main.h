#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

enum gba_state {
  INIT,
  WAIT_FOR_START,
  CONFIGURATION,
  WAIT_FOR_SELECTION,
  INIT_BOUNCE,
  STARTING,
  PLAY,
  DRAW_FRUIT,
  STRIKE,
  WIN,
  LOSE,
  WAIT_FOR_RESTART
};

struct Fruit {
    int row;
    int col;
    int size;
    int speedDown;
    int speedSide;
    int score;
    int sliced;
    const u16 *image;
} *cherryP, *eraseCherry, *bananaP, *eraseBanana, *mangoP, *eraseMango;

struct Onion {
    int row;
    int col;
    // int size;
    int speedDown;
    int speedSide;
    const u16 *image;
} *onionP, *eraseOnion;


struct State {
    enum gba_state state;
    struct Fruit fruit[3];
    struct Onion onions;
    int location;
    int strikeLocation;
    int strikeCol;
    int strikeRight;
    int strikeLeft;
    int time;
    int score;
    int sizeWidth;
    int sizeLength;
    int speed;
    char *title;
    int letterCount;
    int frameCount;
    int selectionArrowRow;
    int timeLimit;

    
    int bounceFrames;
    struct Letter *letters;
};

struct Letter {
	int row;
	int init_row;
	int col;
	int speed;
};

#endif
