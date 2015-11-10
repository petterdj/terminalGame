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
}

AStar::AStar(AStar&& o) {
  if (this == &o) return;
  _map = o._map;
  _map = nullptr;
}

// OPERATORS //
AStar& AStar::operator=(const AStar& o) {
  if (this == &o) return *this;
  _map = o._map;
  return *this;
}

AStar& AStar::operator=(AStar&& o) {
  if (this == &o) return *this;
  _map = o._map;
  _map = nullptr;
  return *this;
}

// DESTRUCTOR //
AStar::~AStar() {
  _map = nullptr;
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

void AStar::addNext(Block* next, Block* current, blockPriorityQueue& frontier, std::set<Block*>& visited, std::map<Block*, Block*>& cameFrom) {
  if (next && visited.find(next) == visited.end()) {
    visited.emplace(next);
   
    bool accessible = false;
    if (!next->isFullyPassable()) {
      // If the next object is not fully passable, determine from which direction we're coming and see if it is passable from this direction
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
    if (accessible) {
      frontier.push(next);
      cameFrom.emplace(next, current);
    }
  }
}


std::vector<Block*> AStar::findPath(Block* origin, Block* target) {
  blockPriorityQueue frontier(target);
  std::set<Block*> visited;
  std::map<Block*, Block*> cameFrom;
  std::vector<Block*> path;
  Block* current;
  Block* next;
  int y;
  int x;
  
  if (!origin || !target) return path;
  
  frontier.push(origin);
  visited.emplace(origin);
  cameFrom.emplace(origin, nullptr);

  while(!frontier.empty()) {
    current = frontier.top(); frontier.pop();
    if (current == target) break;
    y = current->getYPosition();
    x = current->getXPosition();

    next = _map->getBlockAtPosition(y+ABOVE, x);
    addNext(next, current, frontier, visited, cameFrom);
    next = _map->getBlockAtPosition(y+BELOW, x);
    addNext(next, current, frontier, visited, cameFrom);
    next = _map->getBlockAtPosition(y, x+LEFT);
    addNext(next, current, frontier, visited, cameFrom);
    next = _map->getBlockAtPosition(y, x+RIGHT);
    addNext(next, current, frontier, visited, cameFrom);
  }

  if (visited.find(target) != visited.end()) {
    // Only finalize the path if the target was found
    current = target;
    path.push_back(current);
    while (current != origin) {
      current = cameFrom[current];
      path.push_back(current);
    }
    std::reverse(path.begin(), path.end());
  }
  return path;
}
