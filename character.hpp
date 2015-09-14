#ifndef MYCHARACTER
#define MYCHARACTER
#include "gravityObject.hpp"
#include <iostream>

namespace terminalGame {

  class Character : public GravityObject {
    protected:
      int _facing;
      std::string _secondaryDrawChar; // Facing right

    public:
      // CONSTRUCTORS //
      Character();
      Character(const float, const float, const std::string, const std::string, const int, const float elasticity=0.0, const int shape=SPHERE);
      Character(const Character&);
      Character(Character&&);

      // OPERATORS //
      Character& operator=(const Character&);
      Character& operator=(Character&&);

      // DESTRUCTOR //
      ~Character();

      // FUNCTIONS //
      virtual int getFacing() const;
      virtual void setFacing(const int);

      virtual std::string getDrawChar() const; // Overloading
  };
}
#endif
