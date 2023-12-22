#include <iostream>

class Player{
public:
  Player(){
    std::cout << "player instantiated\n";
  }
  int getMove(int board[]){
    bool validMove = false;
    int move;
    while(!validMove){
      std::cout << "Enter your move.\n";
      std::cin >> move;
      if(move > 0 && move < 9 && board[move] == 2){
        validMove = true;
      }
    }
    return move;
  }
};
