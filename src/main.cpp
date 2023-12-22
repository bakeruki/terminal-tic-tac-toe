#include <iostream>
#include "game.cpp"

int main(){
  Game *game = new Game();
  game->start();
  delete game;
  return 0;
}
