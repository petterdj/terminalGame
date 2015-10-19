#ifndef MYAI
#define MYAI
#include <vector>
#include <initializer_list>
#include "character.hpp"
namespace terminalGame {

class AI {
protected:
  float _reactionTime; // How often the AI may execute in the main loop
  std::vector<Character *> _controlledCharacters;

public:
  // CONSTRUCTORS //
  AI();
  AI(float reactionTime, const std::initializer_list<Character *>);

  AI(const AI&);
  AI(AI&&);

  // OPERATORS //
  AI& operator=(const AI&);
  AI& operator=(AI&&);

  // DESTRUCTOR //
  ~AI();

  // FUNCTIONS //
  float getReactionTime() const;
  std::vector<Character *> getControlledCharacters() const;

  void setReactionTime(const float);
  void setControlledCharacterList(const std::initializer_list<Character *>);
  void addControlledCharacter(Character *);

  void attack(const Character*);

};
}

#endif
