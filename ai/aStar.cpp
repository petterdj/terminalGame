#include "aStar.hpp"
#include <algorithm>

using namespace terminalGame;

// CONSTRUCTORS //
AStar::AStar() {
  _map = nullptr;
  _originY = 0;
  _originX = 0;
  _targetY = 0;
  _targetX = 0;
}

AStar::AStar(Level* map, int originY, int originX, int targetY, int targetX) {
  _map = map;
  _originY = originY;
  _originX = originX;
  _targetY = targetY;
  _targetX = targetX;
}

AStar::AStar(const AStar& o) {
  if (this == &o) return;
  _map = o._map;
  _originY = o._originY;
  _originX = o._originX;
  _targetY = o._targetY;
  _targetX = o._targetX;
  _frontier = o._frontier;
  _visited = o._visited;
}

AStar::AStar(AStar&& o) {
  if (this == &o) return;
  _map = o._map;
  _originY = o._originY;
  _originX = o._originX;
  _targetY = o._targetY;
  _targetX = o._targetX;
  _frontier = o._frontier;
  _visited = o._visited;
  _map = nullptr;
  o._originY = 0;
  o._originX = 0;
  o._targetY = 0;
  o._targetX = 0;
  std::queue<Block*> q;
  std::swap(o._frontier, q);
  o._visited.clear();
}

// OPERATORS //
AStar& AStar::operator=(const AStar& o) {
  if (this == &o) return *this;
  _map = o._map;
  _originY = o._originY;
  _originX = o._originX;
  _targetY = o._targetY;
  _targetX = o._targetX;
  _frontier = o._frontier;
  _visited = o._visited;
  return *this;
}

AStar& AStar::operator=(AStar&& o) {
  if (this == &o) return *this;
  _map = o._map;
  _originY = o._originY;
  _originX = o._originX;
  _targetY = o._targetY;
  _targetX = o._targetX;
  _frontier = o._frontier;
  _visited = o._visited;
  _map = nullptr;
  o._originY = 0;
  o._originX = 0;
  o._targetY = 0;
  o._targetX = 0;
  std::queue<Block*> q;
  std::swap(o._frontier, q);
  o._visited.clear();
  return *this;
}

// DESTRUCTOR //
AStar::~AStar() {
  _map = nullptr;
  _originY = 0;
  _originX = 0;
  _targetY = 0;
  _targetX = 0;
  std::queue<Block*> q;
  std::swap(_frontier, q);
  _visited.clear();
}

// FUNCTIONS //

