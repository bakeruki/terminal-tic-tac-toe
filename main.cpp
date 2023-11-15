#include <iostream>
#include <cstdlib>

int board[3][3];
//board works as follows
// 0 represents empty square
// 1 represents X
// 2 represents O

int turn = 1;
int playerTurn = 0;
// 1 represents X turn
// 2 represents O turn

bool playing = false;

//draws the board
void drawBoard(){
  std::cout << "\n";
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      switch(board[i][j]){
        case 0:
          std::cout << " ";
          break;
        case 1:
          std::cout << "X";
          break;
        case 2:
          std::cout << "O";
          break;
        default:
          std::cout << "E";
          break;
      }
      if(j != 2) {std::cout << " | ";}
    }
    if(i != 2) {std::cout << "\n" << "---------" << "\n";}
  }
  std::cout << "\n";
}

//does all drawing
void draw(){
  std::system("clear"); //clear the screen

  drawBoard();
}

//initialize game stuff
void init(){
  //initialize board
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      board[i][j] = 0;
    }
  }
}

//allow the player to choose which side they would like to play
void chooseSide(){
  bool chosen = false;
  while(!chosen){
    std::string ans = "";
    std::cout << "Would you like to play X or O?\n";
    std::cin >> ans;

    if(ans == "X"){
      chosen = true;
      playerTurn = 1;
    }else if(ans == "O"){
      chosen = true;
      playerTurn = 2;
    }else{
      std::cout << "Please enter X or O.\n";
    }
  }
  playing = true;
}

//tries to parse a players move. returns 0 if successful, 1 if failed.
//updates the board if successful
int parseMove(std::string move){
  //too many characters
  if(move.length() != 3){return 1;}
  //incorrect formatting
  if(!(isdigit(move.at(0)) || isdigit(move.at(2)) || move.at(1) == ',')){
    return 1;
  }

  int col = std::stoi(move.substr(0,1)) - 1;
  int row = std::stoi(move.substr(2,1)) - 1;
  //coordinate too big or small
  if(col < 0 || col > 2 || row < 0 || row > 2){
    return 1;
  }
  //move already played in that spot
  if(board[row][col] != 0){return 1;}

  board[row][col] = turn;
  return 0;
}

//gets a move from the player
void getMove(){
  bool chosen = false;
  while(!chosen){
    std::string ans = "";
    (turn == 1) ? std::cout << "Player X: " : std::cout << "Player O: ";
    std::cout << "Enter your move in the form of a coordinate col,row\n";
    std::cin >> ans;
    if(parseMove(ans) == 0){
      chosen = true;
      turn = (turn == 1) ? 2 : 1;
    }else{
      std::cout << "Move input invalid.\n";
    }
  }
}

int checkWin(){
  //check horizontal wins (rows)
  for(int i = 0; i < 3; i++){
    if(board[i][0] == board[i][1] && board[i][1] == board[i][2]){
      return board[i][0];
    }
  }
  //check vertical wins (cols)
  for(int i = 0; i < 3; i++){
    if(board[0][i] == board[1][i] && board[1][i] == board[2][i]){
      return board[0][i];
    }
  }
  //check diagonal wins
  if(board[0][0] == board[1][1] && board[1][1] == board[2][2]){
    return board[0][0];
  }
  if(board[0][2] == board[1][1] && board[1][1] == board[2][0]){
    return board[0][2];
  }

  return 0;
}

void runGame(){
  while(playing){
    draw();
    getMove();
    int winner = checkWin();
    if(winner != 0){
      draw();
      (winner == 1 ? std::cout << "Player X " : std::cout << "Player O ");
      std::cout << "wins!\n";
      playing = false;
    }
  }
}

//main
int main(){
  init();
  std::cout << "Welcome to tic tac toe.\n";
  chooseSide();
  runGame();

  return 0;
}
