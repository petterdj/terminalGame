#ifndef MYBLOCKCOMPARISON
#define MYBLOCKCOMPARISON
#include "block.hpp"
#include <stdlib.h>
#include <tuple>

namespace terminalGame {
class blockComparison {
  private:
  public:
    blockComparison() { }
    ~blockComparison() { }

    bool operator()(const std::tuple<Block*, int> a, const std::tuple<Block*, int> b) const { 
      return std::get<1>(a) > std::get<1>(b);
    }
};
}
#endif
