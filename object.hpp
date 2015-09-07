#ifndef MYOBJECT
#define MYOBJECT
#include <iostream>

namespace terminalGame {
  
  class Object {
    protected:
      float _yPosition;
      float _xPosition;
      string _drawChar;

    public:
      // CONSTRUCTORS //
      Object();
      Object(const float, const float, const string);
      Object(const Object&);
      Object(Object&&);

      // OPERATORS //
      Object& operator=(const Object&);
      Object& operator=(Object&&);

      // DESTRUCTOR //
      virtual ~Object();

      // FUNCTIONS //
      virtual float getYPosition() const;
      virtual float getXPosition() const;
      virtual string getDrawChar() const;
      virtual void setYPosition(const float);
      virtual void setXPosition(const float);
      virtual void setDrawChar(const string);
  }
}

#endif
