#include "character.hpp"
#include "constants.h"

using namespace terminalGame;

// CONSTRUCTORS //
  Character::Character() :
    Object() {
   _facing = RIGHT; 
  }

  Character::Character(const float y, const float x, const string drawChar, const int facing) :
    Object(y, x, drawChar) {
    _facing = facing;
  }

  Character::Character(const Character& o) :
    Object(o) {
    if (this == &o) return;
    _facing(o._facing);
  }

  Character::Character(Character&& o) :
    Object(o) {
    _facing = o._facing;
    o._facing = 0;
  }

// OPERATORS //
  Character& Character::operator=(const Character& o) :
    Object::operator=(o) {
    if (this == &o) return *this;
    _facing = o._facing;
  }

  Character& operator=(Character&& o) :
    Object::operator=(o) {
    if (this == &o) return *this;
    _facing = o._facing;
    o._facing = 0;
  }

// DESTRUCTOR //
  Character::~Character() {
    ~Object();
    _facing = 0;
  }

// FUNCTIONS //
  const int Character::getFacing() const {
    return _facing;
  }

  void Character::setFacing(const int facing) {
    _facing = facing;
  }

