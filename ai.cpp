#include "ai.hpp"

using namespace terminalGame;

// CONSTRUCTORS //
  AI::AI() {
    _reactionTime = 1;
  }

  AI::AI(float reactionTime) {
    _reactionTime = reactionTime < 0 ? 0 : reactionTime;
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

  void AI::setReactionTime(const float reactionTime) { _reactionTime = reactionTime < 0 ? 0 : reactionTime; }

  

