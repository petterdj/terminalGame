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
    character->setAcceleration(1000, UP);
  }
}

void downkey(Character* character) {
  // Nothing yet
}

void rightkey(Character* character) {
  if (_heavyAttackTimer == 0) {
    _directionKeyTimer = 5;
    character->setAcceleration(MOVEMENTACCELERATION, RIGHT);
    character->setFacing(RIGHT);
  }
}

void leftkey(Character* character) {
  if (_heavyAttackTimer == 0) {
    _directionKeyTimer = 5;
    character->setAcceleration(MOVEMENTACCELERATION, LEFT);
    character->setFacing(LEFT);
  }
}

void nokey(Character* character) {
  float facing = character->getFacing();
  float xVelocity = character->getXVelocity();
  character->setAcceleration(0, UP);
  if (_directionKeyTimer <= 0) {
    _directionKeyTimer = 0;
    if (xVelocity < 0.1 && xVelocity > -0.9) {
      character->setXVelocity(0);
      character->setAcceleration(0, facing);
    } else if (facing == RIGHT) character->setAcceleration(xVelocity*DECELERATIONRIGHT, LEFT);
    else if (facing == LEFT) character->setAcceleration(xVelocity*DECELERATIONLEFT, RIGHT);
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
  float yVelocity = character->getYVelocity();
  float xVelocity = character->getXVelocity();
  float elasticity = character->getElasticity();
  if (y == HEIGHT) character->setYPosition(HEIGHT); // Temporary solutions to avoid falling out of bounds
  if (x == WIDTH) character->setXPosition(WIDTH); // -||-
  // Check if a block is below
  Block* block = _level[y+BELOW][x];
  if (block != 0 && !block->isPassableFromAbove() && yVelocity > 0) {
    character->setYPosition(y + 0.1);
    character->setYVelocity(bounce(yVelocity, elasticity));
  }
  // Check if a block is above
  block = _level[y+ABOVE][x];
  if (block != 0 && !block->isPassableFromBelow() && yVelocity < 0) {
    character->setYVelocity(bounce(yVelocity, elasticity));
  }
  // Check if a block is to the right
  block = _level[y][x+RIGHT];
  if (block != 0 && !block->isPassableFromLeft() && xVelocity > 0) {
    character->setXPosition(x+0.8);
    character->setXVelocity(bounce(xVelocity, elasticity));
  }
  // Check if a block is to the left
  block = _level[y][x+LEFT];
  if (block != 0 && !block->isPassableFromRight() && xVelocity < 0) {
    character->setXPosition(x+0.2);
    character->setXVelocity(bounce(xVelocity, elasticity));
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

  _player = new Character(10, 10, "<", ">", RIGHT);

  while(run) {
    clear();
    draw();
    mvprintw(1, 1, boost::lexical_cast<std::string>(inputKey).c_str());
    attack(_player);
    timeout(10);
    inputKey = getch();
    keyboardControl(inputKey);
    refresh();

    usleep(2000);

    // Objects affected by gravity should have individual terminal velocities
    _player->setYVelocity(newVelocity(_player->getYVelocity(), _player->getYAcceleration(), _player->getTerminalVelocity(), true));
    _player->setXVelocity(newVelocity(_player->getXVelocity(), _player->getXAcceleration(), _player->getTerminalVelocity()));
    _player->setYPosition(newPosition(_player->getYPosition(), _player->getYVelocity()));
    _player->setXPosition(newPosition(_player->getXPosition(), _player->getXVelocity()));

    collisionDetect(_player);

    time += _timestep; 
    if (inputKey == 50) break;
  }
  std::cout << "Goodbye5" << std::endl;
  teardown();
  endwin();
}

