#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

    char board[9][9];
//  
//    cout << " Question 1 ======================" << endl << endl;
//  
//    load_board( getFileName(), board);
//    cout << "Board is ";
//    if (!is_complete(board))
//      cout << "NOT ";
//    cout << "complete." << endl << endl;
//	display_board( board );
//  
//  
//    load_board( getFileName() , board);
//    cout << "Board is ";
//    if (!is_complete(board))
//      cout << "NOT ";
//    cout << "complete." << endl << endl;
//	display_board( board );
//  
//    cout << " Question 2 ======================" << endl << endl;
//  
//    load_board( getFileName(), board);
//  
//    // Should be OK
//    cout << "Putting '1' into I8 is ";
//    if (!make_move( "I8", '1', board)) cout << "NOT ";
//    cout << "a valid move. The board is:" << endl;
//    display_board(board);
//  
//  	// write more tests
//  
//    cout << "Question 3 ======================" << endl << endl;
//  
//    load_board("easy.dat", board);
//    if(save_board("easy-copy.dat", board))
//      cout << "Save board to 'easy-copy.dat' successful." << endl;
//    else
//      cout << "Save board failed." << endl;
//    cout << endl;
//  
      cout << " Question 4 ======================" << endl << endl;
  
    load_board("diab.dat", board);
	display_board( board );
    if (solve_board(board)) {
      cout << "The 'worlds toughest.dat' board has a solution:" << endl;
	  display_board( board );
    } else 
      cout << "A solution cannot be found." << endl;
    cout << endl;
  
    load_board("easy-solution.dat", board);
    if (solve_board(board)) {
      cout << "The 'easy-solution' board has a solution:" << endl;
		display_board( board );
    } else 
      cout << "A solution cannot be found." << endl;
    cout << endl;
  
  	// write more tests
  
//  cout << "Question 5 ======================" << endl << endl;
//
//	// write more tests
//
//  return 0;
}
