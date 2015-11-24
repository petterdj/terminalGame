#include "aStar.hpp"
#include <algorithm>
#include <ncurses.h>
#include <boost/lexical_cast.hpp>

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
int AStar::direction(const Node& next, const Node& current) const {
  if (next.y < current.y) return UP;
  if (next.y > current.y) return DOWN;
  if (next.x < current.x) return LEFT;
  if (next.x > current.x) return RIGHT;
  return 0;
}

int AStar::distanceToTarget(const Node current, const Node target) const {
  return abs(current.y-target.y) + abs(current.x-target.x);
}

int AStar::costToNext(const Node& next) const {
  return 1;
}

bool AStar::accessibleFromCurrent(const Node& next, const Node& current) const {
  Block* nextBlock = _map->getBlockAtPosition(next.y, next.x);
  if (!nextBlock) return false;
  // Determine from which direction we're coming and see if it is passable from this direction, and if it is possible to keep going up
  switch(direction(next, current)) {
    case UP:
      if (next.z > MAXJUMPHEIGHT) return false;
        if (nextBlock->isPassableFromBelow()) return true;
    case DOWN:
      if (nextBlock->isPassableFromAbove() || nextBlock->isPassableFromAboveKeyDown()) return true;
    case LEFT:
      if (next.z > MAXJUMPHEIGHT) return false;
      if (nextBlock->isPassableFromLeft()) return true;
    case RIGHT:
      if (next.z > MAXJUMPHEIGHT) return false;
      if (nextBlock->isPassableFromRight()) return true;
    default:
      return false;
  }
}

int AStar::nextZValue(const Node& current, const Node& next, const Block* belowNext) const {
  if (belowNext && belowNext->isPassableFromAbove()) {
    if (next.z % 2 == 0) return current.z + 2;
    return current.z + 1;
  }
  return 0;
}

void AStar::addNext(Node& next, Node& current, Node& target, nodePriorityQueue& frontier, std::set<Node>& visited, 
                    std::map<Node, Node>& cameFrom, std::map<Node, int>& costSoFar) {
  if (visited.find(next) == visited.end()) {
    visited.emplace(next);
    if (accessibleFromCurrent(next, current)) {
      int newCost = costSoFar[current] + costToNext(next);
      int priority = newCost + distanceToTarget(next, target);
      std::tuple<Node, int> newFrontier(next, priority);
      frontier.push(newFrontier);
      cameFrom.emplace(next, current);
      costSoFar.emplace(next, newCost);
      //mvprintw(next.y, next.x, boost::lexical_cast<std::string>(next.z).c_str()); // For debugging or optimization
    }
  }
}

std::vector<Block*> AStar::findPath(Block* origin, Block* target) {
  nodePriorityQueue frontier;
  std::set<Node> visited;
  std::vector<Block*> path;
  std::map<Node, Node> cameFrom;
  std::map<Node, int> costSoFar;
  Node current;
  Node next;
  Block* nextBlock;
  Block* belowNextBlock;
  int y;
  int x;
  
  if (!origin || !target || !target->isPassable() || !origin->isPassable()) return path;
  Node originNode(origin->getYPosition(), origin->getXPosition(), 0);
  Node targetNode(target->getYPosition(), target->getXPosition(), 0);
  std::tuple<Node, int> originTuple(originNode, 0);
  frontier.push(originTuple);
  visited.emplace(originNode);
  cameFrom.emplace(originNode, Node(-1,-1,-1));
  costSoFar.emplace(originNode, 0);

  while(!frontier.empty()) {
    current = std::get<0>(frontier.top()); frontier.pop();
    if (current.y == targetNode.y && current.x == targetNode.x) break;
    y = current.y;
    x = current.x;

    // BELOW
    nextBlock = _map->getBlockAtPosition(y+BELOW, x);
    belowNextBlock = _map->getBlockAtPosition(y+2*BELOW, x);
    (belowNextBlock && belowNextBlock->isPassableFromAbove()) ? next.z = current.z : next.z = 0;
    next.y = nextBlock->getYPosition(); next.x = nextBlock->getXPosition();
    addNext(next, current, targetNode, frontier, visited, cameFrom, costSoFar);
    // LEFT
    nextBlock = _map->getBlockAtPosition(y, x+LEFT);
    belowNextBlock = _map->getBlockAtPosition(y+BELOW, x+LEFT);
    (belowNextBlock && belowNextBlock->isPassableFromAbove()) ? next.z = current.z+1 : next.z = 0;
    next.y = nextBlock->getYPosition(); next.x = nextBlock->getXPosition();
    addNext(next, current, targetNode, frontier, visited, cameFrom, costSoFar);
    // RIGHT
    nextBlock = _map->getBlockAtPosition(y, x+RIGHT);
    belowNextBlock = _map->getBlockAtPosition(y+BELOW, x+RIGHT);
    (belowNextBlock && belowNextBlock->isPassableFromAbove()) ? next.z = current.z+1 : next.z = 0;
    next.y = nextBlock->getYPosition(); next.x = nextBlock->getXPosition();
    addNext(next, current, targetNode, frontier, visited, cameFrom, costSoFar);
    // UP
    nextBlock = _map->getBlockAtPosition(y+ABOVE, x);
    belowNextBlock = _map->getBlockAtPosition(y, x);
    next.y = nextBlock->getYPosition(); next.x = nextBlock->getXPosition(); next.z = nextZValue(next, current, belowNextBlock);
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
