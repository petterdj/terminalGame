#ifndef MYLEVEL
#define MYLEVEL
#include <iostream>
#include <vector>
#include "utils/constants.h"
#include "block.hpp"

namespace terminalGame {

class Level {

  protected:
    Block* _map[HEIGHT][WIDTH];
    std::vector<Block*> _levelVector;

  public:
    // CONSTRUCTORS //
    Level();
    Level(const Level&) = delete;
    Level(Level&&) = delete;

    // OPERATORS //
    Level& operator=(const Level&) = delete;
    Level& operator=(Level&&) = delete;

    // DESTRUCTOR //
    ~Level();

    // FUNCTIONS //
    void loadLevel(const std::string);

    Block* getBlockAtPosition(const int y, const int x);
    std::vector<Block*> getLevelVector();
};
}

#endif
