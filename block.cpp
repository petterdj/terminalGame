#include "block.hpp"

using namespace terminalGame;

// CONSTRUCTORS //
Block::Block() : 
  Object() {
  _passableFromLeft = false;
  _passableFromRight = false;
  _passableFromBelow = false;
  _passableFromAbove = false;
  _passableFromAboveKeyDown = false;
}

Block::Block(const int y, const int x, const std::string drawChar, const bool fromAboveKeyDown, const bool fromLeft, const bool fromRight, const bool fromBelow, const bool fromAbove) : 
  Object(y, x, drawChar) {
  _passableFromLeft = fromLeft;
  _passableFromRight = fromRight;
  _passableFromBelow = fromBelow;
  _passableFromAbove = fromAbove;
  _passableFromAboveKeyDown = fromAboveKeyDown;
}

Block::Block(const Block& o) : 
  Object(o) {
  if (this == &o) return;
  _passableFromLeft = o._passableFromLeft;
  _passableFromRight = o._passableFromRight;
  _passableFromBelow = o._passableFromBelow;
  _passableFromAbove = o._passableFromAbove;
  _passableFromAboveKeyDown = o._passableFromAboveKeyDown;
}

Block::Block(Block&& o) : 
  Object(o) {
  _passableFromLeft = o._passableFromLeft;
  _passableFromRight = o._passableFromRight;
  _passableFromBelow = o._passableFromBelow;
  _passableFromAbove = o._passableFromAbove;
  _passableFromAboveKeyDown = o._passableFromAboveKeyDown;
  o._passableFromLeft = false;
  o._passableFromRight = false;
  o._passableFromBelow = false;
  o._passableFromAbove = false;
  o._passableFromAboveKeyDown = false;
}

// OPERATORS //
Block& Block::operator=(const Block& o) {
  if (this == &o) return *this;
  Object::operator=(o);
  _passableFromLeft = o._passableFromLeft;
  _passableFromRight = o._passableFromRight;
  _passableFromBelow = o._passableFromBelow;
  _passableFromAbove = o._passableFromAbove;
  _passableFromAboveKeyDown = o._passableFromAboveKeyDown;
  return *this;
}

Block& Block::operator=(Block&& o) {
  if (this == &o) return *this;
  Object::operator=(o);
  _passableFromLeft = o._passableFromLeft;
  _passableFromRight = o._passableFromRight;
  _passableFromBelow = o._passableFromBelow;
  _passableFromAbove = o._passableFromAbove;
  _passableFromAboveKeyDown = o._passableFromAboveKeyDown;
  o._passableFromLeft = false;
  o._passableFromRight = false;
  o._passableFromBelow = false;
  o._passableFromAbove = false;
  o._passableFromAboveKeyDown = false;
  return *this;
}


// DESTRUCTOR //
Block::~Block() {
  _passableFromLeft = false;
  _passableFromRight = false;
  _passableFromBelow = false;
  _passableFromAbove = false;
  _passableFromAboveKeyDown = false;
}

// FUNCTIONS //
bool Block::isPassableFromLeft() const {
  return _passableFromLeft;
}

bool Block::isPassableFromRight() const {
  return _passableFromRight;
}

bool Block::isPassableFromBelow() const {
  return _passableFromBelow;
}

bool Block::isPassableFromAbove() const {
  return _passableFromAbove;
}

bool Block::isPassableFromAboveKeyDown() const {
  return _passableFromAboveKeyDown;
}

bool Block::isPassableFromSides() const {
  return _passableFromLeft && _passableFromRight;
}

bool Block::isPlatformPassable() const {
  return isPassableFromAboveKeyDown() && isPassableFromSides() && isPassableFromBelow() && !isPassableFromAbove();
}

bool Block::isFullyPassable() const {
  return isPassableFromSides() && isPassableFromAbove() && isPassableFromAboveKeyDown() && isPassableFromBelow();
}

bool Block::isPassable() const {
  return isPassableFromSides() || isPassableFromAbove() || isPassableFromAboveKeyDown() || isPassableFromBelow();
}

void Block::setPassableFromLeft(const bool passable) {
  _passableFromLeft = passable;
}

void Block::setPassableFromRight(const bool passable) {
  _passableFromRight = passable;
}

void Block::setPassableFromBelow(const bool passable) {
  _passableFromBelow = passable;
}

void Block::setPassableFromAbove(const bool passable) {
  _passableFromAbove = passable;
}

void Block::setPassableFromAboveKeyDown(const bool passable) {
  _passableFromAboveKeyDown = passable;
}

void Block::setPassableFromSides(const bool passable) { 
  setPassableFromLeft(passable);
  setPassableFromRight(passable);
}

void Block::setPlatformPassable() {
  setPassableFromSides(true);
  setPassableFromBelow(true);
  setPassableFromAbove(false);
  setPassableFromAboveKeyDown(true);
}

void Block::setFullyPassable(const bool passable) {
  setPassableFromSides(passable);
  setPassableFromBelow(passable);
  setPassableFromAbove(passable);
  setPassableFromAboveKeyDown(false);
}

