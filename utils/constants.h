#ifndef GAMECONSTANTS
#define GAMECONSTANTS

// Direction and map constants
const int RIGHT = 1;
const int LEFT = -1;
const int UP = -2;
const int DOWN = 2;
const int ABOVE = -1;
const int BELOW = 1;
const float RIGHTOFFSET = 0.8; // For collisions to the right
const float LEFTOFFSET = 0.2; // -||- to the left
const float DOWNOFFSET = 0.1; // -||- downwards

// Map size
const int HEIGHT = 21;
const int WIDTH = 81;

// Choice aliases
const int SPHERE = 0;
const int RECTANGLE = 1;

// Physics constants
const bool GRAVITY = true;
const float TIMESTEP = 0.01;
const float G = 9.8;
const float PI = 3.14;
const float AIRDENSITY = 1.225; // Air at 15deg C at sea level
const float SPHEREDRAGCOEFFICIENT = 0.47; // Drag coefficient for a sphere
const float RECTANGLEDRAGCOEFFICIENT = 1.28; // -||- rectangle
const float MOVEMENTACCELERATION = 100;
const float DECELERATIONRIGHT = 5;
const float DECELERATIONLEFT = -5;

// AI constants
const int ATTACK = 0;
const int SURVIVE = 1;
const int MAXJUMPHEIGHT = 10;
#endif
