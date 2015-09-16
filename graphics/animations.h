#ifndef ANIMATIONS
#define ANIMATIONS
#include <ncurses.h>
#include "../utils/constants.h"

int performHeavyAttack(int attackTimer, int facing, float yPosition, float xPosition) {
  if(facing == RIGHT) {
    if(attackTimer > 60) // Frame 1
      mvprintw(yPosition+ABOVE, xPosition, "|");
    else if(attackTimer > 45) // Frame 2
      mvprintw(yPosition+ABOVE, xPosition, "/");
    else if(attackTimer > 35) // Frame 3
      mvprintw(yPosition+ABOVE, xPosition+facing, "/");
    else if(attackTimer > 0) // Frame 5
      mvprintw(yPosition, xPosition+facing, "\\");
  } else {
    if(attackTimer > 60) // Frame 1
      mvprintw(yPosition+ABOVE, xPosition, "|");
    else if(attackTimer > 45) // Frame 2
      mvprintw(yPosition+ABOVE, xPosition, "\\");
    else if(attackTimer > 35) // Frame 3
      mvprintw(yPosition+ABOVE, xPosition+facing, "\\");
    else if(attackTimer > 0) // Frame 5
      mvprintw(yPosition, xPosition+facing, "/");
  }
  return attackTimer-1;
}

int performLightAttack(int attackTimer, int facing, float yPosition, float xPosition) {
  mvprintw(yPosition, xPosition+facing, "-");
  return attackTimer-1;
}

#endif
