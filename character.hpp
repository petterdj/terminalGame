#ifndef MYCHARACTER
#define MYCHARACTER
#include "object.hpp"
#include <iostream>

namespace terminalGame {

  class Character : public Object {
    protected:
      int _facing;

    public:
      // CONSTRUCTORS //
      Character();
      Character(const float, const float, const std::string, const int);
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
  };
}
#endif
