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
  const std::string menu = "Menu:\n1. Human vs Human\n2. Human vs AI\n3. AI vs AI\n4. AI trains AI\n5. Display AI1 hats\n6. Display AI2 hats\n7. Exit\n";
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
      turn++;

      draw();

      int win = checkWin();
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

  void PlayerVsAI(){
    bool validResponse = false;
    int playerTurn;
    while(!validResponse){
        std::cout << "Enter 0 to be X, 1 to be 0\n";
        std::cin >> playerTurn;
        if(playerTurn == 0 || playerTurn == 1){
          validResponse = true;
        }
    }

    turn = 0;
    currentTurn = 0;
    resetBoard();

    bool gameOver = false;
    while(!gameOver){
      std::cout << "Player " << (currentTurn == 0 ? "X" : "O") << "'s turn.\n";

      int move;
      if(currentTurn == playerTurn){
        move = playerX.getMove(board);
      }else{
        bool validMove = false;
        while(!validMove){
          move = ai1.getMove(turn);
          if(board[move] == 2){
            validMove = true;
          }
        }
      }

      board[move] = currentTurn;
      currentTurn = currentTurn == 0 ? 1 : 0;
      turn++;

      draw();
      std::cout << "AI plays " << move << ".\n";

      int win = checkWin();
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

  void PlayerTrainsAI(){

  }

  void AITrainsAI(int *ai1wins, int *ai2wins, int *draws){
    turn = 0;
    currentTurn = 0;
    resetBoard();
    ai1.startTrainingGame();
    ai2.startTrainingGame();

    std::random_device rand;
    std::mt19937 rng(rand());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1);
    int ai1turn = dist6(rng);
    int ai2turn = ai1turn == 1 ? 0 : 1;

    bool gameOver = false;
    while(!gameOver){
      int move;
      bool validMove = false;
      if(currentTurn == ai1turn){
        while(!validMove){
          move = ai1.getMove(turn);
          if(board[move] == 2){
            validMove = true;
          }
        }
      }else{
        while(!validMove){
          move = ai2.getMove(turn);
          if(board[move] == 2){
            validMove = true;
          }
        }
      }

      board[move] = currentTurn;
      currentTurn = currentTurn == 0 ? 1 : 0;
      turn++;

      int win = checkWin();
      if(win == 0){
        ai1.winTrainingGame();
        ai2.loseTrainingGame();
        gameOver = true;
        *ai1wins += 1;
      }else if(win == 1){
        ai2.winTrainingGame();
        ai1.loseTrainingGame();
        gameOver = true;
        *ai2wins += 1;
      }else if(win == 2){
        gameOver = true;
        *draws += 1;
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
        case 2:
          PlayerVsAI();
          break;
        case 4: //ai vs ai training game
          {
          int *ai1winsptr = new int;
          int *ai2winsptr = new int;
          int *drawsptr = new int;
          *ai1winsptr = 0;
          *ai2winsptr = 0;
          *drawsptr = 0;
          int numGames = 50000;
          std::cout << "Starting " << numGames << " training games between AI...\n";
          for(int i = 0; i < numGames + 1; i++){
            AITrainsAI(ai1winsptr, ai2winsptr, drawsptr);
          }
          std::cout << "AI 1 Won " << *ai1winsptr << " times. ";
          std::cout << "AI 2 Won " << *ai2winsptr << " times. ";
          std::cout << "There were " << *drawsptr << " draws.\n";
          delete ai1winsptr;
          delete ai2winsptr;
          delete drawsptr;
          break;
          }
        case 5:
          ai1.printHats();
          break;
        case 6:
          ai2.printHats();
          break;
        case 7: //exit (stop program)
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
