#ifndef GAMECONSTANTS
#define GAMECONSTANTS

// Direction and map constants
const int YOFFSET = 20;
const int XOFFSET = 20;
const int RIGHT = 1;
const int LEFT = -1;
const int UP = -2;
const int DOWN = 2;
const int ABOVE = -1;
const int BELOW = 1;

// Map size
const int HEIGHT = 21;
const int WIDTH = 81;

// Choice aliases
const int SPHERE = 0;

// Physics constants
const bool GRAVITY = true;
const bool TIMESTEP = 0.01;
const bool G = 9.8;
const float PI = 3.14;
const float AIRDENSITY = 1.225; // Air at 15deg C at sea level
const float SPHEREDRAGCOEFFICIENT = 0.47; // Drag coefficient for a sphere

#endif
