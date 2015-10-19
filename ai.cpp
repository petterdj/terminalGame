#include "ai.hpp"

using namespace terminalGame;

// CONSTRUCTORS //
  AI::AI() {
    _reactionTime = 1;
    // Vector default constructor is automatically called
  }

  AI::AI(float reactionTime, std::initializer_list<Character *> controlledCharacters) {
    _reactionTime = reactionTime < 0 ? 0 : reactionTime; // Reaction time cannot be less than 0
    _controlledCharacters = controlledCharacters;
  }

  AI::AI(const AI& o) {
    if (this == &o) return;
    _reactionTime = o._reactionTime;
  }

  AI::AI(AI&& o) {
    if (this == &o) return;
    _reactionTime = o._reactionTime;
    o._reactionTime = 0;
  }

// OPERATORS //
  AI& AI::operator=(const AI& o) {
    if (this == &o) return *this;
    _reactionTime = o._reactionTime;
    return *this;
  }

  AI& AI::operator=(AI&& o) {
    if (this == &o) return *this;
    _reactionTime = o._reactionTime;
    o._reactionTime = 0;
    return *this;
  }

// DESTRUCTOR //
  AI::~AI() {
    _reactionTime = 0;
  }

// FUNCTIONS //
  float AI::getReactionTime() const { return _reactionTime; }
  std::vector<Character *> AI::getControlledCharacters() const { return _controlledCharacters; }

  void AI::setReactionTime(const float reactionTime) { _reactionTime = reactionTime < 0 ? 0 : reactionTime; }
  void AI::setControlledCharacterList(const std::initializer_list<Character *> cList) { _controlledCharacters = cList; }
  void AI::addControlledCharacter(Character * character) { _controlledCharacters.push_back(character); }

  void AI::attack(const Character* opponent) {
    }


