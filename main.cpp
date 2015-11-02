#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

    char board[9][9];
  
    cout << " Question 1 ======================" << endl << endl;
  
    load_board( "easy.dat", board);
    cout << "Board is ";
    if (!is_complete(board))
      cout << "NOT ";
    cout << "complete." << endl << endl;
  	display_board( board );
  
  
    load_board( "easy.dat" , board);
    cout << "Board is ";
    if (!is_complete(board))
      cout << "NOT ";
    cout << "complete." << endl << endl;
  	display_board( board );
  
    cout << " Question 2 ======================" << endl << endl;
  
    load_board( "easy.dat", board);
  
    // Should be OK
    cout << "Putting '1' into I8 is ";
    if (!make_move( "I8", '1', board)) cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);
 
	  // position range error: Row below bottom left
    cout << "Putting '1' into J9 is ";
    if (!make_move( "J9", '1', board)) cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);
 		
		// position range error: Col to the right of bottom left
    cout << "Putting '1' into I10 is ";
    if (!make_move( "I10", '1', board)) cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);
 
		// position range error: Col to the right of top right 
    cout << "Putting '1' into A10 is ";
    if (!make_move( "A10", '1', board)) cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);
 
		// Position range error: Row above top right 
    cout << "Putting '1' into @9 is ";
    if (!make_move( "@9", '1', board)) cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);
 
		// Position range error: Row above top left 
    cout << "Putting '1' into @1 is ";
    if (!make_move( "@1", '1', board)) cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);
		
		// Position range error: Col left of top left
    cout << "Putting '1' into A0 is ";
    if (!make_move( "A0", '1', board)) cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);

		// Position range error: Row below bottom left
    cout << "Putting '1' into J1 is ";
    if (!make_move( "J1", '1', board)) cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);

		// Position range error: Col left of bottom left	
    cout << "Putting '1' into I0 is ";
    if (!make_move( "I0", '1', board)) cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);

		// Board input value not in range
    cout << "Putting '10' into I8 is ";
    if (!make_move( "I8", '10', board)) cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);

		// Board input value not in range	
    cout << "Putting '.' into I0 is ";
    if (!make_move( "I8", '.', board)) cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);
  
  
    cout << "Question 3 ======================" << endl << endl;
  
    load_board("easy.dat", board);
    if(save_board("easy-copy.dat", board))
      cout << "Save board to 'easy-copy.dat' successful." << endl;
    else
      cout << "Save board failed." << endl;
    cout << endl;
  
    cout << " Question 4 ======================" << endl << endl;
  
    load_board("diabolical.dat", board);
    if (solve_board(board)) {
      cout << "The board 'diabolical.dat' has a solution:" << endl;
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

    load_board("easy.dat", board);
    if (solve_board(board)) {
      cout << "The 'easy.dat' board has a solution:" << endl;
		display_board( board );
    } else 
      cout << "A solution cannot be found." << endl;
    cout << endl;

    load_board("medium.dat", board);
    if (solve_board(board)) {
      cout << "The 'medium.dat' board has a solution:" << endl;
		display_board( board );
    } else 
      cout << "A solution cannot be found." << endl;
    cout << endl;

    load_board("mystery2.dat", board);
    if (solve_board(board)) {
      cout << "The 'mystery2.dat' board has a solution:" << endl;
		display_board( board );
    } else 
      cout << "A solution cannot be found." << endl;
    cout << endl;

    load_board("mystery3.dat", board);
    if (solve_board(board)) {
      cout << "The 'mystery3.dat' board has a solution:" << endl;
		display_board( board );
    } else 
      cout << "A solution cannot be found." << endl;
    cout << endl;

    load_board("mystery1.dat", board);
    if (solve_board(board)) {
      cout << "The 'mystery1.dat' board has a solution:" << endl;
		display_board( board );
    } else 
      cout << "A solution cannot be found." << endl;
    cout << endl;


		
  
    cout << "Question 5 ======================" << endl << endl;
  
  	// write more tests
  
    return 0;
}
