#include <iostream>

class AI{
private:
  //the x coordinate represents the current turn
  //the y coordinate represents the move that was played
  //after each game, if the AI won, the moves it played on each turn will be
  //incremented, otherwise they will be decreased
  int hats[9][9];
  //keeps track of the moves played during the current game
  //-1 means a move was not played on that turn
  int currentGame[9];
public:
  int getMove(int currentTurn){
    //int currentHat[9] = hats[currentTurn];
    return 0;
  }

  void startTrainingGame(){
    for(int i = 0; i < 9; i++){
      currentGame[i] = -1;
    }
  }

  void winTrainingGame(){
    for(int i = 0; i < 9; i++){
      if(currentGame[i] != -1){
        hats[i][currentGame[i]]++;
      }
    }
  }

  void loseTrainingGame(){
    for(int i = 0; i < 9; i++){
      if(currentGame[i] != -1 && hats[i][currentGame[i]] != 1){
        hats[i][currentGame[i]]--;
      }
    }
  }
};
