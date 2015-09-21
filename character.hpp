#ifndef MYCHARACTER
#define MYCHARACTER
#include "gravityObject.hpp"
#include "weapon.hpp"
#include <iostream>

namespace terminalGame {

  class Character : public GravityObject {
    protected:
      int _facing;
      int _heavyAttackTimer;
      int _lightAttackTimer;
      std::string _secondaryDrawChar; // Facing right
      Weapon* _equippedWeapon;
      
    public:
      // CONSTRUCTORS //
      Character();
      Character(const float y, const float x, const std::string leftDrawChar, 
        const std::string rightDrawChar, const int facing, 
        const float elasticity=0.0, const int shape=SPHERE);
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
      virtual Weapon* getEquippedWeapon() const;
      virtual void drop(GravityObject*);
      virtual void equip(Weapon*);

      virtual std::string getDrawChar() const; // Overloading
      virtual void heavyAttack();
      virtual void lightAttack();
      virtual void countDownTimers(); // Overloading
      virtual void move(int direction);
  };
}
#endif
