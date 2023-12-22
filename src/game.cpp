#include <string>
#include <iostream>
#include <cstdlib>

#include "player.cpp"
#include "ai.cpp"

class Game{
private:
  // 0 is X , 1 is O, 2 is empty
  int board[9] = {2,2,2,2,2,2,2,2,2};
  /*
     0 | 1 | 2
     3 | 4 | 5
     6 | 7 | 8
  */

  //total number of turns that have passed
  int turn = 0;
  //current player
  int currentTurn = 0;

  AI ai1;
  AI ai2;
  Player playerX;
  Player playerO;

  //true if the game is running, false if the game has ended
  bool running = true;

  //contains the menu
  const std::string menu = "Menu:\n1. Human vs Human\n2. Exit\n";
  //contains location combinations of wins
  const int winConditions[8][3] = {{0, 1, 2},
                                 {3, 4, 5},
                                 {6, 7, 8},
                                 {0, 3, 6},
                                 {1, 4, 7},
                                 {2, 5, 8},
                                 {0, 4, 8},
                                 {2, 4, 6}};

  //draw the current state of the game
  void draw(){
    std::system("clear"); //clear the screen

    drawBoard();
  }

  //draw the board
  void drawBoard(){
    std::string res;
    for(int i = 0; i < 9; i++){
      res.append(board[i] == 2 ? " " : (board[i] == 0 ? "X" : "O"));
      if(i % 3 == 2){
        res.append("\n");
      }else{
        res.append(" | ");
      }
    }
    std::cout << res;
  }

  //checks whether one of the winconditions has appeared
  //returns 0 if X won
  //returns 1 if O won
  //returns 2 if draw
  //returns 3 if continue
  int checkWin(){
    for(int i = 0; i < 8; i++){
      if(board[winConditions[i][0]] == board[winConditions[i][1]] &&
         board[winConditions[i][1]] == board[winConditions[i][2]] &&
         board[winConditions[i][0]] != 2){
           return board[winConditions[i][0]];
         }
    }
    if(turn == 9){
      return 2;
    }else{
      return 3;
    }
  }

  void resetBoard(){
    for(int i = 0; i < 9; i++){
      board[i] = 2;
    }
  }

  //start a player vs player game
  void PlayerVsPlayer(){
    std::cout << "human v human selected\n";
    turn = 0;
    currentTurn = 0;
    resetBoard();

    bool gameOver = false;
    while(!gameOver){
      std::cout << "Player " << (currentTurn == 0 ? "X" : "O") << "'s turn.\n";
      int move;
      if(currentTurn == 0){
        move = playerX.getMove(board);
      }else{
        move = playerO.getMove(board);
      }
      board[move] = currentTurn;
      currentTurn = currentTurn == 0 ? 1 : 0;
      draw();
      turn++;
      std::cout << "turn" << turn << "\n";
      int win = checkWin();
      std::cout << "checkwin: " << checkWin() << "\n";
      if(win == 0){
        std::cout << "Player X wins!\n";
        gameOver = true;
      }else if(win == 1){
        std::cout << "Player O wins!\n";
        gameOver = true;
      }else if(win == 2){
        std::cout << "The game was a draw.\n";
        gameOver = true;
      }
    }
  }

public:
  void start(){
    std::cout << "start\n";
    //main menu loop
    while(running){
      int choice;
      std::cout << menu; //print the menu
      std::cin >> choice; //get user choice
      switch(choice){
        case 1: //human vs human game
          PlayerVsPlayer();
          break;
        case 2: //exit (stop program)
          std::cout << "exiting\n";
          running = false;
          break;
        default: //invalid input
          std::cout << "please choose from one of the choices above\n";
          break;
      }
    }
  }
};
