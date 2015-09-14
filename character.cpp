#include "character.hpp"
#include "utils/constants.h"

using namespace terminalGame;

// CONSTRUCTORS //
  Character::Character() :
    Object() {
   _facing = RIGHT; 
  }

  Character::Character(const float y, const float x, const std::string drawChar, const int facing) :
    Object(y, x, drawChar) {
    _facing = facing;
  }

  Character::Character(const Character& o) :
    Object(o) {
    if (this == &o) return;
    _facing = o._facing;
  }

  Character::Character(Character&& o) :
    Object(o) {
    _facing = o._facing;
    o._facing = 0;
  }

// OPERATORS //
  Character& Character::operator=(const Character& o) {
    if (this == &o) return *this;
    Object::operator=(o);
    _facing = o._facing;
    return *this;
  }

  Character& Character::operator=(Character&& o) {
    if (this == &o) return *this;
    Object::operator=(o);
    _facing = o._facing;
    o._facing = 0;
    return *this;
  }

// DESTRUCTOR //
  Character::~Character() {
    _facing = 0;
  }

// FUNCTIONS //
  int Character::getFacing() const {
    return _facing;
  }

  void Character::setFacing(const int facing) {
    _facing = facing;
  }

