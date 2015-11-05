#ifndef MYAICHARACTER
#define MYAICHARACTER
#include "character.hpp"
#include <iostream>

namespace terminalGame {

  class AICharacter : public Character {
    protected:
      float _aggroThreshold;
      //Path _path; // TODO Object or vector? It is basically an ordered set of instructions for reaching a specified point

    public:
      // CONSTRUCTORS //
      AICharacter();
      AICharacter(const float y, const float x, const std::string leftDrawChar, 
        const std::string rightDrawChar, const int facing, 
        const float aggroThreshold = 10.0, const float elasticity=0.0, 
        const int shape=SPHERE);
      AICharacter(const AICharacter&);
      AICharacter(AICharacter&&);

      // OPERATORS //
      AICharacter& operator=(const AICharacter&);
      AICharacter& operator=(AICharacter&&);

      // DESTRUCTOR //
      ~AICharacter();

      // FUNCTIONS //
      float getAggroThreshold() const;
      
     // void setPath(const Path);
  };
}
#endif
