#include "ai.hpp"

using namespace terminalGame;

// CONSTRUCTORS //
  AI::AI() {
    _reactionTime = 1;
  }

  AI::AI(const AI& o) {
    if (this == &o) return;
  }

  AI::AI(AI&& o) {
    if (this == &o) return;
  }

// OPERATORS //
  AI& AI::operator=(const AI& o) {
    if (this == &o) return *this;
    return *this;
  }

  AI& AI::operator=(AI&& o) {
    if (this == &o) return *this;
    return *this;
  }

// DESTRUCTOR //
  AI::~AI() {}

// FUNCTIONS //
