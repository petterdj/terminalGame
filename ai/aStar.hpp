#ifndef MYASTAR
#define MYASTAR
#include <queue>
#include <map>
#include <set>
#include "../block.hpp"
#include "../level.hpp"
#include "../blockComparison.hpp"

namespace terminalGame {

typedef std::priority_queue<Block*, std::vector<Block*>, blockComparison> blockPriorityQueue;

class AStar {

  protected:
    Level* _map;

    // HELPERS //
    int direction(Block*, Block*);
    void addNext(Block*, Block*, blockPriorityQueue& frontier, std::set<Block*>& visited, std::map<Block*, Block*>& cameFrom);
    int distanceToTarget(Block*, Block*);

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
