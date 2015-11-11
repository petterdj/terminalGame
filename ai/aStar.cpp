#include "aStar.hpp"
#include <algorithm>
#include <ncurses.h>

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

int AStar::distanceToTarget(const Block* current, const Block* target) const {
  int cY = current->getYPosition(); int cX = current->getXPosition(); 
  int tY = target->getYPosition(); int tX = target->getXPosition();
  return abs(cY-tY) + abs(cX-tX);
}

int AStar::costToNext(const Block* next) const {
  return 1;
}

void AStar::addNext(Block* next, Block* current, Block* target, blockPriorityQueue& frontier, std::set<Block*>& visited, 
                    std::map<Block*, Block*>& cameFrom, std::map<Block*, int>& costSoFar) {
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
      int newCost = costSoFar[current] + costToNext(next);
      int priority = newCost + distanceToTarget(next, target);
      std::tuple<Block*, int> newFrontier(next, priority);
      frontier.push(newFrontier);
      cameFrom.emplace(next, current);
      costSoFar.emplace(next, newCost);
      mvprintw(next->getYPosition(), next->getXPosition(), "*");
    }
  }
}


std::vector<Block*> AStar::findPath(Block* origin, Block* target) {
  blockPriorityQueue frontier;
  std::set<Block*> visited;
  std::map<Block*, Block*> cameFrom;
  std::map<Block*, int> costSoFar;
  std::vector<Block*> path;
  Block* current;
  Block* next;
  int y;
  int x;
  
  if (!origin || !target) return path;
  
  std::tuple<Block*, int> originTuple(origin, 0);
  frontier.push(originTuple);
  visited.emplace(origin);
  cameFrom.emplace(origin, nullptr);
  costSoFar.emplace(origin, 0);

  while(!frontier.empty()) {
    current = std::get<0>(frontier.top()); frontier.pop();
    if (current == target) break;
    y = current->getYPosition();
    x = current->getXPosition();

    next = _map->getBlockAtPosition(y+ABOVE, x);
    addNext(next, current, target, frontier, visited, cameFrom, costSoFar);
    next = _map->getBlockAtPosition(y+BELOW, x);
    addNext(next, current, target, frontier, visited, cameFrom, costSoFar);
    next = _map->getBlockAtPosition(y, x+LEFT);
    addNext(next, current, target, frontier, visited, cameFrom, costSoFar);
    next = _map->getBlockAtPosition(y, x+RIGHT);
    addNext(next, current, target, frontier, visited, cameFrom, costSoFar);
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
