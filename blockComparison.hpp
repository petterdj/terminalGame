#ifndef MYBLOCKCOMPARISON
#define MYBLOCKCOMPARISON
#include "block.hpp"
#include <stdlib.h>

namespace terminalGame {
class blockComparison {
  private:
    Block* _target;
  public:
    blockComparison(Block* target) { _target = target; }
    int distanceToTarget(const Block* current, const Block* target) const {
      int cY = current->getYPosition(); int cX = current->getXPosition(); 
      int tY = target->getYPosition(); int tX = target->getXPosition();
    return abs(cY-tY) + abs(cX-tX);
    }
    bool operator()(const Block * a, const Block* b) const { 
      return distanceToTarget(a, _target) > distanceToTarget(b, _target);
    }
    ~blockComparison() { _target = nullptr; }
};
}
#endif
