#include "aStar.hpp"
#include <algorithm>

using namespace terminalGame;

// CONSTRUCTORS //
AStar::AStar() {
  _map = nullptr;
}

AStar::AStar(Level* map) {
  _map = map;
}

AStar::AStar(const AStar& o) {
  if (this == &o) return;
  _map = o._map;
  _frontier = o._frontier;
  _visited = o._visited;
  _cameFrom = o._cameFrom;
}

AStar::AStar(AStar&& o) {
  if (this == &o) return;
  _map = o._map;
  _frontier = o._frontier;
  _visited = o._visited;
  _cameFrom = o._cameFrom;
  _map = nullptr;
  std::queue<Block*> q;
  std::swap(o._frontier, q);
  o._visited.clear();
  o._cameFrom.clear();
}

// OPERATORS //
AStar& AStar::operator=(const AStar& o) {
  if (this == &o) return *this;
  _map = o._map;
  _frontier = o._frontier;
  _visited = o._visited;
  _cameFrom = o._cameFrom;
  return *this;
}

AStar& AStar::operator=(AStar&& o) {
  if (this == &o) return *this;
  _map = o._map;
  _frontier = o._frontier;
  _visited = o._visited;
  _cameFrom = o._cameFrom;
  _map = nullptr;
  std::queue<Block*> q;
  std::swap(o._frontier, q);
  o._visited.clear();
  o._cameFrom.clear();
  return *this;
}

// DESTRUCTOR //
AStar::~AStar() {
  _map = nullptr;
  std::queue<Block*> q;
  std::swap(_frontier, q);
  _visited.clear();
  _cameFrom.clear();
}

// FUNCTIONS //

int AStar::direction(Block* next, Block* current) {
  int nY = next->getYPosition();
  int nX = next->getXPosition();
  int cY = current->getYPosition();
  int cX = current->getXPosition();
  if (nY < cY) return UP;
  if (nY > cY) return DOWN;
  if (nX < cX) return LEFT;
  if (nX > cX) return RIGHT;
  return 0;
}

void AStar::addNext(Block* next, Block* current) {
  if (next && _visited.find(next) == _visited.end()) {
    _visited.emplace(next);
    _cameFrom.emplace(next, current);
   
    bool accessible = false;
    if (!next->isFullyPassable()) {
      switch(direction(next, current)) {
        case UP:
          if (next->isPassableFromBelow()) accessible = true;
          break;
        case DOWN:
          if (next->isPassableFromAbove() || next->isPassableFromAboveKeyDown()) accessible = true;
          break;
        case LEFT:
          if (next->isPassableFromLeft()) accessible = true;
          break;
        case RIGHT:
          if (next->isPassableFromRight()) accessible = true;
        default:
          break;
      }
    }
    if (accessible) _frontier.push(next);
  }
}

std::vector<Block*> AStar::findPath(Block* origin, Block* target) {
  _frontier.push(origin);
  _visited.emplace(origin);
  _cameFrom.emplace(origin, nullptr);
  std::vector<Block*> path;
  Block* current;
  Block* next;
  int y;
  int x;

  if (!origin || !target) return path;

  while(!_frontier.empty()) {
    current = _frontier.front(); _frontier.pop();
    if (current == target) break;
    y = current->getYPosition();
    x = current->getXPosition();

    next = _map->getBlockAtPosition(y+ABOVE, x);
    addNext(next, current);
    next = _map->getBlockAtPosition(y+BELOW, x);
    addNext(next, current);
    next = _map->getBlockAtPosition(y, x+LEFT);
    addNext(next, current);
    next = _map->getBlockAtPosition(y, x+RIGHT);
    addNext(next, current);
  }

  current = target;
  path.push_back(current);
  while (current != origin) {
    current = _cameFrom[current];
    path.push_back(current);
  }
  std::reverse(path.begin(), path.end());

  return path;
}
