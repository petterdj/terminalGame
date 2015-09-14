#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/tuple/tuple.hpp>
#include "utils/animations.h"
#include "utils/constants.h"
#include "utils/physics.h"
#include "block.hpp"
#include "character.hpp"

using namespace terminalGame;

float _terminalVelocity = 0;
float _timestep = 0.01;

int _directionKeyTimer = 0;

int _heavyAttackTimer = 0;
int _lightAttackTimer = 0;

std::vector<Block*> _levelVector;
Block* _level[HEIGHT][WIDTH];

Character* _player;

bool atRest(Character* character) {
  int y = int(character->getYPosition());
  int x = int(character->getXPosition());
  Block* block = _level[y+1][x];
  if (block == 0 || (block != 0 && block->isPassableFromAbove())) return false;
  return true;
}

void upkey(Character* character) {
  if (atRest(character)) {
    character->setAcceleration(10, UP);
  }
}

void downkey(Character* character) {
  // Nothing yet
}

void rightkey(Character* character) {
  if (_heavyAttackTimer == 0) {
    _directionKeyTimer = 5;
    character->setAcceleration(10, RIGHT);
    character->setFacing(RIGHT);
  }
}

void leftkey(Character* character) {
  if (_heavyAttackTimer == 0) {
    _directionKeyTimer = 5;
    character->setAcceleration(10, LEFT);
    character->setFacing(LEFT);
  }
}

// TODO Requires some tuning to get desired behaviour. Idea is to accelerate opposite of movement direction until velocity reaches 0
void nokey(Character* character) {
  if (_directionKeyTimer <= 0) {
    _directionKeyTimer = 0;
    character->setAcceleration(character->getXAcceleration(), character->getFacing());
  } else _directionKeyTimer--;
}

void akey(Character* character) {
  character->setAcceleration(10, UP);
}

void skey(Character* character) { // Heavy attack
  if (_heavyAttackTimer == 0 && _lightAttackTimer == 0) _heavyAttackTimer = 70;
}

void dkey(Character* character) { // Light attack
  if(_heavyAttackTimer == 0 && _lightAttackTimer == 0) _lightAttackTimer = 20;
}

void keyboardControl(int inputKey) {
  switch (inputKey) {
    case 65: // Up
      upkey(_player);
      break;
    case 66: // Down
      downkey(_player);
      break;
    case 67: // Right
      rightkey(_player);
      break;
    case 68: // Left
      leftkey(_player);
      break;
    case 97: // a
      akey(_player);
      break;
    case 115: // s
      skey(_player);
      break;
    case 100: // d
      dkey(_player);
      break;
    default:
      nokey(_player);
  }
}

void drawPlayer() {
  mvprintw(_player->getYPosition(), _player->getXPosition(), _player->getDrawChar().c_str());
}

void drawLevel() {
  for (auto &it : _levelVector) mvprintw(it->getYPosition(), it->getXPosition(), it->getDrawChar().c_str());
}

void draw() {
  drawPlayer();
  mvprintw(1, 10, boost::lexical_cast<std::string>(_player->getXVelocity()).c_str());
  mvprintw(2, 10, boost::lexical_cast<std::string>(_player->getXAcceleration()).c_str());
  mvprintw(1, 30, boost::lexical_cast<std::string>(_player->getYVelocity()).c_str());
  mvprintw(2, 30, boost::lexical_cast<std::string>(_player->getYAcceleration()).c_str());
  mvprintw(3, 10, boost::lexical_cast<std::string>(_player->getXPosition()).c_str());
  mvprintw(3, 30, boost::lexical_cast<std::string>(_player->getYPosition()).c_str());
  drawLevel();
}

void attack(Character* character) {
  if (_heavyAttackTimer > 0)
    _heavyAttackTimer = performHeavyAttack(_heavyAttackTimer, character->getFacing(), character->getYPosition(), character->getXPosition());
  if (_lightAttackTimer > 0)
    _lightAttackTimer = performLightAttack(_lightAttackTimer, character->getFacing(), character->getYPosition(), character->getXPosition());
}

void loadLevel() {
  std::ifstream infile("levels/level1");
  std::string line;
  size_t y = 0;
  while(std::getline(infile, line)) {
    for (size_t x = 0; x < line.length(); ++x) {
      if(line[x] == '#') {
        Block* block = new Block((int) y, (int) x); 
        _levelVector.push_back(block);
        _level[y][x] = block;
      }
    }
    ++y;
  }
  infile.close();
}

void collisionDetect(Character* character) {
  int y = int(character->getYPosition());
  int x = int(character->getXPosition());
  if (y == HEIGHT) character->setYPosition(HEIGHT);
  if (x == WIDTH) character->setXPosition(WIDTH);
  Block* block = _level[y+1][x];
  if (block != 0 && !block->isPassableFromAbove() && character->getYVelocity() > 0) {
    character->setYPosition(y + 0.1);
    character->setYVelocity(bounce(character->getYVelocity(), character->getElasticity()));
  } // TODO: Store x and y velocity in local variables to avoid accessing over and over
  block = _level[y-1][x];
  if (block != 0 && !block->isPassableFromBelow() && character->getYVelocity() < 0) {
    _yVelocity = bounce(_yVelocity);
  }
  block = _level[y][x+1];
  if (block != 0 && !block->isPassableFromLeft() && _xVelocity > 0) {
    _xPosition = x+0.8;
    _xVelocity = bounce(_xVelocity);
  }
  block = _level[y][x-1];
  if (block != 0 && !block->isPassableFromRight() && _xVelocity < 0) {
    _xPosition = x+0.2;
    _xVelocity = bounce(_xVelocity);
  }
}

void teardown() {
  for (auto &it : _levelVector) delete it;
}

int main(int argc, char *argv[]) {
  initscr();
  noecho();
  curs_set(FALSE);
  raw();
  resize_term(HEIGHT, WIDTH);
  loadLevel();
  bool run = true;
  float time = 0;
  int inputKey = -1;

  _terminalVelocity = terminalVelocity();
  
  _player = new Character(10, 10, "<", ">", RIGHT);

  while(run) {
    clear();
    draw();
    mvprintw(1, 1, boost::lexical_cast<std::string>(inputKey).c_str());
    attack();
    timeout(10);
    inputKey = getch();
    keyboardControl(inputKey);
    refresh();

    usleep(2000);

    _yVelocity = newVelocity(_yVelocity, _yAcceleration, _timestep, _terminalVelocity, true);
    _xVelocity = newVelocity(_xVelocity, _xAcceleration, _timestep, _terminalVelocity); 
    _yPosition = _yPosition + _yVelocity * _timestep;
    _xPosition = _xPosition + _xVelocity * _timestep;
    
    collisionDetect();

    time += _timestep; 
    if (inputKey == 50) break;
  }
  std::cout << "Goodbye5" << std::endl;
  teardown();
  endwin();
}

