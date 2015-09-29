#include "aiCharacter.hpp"

using namespace terminalGame;

// CONSTRUCTORS //
AICharacter::AICharacter() :
  Character() {
  _ai = nullptr;
}


AICharacter::AICharacter(const float y, const float x, const std::string leftDrawChar, std::string rightDrawChar, const int facing, AI* const ai, const float elasticity, const int shape) :
  Character(y, x, leftDrawChar, rightDrawChar, facing, elasticity, shape) {
  _ai = ai;
}

AICharacter::AICharacter(const AICharacter& o) :
  Character(o) {
  if (this == &o) return;
  _ai = o._ai;
}

AICharacter::AICharacter(AICharacter&& o) :
  Character(o) {
  if (this == &o) return;
  _ai = o._ai;
  o._ai = nullptr;
}

// OPERATORS //
AICharacter& AICharacter::operator=(const AICharacter& o) {
  if (this == &o) return *this;
  Character::operator=(o);
  _ai = o._ai;
  return *this;
}

AICharacter& AICharacter::operator=(AICharacter&& o) {
  if (this == &o) return *this;
  _ai = o._ai;
  o._ai = nullptr;
  return *this;
}

// DESTRUCTOR //
AICharacter::~AICharacter() {
  _ai = nullptr;
}

