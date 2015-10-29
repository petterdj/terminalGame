#ifndef MYAI
#define MYAI
#include <vector>
#include <initializer_list>
#include "../aiCharacter.hpp"
#include "aStar.hpp"

namespace terminalGame {

class AI {
protected:
  float _reactionTime; // How often the AI may execute in the main loop
  std::vector<AICharacter *> _controlledCharacters;
  AStar _pathfinder;

public:
  // CONSTRUCTORS //
  AI();
  AI(float reactionTime, const std::initializer_list<AICharacter *>);

  AI(const AI&);
  AI(AI&&);

  // OPERATORS //
  AI& operator=(const AI&);
  AI& operator=(AI&&);

  // DESTRUCTOR //
  ~AI();

  // FUNCTIONS //
  float getReactionTime() const;
  std::vector<AICharacter *> getControlledCharacters() const;

  void setReactionTime(const float);
  void setControlledCharacterList(const std::initializer_list<AICharacter *>);
  void addControlledCharacter(AICharacter *);

  void control();
  bool playerInCharacterAggroRange(const AICharacter *) const;
};
}

#endif
