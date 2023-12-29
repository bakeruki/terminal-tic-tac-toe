#include <iostream>
#include <random>

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
  AI(){
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
        hats[i][j] = 1;
      }
    }
  }
  int getMove(int currentTurn){
    int currentHat[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int sum = 0;
    for(int i = 0; i < 9; i++){
      currentHat[i] = hats[currentTurn][i];
      sum += currentHat[i];
    }
    //random number between 1 and sum
    std::random_device rand;
    std::mt19937 rng(rand());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, sum);
    int randomNum = dist6(rng);
    //check which hat random lies in e.g. if random >= currentHat[3] and random <= currentHat[4]
    int selectedMove = 0;
    for(int i = 0; i < 9; i++){
      int low = 0;
      for(int j = 0; j < i; j++){
        low += currentHat[j];
      }
      int high = low + currentHat[i];
      if(randomNum >= low && randomNum < high){
        selectedMove = i;
        break;
      }
    }
    //store the move made in currentGame
    currentGame[currentTurn] = selectedMove;
    //return the number of that hat as the selected move
    return selectedMove;
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

  void printHats(){
    std::cout << "  0 1 2 3 4 5 6 7 8\n";
    for(int i = 0; i < 9; i++){
      std::cout << i << " ";
      for(int j = 0; j < 9; j++){
        std::cout << hats[i][j] << " ";
      }
      std::cout << "\n";
    }
  }
};
