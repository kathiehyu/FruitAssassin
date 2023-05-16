#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "background1.h"
#include "cherry.h"
#include "banana.h"
#include "mango.h"
#include "onion.h"
#include "gameOver.h"
#include "win.h"

#include "gba.h"
/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

// int collision(struct Fruit *fruit, struct State cs);

int main(void) {
    /* TODO: */
    // Manipulate REG_DISPCNT here to set Mode 3. //
    REG_DISPCNT = MODE3 | BG2_ENABLE;

  // GETTING STATES
  struct State cs, ps, beforeStrike;
  // initialize everything to 0?


  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

    int leftBorder = 30;
    // change to largest size fruit
    int rightBorder = WIDTH - 45;

  // Load initial application state
  // cs.gameState = INIT;
  cs.state = INIT;
  cs.time = 0;
  int temp;

  // int frameCount = 0;
  // int letterCount = 0;
  // frameCount++;
  // UNUSED(letterCount);

  while (1) {
    // frame++;

    if (ps.state != STRIKE) {
        beforeStrike = ps;
    }
    ps = cs;
    cs.frameCount++;

    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw

    // calculating what to draw
    switch (cs.state) {

    case INIT:
        cherryP = &cs.fruit[0];
        bananaP = &cs.fruit[1];
        mangoP = &cs.fruit[2];
        onionP = &cs.onions;

        cherryP -> row = 0;
        cherryP -> col = randint(leftBorder, rightBorder);
        cherryP -> speedDown = 1;
        cherryP -> speedSide = randint(-1, 1);
        cherryP -> size = CHERRY_WIDTH;
        cherryP -> image = cherry;
        cherryP -> score = 2;
        cherryP -> sliced = 0;

        mangoP -> row = 0;
        mangoP -> col = randint(leftBorder, rightBorder);
        mangoP -> speedDown = 4;
        mangoP -> speedSide = randint(-2, 2);
        mangoP -> size = MANGO_WIDTH;
        mangoP -> image = mango;
        mangoP -> score = 4;
        mangoP -> sliced = 0;

        bananaP -> row = 0;
        bananaP -> col = randint(leftBorder, rightBorder);
        bananaP -> speedDown = 2;
        bananaP -> speedSide = randint(-1, 1);
        // bananaP -> size = BANANA_WIDTH;
        bananaP -> image = banana;
        bananaP -> score = 3;
        bananaP -> sliced = 0;

        onionP -> row = 0;
        onionP -> col = randint(leftBorder, rightBorder);
        onionP -> speedDown = 3;
        onionP -> speedSide = randint(-1, 1);
        // onionP -> size = 20;
        onionP -> image = onion;

        cs.location = 100;
        cs.fruit[0] = *cherryP;
        cs.fruit[1] = *bananaP;
        cs.fruit[2] = *mangoP;
        cs.onions = *onionP;

        cs.score = 0;
        cs.sizeWidth = 3;
        cs.sizeLength = 20;
        cs.speed = 3;
        cs.frameCount = 0;
        cs.letterCount = 0;
        cs.title = "FRUIT ASSASSIN";
        beforeStrike.score = 0;
        cs.selectionArrowRow = 53;
        // struct Letter *letter;

        for (int i = 0; i < 14; i++) {
            // struct Letter l = {75, 75, 74 + (i * 6), 1};
            // letter = &l;
            // cs.letters[i] = letter;
            (cs.letters[i]).row = 75;
            (cs.letters[i]).init_row = 75;
            (cs.letters[i]).col = 74 + (i * 7);
            (cs.letters[i]).speed = 1;
        }
        cs.bounceFrames = 16;

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            cs.state = INIT;
        }

        break;

    case WAIT_FOR_START:
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            cs.state = INIT;
        }
        if (cs.frameCount > cs.bounceFrames) {
            cs.letterCount++;
            cs.frameCount = 0;
            if (cs.letterCount > 13) {
                cs.letterCount = 0;
                cs.state = INIT_BOUNCE;
                break;
            }
        }
        if (cs.frameCount <= (cs.bounceFrames / 2)) {
            if (cs.frameCount % 2) {
                cs.letters[cs.letterCount].row -= (cs.letters[cs.letterCount]).speed;
                if (cs.letters[cs.letterCount].row < (((cs.bounceFrames) / 2) * (cs.letters[cs.letterCount]).speed)) {
                    cs.letters[cs.letterCount].row -= (((cs.letters[cs.letterCount]).speed) * 2);
                }
            }
        } else {
            if (cs.frameCount % 2) {
                cs.letters[cs.letterCount].row += (cs.letters[cs.letterCount]).speed;
                if (cs.letters[cs.letterCount].row > cs.letters[cs.letterCount].init_row) {
                    cs.letters[cs.letterCount].row = cs.letters[cs.letterCount].init_row;
                }   
            }
        }
        break;

    case CONFIGURATION:
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            cs.state = INIT;
        }
        break;

    case WAIT_FOR_SELECTION:
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            cs.state = INIT;
        }
        if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {
            cs.selectionArrowRow += 20;
            if (cs.selectionArrowRow > 93) {
                cs.selectionArrowRow = 53;
            }
        }
        if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {
            cs.selectionArrowRow -= 20;
            if (cs.selectionArrowRow < 53) {
                cs.selectionArrowRow = 93;
            }
        }

        break;


    case INIT_BOUNCE:
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            cs.state = INIT;
        }
        break;

    case STARTING:
        vBlankCounter = 0;
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            cs.state = INIT;
        }
        break;

    case PLAY:
        cherryP -> sliced = 0;
        bananaP -> sliced = 0;
        mangoP -> sliced = 0;
        cs.time = vBlankCounter / 60;
        // if (frames >= 60) {
        //     frames = 0;
        //     cs.time++;
        // }
        if (cs.time > cs.timeLimit) {
             cs.state = WIN;
             break;
        }
        if (KEY_DOWN(BUTTON_UP, BUTTONS)) {
            cs.location -= cs.speed;
            if (cs.location < 5) {
                cs.location = 5;
            }
        } else if (KEY_DOWN(BUTTON_DOWN, BUTTONS)) {
            cs.location += cs.speed;
            if (cs.location > 150) {
                cs.location = 150;
            }
        } else if ((KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons) | KEY_JUST_PRESSED(BUTTON_RIGHT, currentButtons, previousButtons))) {
            if (ps.state != STRIKE ){
                cs.strikeLocation = cs.location;
                cs.strikeLeft = leftBorder;
                cs.strikeRight = rightBorder;
                cs.state = STRIKE;
            }
        }
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            cs.state = INIT;
        }
    
        // state = ?
        break;

    case DRAW_FRUIT:


        if (((KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons)) | (KEY_JUST_PRESSED(BUTTON_RIGHT, currentButtons, previousButtons)))) {
            if (ps.state != STRIKE ){
                cs.strikeLocation = cs.location;
                cs.strikeLeft = leftBorder;
                cs.strikeRight = rightBorder;
                cs.state = STRIKE;
            }
        } else {
            if (cherryP) {
                cherryP -> row += cherryP -> speedDown;
                if (cherryP -> row > HEIGHT) {
                    cherryP -> row = 0 - CHERRY_HEIGHT;
                    cherryP -> col = randint(leftBorder, rightBorder);
                }

                cherryP -> col += cherryP -> speedSide;
                if ((cherryP -> col > rightBorder) | (cherryP -> col < leftBorder)) {
                    cherryP -> speedSide *= -1;
                }
            } else {
                cherryP = &cs.fruit[0];
                cherryP -> row = 0;
                cherryP -> col = randint(leftBorder, rightBorder);
                cherryP -> speedDown++;
                if (cherryP -> speedDown > 6) {
                    cherryP -> speedDown = 6;
                }
                cherryP -> speedSide = randint(-1, 1);
            }

            if (bananaP) {
                bananaP -> row += bananaP -> speedDown;
                if (bananaP -> row > HEIGHT) {
                    bananaP -> row = 0 - BANANA_HEIGHT;
                    bananaP -> col = randint(leftBorder, rightBorder);
                }
                bananaP -> col += bananaP -> speedSide;
                if ((bananaP -> col > rightBorder) | (bananaP -> col < leftBorder)) {
                    bananaP -> speedSide *= -1;
                }
            } else {
                bananaP = &cs.fruit[1];
                bananaP -> row = 0;
                bananaP -> col = randint(leftBorder, rightBorder);
                bananaP -> speedDown++;
                if (bananaP -> speedDown > 7) {
                    bananaP -> speedDown = 7;
                }
                bananaP -> speedSide = randint(-1, 1);
            }

            if (mangoP) {
                mangoP -> row += mangoP -> speedDown;
                if (mangoP -> row > HEIGHT) {
                    mangoP -> row = 0 - MANGO_HEIGHT;
                    mangoP -> col = randint(leftBorder, rightBorder);
                }

                mangoP -> col += mangoP -> speedSide;
                if ((mangoP -> col > rightBorder) | (mangoP -> col < leftBorder)) {
                    mangoP -> speedSide *= -1;
                }
            } else {
                mangoP = &cs.fruit[2];
                mangoP -> row = 0;
                mangoP -> col = randint(leftBorder, rightBorder);
                mangoP -> speedDown++;
                if (mangoP -> speedDown > 6) {
                    mangoP -> speedDown = 6;
                }
                mangoP -> speedSide = randint(-2, 2);
            }

            onionP -> row += onionP -> speedDown;
            if (onionP -> row > HEIGHT) {
                onionP -> row = 0 - ONION_WIDTH;
                onionP -> col = randint(leftBorder, rightBorder);
            }

            onionP -> col += onionP -> speedSide;
            if ((onionP -> col > rightBorder) | (onionP -> col < leftBorder)) {
                onionP -> speedSide *= -1;
            }
        }
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            cs.state = INIT;
        }

        break;

    case STRIKE:
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            cs.state = INIT;
        }
        if (!cherryP) {

            // horizontal collision: left hit from left
        } else if ((
            // cherry collision
            ((((cs.strikeLeft + (cs.sizeLength)) > (cherryP -> col)) &
                    (cs.strikeLeft < ((cherryP -> col) + (CHERRY_WIDTH)))) &
                    // vertical collision: at bottom of knife
                    ((((cs.location + (cs.sizeWidth)) > (cherryP -> row)) &
                        ((cs.location + (cs.sizeWidth)) < ((cherryP -> row) + (CHERRY_WIDTH)))) |
                    // vertical collision: at top of knife
                    (((cs.location) > (cherryP -> row)) &
                        ((cs.location) < ((cherryP -> row) + (CHERRY_WIDTH)))))
                    ) |
            // right hit from right
            (
                (((cs.strikeRight) > (cherryP -> col)) &
                    (cs.strikeRight < ((cherryP -> col) + (cherryP -> size)))) &
                    // vertical collision: at bottom of knife
                    ((((cs.location + (cs.sizeWidth)) > (cherryP -> row)) &
                        ((cs.location + (cs.sizeWidth)) < ((cherryP -> row) + (CHERRY_WIDTH)))) |
                    // vertical collision: at top of knife
                    (((cs.location) > (cherryP -> row)) &
                        ((cs.location) < ((cherryP -> row) + (CHERRY_WIDTH)))))
                    ))

            ) {
            if (!(ps.fruit[0].sliced)) {
                cs.score += cherryP -> score;
                cherryP -> sliced = 1;
                cherryP = 0;
            }
        }
        if // banana collision
        (
            ((((cs.strikeLeft + (cs.sizeLength)) > (bananaP -> col)) &
                    (cs.strikeLeft < ((bananaP -> col) + (BANANA_WIDTH)))) &
                    // vertical collision: at bottom of knife
                    ((((cs.location + (cs.sizeWidth)) > (bananaP -> row)) &
                        ((cs.location + (cs.sizeWidth)) < ((bananaP -> row) + (BANANA_WIDTH)))) |
                    // vertical collision: at top of knife
                    (((cs.location) > (bananaP -> row)) &
                        ((cs.location) < ((bananaP -> row) + (BANANA_WIDTH)))))
                    ) |
            // right hit from right
            (
                (((cs.strikeRight) > (bananaP -> col)) &
                    (cs.strikeRight < ((bananaP -> col) + (BANANA_WIDTH)))) &
                    // vertical collision: at bottom of knife
                    ((((cs.location + (cs.sizeWidth)) > (bananaP -> row)) &
                        ((cs.location + (cs.sizeWidth)) < ((bananaP -> row) + (BANANA_WIDTH)))) |
                    // vertical collision: at top of knife
                    (((cs.location) > (bananaP -> row)) &
                        ((cs.location) < ((bananaP -> row) + (BANANA_WIDTH)))))
                    )
            ) {
            if (!(ps.fruit[1].sliced)) {
                cs.score += bananaP -> score;
                bananaP -> sliced = 1;
                bananaP = 0;
            }
        }
        if // mango collision
        (
            ((((cs.strikeLeft + (cs.sizeLength)) > (mangoP -> col)) &
                    (cs.strikeLeft < ((mangoP -> col) + (MANGO_WIDTH)))) &
                    // vertical collision: at bottom of knife
                    ((((cs.location + (cs.sizeWidth)) > (mangoP -> row)) &
                        ((cs.location + (cs.sizeWidth)) < ((mangoP -> row) + (MANGO_WIDTH)))) |
                    // vertical collision: at top of knife
                    (((cs.location) > (mangoP -> row)) &
                        ((cs.location) < ((mangoP -> row) + (MANGO_WIDTH)))))
                    ) |
            // right hit from right
            (
                (((cs.strikeRight) > (mangoP -> col)) &
                    (cs.strikeRight < ((mangoP -> col) + (MANGO_WIDTH)))) &
                    // vertical collision: at bottom of knife
                    ((((cs.location + (cs.sizeWidth)) > (mangoP -> row)) &
                        ((cs.location + (cs.sizeWidth)) < ((mangoP -> row) + (MANGO_WIDTH)))) |
                    // vertical collision: at top of knife
                    (((cs.location) > (mangoP -> row)) &
                        ((cs.location) < ((mangoP -> row) + (MANGO_WIDTH)))))
                    )
            ) {
            if (!(ps.fruit[2].sliced)) {
                cs.score += mangoP -> score;
                mangoP -> sliced = 1;
                mangoP = 0;
            }
        }

        // ONION COLLISION: END GAME
        if
        (
            ((((cs.strikeLeft + (cs.sizeLength)) > (onionP -> col)) &
                    (cs.strikeLeft < ((onionP -> col) + (ONION_WIDTH)))) &
                    // vertical collision: at bottom of knife
                    ((((cs.location + (cs.sizeWidth)) > (onionP -> row)) &
                        ((cs.location + (cs.sizeWidth)) < ((onionP -> row) + (ONION_WIDTH)))) |
                    // vertical collision: at top of knife
                    (((cs.location) > (onionP -> row)) &
                        ((cs.location) < ((onionP -> row) + (ONION_WIDTH)))))
                    ) |
            // right hit from right
            (
                (((cs.strikeRight) > (onionP -> col)) &
                    (cs.strikeRight < ((onionP -> col) + (ONION_WIDTH)))) &
                    // vertical collision: at bottom of knife
                    ((((cs.location + (cs.sizeWidth)) > (onionP -> row)) &
                        ((cs.location + (cs.sizeWidth)) < ((onionP -> row) + (ONION_WIDTH)))) |
                    // vertical collision: at top of knife
                    (((cs.location) > (onionP -> row)) &
                        ((cs.location) < ((onionP -> row) + (ONION_WIDTH)))))
                    )
            ) {
            cs.state = LOSE;
        }
        cs.strikeRight -= 10;
        cs.strikeLeft += 10;

        break;

      case WIN:
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            cs.state = INIT;
        }

        // state = ?
        break;
      case LOSE:
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            cs.state = INIT;
        }

        // state = ?
        break;

    case WAIT_FOR_RESTART:
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            cs.state = INIT;
        }
        break;
    }









    waitForVBlank();









    // drawing
    switch (cs.state) {
    case INIT:
        // drawing background
        if (ps.state == INIT) {
            drawFullScreenImageDMA(background1);

            drawCenteredString(90, 100, 130, 100, "Press ENTER to start", WHITE);


            cs.state = INIT_BOUNCE;
        }
        break;

    case WAIT_FOR_START:
        undrawImageDMA((cs.letters[cs.letterCount].row) - ((cs.bounceFrames) / 2), (cs.letters[cs.letterCount].col), 7, 10 + ((cs.bounceFrames) / 2), background1);


        drawChar((cs.letters[cs.letterCount].row) + 2, (cs.letters[cs.letterCount].col) + 1, cs.title[cs.letterCount], BLACK);
        drawChar((cs.letters[cs.letterCount].row), (cs.letters[cs.letterCount].col), cs.title[cs.letterCount], WHITE);

        // undrawImageDMA((cs.letters[cs.letterCount] -> row) - ((cs.bounceFrames) / 2), (cs.letters[cs.letterCount] -> col), 7, 10, background1);

        // drawChar((cs.letters[cs.letterCount] -> row) + 2, (cs.letters[cs.letterCount] -> col) + 1, cs.title[cs.letterCount], BLACK);
        // drawChar((cs.letters[cs.letterCount] -> row), (cs.letters[cs.letterCount] -> col), cs.title[cs.letterCount], WHITE);


        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
            cs.state = CONFIGURATION;
        }

        break;

    case CONFIGURATION:
        fillScreenDMA(BLACK);

        drawString(53, 45, "20S", WHITE);
        drawString(73, 45, "40S", WHITE);
        drawString(93, 45, "60S", WHITE);

        drawString(53, 68, "<-", WHITE);

        drawString(66, 127, "Select your", WHITE);
        drawString(76, 130, "time limit", WHITE);

        drawString(110, 110, "UP / DOWN / START", WHITE);


        cs.state = WAIT_FOR_SELECTION;
        break;

    case WAIT_FOR_SELECTION:
        if (cs.selectionArrowRow != ps.selectionArrowRow) {
            drawRectDMA(ps.selectionArrowRow, 68, 20, 10, BLACK);
            drawString(cs.selectionArrowRow, 68, "<-", WHITE);
        }
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
            cs.timeLimit = cs.selectionArrowRow - 33;
            cs.state = STARTING;
        }
        break;

    case INIT_BOUNCE:
        for (int i = 0; i < 14; i++) {
            // drawChar((cs.letters[i] -> init_row) + 2, (cs.letters[i] -> col) + 1, cs.title[i], BLACK);
            // drawChar((cs.letters[i] -> init_row), (cs.letters[i] -> col), cs.title[i], WHITE);
            drawChar((cs.letters[i].init_row) + 2, (cs.letters[i].col) + 1, cs.title[i], BLACK);
            drawChar((cs.letters[i].init_row), (cs.letters[i].col), cs.title[i], WHITE);
        }
        cs.state = WAIT_FOR_START;
        break;

    case STARTING:
      
        fillScreenDMA(BLACK);
        drawChar(140, 20, (char) (cs.score + 48), RED);
        // drawFullScreenImageDMA(background1);

        drawRectDMA(cs.location, 5, (cs.sizeLength), (cs.sizeWidth), WHITE);
        drawRectDMA(cs.location, 215, (cs.sizeLength), (cs.sizeWidth), WHITE);

        cs.state = PLAY;
        break;

    case PLAY:

        // draw timer
        // if ((beforeStrike.time % 10 == 0) | (beforeStrike.time < 10)) {
            temp = beforeStrike.time / 10;
            //drawChar(140, 190, (char) (temp + 48), BLACK);
            drawRectDMA(140, WIDTH - 28, 6, 8, BLACK);
            drawChar(140, WIDTH - 28, (char) ((cs.time / 10)+ 48), WHITE);
        // }
        
        // drawChar(140, 196, (char) ((beforeStrike.time % 10) + 48), BLACK);
        drawRectDMA(140, WIDTH - 28 + 6, 6, 8, BLACK);
        drawChar(140, WIDTH - 28 + 6, (char) ((cs.time % 10) + 48), WHITE);

        // draw score
        temp = beforeStrike.score / 100;
        drawChar(140, 8, (char) (temp + 48), BLACK);
        drawChar(140, 8, (char) ((cs.score / 100) + 48), RED);

        temp = (beforeStrike.score / 10) % 10;
        drawChar(140, 14, (char) (temp + 48), BLACK);
        drawChar(140, 14, (char) (((cs.score / 10) % 10) + 48), RED);

        drawChar(140, 20, (char) ((beforeStrike.score % 10) + 48), BLACK);
        drawChar(140, 20, (char) ((cs.score % 10) + 48), RED);

        //draw knives
        drawRectDMA(beforeStrike.location, 5, (cs.sizeLength), (cs.sizeWidth), BLACK);
        drawRectDMA(beforeStrike.location, 215, (cs.sizeLength), (cs.sizeWidth), BLACK);

        drawRectDMA(cs.location, 5, (cs.sizeLength), (cs.sizeWidth), WHITE);
        drawRectDMA(cs.location, 215, (cs.sizeLength),(cs.sizeWidth), WHITE);
        waitForVBlank();

        cs.state = DRAW_FRUIT;
        break;

    case DRAW_FRUIT:
        waitForVBlank();
        if (cherryP) {
            eraseCherry = &(beforeStrike.fruit[0]);
            // are we supposed to erase only what we drew?
            drawRectDMA(eraseCherry -> row, eraseCherry -> col, CHERRY_WIDTH,
                CHERRY_WIDTH, BLACK);  
        }

        if (bananaP) {
            eraseBanana = &(beforeStrike.fruit[1]);
            drawRectDMA(eraseBanana -> row, eraseBanana -> col, BANANA_WIDTH,
                BANANA_WIDTH, BLACK);
        }

        if (mangoP) {
            eraseMango = &(beforeStrike.fruit[2]);
            drawRectDMA(eraseMango -> row, eraseMango -> col, MANGO_WIDTH,
                MANGO_WIDTH, BLACK);  
        }
        if (bananaP)
        drawImageDMA(bananaP -> row, bananaP -> col, BANANA_WIDTH, BANANA_WIDTH, bananaP -> image);
        if (mangoP)
        drawImageDMA(mangoP -> row, mangoP -> col, MANGO_WIDTH, MANGO_WIDTH, mangoP -> image);
        if (cherryP)
        drawImageDMA(cherryP -> row, cherryP -> col, CHERRY_WIDTH, CHERRY_WIDTH, cherryP -> image);


        eraseOnion = &(beforeStrike.onions);
        drawRectDMA(eraseOnion -> row, eraseOnion -> col, ONION_WIDTH,
            ONION_WIDTH, BLACK);
    
        drawImageDMA(onionP -> row, onionP -> col, ONION_WIDTH, ONION_WIDTH, onionP -> image);
        waitForVBlank();

        cs.state = PLAY;

        break;

    case STRIKE:
        drawRectDMA(beforeStrike.location, 5, (beforeStrike.sizeLength), (beforeStrike.sizeWidth), BLACK);
        drawRectDMA(beforeStrike.location, 215, (beforeStrike.sizeLength), (beforeStrike.sizeWidth), BLACK);

        drawRectDMA(ps.strikeLocation, ps.strikeLeft - 5, (cs.sizeLength) + 5,(cs.sizeWidth), BLACK);
        drawRectDMA(cs.strikeLocation, cs.strikeLeft - 5, 5, (cs.sizeWidth), COLOR(28,28,28));
        drawRectDMA(cs.strikeLocation, cs.strikeLeft, (cs.sizeLength), (cs.sizeWidth), WHITE);

        drawRectDMA(ps.strikeLocation, ps.strikeRight, (cs.sizeLength) + 5, (cs.sizeWidth), BLACK);
        drawRectDMA(cs.strikeLocation, cs.strikeRight + (cs.sizeLength), 5, (cs.sizeWidth), COLOR(28,28,28));
        drawRectDMA(cs.strikeLocation, cs.strikeRight, (cs.sizeLength), (cs.sizeWidth), WHITE);

        if (cs.strikeLeft + (cs.sizeLength) > cs.strikeRight) {
            // cs.state = REMOVE_STRIKE;
            drawRectDMA(ps.strikeLocation, ps.strikeLeft, (cs.sizeLength) * 2, (cs.sizeWidth), BLACK);
            cs.state = PLAY;
        }
        break;

    case WIN:
        drawFullScreenImageDMA(win);

        drawString(40, 8, "Your Score:", WHITE);

        drawChar(40, 76, (char) ((cs.score / 100) + 48), YELLOW);
        drawChar(40, 82, (char) (((cs.score / 10) % 10) + 48), YELLOW);
        drawChar(40, 88, (char) ((cs.score % 10) + 48), YELLOW);

        drawString(29, 8, "Time's up!", WHITE);

        drawString(29, 183, "Again?", WHITE);
        drawString(40, 173, "-> SELECT", WHITE);

        cs.state = WAIT_FOR_RESTART;

        // state = ?
        break;

    case LOSE:
        drawFullScreenImageDMA(gameOver);
        drawString(20, 10, "GAME OVER", WHITE);
        drawString(20, 162, "You cut the", WHITE);
        drawString(31, 157, "poor onion :(", WHITE);

        drawString(40, 6, "Your Score:", WHITE);
        drawChar(51, 25, (char) ((cs.score / 100) + 48), RED);
        drawChar(51, 31, (char) (((cs.score / 10) % 10) + 48), RED);
        drawChar(51, 37, (char) ((cs.score % 10) + 48), RED);

        drawString(133, 183, "Again?", BLACK);
        drawString(144, 173, "-> SELECT", BLACK);


        cs.state = WAIT_FOR_RESTART;

        // state = ?
        break;

    case WAIT_FOR_RESTART:
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  return 0;
}

// int collision(struct Fruit *fruit, struct State cs) {
//     return (
//             (
//                 (((cs.strikeLeft + (cs.sizeLength)) > (fruit -> col)) &
//                     (cs.strikeLeft < ((fruit -> col) + (fruit -> size)))) &

//                 // vertical collision: at bottom of knife
//                 ((((cs.location + (cs.sizeWidth)) > (fruit -> row)) &
//                     ((cs.location + (cs.sizeWidth)) < ((fruit -> row) + (fruit -> size)))) |

//                 // vertical collision: at top of knife
//                 (((cs.location) > (fruit -> row)) &
//                     ((cs.location) < ((fruit -> row) + (fruit -> size)))))
//             ) |
//             // right hit from right
//                 (
//                     (((cs.strikeRight) > (fruit -> col)) &
//                         (cs.strikeRight < ((fruit -> col) + (fruit -> size)))) &

//                     // vertical collision: at bottom of knife
//                     ((((cs.location + (cs.sizeWidth)) > (fruit -> row)) &
//                         ((cs.location + (cs.sizeWidth)) < ((fruit -> row) + (fruit -> size)))) |

//                     // vertical collision: at top of knife
//                     (((cs.location) > (fruit -> row)) &
//                         ((cs.location) < ((fruit -> row) + (fruit -> size)))))
//                 )
//             );
// }