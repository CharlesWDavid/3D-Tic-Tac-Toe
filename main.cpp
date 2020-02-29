#include <iostream>
#include <cstdlib>
#include <string>
#include "functions.cpp"

using namespace std;

int main(){

    greetAndInstruct();

    // Array containing all the moves made
    char movesBoard[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',',','.'};

    // Initialize the board
    displayBoard(movesBoard); 

    // Game keeps looping as long as there is no winner
    do {

        // Next Player's turn
        whoseTurn++;
        // Giving marks to each players
        char mark = (whoseTurn % 2 == 0 ) ? 'O': 'X';

        // Player's turn
        if (whoseTurn % 2){
            do {
                cout << "Please enter a number:  ";
                cin >> currentMove; 
            } while (!checkIfLegal(currentMove, movesBoard));

            movesBoard[currentMove] = mark;  
            playerMoves[currentMove] = mark;
            displayBoard(movesBoard);  
        }
        // Computer's Turn
        else if (whoseTurn % 2 == 0){
            computerMove(movesBoard);
            movesBoard[currentMove] = mark;
            cpuMoves[currentMove] = mark;
            cout << "Computer marked cell " << currentMove << endl;
            displayBoard(movesBoard);      
        }  

    } while (!checkWinner(movesBoard));    

    // Winner message
    if (whoseTurn % 2)
        cout << "Victory :D" << endl;
    else  
        cout << "Defeat D:" << endl;

    return 0;
}
