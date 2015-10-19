#include "ai.hpp"
#include <math.h>

using namespace terminalGame;

// CONSTRUCTORS //
  AI::AI() {
    _reactionTime = 1;
    // Vector default constructor is automatically called
  }

  AI::AI(float reactionTime, std::initializer_list<AICharacter *> controlledCharacters) {
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
  std::vector<AICharacter *> AI::getControlledCharacters() const { return _controlledCharacters; }

  void AI::setReactionTime(const float reactionTime) { _reactionTime = reactionTime < 0 ? 0 : reactionTime; }
  void AI::setControlledCharacterList(const std::initializer_list<AICharacter *> cList) { _controlledCharacters = cList; }
  void AI::addControlledCharacter(AICharacter * character) { _controlledCharacters.push_back(character); }

  void AI::control() {
    for (auto &c : _controlledCharacters) {
      if (playerInCharacterAggroRange(c)) {
        c->setPath(findPathForCharacterToPlayer(c));
      }
    }
  }

  bool AI::playerInCharacterAggroRange(const AICharacter* c) const {
    float characterY = c->getYPosition();
    float characterX = c->getXPosition();
    float playerY = 10; // Placeholder
    float playerX = 10; // Placeholder
    
    float dY = characterY - playerY;
    float dX = characterX - playerX;
    float distance = sqrt(pow(dY, 2.0) + pow(dX, 2.0));

    return distance < c->getAggroThreshold();
  }

  Path AI::findPathForCharacterToPlayer(const AICharacter * c) const {
    Path p;
    return p;
  }

