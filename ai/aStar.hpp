#ifndef MYASTAR
#define MYASTAR
#include <queue>
#include <map>
#include <set>
#include <tuple>
#include "../block.hpp"
#include "../level.hpp"

namespace terminalGame {
class AStar {

  protected:
    Level* _map;
    std::queue<Block*> _frontier;
    std::set<Block*> _visited;
    std::map<Block*, Block*> _cameFrom;

    // HELPERS //
    void addNext(Block*, Block*);
    int direction(Block*, Block*);
  public:
    // CONSTRUCTORS //
    AStar();
    AStar(Level*);
    AStar(const AStar&);
    AStar(AStar&&);

    // OPERATORS //
    AStar& operator=(const AStar&);
    AStar& operator=(AStar&&);

    // DESTRUCTOR //
    ~AStar();

    // FUNCTIONS //    
    std::vector<Block*> findPath(Block*, Block*);
};
}
#endif
