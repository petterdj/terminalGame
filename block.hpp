#ifndef MYBLOCK
#define MYBLOCK

namespace terminalGame {

  class Block : public Object {
    private:
      bool _fullyPassable;
      bool _passableFromLeft;
      bool _passableFromRight;
      bool _passableFromBelow;
      bool _passableFromAbove;
      bool _passableFromAboveKeyDown;

    public:
      // CONSTRUCTORS //
      Block();
      Block(const bool, const bool, const bool, const bool, const bool, const bool=false);
      Block(const Block&);
      Block(Block&&);

      // OPERATORS //
      Block& operator=(const Block&);
      Block& operator=(Block&&);

      // DESTRUCTOR //
      ~Block();

      // FUNCTIONS //
      const bool getFullyPassable() const;
      const bool getPlatformPassable() const;
      const bool getPassableFromSides() const;
      const bool getPassableFromLeft() const;
      const bool getPassableFromRight() const;
      const bool getPassableFromBelow() const;
      const bool getPassableFromAbove() const;
      const bool getPassableFromAboveKeyDown() const;

      void setFullyPassable(const bool);
      void setPlatformPassable(const bool);
      void setPassableFromSides(const bool); 
      void setPassableFromLeft(const bool);
      void setPassableFromRight(const bool);
      void setPassableFromBelow(const bool);
      void setPassableFromAboveKeyDown(const bool);
  }
}

#endif
