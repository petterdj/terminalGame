#ifndef MYAICHARACTER
#define MYAICHARACTER
#include "character.hpp"
#include "ai.hpp"
#include <iostream>

namespace terminalGame {

class AICharacter : public Character {
  protected:
    AI* _ai;

  public:
    // CONSTRUCTORS //
    AICharacter();
    AICharacter(const float y, const float x, const std::string leftDrawChar, 
      const std::string rightDrawChar, const int facing, AI* const ai, 
      const float elasticity=0.0, const int shape=SPHERE);
    AICharacter(const AICharacter&);
    AICharacter(AICharacter&&);

    // OPERATORS //
    AICharacter& operator=(const AICharacter&);
    AICharacter& operator=(AICharacter&&);

    // DESTRUCTOR //
    ~AICharacter();

    // FUNCTIONS //
  };
}
#endif
