#include "aiCharacter.hpp"

using namespace terminalGame;

// CONSTRUCTORS //
AICharacter::AICharacter() :
  Character() {
    _aggroThreshold = 0;
    //_path; // TODO Object or vector? It is basically an ordered set of instructions for reaching a specified point
}


AICharacter::AICharacter(const float y, const float x, const std::string leftDrawChar, 
                         std::string rightDrawChar, const int facing, const float aggroThreshold,
                         const float elasticity, const int shape) :
  Character(y, x, leftDrawChar, rightDrawChar, facing, elasticity, shape) {
  _aggroThreshold = aggroThreshold;
}

AICharacter::AICharacter(const AICharacter& o) :
  Character(o) {
  if (this == &o) return;
  _aggroThreshold = o._aggroThreshold;
}

AICharacter::AICharacter(AICharacter&& o) :
  Character(o) {
  if (this == &o) return;
  _aggroThreshold = o._aggroThreshold;
  o._aggroThreshold = 0;
}

// OPERATORS //
AICharacter& AICharacter::operator=(const AICharacter& o) {
  if (this == &o) return *this;
  Character::operator=(o);
  _aggroThreshold = o._aggroThreshold;
  return *this;
}

AICharacter& AICharacter::operator=(AICharacter&& o) {
  if (this == &o) return *this;
  Character::operator=(o);
  _aggroThreshold = o._aggroThreshold;
  o._aggroThreshold = 0;
  return *this;
}

// DESTRUCTOR //
AICharacter::~AICharacter() {
  _aggroThreshold = 0;
}

// FUNCTIONS //
float AICharacter::getAggroThreshold() const { return _aggroThreshold; }

//void AICharacter::setPath(Path p) { _path = p; }

