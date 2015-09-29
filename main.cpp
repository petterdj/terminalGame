#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/tuple/tuple.hpp>
#include "graphics/animations.h"
#include "graphics/draw.h"
#include "utils/constants.h"
#include "utils/physics.h"
#include "block.hpp"
#include "character.hpp"
#include "weapon.hpp"

using namespace terminalGame;

float _timestep = 0.01;

int _directionKeyTimer = 0;

std::vector<Block*> _levelVector;
Block* _level[HEIGHT][WIDTH];

std::vector<Character*> _characterVector;
Character* _player;

std::vector<Weapon*> _weaponVector;

std::vector<GravityObject*> _gravityObjectVector;

void upkey(Character* character) { if (!character->inAir()) character->jump(); } // TODO Do something else with up-key
void downkey(Character* character) {
  if (!character->inAir()) {
    int y = character->getYPosition();
    int x = character->getXPosition();
    Block* block = _level[y+BELOW][x];
    if (block != nullptr && block->isPassableFromAboveKeyDown()) character->setYPosition(y+BELOW);
  }
}

void rightkey(Character* character) {
  character->move(RIGHT);
  _directionKeyTimer = 5;
}

void leftkey(Character* character) {
  character->move(LEFT);
  _directionKeyTimer = 5;
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

void akey(Character* character) { if (!character->inAir()) character->jump(); }
void skey(Character* character) { character->heavyAttack(); }
void dkey(Character* character) { character->lightAttack(); }

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

void loadLevel() {
  std::ifstream infile("levels/level1");
  std::string line;
  int y = 0;
  while (std::getline(infile, line)) {
    for (int x = 0; (size_t) x < line.length(); ++x) {
      Block* block = nullptr;
      if (line[x] == '#') { // Normal impassable block
        block = new Block((int) y, (int) x); 
      } else if (line[x] == '-') { // Platform block
        block = new Block((int) y, (int) x, "-");
        block->setPlatformPassable();
      } else if (line[x] == '=') { // Block that is impassable except on down arrow
        block = new Block(y, x, "=", true);
      }
      if (block != nullptr) _levelVector.push_back(block);
      _level[y][x] = block;
    }
    ++y;
  }
  infile.close();
}

void collisionDetect(GravityObject* object) {
  int y = int(object->getYPosition());
  int x = int(object->getXPosition());
  float yVelocity = object->getYVelocity();
  float xVelocity = object->getXVelocity();
  float elasticity = object->getElasticity();
  bool inAir = true;
  if (y == HEIGHT) object->setYPosition(HEIGHT); // TODO Temporary solutions to avoid falling out of bounds
  if (x == WIDTH) object->setXPosition(WIDTH); // -||-
  // Check if a block is below and at the same time set if the object is in the air or on the ground
  Block* block = _level[y+BELOW][x];
  inAir = (block == nullptr || block->isPassableFromAbove());
  object->setInAir(inAir);
  if (!inAir && yVelocity > 0) {
    object->setYPosition(y + 0.1);
    object->setYVelocity(bounce(yVelocity, elasticity));
  }
  // Check if a block is above
  block = _level[y+ABOVE][x];
  if (block != nullptr && !block->isPassableFromBelow() && yVelocity < 0) {
    object->setYVelocity(bounce(yVelocity, elasticity));
  }
  // Check if a block is to the right
  block = _level[y][x+RIGHT];
  if (block != nullptr && !block->isPassableFromLeft() && xVelocity > 0) {
    object->setXPosition(x+0.8);
    object->setXVelocity(bounce(xVelocity, elasticity));
  }
  // Check if a block is to the left
  block = _level[y][x+LEFT];
  if (block != nullptr && !block->isPassableFromRight() && xVelocity < 0) {
    object->setXPosition(x+0.2);
    object->setXVelocity(bounce(xVelocity, elasticity));
  }
}

void teardown() {
  for (auto &it : _levelVector) delete it;
  for (auto &it : _characterVector) delete it;
  for (auto &it : _weaponVector) delete it;
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
  _characterVector.push_back(_player);
  _gravityObjectVector.push_back(_player);

  Weapon* weapon = new Weapon(10, 4, 4, "/");
  _weaponVector.push_back(weapon);
  _gravityObjectVector.push_back(weapon);
  _player->equip(weapon);

  while(run) {
    clear();
    draw(_levelVector, _characterVector, _weaponVector);
    mvprintw(1, 1, boost::lexical_cast<std::string>(inputKey).c_str());
    timeout(10);
    inputKey = getch();
    keyboardControl(inputKey);
    refresh();

    usleep(2000);

    // Objects affected by gravity should have individual terminal velocities
    for (auto &it : _gravityObjectVector) {
      it->setYVelocity(newVelocity(it->getYVelocity(), it->getYAcceleration(), it->getTerminalVelocity(), true));
      it->setXVelocity(newVelocity(it->getXVelocity(), it->getXAcceleration(), it->getTerminalVelocity()));
      it->setYPosition(newPosition(it->getYPosition(), it->getYVelocity()));
      it->setXPosition(newPosition(it->getXPosition(), it->getXVelocity()));
      collisionDetect(it);
      it->countDownTimers();
    }

    time += _timestep; 
    if (inputKey == 50) break;
  }
  teardown();
  endwin();
}

