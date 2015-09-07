#include "object.hpp"

using namespace terminalGame;

// CONSTRUCTORS //
Object::Object() {
  _yPosition = 0;
  _xPosition = 0;
  _drawChar = " ";
}

Object::Object(const float y, const float x, const string drawChar) :
  _yPosition(y);
  _xPosition(x);
  _drawChar(drawChar) {}

Object::Object(const Object& o) {
  if (this == &o) return;
  _yPosition = o._yPosition;
  _xPosition = o._xPosition;
  _drawChar = o._drawChar;
}

Object::Object(Object&& o) :
  _yPosition(o._yPosition),
  _xPosition(o._xPosition),
  _drawChar(o._drawChar) {
  o._yPosition = 0;
  o._xPosition = 0;
  o._drawChar = "";
}

// OPERATORS //
Object& Object::operator=(const Object& o) {
  if (this == &o) return *this;
  _yPosition = o._yPosition;
  _xPosition = o._xPosition;
  _drawChar = o._drawChar;
  return this;
}

Object& Object::operator=(Object&& o) {
  if (this == &o) return *this;
  _yPosition = o._yPosition;
  _xPosition = o._xPosition;
  _drawChar = o._drawChar;
  
  o._yPosition = 0;
  o._xPosition = 0;
  o._drawChar = "";
}

// DESTRUCTOR //
Object::~Object() {
  _yPosition = 0;
  _xPosition = 0;
  _drawChar = "";
}

// FUNCTIONS //
float Object::getYPosition() const {
  return _yPosition;
}

float Object::getXPosition() const {
  return _xPosition;
}

float Object::getDrawChar() const {
  return _drawChar;
}

void Object::setYPosition(const float y) {
  _yPosition = y;
}

void Object::setXPosition(const float x) {
  _xPosition = x;
}

void Object::setDrawChar(const string drawChar) {
  _drawChar = drawChar;
}
