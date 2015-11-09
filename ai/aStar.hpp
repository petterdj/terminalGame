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

    // HELPERS //
    void addNext(Block*, Block*, std::set<Block*>& visited, std::map<Block*, Block*>& cameFrom, std::queue<Block*> frontier);
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
