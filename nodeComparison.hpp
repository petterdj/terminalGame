#ifndef MYNODECOMPARISON
#define MYNODECOMPARISON
#include <stdlib.h>
#include <tuple>

namespace terminalGame {
// LOCAL STRUCT NODE //

struct Node { int y; int x; int z;
  Node() {}
  Node(int v, int u, int w) { y = v; x = u; z = w; }
};
bool operator<(const Node& l, const Node& r) { return std::tie(l.y, l.x, l.z) < std::tie(r.y, r.x, r.z); }
bool operator==(const Node& l, const Node& r) { return std::tie(l.y, l.x, l.z) == std::tie(r.y, r.x, r.z); }
bool operator!=(const Node& l, const Node& r) { return std::tie(l.y, l.x, l.z) != std::tie(r.y, r.x, r.z); }

class nodeComparison {
  private:
  public:
    nodeComparison() { }
    ~nodeComparison() { }

    bool operator()(const std::tuple<Node, int> a, const std::tuple<Node, int> b) const { 
      return std::get<1>(a) > std::get<1>(b);
    }
};
}
#endif
