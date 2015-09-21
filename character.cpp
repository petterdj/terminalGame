#include "character.hpp"
#include "weapon.hpp"
#include "utils/constants.h"

using namespace terminalGame;

// CONSTRUCTORS //
Character::Character() :
  GravityObject() {
  _facing = RIGHT;
  _heavyAttackTimer = 0;
  _lightAttackTimer = 0;
  _secondaryDrawChar = " ";
  _equippedWeapon = nullptr;
}


Character::Character(const float y, const float x, const std::string leftDrawChar, std::string rightDrawChar, const int facing, const float elasticity, const int shape) :
  GravityObject(y, x, leftDrawChar, elasticity, shape) {
  _facing = facing;
  _heavyAttackTimer = 0;
  _lightAttackTimer = 0;
  _secondaryDrawChar = rightDrawChar;
  _equippedWeapon = nullptr;
}

Character::Character(const Character& o) :
  GravityObject(o) {
  if (this == &o) return;
  _facing = o._facing;
  _heavyAttackTimer = o._heavyAttackTimer;
  _lightAttackTimer = o._lightAttackTimer;
  _secondaryDrawChar = o._secondaryDrawChar;
  _equippedWeapon = o._equippedWeapon;
}

Character::Character(Character&& o) :
  GravityObject(o) {
  if (this == &o) return;
  _facing = o._facing;
  _heavyAttackTimer = o._heavyAttackTimer;
  _lightAttackTimer = o._lightAttackTimer;
  _secondaryDrawChar = o._secondaryDrawChar;
  _equippedWeapon = o._equippedWeapon;
  o._facing = 0;
  o._heavyAttackTimer = 0;
  o._lightAttackTimer = 0;
  o._secondaryDrawChar = "";
  o._equippedWeapon = nullptr;
}

// OPERATORS //
Character& Character::operator=(const Character& o) {
  if (this == &o) return *this;
  GravityObject::operator=(o);
  _facing = o._facing;
  _heavyAttackTimer = o._heavyAttackTimer;
  _lightAttackTimer = o._lightAttackTimer;
  _secondaryDrawChar = o._secondaryDrawChar;
  _equippedWeapon = o._equippedWeapon;
  return *this;
}

Character& Character::operator=(Character&& o) {
  if (this == &o) return *this;
  GravityObject::operator=(o);
  _facing = o._facing;
  _heavyAttackTimer = o._heavyAttackTimer;
  _lightAttackTimer = o._lightAttackTimer;
  _secondaryDrawChar = o._secondaryDrawChar;
  _equippedWeapon = o._equippedWeapon;
  o._facing = 0;
  o._heavyAttackTimer = 0;
  o._lightAttackTimer = 0;
  o._secondaryDrawChar = "";
  o._equippedWeapon = nullptr;
  return *this;
}

// DESTRUCTOR //
Character::~Character() {
  _facing = 0;
  _secondaryDrawChar = "";
  _equippedWeapon = nullptr;
}

// FUNCTIONS //
int Character::getFacing() const { return _facing; }
void Character::setFacing(const int facing) { _facing = facing; }
Weapon* Character::getEquippedWeapon() const { return _equippedWeapon; }

void Character::drop(GravityObject* object) {
  if (object == nullptr) return;
  object->setYPosition(_yPosition+ABOVE);
  object->setXPosition(_xPosition-_facing);
  object->setXVelocity(5);
}

void Character::equip(Weapon* weapon) {
  if (weapon == nullptr) return;
  if (_equippedWeapon != nullptr) {
    _equippedWeapon->setEquipped(false);
    drop(_equippedWeapon);
  }
  weapon->setEquipped(true);
  _equippedWeapon = weapon;
}

std::string Character::getDrawChar() const {
  if (_facing == LEFT) return _drawChar;
  if (_facing == RIGHT) return _secondaryDrawChar;
  return NULL; // Should never happen, but if it does this should help identify it
}

void Character::heavyAttack() {
  if (_equippedWeapon == nullptr) return;
  if (_lightAttackTimer > 0) _lightAttackTimer = 0;
  if (_heavyAttackTimer > 0) _heavyAttackTimer = _equippedWeapon->performHeavyAttack(_heavyAttackTimer, _facing,
    _yPosition, _xPosition);
  else _heavyAttackTimer = 70;
}

void Character::lightAttack() {
  if (_heavyAttackTimer > 0 || _equippedWeapon == nullptr) return;
  if (_lightAttackTimer > 0)
    _lightAttackTimer = _equippedWeapon->performLightAttack(_lightAttackTimer, _facing,
      _yPosition, _xPosition);
  else _lightAttackTimer = 20;
}
