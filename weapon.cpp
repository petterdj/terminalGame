#include "weapon.hpp"
#include <iostream>

using namespace terminalGame;


// CONSTRUCTORS //
Weapon::Weapon() : 
  GravityObject() {
  _damageValue = 0;
  _oldDamageValue = 0;
  _timer = 0;
  _equipped = false;
}

Weapon::Weapon(const int damageValue, const float y, const float x, 
  const std::string drawChar, const float elasticity, const int shape) :
  GravityObject(y, x, drawChar, elasticity, shape) {
  _damageValue = damageValue;
  _oldDamageValue = 0;
  _timer = 0;
  _equipped = false;
}

Weapon::Weapon(const Weapon& o) : 
  GravityObject(o) {
  if (this == &o) return;
  _damageValue = o._damageValue;
  _oldDamageValue = o._oldDamageValue;
  _timer = o._timer;
  _equipped = o._equipped;

}

Weapon::Weapon(Weapon&& o) :
  GravityObject(o) {
  if (this == &o) return;
  _damageValue = o._damageValue;
  _oldDamageValue = o._oldDamageValue;
  _timer = o._timer;
  _equipped = o._equipped;
  o._damageValue = 0;
  o._oldDamageValue = 0;
  o._timer = 0;
  o._equipped = false;
}

// OPERATORS //
Weapon& Weapon::operator=(const Weapon& o) {
  if (this == &o) return *this;
  GravityObject::operator=(o);
  _damageValue = o._damageValue;
  _oldDamageValue = o._oldDamageValue;
  _timer = o._timer;
  _equipped = o._equipped;
  return *this;
}

Weapon& Weapon::operator=(Weapon&& o) {
  if (this == &o) return *this;
  _damageValue = o._damageValue;
  _oldDamageValue = o._oldDamageValue;
  _timer = o._timer;
  _equipped = o._equipped;
  o._damageValue = 0;
  o._oldDamageValue = 0;
  o._timer = 0;
  o._equipped = false;
  return *this;
}

// DESTRUCTOR //
Weapon::~Weapon() {
  _damageValue = 0;
  _oldDamageValue = 0;
  _timer = 0;
  _equipped = false;
}

// FUNCTIONS //
int Weapon::getDamageValue() const { return _damageValue; }
int Weapon::getTime() const { return _timer; }

void Weapon::setDamageValue(const int damageValue) {
  _oldDamageValue = _damageValue;
  _damageValue = damageValue;
}

void Weapon::setTempDamageValue(const int damageValue, const int time) {
  _timer = time;
  _oldDamageValue = _damageValue;
  _damageValue = damageValue;
}

void Weapon::restoreDamageValue() {
  _damageValue = _oldDamageValue;
}

void Weapon::countDown() {
  if (_timer > 0) {
    _timer--;
    if ( _timer == 0) restoreDamageValue();
  }
}

void Weapon::setTimer(const int timerValue) {
  if (_timer > 0 && timerValue == 0) restoreDamageValue();
  _timer = timerValue;
}

void Weapon::setEquipped(const bool equipValue) {
  _equipped = equipValue;
}
