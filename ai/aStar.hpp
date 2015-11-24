#ifndef MYASTAR
#define MYASTAR
#include <queue>
#include <map>
#include <set>
#include <tuple>
#include "../block.hpp"
#include "../level.hpp"
#include "../nodeComparison.hpp"

namespace terminalGame {

typedef std::priority_queue<std::tuple<Node, int>, std::vector<std::tuple<Node, int>>, nodeComparison> nodePriorityQueue;

class AStar {

  protected:
    Level* _map;

    // HELPERS //
    int direction(const Node&, const Node&) const;
    void addNext(Node&, Node&, Node&, nodePriorityQueue& frontier, std::set<Node>& visited, std::map<Node, Node>& cameFrom, std::map<Node, int>& costSoFar);
    int distanceToTarget(const Node, const Node) const;
    int costToNext(const Node&) const;
    bool accessibleFromCurrent(const Node&, const Node&) const;

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
