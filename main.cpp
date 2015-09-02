#include <iostream>
#include <stdio.h>
#include <math.h>
#include <ncurses.h>
#include <unistd.h>
#include <boost/lexical_cast.hpp>

float _terminalVelocity = 0;
float _timestep = 0.01;
float _g = -9.8;
float _pi = 3.14;

float _yPosition = 20;
float _xPosition = 0;
float _yVelocity = 0;
float _xVelocity = 0;


float newVelocity(float velocity, float acceleration) {
  velocity = velocity + acceleration * _timestep;
  if (fabs(velocity) >= _terminalVelocity) return _terminalVelocity;
  return velocity;
}

void upkey() {
  if (_yPosition == 0) {
    _yVelocity = 10;
  }
}

void downkey() {
  // Nothing yet
}

void rightkey() {
  _xVelocity = -30;
}

void leftkey() {
  _xVelocity = 30;
}

void nokey() {
  _xVelocity = 0;
}

void keyboardControl(int inputKey) {
  switch (inputKey) {
    case 65: // Up
      upkey();
      break;
    case 66: // Down
      downkey();
      break;
    case 67: // Right
      rightkey();
      break;
    case 68: // Left
      leftkey();
      break;
    default:
      nokey();
  }
}

int main(int argc, char *argv[]) {
  initscr();
  noecho();
  curs_set(FALSE);
  raw();

  float time = 0;

  float yAcceleration = 0;
  float xAcceleration = 0;

  float radius = 1;
  float mass = 10;
  float elasticity = 0.5;
  
  float fluidDensity = 1.225; // Air at 15deg C at sea level
  float projectedObjectArea = _pi*pow(radius, 2.0); // Sphere with r=1
  float dragCoefficient = 0.47; // Drag coefficient for a sphere
  float terminalVelocitySquared = ((2.0*mass*_g)/(fluidDensity*projectedObjectArea*dragCoefficient));
  
  int inputKey;

  _terminalVelocity = sqrt(terminalVelocitySquared);

  while(true) {
    clear();
    mvprintw(21, 0, "###################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################################");
    mvprintw(-_yPosition+20, -_xPosition+20, "o");
    mvprintw(0, 0, boost::lexical_cast<std::string>(inputKey).c_str());
    timeout(10);
    inputKey = getch();
    if (inputKey == 50) break;
    keyboardControl(inputKey);
    refresh();


    usleep(3000);

    _yVelocity = newVelocity(_yVelocity, _g + yAcceleration);
    _xVelocity = newVelocity(_xVelocity, xAcceleration); 
    _yPosition = _yPosition + _yVelocity * _timestep;
    _xPosition = _xPosition + _xVelocity * _timestep;
    
    if (_yPosition <= 0) {
      _yPosition = 0;
      _yVelocity = -elasticity*_yVelocity;
    }
 
    time += _timestep; 
  }

  endwin();
}

