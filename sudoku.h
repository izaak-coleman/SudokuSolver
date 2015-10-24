// Authour: Izaak Coleman
// Last modificaton : 00000

/* Note: When refering to 
 * identifiers (parameter, function etc), '@' is 
 * prefixed to the identifier name to expilcitly show 
 * show the reference */



#ifndef SUDOKU_H
#define SUDOKU_H
void load_board(const char *filename, char board[9][9]);
void display_board(const char board[9][9]);

///////////////////////////////// My functions

char alphaCharToNumChar( char alphaRepresentation );
/* Converts chars 'A' - 'I' into
 * chars '1' - '9' */

char* getFileName(); // DRIVER FUNCTION
/* Promts user to input filename 
 * helper function for @load_board */

bool inRange( int index );
/* Identifies if an integer value which will be
 * used to specify an array index on the sudoku board
 * is within the range of the board. Range: 0-8. */

bool isDigit( char boardPosition );
/* Returns true if value of @boardPosition is
 * a char digit. */ 

bool is_complete( char board[9][9] );
/* Returns true if each position of the sudoku 
 * board @board contains a digit. NOTE: Does   
 * not check @board for correctness. */

char* getPositionCoordinates(); // DRIVER FUNCTION
/* Prompts user for the board coordinates where
 * the user would like to make their next move */

char* getPositionValue(); // DRIVER FUNCTION
/* Prompts the user for the value they wish to input
 * at the board coordinates specified in
 * @getPositionCoordinates */

bool make_move( const char *coordinate, const char value, char board[9][9] );
/* Tries to input the user specified @value at 
 * the location of @coordinate, on the @board.
 * Returns false if there is input failure */



#endif
