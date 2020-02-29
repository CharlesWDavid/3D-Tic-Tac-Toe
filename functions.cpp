#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

// array for board positions
string printBoard[28] = {"z","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27"}; 

// Stores moves made by each players
char playerMoves[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',',','.'};
char cpuMoves[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',',','.'};

// 2D array containing all the possible win conditions
int winCond[49][3] = {
    {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12}, {13,14,15}, {16,17,18}, {19,20,21}, {22,23,24}, {25,26,27},
    {1,4,7}, {2,5,8}, {3,6,9}, {10,13,16}, {11,14,17}, {12,15,18}, {19,22,25}, {20,23,26}, {21,24,27},
    {1,10,19}, {2,11,20}, {3,12,21}, {4,13,22}, {5,14,23}, {6,15,24}, {7,16,25}, {8,17,26}, {9,18,27},
    {1,5,9}, {3,5,7}, {10,14,18}, {12,14,16}, {19,23,27}, {21,23,25},
    {1,11,21}, {19,11,3}, {4,14,24}, {22,14,6}, {7,17,27}, {25,17,9},
    {1,13,25}, {2,14,26}, {3,15,27}, {7,13,19}, {8,14,20}, {9,15,21},
    {1,14,27}, {19,14,9}, {21,14,7}, {3,14,25}
};

// Player is odd and Computer is even
int whoseTurn = 0;

// Stores most recent move made by a player
int currentMove;

void greetAndInstruct(){
    
    cout << endl << "Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer." << endl << endl;
    
    cout << "The board is numbered from 1 to 27 as per the following:" << endl << endl;

    // initizaling labels for each cells of the 3 boards
    int i = 1; int j = 10; int k = 19;  
    // printing each row of board
    for (int row = 0; row < 3; row++){
        cout << printBoard[i] << " | " << printBoard[i+1] << " | " << printBoard[i+2] << '\t' << printBoard[j] << " | " << printBoard[j+1] << " | " << printBoard[j+2] << '\t' << printBoard[k] << " | " << printBoard[k+1] << " | " << printBoard[k+2] << endl;
        if (row < 2){
            // printing middle horizontal lines
            cout << "---------" << '\t' << "------------" << '\t' << "------------" << endl;
            // incrementing each pointers by 3 to move to next row
            i += 3; j+= 3, k += 3; 
        } else {
            cout << endl; // skip line for last row to print following text
        }
    }

    cout << "Player starts first. Simply input the number of the cell you want to occupy. Player’s move" << endl << "is marked with X. Computer’s move is marked with O." << endl << endl;

    cout << "Start? (y/n)" << endl << endl;
    

    string answer; // variable to store user's answer
    
    // ensuring user inputs the correct 'y' or 'n' 
    while (answer.compare("n") != 0 && answer.compare("y") != 0) cin >> answer;

    if (answer.compare("n") == 0){
        // exit if user inputs 'n'
        exit(0); 
    } 
}

void displayBoard(char board[]){

    for (int i = 1; i < 28; i++){
        if (board[i] == 'X') printBoard[i] = "X";
        else if (board[i] == 'O') printBoard[i] = "O";
    }

    cout << endl;

    // print board
    int i = 1; int j = 10; int k = 19;  
    
    for (int row = 0; row < 3; row++){
        cout << printBoard[i] << " | " << printBoard[i+1] << " | " << printBoard[i+2] << '\t' << printBoard[j] << " | " << printBoard[j+1] << " | " << printBoard[j+2] << '\t' << printBoard[k] << " | " << printBoard[k+1] << " | " << printBoard[k+2] << endl;
        if (row < 2){
            
            cout << "---------" << '\t' << "------------" << '\t' << "------------" << endl;
            
            i += 3; j+= 3, k += 3; 
        } else {
            cout << endl; 
        }
    }
}

bool checkIfLegal(int cellNbre, char board[]){

    if (cellNbre < 1 || cellNbre > 27){
        // check if cellNbre entered by player is out of bounds
        if (whoseTurn % 2 == 1) cout << "Cell number is out of bounds. Please enter a valid one." << endl;
        return false;
    }
    else if (board[cellNbre] == 'X' || board[cellNbre] == 'O'){
        // check if cellNbre entered by player is already occupied
        if (whoseTurn % 2 == 1) cout << "Cell is already occupied. Please select a valid one." << endl;
        return false;
    } 
    return true;
}

bool checkWinner(char board[]){
    for (int i=0; i<49; i++){
        int count1 = 0; // counting the number of O's
        int count2 = 0; // counting the number of X's
        for (int j=0; j<3; j++){
            // count the number of cells marked in a win condition
            if (cpuMoves[winCond[i][j]] == 'O') count1++;
            if (playerMoves[winCond[i][j]] == 'X') count2++;
        }
        if (count1 == 3 || count2 == 3){
            // if count 3 O's or X's then there is a win
            return true;
        }
    }
    return false;      
}

void computerMove(char board[]){

    bool cpuMoveFound, blockPlayerFound = false;
    
    if (whoseTurn >= 6){
        // only possible to find winning move on turn 6 for cpu
        for (int i=0; i<49; i++){
            int count = 0;
            for (int j=0; j<3; j++){
                // count the number of cells marked in a win condition
                if (cpuMoves[winCond[i][j]] == 'O') count++;
            }
            if (count == 2){
                // if 2 out of 3 cells for a win condition are marked then the next move is a winning one
                for (int j=0; j<3; j++){
                    if (cpuMoves[winCond[i][j]] != 'O'){
                        currentMove = winCond[i][j];
                    }
                }
                if (checkIfLegal(currentMove, board)){
                    cpuMoveFound = true;
                    break;
                } 
            }
        }
    }
    if (whoseTurn >= 4 && !cpuMoveFound){
        // check the same thing for the player's move and block if they can win on the next turn
        for (int i=0; i<49; i++){
            int count = 0;
            for (int j=0; j<3; j++){
                if (playerMoves[winCond[i][j]] == 'X') count++;
            }
            if (count == 2){
                for (int j=0; j<3; j++){
                    if (playerMoves[winCond[i][j]] != 'X'){
                        currentMove = winCond[i][j];
                    }
                }
                if (checkIfLegal(currentMove, board)){
                    blockPlayerFound = true;
                    break;
                }
            }
        }
    } 
    if (!blockPlayerFound && !cpuMoveFound){
        // if nothing else can be done, choose a random cell
        srand(clock());
        do {
            currentMove = (rand() % 27) + 1; // Generate random move between 1 and 27
        } while (!checkIfLegal(currentMove, board));
    }
}


