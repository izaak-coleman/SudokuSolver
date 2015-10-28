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

bool is_complete( char board[9][9] );
/* Returns true if each position of the sudoku 
 * board @board contains a digit. NOTE: Does   
 * not check @board for correctness. */

bool make_move( const char *coordinate, const char value, char board[9][9] );
/* Tries to input the user specified @value at 
 * the location of @coordinate, on the @board.
 * Returns false if there is input failure */

bool save_board( const char *outputFileName, char board[9][9] );
/* Saves a boards current state to a .dat file of name
 * @outputFileName. .dat file format is readable by
 * @load_board. */

bool solve_board( char board[9][9] );
/* Solves a sudoku board. */
/* Finds the first blank position on @board and seeds it.
 * Then calls @elimPossibles to find the possible values for
 * each position. Once elimPossibles reaches the end of a 
 * constraint set, the board will either be solved or not.
 * It not, reseed the position and try again */

void elimPossibles(char board[9][9], bool procLoc[9][9],
                   char pCube[9][9][9], int row=0,
				   int col=0); 
/* Major recursive funtion which calls helper funtions
 * to logically eliminate digits in @pCube, based on the
 * digits suppied by @board. Function ends when 
 * every unprocessed digit on board has been used to 
 * eliminate possible digits in pCube, pCube as a sparse
 * 3dArray */ 

void elimRowPossibles( char pCube[9][9][9], char board[9][9],
                       int row, int col, int indexToEliminate,
                       int rowIt=0 );
/* Removes the single possibility from the entire row, found
 * at @indexToEliminate */

void elimColPossibles( char pCube[9][9][9], char board[9][9],
                       int row, int col, int indexToEliminate,
                       int colIt=0 );
/* Removes the single possibility from the entire colum,
 * found at @indexToEliminate */

void elimFieldPossibles( char pCube[9][9][9], char board[9][9],
                         int row, int col, int indexToEliminate );
/* Removes the single possibiliy from the field, found at
 * @indexToElement */

void setSuppliedVals( char pCube[9][9][9], char board[9][9],
                     int correctIndex, int row, int col,
                     int indexBaseCase=0 );
/* Removes incorrect possibilities in the suppied at the 
 * positions suppied from data file. */


bool processedAllPositions( char board[9][9], bool processedPositions[9][9] );
/* Identifies new positions on the board that have yet
 * to be processed. Returns false if all positions have
 * been processed. */

void updateBoard( char board[9][9], int row, int col, char correctVal );
/* Submits a known position to the board */

bool successfulElimination( char board[9][9], char pCube[9][9][9], int row, int col );
/* Checks if a board position in pCube contains only 1 
 * remaining possibility. If true, this char is submitted to
 * @board using @updateBoard. */

bool onlyViableFieldPosition( char pCube[9][9][9], int row,
							  int col, int posVal );
/* Called by @successfulElimination. Checks if the digit 
 * at the current cells is the only possible position for
 * the digit in the field. Returns true if so. */

char alphaToNum( char alphaRepresentation );
/* changes alpha char 'A' - 'I' to digit char '1' - '9'*/

void seed_board( char board[9][9], int &r, int &c, 
                 char guessVal );
/* Finds the first empty position from 0,0 and inputs the
 * value of @guessVal*/

void setTestBoard( char baseBoard[9][9], char testBoard[9][9] );
/* resets the testBoard to the value of baseBoard */

bool solved_board( char board[9][9] );
/* Sums each row, and sums each column of a board. Signals
 * board is solved by returning true, if each column or each
 * row sums to 45.*/

void generatePossibilityCube( char pCube[9][9][9] );
/* Generates a 3D array of chars. The breadth and depth
 * of the cube correlate to the positions on the sudoku board.
 * The height contains each of the possible values a position
 * can take (chars from '1' to '9'. */

void generateLocationArray( bool processedLocs[9][9] );
/* Generates a 2D array of bools. The array positions correlate
 * to the array positions in the sudoku board. Default is false,
 * and a position is changed to true when @deleteIncorrectValues
 * has been called on the position. Important for deciding board
 * solvability. */

bool inputValueToBoard( char inputDigit, char* inputLocation );
/* Adds @inputDigit to the board at *@position. Uses array
 * coordinates, rather than user alpha-num coordinates.
 * Returns false if @inputDigit is out of range. Range: 1-9
 * Returns false if *@postiion is currently occupied */ 

char alphaCharToNumChar( char alphaRepresentation );
/* Converts chars 'A' - 'I' into
 * chars '1' - '9' */

bool inRange( int index );
/* Identifies if an integer value which will be
 * used to specify an array index on the sudoku board
 * is within the range of the board. Range: 0-8. */

bool isDigit( char boardPosition );
/* Returns true if value of @boardPosition is
 * a char digit. */ 

#endif
