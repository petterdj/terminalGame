#ifndef MYGRAVOBJECT
#define MYGRAVOBJECT
#include "object.hpp"
#include "utils/constants.h"

namespace terminalGame {
  class GravityObject : public Object {
    protected:
      float _elasticity;
      int _shape;
      float _yVelocity;
      float _xVelocity;
      float _yAcceleration;
      float _xAcceleration;
      float _terminalVelocity;
      bool _inAir;
    public:
      // CONSTRUCTORS //
      GravityObject();
      GravityObject(const float y, const float x, const std::string drawChar, const float elasticity=0.0, const int shape=SPHERE);
      GravityObject(const GravityObject&);
      GravityObject(GravityObject&&);
     
      // OPERATORS //
      GravityObject& operator=(const GravityObject&);
      GravityObject& operator=(GravityObject&&);

      // DESTRUCTOR //
      ~GravityObject();

      // FUNCTIONS //
      float getElasticity() const;
      int getShape() const;
      float getYVelocity() const;
      float getXVelocity() const;
      float getYAcceleration() const;
      float getXAcceleration() const;
      float getTerminalVelocity() const;
      bool inAir() const;

      void setElasticity(const float);
      void setShape(const int);
      void setYVelocity(const float);
      void setXVelocity(const float);
      int setAcceleration(const float, const int direction=UP);
      void setInAir(const bool);
      virtual void countDownTimers() = 0;
  };
}

#endif
