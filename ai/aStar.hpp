#ifndef MYASTAR
#define MYASTAR
#include <queue>
#include <map>
#include <set>
#include <tuple>
#include "../block.hpp"
#include "../level.hpp"
#include "../blockComparison.hpp"

namespace terminalGame {

typedef std::priority_queue<std::tuple<Block*, int>, std::vector<std::tuple<Block*, int>>, blockComparison> blockPriorityQueue;

class AStar {

  protected:
    Level* _map;

    // HELPERS //
    int direction(const Block*, const Block*) const;
    void addNext(Block*, Block*, Block*, blockPriorityQueue& frontier, std::set<Block*>& visited, std::map<Block*, Block*>& cameFrom, std::map<Block*, int>& costSoFar);
    int distanceToTarget(const Block*, const Block*) const;
    int costToNext(const Block*) const;
    bool accessibleFromCurrent(const Block*, const Block*) const;

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
