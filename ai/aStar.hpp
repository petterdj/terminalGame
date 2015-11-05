#ifndef MYASTAR
#define MYASTAR
#include <queue>
#include <set>
#include <tuple>
#include "../block.hpp"
#include "../level.hpp"

namespace terminalGame {
class AStar {

  protected:
    Level* _map;
    int _originY;
    int _originX;
    int _targetY;
    int _targetX;
    std::queue<Block*> _frontier;
    std::set<Block*> _visited;

  public:
    // CONSTRUCTORS //
    AStar();
    AStar(Level*, int oY, int oX, int tY, int tX);
    AStar(const AStar&);
    AStar(AStar&&);

    // OPERATORS //
    AStar& operator=(const AStar&);
    AStar& operator=(AStar&&);

    // DESTRUCTOR //
    ~AStar();

    // FUNCTIONS //
    

};
}
#endif
