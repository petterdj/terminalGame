#include "character.hpp"
#include "utils/constants.h"

using namespace terminalGame;

// CONSTRUCTORS //
  Character::Character() :
    GravityObject() {
   _facing = RIGHT;
   _secondaryDrawChar = " ";
  }

  Character::Character(const float y, const float x, const std::string leftDrawChar, std::string rightDrawChar, const int facing, const float elasticity, const int shape) :
    GravityObject(y, x, leftDrawChar, elasticity, shape) {
    _facing = facing;
    _secondaryDrawChar = rightDrawChar;
  }

  Character::Character(const Character& o) :
    GravityObject(o) {
    if (this == &o) return;
    _facing = o._facing;
    _secondaryDrawChar = o._secondaryDrawChar;
  }

  Character::Character(Character&& o) :
    GravityObject(o) {
    _facing = o._facing;
    _secondaryDrawChar = o._secondaryDrawChar;
    o._facing = 0;
    o._secondaryDrawChar = "";
  }

// OPERATORS //
  Character& Character::operator=(const Character& o) {
    if (this == &o) return *this;
    GravityObject::operator=(o);
    _facing = o._facing;
    _secondaryDrawChar = o._secondaryDrawChar;
    return *this;
  }

  Character& Character::operator=(Character&& o) {
    if (this == &o) return *this;
    GravityObject::operator=(o);
    _facing = o._facing;
    _secondaryDrawChar = o._secondaryDrawChar;
    o._facing = 0;
    o._secondaryDrawChar = "";
    return *this;
  }

// DESTRUCTOR //
  Character::~Character() {
    _facing = 0;
    _secondaryDrawChar = "";
  }

// FUNCTIONS //
  int Character::getFacing() const {
    return _facing;
  }

  void Character::setFacing(const int facing) {
    _facing = facing;
  }

  std::string Character::getDrawChar() const {
    if (_facing == LEFT) return _drawChar;
    if (_facing == RIGHT) return _secondaryDrawChar;
    return NULL; // Should never happen, but if it does this should help identify it
  }
