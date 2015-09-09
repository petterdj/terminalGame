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
      Block(const int, const int, const std::string drawChar="#", const bool fromLeft=false, const bool fromRight=false, const bool fromBelow=false, const bool fromAbove=false, const bool fromAboveKeyDown=false);
      Block(const Block&);
      Block(Block&&);

      // OPERATORS //
      Block& operator=(const Block&);
      Block& operator=(Block&&);

      // DESTRUCTOR //
      ~Block();

      // FUNCTIONS //
      bool isPassableFromLeft() const;
      bool isPassableFromRight() const;
      bool isPassableFromBelow() const;
      bool isPassableFromAbove() const;
      bool isPassableFromAboveKeyDown() const;
      bool isPassableFromSides() const;
      bool isPlatformPassable() const;
      bool isFullyPassable() const;

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
