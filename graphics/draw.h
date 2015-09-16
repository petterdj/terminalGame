#ifndef MYDRAW
#define MYDRAW
#include "../character.hpp"
#include "../block.hpp"
#include <vector>

using namespace terminalGame;

void drawCharacters(std::vector<Character*> characters) {
  for (auto &it : characters) mvprintw(it->getYPosition(), it->getXPosition(), it->getDrawChar().c_str());
}

void drawLevel(std::vector<Block*> levelVector) {
  for (auto &it : levelVector) mvprintw(it->getYPosition(), it->getXPosition(), it->getDrawChar().c_str());
}

inline void draw(std::vector<Block*> levelVector, std::vector<Character*> characterVector) {
  drawCharacters(characterVector);
  drawLevel(levelVector);
}

#endif
