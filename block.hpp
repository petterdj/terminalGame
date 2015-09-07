#ifndef MYBLOCK
#define MYBLOCK
#include "object.hpp"
#include <iostream>

namespace terminalGame {

  class Block : public Object {
    private:
      bool _passableFromLeft;
      bool _passableFromRight;
      bool _passableFromBelow;
      bool _passableFromAbove;
      bool _passableFromAboveKeyDown;

    public:
      // CONSTRUCTORS //
      Block();
      Block(const int, const int, const bool, const bool, const bool, const bool, const bool, const std::string);
      Block(const Block&);
      Block(Block&&);

      // OPERATORS //
      Block& operator=(const Block&);
      Block& operator=(Block&&);

      // DESTRUCTOR //
      ~Block();

      // FUNCTIONS //
      bool getPassableFromLeft() const;
      bool getPassableFromRight() const;
      bool getPassableFromBelow() const;
      bool getPassableFromAbove() const;
      bool getPassableFromAboveKeyDown() const;
      bool getPassableFromSides() const;
      bool getPlatformPassable() const;
      bool getFullyPassable() const;

      void setPlatformPassable();
      void setPassableFromLeft(const bool);
      void setPassableFromRight(const bool);
      void setPassableFromBelow(const bool);
      void setPassableFromAbove(const bool);
      void setPassableFromAboveKeyDown(const bool);
      void setPassableFromSides(const bool); 
      void setFullyPassable(const bool);
  };
}

#endif
