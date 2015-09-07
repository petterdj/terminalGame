#ifndef MYPHYSICS
#define MYPHYSICS
#include <math.h>
#include "constants.h"

float pi = 3.14;
float g = 9.8;
float elasticity = 0;
float dragCoefficient = 0.47; // Drag coefficient for a sphere
float fluidDensity = 1.225; // Air at 15deg C at sea level

float newVelocity(float velocity, float acceleration, float timestep, float terminalVelocity, bool gravity = false) {
  if (gravity) acceleration = acceleration + g;
  velocity = velocity + acceleration * timestep;
  
  if (fabs(velocity) >= terminalVelocity) {
    if (velocity < 0) return -terminalVelocity;
    return terminalVelocity;
  }
  return velocity;
}

float projectedObjectArea(int shape = SPHERE, float radius = 1) {
  if (shape == SPHERE) return pi*pow(radius, 2.0); // Sphere
  return 0;
}

float terminalVelocity(float mass = 10, int shape = SPHERE, float radius = 1){
  return sqrt(((2.0*mass*g)/(fluidDensity*projectedObjectArea()*dragCoefficient)));
}
#endif
