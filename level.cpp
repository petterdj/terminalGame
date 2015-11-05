#include "level.hpp"
#include <fstream>
#include <sstream>

using namespace terminalGame;

// CONSTRUCTORS //
Level::Level() {
  std::vector<Block*> v;
  _levelVector = v;
}

// DESTRUCTOR //
Level::~Level() {
  for (auto &it : _levelVector) delete it;
}

// FUNCTIONS //

void Level::loadLevel(const std::string levelPath) {
  std::ifstream infile(levelPath);
  std::string line;
  int y = 0;
  while (std::getline(infile, line)) {
    for (int x = 0; (size_t) x < line.length(); ++x) {
      Block* block = nullptr;
      if (line[x] == '#') { // Normal impassable block
        block = new Block((int) y, (int) x); 
      } else if (line[x] == '-') { // Platform block
        block = new Block((int) y, (int) x, "-");
        block->setPlatformPassable();
      } else if (line[x] == '=') { // Block that is impassable except on down arrow
        block = new Block(y, x, "=", true);
      } else { // Empty square
        block = new Block(y, x, "");
        block->setFullyPassable(true);
      }
      if (block != nullptr) _levelVector.push_back(block);
      _map[y][x] = block;
    }
    ++y;
  }
  infile.close();
}

Block* Level::getBlockAtPosition(const int y, const int x) { return _map[y][x]; }

std::vector<Block*> Level::getLevelVector() { 
  std::cout << "get level vector" << std::endl;
  std::cout << _levelVector.size() << std::endl;
  return _levelVector;
}
