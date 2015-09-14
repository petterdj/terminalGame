#include "gravityobject.hpp"
#include "utils/constants.h"
#include "iostream"

// CONSTRUCTORS //
GravityObject::GravityObject():
  Object() {
  _elasticity = 0.0;
  _shape = SPHERE;
  _yVelocity = 0;
  _xVelocity = 0;
  _yAcceleration = 0;
  _xAcceleration = 0;
}

GravityObject::GravityObject(const float y, const float x, const std::string drawChar, const float elasticity, const int shape):
  Item(y, x, drawChar) {
  _elasticity = elasticity;
  _shape = shape;
  _yVelocity = 0;
  _xVelocity = 0;
  _yAcceleration = 0;
  _xAcceleration = 0;
}

GravityObject::GravityObject(const GravityObject& o) :
  Object(o) {
  if (this == &o) return;
  _elasticity = o._elasticity;
  _shape = o._shape;
  _yVelocity = o._yVelocity;
  _xVelocity = o._xVelocity;
  _yAcceleration = o._yAcceleration;
  _xAcceleration = o._xAcceleration;
}

GravityObject::GravityObject(GravityObject&& o) :
  Object(o) {
  _elasticity = o._elasticity;
  _shape = o._shape;
  _yVelocity = o._yVelocity;
  _xVelocity = o._xVelocity;
  _yAcceleration = o._yAcceleration;
  _xAcceleration = o._xAcceleration;
  o._elasticity = 0;
  o._shape = 0;
  o._yVelocity = 0;
  o._xVelocity = 0;
  o._yAcceleration = 0;
  o._xAcceleration = 0;
}

// OPERATORS //
GravityObject& GravityObject::operator=(const GravityObject& o) {
  if (this == &o) return *this;
  Object::operator=(o);
  _elasticity = o._elasticity;
  _shape = o._shape;
  _yVelocity = o._yVelocity;
  _xVelocity = o._xVelocity;
  _yAcceleration = o._yAcceleration;
  _xAcceleration = o._xAcceleration;
  return *this;
}

GravityObject& GravityObject::operator=(GravityObject&& o) {
  if (this == &o) return *this;
  Object::operator=(o);
  _elasticity = o._elasticity;
  _shape = o._shape;
  _yVelocity = o._yVelocity;
  _xVelocity = o._xVelocity;
  _yAcceleration = o._yAcceleration;
  _xAcceleration = o._xAcceleration;
  o._elasticity = 0;
  o._shape = 0;
  o._yVelocity = 0;
  o._xVelocity = 0;
  o._yAcceleration = 0;
  o._xAcceleration = 0;
  return *this;
}

// DESTRUCTOR //
GravityObject::~GravityObject() {
  _elasticity = 0;
  _shape = 0;
  _yVelocity = 0;
  _xVelocity = 0;
  _yAcceleration = 0;
  _xAcceleration = 0;
}

// FUNCTION //
float GravityObject::getElasticity() const { return _elasticity; }
int GravityObject::getShape() const { return _shape; }
float GravityObject::getYVelocity() const { return _yVelocity; }
float GravityObject::getXVelocity() const { return _xVelocity; }
float GravityObject::getYAcceleration() const { return _yAcceleration; }
float GravityObject::getXAcceleration() cosnt { return _xAcceleration; }

void GravityObject::setElasticity(const float elasticity) {
  _elasticity = elasticity;
}

void GravityObject::setShape(const int shape) {
  _shape = shape;
}

void GravityObject::setYVelocity(const float yVelocity) { _yVelocity = yVelocity; }
void GravityObject::setXVelocity(const float xVelocity) { _xVelocity = xVelocity; }

void GravityObject::setAcceleration(float value, int direction) {
  if (direction == UP) _yAcceleration = -value;
  else if (direction == DOWN) _yAcceleration = value;
  else if (direction == LEFT) _xAcceleration = -value;
  else if (direction == RIGHT) _xAcceleration = value;
  else // Bad input TODO: Throw exception
}
