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
//int AStar::direction(const Block* next, const Block* current) const {
int AStar::direction(const Node& next, const Node& current) const {
  //int nY = next->getYPosition();
  //int nX = next->getXPosition();
  //int cY = current->getYPosition();
  //int cX = current->getXPosition();
  if (next.y < current.y) return UP;
  if (next.y > current.y) return DOWN;
  if (next.x < current.x) return LEFT;
  if (next.x > current.x) return RIGHT;
  return 0;
}

//int AStar::distanceToTarget(const Block* current, const Block* target) const {
int AStar::distanceToTarget(const Node current, const Node target) const {
  //int cY = current->getYPosition(); int cX = current->getXPosition(); 
  //int tY = target->getYPosition(); int tX = target->getXPosition();
  //return abs(cY-tY) + abs(cX-tX);
  return abs(current.y-target.y) + abs(current.x-target.x);
}

//int AStar::costToNext(const Block* next) const {
int AStar::costToNext(const Node& next) const {
  return 1;
}

bool AStar::accessibleFromCurrent(const Node& next, const Node& current) const {
  Block* nextBlock = _map->getBlockAtPosition(next.y, next.x);
  // Determine from which direction we're coming and see if it is passable from this direction, and if it is possible to keep going up
  switch(direction(next, current)) {
    case UP:
      if (next.z <= MAXJUMPHEIGHT && nextBlock->isPassableFromBelow()) return true;
    case DOWN:
      if (nextBlock->isPassableFromAbove() || nextBlock->isPassableFromAboveKeyDown()) return true;
    case LEFT:
      if (nextBlock->isPassableFromLeft()) return true;
    case RIGHT:
      if (nextBlock->isPassableFromRight()) return true;
    default:
      return false;
  }
}

//void AStar::addNext(Block* next, Block* current, Block* target, blockPriorityQueue& frontier, std::set<Block*>& visited, 
//                    std::map<Block*, Block*>& cameFrom, std::map<Block*, int>& costSoFar) {
void AStar::addNext(Node& next, Node& current, Node& target, nodePriorityQueue& frontier, std::set<Node>& visited, 
                    std::map<Node, Node>& cameFrom, std::map<Node, int>& costSoFar) {
  if (visited.find(next) == visited.end()) {
    visited.emplace(next);
    //visitedNodes.emplace(next->getYPosition(), next->getXPosition(), 0);
    if (accessibleFromCurrent(next, current)) {
      int newCost = costSoFar[current] + costToNext(next);
      int priority = newCost + distanceToTarget(next, target);
      //std::tuple<Block*, int> newFrontier(next, priority);
      std::tuple<Node, int> newFrontier(next, priority);
      frontier.push(newFrontier);
      cameFrom.emplace(next, current);
      costSoFar.emplace(next, newCost);
      mvprintw(next.y, next.x, "*"); // For debugging or optimization
    }
  }
}

std::vector<Block*> AStar::findPath(Block* origin, Block* target) {
  nodePriorityQueue frontier;
  //std::set<Block*> visited;
  std::set<Node> visited;
  //std::map<Block*, Block*> cameFrom;
  //std::map<Block*, int> costSoFar;
  std::vector<Block*> path;
  std::map<Node, Node> cameFrom;
  std::map<Node, int> costSoFar;
  //Block* current;
  Node current;
  //Block* next;
  Node next;
  Block* nextBlock;
  int y;
  int x;
  
  if (!origin || !target || !target->isPassable() || !origin->isPassable()) return path;
  Node originNode(origin->getYPosition(), origin->getXPosition(), 0);
  Node targetNode(target->getYPosition(), target->getXPosition(), 0);
  //std::tuple<Block*, int> originTuple(origin, 0);
  std::tuple<Node, int> originTuple(originNode, 0);
  frontier.push(originTuple);
  visited.emplace(originNode);
  cameFrom.emplace(originNode, Node(-1,-1,-1));
  costSoFar.emplace(originNode, 0);

  while(!frontier.empty()) {
    current = std::get<0>(frontier.top()); frontier.pop();
    if (current == targetNode) break;
    y = current.y;
    x = current.x;

    next.z = 0; // TODO: SET APPROPRIATE Z-VALUE AND RESET IT WHEN THERE IS A BLOCK BELOW
    nextBlock = _map->getBlockAtPosition(y+BELOW, x);
    next.y = nextBlock->getYPosition(); next.x = nextBlock->getXPosition();
    addNext(next, current, targetNode, frontier, visited, cameFrom, costSoFar);
    nextBlock = _map->getBlockAtPosition(y, x+LEFT);
    next.y = nextBlock->getYPosition(); next.x = nextBlock->getXPosition();
    addNext(next, current, targetNode, frontier, visited, cameFrom, costSoFar);
    nextBlock = _map->getBlockAtPosition(y, x+RIGHT);
    next.y = nextBlock->getYPosition(); next.x = nextBlock->getXPosition();
    addNext(next, current, targetNode, frontier, visited, cameFrom, costSoFar);
    nextBlock = _map->getBlockAtPosition(y+ABOVE, x);
    next.y = nextBlock->getYPosition(); next.x = nextBlock->getXPosition();
    addNext(next, current, targetNode, frontier, visited, cameFrom, costSoFar);
  }

  if (visited.find(targetNode) != visited.end()) {
    // Only finalize the path if the target was found
    current = targetNode;
    path.push_back(_map->getBlockAtPosition(current.y, current.x));
    while (current != originNode) {
      current = cameFrom[current];
      path.push_back(_map->getBlockAtPosition(current.y, current.x));
    }
    std::reverse(path.begin(), path.end());
  }
  return path;
}
