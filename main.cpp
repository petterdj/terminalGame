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

std::vector<boost::tuple<int, int>> _level;

bool atRest() {
  // TODO Logic to check if player is at rest on the ground
  return true;
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
  _directionKeyTimer = 5;
  _xVelocity = 100;
  _facing = RIGHT;
}

void leftkey() {
  _directionKeyTimer = 5;
  _xVelocity = -100;
  _facing = LEFT;
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

void drawBorder() {
  for (unsigned int i = 0; i < HEIGHT; ++i) {
    mvprintw(i, 0, "#");
    mvprintw(i, WIDTH-1, "#");
  }

  for (unsigned int i = 0; i < WIDTH; ++i) {
    mvprintw(0, i, "#");
    mvprintw(HEIGHT-1, i, "#");
  }
}

void drawLevel() {
  for(unsigned int i; i < _level.size(); ++i) {
    mvprintw(_level[i].get<0>(), _level[i].get<1>(), "#");
  }
}

void draw() {
  mvprintw(_yPosition, _xPosition, "o");
  mvprintw(1, 10, boost::lexical_cast<std::string>(_xVelocity).c_str());
  mvprintw(2, 10, boost::lexical_cast<std::string>(_xAcceleration).c_str());
  mvprintw(1, 30, boost::lexical_cast<std::string>(_yVelocity).c_str());
  mvprintw(2, 30, boost::lexical_cast<std::string>(_yAcceleration).c_str());
  mvprintw(3, 10, boost::lexical_cast<std::string>(_xPosition).c_str());
  mvprintw(3, 30, boost::lexical_cast<std::string>(_yPosition).c_str());
  drawBorder();
  drawLevel();
}

void loadLevel() {
  std::ifstream infile("level1");
  std::string line;
  unsigned int y = 0;
  while(std::getline(infile, line)) {
    for (unsigned int x = 0; x < line.length(); ++x) {
      if(line[x] == '#') _level.push_back(boost::tuple<int, int>(y, x));
    }
    ++y;
  }
  infile.close();
}

void collisionDetect() {
  int y;
  int x;
  for (unsigned int i = 0; i < _level.size(); ++i) {
    y = _level[i].get<0>();
    x = _level[i].get<1>();
    if ((_yPosition >= y && _yPosition <= y+0.1) && (_xPosition >= x && _xPosition <= x+0.9)) {
      _yPosition = y;
      _yVelocity = -elasticity*_yVelocity;
    }
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
    if (_heavyAttackTimer > 0)
      _heavyAttackTimer = performHeavyAttack(_heavyAttackTimer, _facing, _yPosition, _xPosition);
    if (_lightAttackTimer > 0)
      _lightAttackTimer = performLightAttack(_lightAttackTimer, _facing, _yPosition, _xPosition);
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

    //if (_yPosition >= HEIGHT-2) {
    //  _yPosition = HEIGHT-2;
    //  _yVelocity = -elasticity*_yVelocity;
    //}

    time += _timestep; 
  }

  endwin();
}

