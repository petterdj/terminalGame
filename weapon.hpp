#ifndef MYWEAPON
#define MYWEAPON
#include "gravityObject.hpp"
#include "iostream"

namespace terminalGame {
  class Weapon : public GravityObject {
    protected:
      int _damageValue;
      int _oldDamageValue;
      int _timer;
      bool _equipped;
      bool _hazardous;

    public:
      // CONSTRUCTORS //
      Weapon();
      Weapon(const int damageValue, const float y, const float x, 
        const std::string drawChar, const float elasticity=0.0, const int shape=RECTANGLE);
      Weapon(const Weapon&);
      Weapon(Weapon&&);

      // OPERATORS //
      Weapon& operator=(const Weapon&);
      Weapon& operator=(Weapon&&);

      // DESTRUCTOR //
      ~Weapon();

      // FUNCTIONS //
      int getDamageValue() const;
      int getTime() const;
      bool getEquipped() const;
      bool getHazardous() const;

      void setDamageValue(const int);
      void setTempDamageValue(const int damageValue, const int time);
      void restoreDamageValue();
      void countDownTimers(); // Overloading
      void setTimer(const int);
      void setEquipped(const bool, const float y=-1, const float x=-1);
      void setHazardous(const bool);

      void beginLightAttack(int facing, float y, float x);
      void endAttack();
      void performHeavyAttack(int attackTimer, int facing, float yPosition, float xPosition, bool inAir);
      void performLightAttack(int attackTimer, int facing, float yPosition, float xPosition);
  };
}

#endif
