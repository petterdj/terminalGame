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

void drawWeapons(std::vector<Weapon*> weaponVector) {
  for (auto &it : weaponVector) mvprintw(it->getYPosition(), it->getXPosition(), it->getDrawChar().c_str());
}

void drawPath(std::vector<Block*> pathVector) {
  for (auto &it : pathVector) mvprintw(it->getYPosition(), it->getXPosition(), ".");
}

// TODO convert this into a template function instead of having several near identical functions
void drawObjects(std::vector<Object*> objectVector) {
  for (auto &it : objectVector) mvprintw(it->getYPosition(), it->getXPosition(), it->getDrawChar().c_str());
}

inline void draw(std::vector<Block*> levelVector, 
    std::vector<Character*> characterVector,
    std::vector<Weapon*> weaponVector,
    std::vector<Block*> pathVector) {
  drawPath(pathVector);
  drawCharacters(characterVector);
  drawLevel(levelVector);
  drawWeapons(weaponVector);
}

#endif
