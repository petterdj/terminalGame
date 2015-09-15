#ifndef MYPHYSICS
#define MYPHYSICS
#include <math.h>
#include "constants.h"

inline float newVelocity(float velocity, float acceleration, float terminalVelocity, bool gravity = false) {
  if (gravity) acceleration = acceleration + G;
  velocity = velocity + acceleration * TIMESTEP;
  
  if (fabs(velocity) >= terminalVelocity) {
    if (velocity < 0) return -terminalVelocity;
    return terminalVelocity;
  }
  return velocity;
}

inline float newPosition(float position, float velocity) {
  return position + velocity * TIMESTEP;
}

inline float projectedObjectArea(int shape = SPHERE, float radius = 1) {
  if (shape == SPHERE) return PI*pow(radius, 2.0); // Sphere
  return 0;
}

inline float terminalVelocity(int shape = SPHERE, float mass = 10, float radius = 1, float fluidDensity = AIRDENSITY, float dragCoefficient = SPHEREDRAGCOEFFICIENT) {
  return sqrt(((2.0*mass*G)/(fluidDensity*projectedObjectArea(shape, radius)*dragCoefficient)));
}

inline float bounce(float velocity, float elasticity) {
  return -elasticity*velocity;
}

#endif
