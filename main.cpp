#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/tuple/tuple.hpp>
#include "animations.h"
#include "constants.h"
#include "physics.h"

float _terminalVelocity = 0;
float _timestep = 0.01;

float _yPosition = 10;
float _xPosition = 10;
float _yVelocity = 0;
float _xVelocity = 0;
float _yAcceleration = 0;
float _xAcceleration = 0;
int _facing = RIGHT;
int _directionKeyTimer = 0;

int _heavyAttackTimer = 0;
int _lightAttackTimer = 0;

std::string _level[HEIGHT][WIDTH];

bool atRest() {
  int y = int(_yPosition);
  int x = int(_xPosition);
  return (_level[y+1][x] == "#");
}

void upkey() {
  if (atRest()) {
    _yVelocity = -10;
  }
}

void downkey() {
  // Nothing yet
}

void rightkey() {
  if (_heavyAttackTimer == 0) {
    _directionKeyTimer = 5;
    _xVelocity = 100;
    _facing = RIGHT;
  }
}

void leftkey() {
  if (_heavyAttackTimer == 0) {
    _directionKeyTimer = 5;
    _xVelocity = -100;
    _facing = LEFT;
  }
}

void nokey() {
  if (_directionKeyTimer <= 0) {
    _directionKeyTimer = 0;
    _xVelocity = 0;
  } else _directionKeyTimer--;
}

void akey() {
  _yVelocity = -10;
}

void skey() { // Heavy attack
  if (_heavyAttackTimer == 0 && _lightAttackTimer == 0) _heavyAttackTimer = 70;
}

void dkey() { // Light attack
  if(_heavyAttackTimer == 0 && _lightAttackTimer == 0) _lightAttackTimer = 20;
}

void keyboardControl(int inputKey) {
  switch (inputKey) {
    case 65: // Up
      upkey();
      break;
    case 66: // Down
      downkey();
      break;
    case 67: // Right
      rightkey();
      break;
    case 68: // Left
      leftkey();
      break;
    case 97: // a
      akey();
      break;
    case 115: // s
      skey();
      break;
    case 100: // d
      dkey();
      break;
    default:
      nokey();
  }
}

void drawPlayer() {
  if (_facing == RIGHT) mvprintw(_yPosition, _xPosition, ">");
  else mvprintw(_yPosition, _xPosition, "<");
}

void drawLevel() {
  for(size_t y = 0; y < HEIGHT; ++y) {
    for(size_t x = 0; x < WIDTH; ++x) {
      mvprintw(y, x, _level[y][x].c_str());
    }
  }
}

void draw() {
  drawPlayer();
  mvprintw(1, 10, boost::lexical_cast<std::string>(_xVelocity).c_str());
  mvprintw(2, 10, boost::lexical_cast<std::string>(_xAcceleration).c_str());
  mvprintw(1, 30, boost::lexical_cast<std::string>(_yVelocity).c_str());
  mvprintw(2, 30, boost::lexical_cast<std::string>(_yAcceleration).c_str());
  mvprintw(3, 10, boost::lexical_cast<std::string>(_xPosition).c_str());
  mvprintw(3, 30, boost::lexical_cast<std::string>(_yPosition).c_str());
  drawLevel();
}

void attack() {
  if (_heavyAttackTimer > 0)
    _heavyAttackTimer = performHeavyAttack(_heavyAttackTimer, _facing, _yPosition, _xPosition);
  if (_lightAttackTimer > 0)
    _lightAttackTimer = performLightAttack(_lightAttackTimer, _facing, _yPosition, _xPosition);
}

void loadLevel() {
  std::ifstream infile("level1");
  std::string line;
  size_t y = 0;
  while(std::getline(infile, line)) {
    for (unsigned int x = 0; x < line.length(); ++x) {
      if(line[x] == '#') _level[y][x] = "#";
    }
    ++y;
  }
  infile.close();
}

float bounce(float velocity) {
  return -elasticity*velocity;
}

void collisionDetect() {
  int y = int(_yPosition);
  int x = int(_xPosition);
  if (_level[y+1][x] == "#" && _yVelocity > 0) {
    _yPosition = y + 0.1;
    _yVelocity = bounce(_yVelocity);
  }
  if (_level[y-1][x] == "#" && _yVelocity < 0) {
    _yVelocity = bounce(_yVelocity);
  }
  if (_level[y][x+1] == "#" && _xVelocity > 0) {
    _xPosition = x+0.8;
    _xVelocity = bounce(_xVelocity);
  }
  if (_level[y][x-1] == "#" && _xVelocity < 0) {
    _xPosition = x+0.2;
    _xVelocity = bounce(_xVelocity);
  }
}

int main(int argc, char *argv[]) {
  initscr();
  noecho();
  curs_set(FALSE);
  raw();
  resize_term(HEIGHT, WIDTH);

  loadLevel();

  float time = 0;
  
  int inputKey;

  _terminalVelocity = terminalVelocity();

  while(true) {
    clear();
    draw();
    mvprintw(1, 1, boost::lexical_cast<std::string>(inputKey).c_str());
    attack();
    timeout(10);
    inputKey = getch();
    if (inputKey == 50) break;
    keyboardControl(inputKey);
    refresh();

    usleep(2000);

    _yVelocity = newVelocity(_yVelocity, _yAcceleration, _timestep, _terminalVelocity, true);
    _xVelocity = newVelocity(_xVelocity, _xAcceleration, _timestep, _terminalVelocity); 
    _yPosition = _yPosition + _yVelocity * _timestep;
    _xPosition = _xPosition + _xVelocity * _timestep;
   
    collisionDetect();

    time += _timestep; 
  }

  endwin();
}

