#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

const int MAX_FILE_NAME_LENGTH = 31;

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}
/*--------------------------- My Functions ----------------------------------*/

bool is_complete( char board[][9] )
{
  for(int row=0; row < 9; ++row){          // check board for non digit
    for(int col=0; col < 9; ++col){ 
      if (! isDigit( board[row][col] )){
        return false;                     // return false if finds a non digit
      }}}
  return true;                            // if only digits, board complete
}

bool make_move( const char *position, const char value, char board[][9] )
{
  int rowIndex, colIndex; 

  if( *(position+2) != 0 ){             // make sure @position is 2 char string
    return false;
  }

  /* Convert string @position into array indicies */
  rowIndex = alphaToNum((*position) - (1 + '0')); 
  colIndex = *(++position) - (1 + '0');         
  
  /* check @position has valid range... */
  if( (!inRange(rowIndex)) || (!inRange(colIndex))) {
    return false;       /* ... if not, return invalid ... */
  }
  else{  /* ... otherwise, in range, so input @value into @board */
    return inputValueToBoard( value, &board[rowIndex][colIndex] );
  }
}

bool save_board( const char *outputFileName, char board[][9] )
{
  ofstream saveFile;
  saveFile.open( outputFileName );
  if( saveFile.fail()){
      return false;
  }

  int row=0, col=0;
  for( ; row < 9; ++row ){        // for each position on board...
    col = 0; // reset col
    for( ; col < 9; ++col ){
                                  // write position to file.
      if( board[row][col] == ' ' ){  
        saveFile << '.';
      }
      else{ 
        saveFile << board[row][col];
      }
    }

    saveFile << "\n"; 
  }

  if( !saveFile.fail() && row == 9 && col == 9 ){ // if write complete...
    return true;                                   // return succesful write
  }
                                                  // Otherwise, write failed...
  return false;                               // so return unsuccessfull write.
}

bool inputValueToBoard( char inputDigit, char* inputLocation )
{
  if ( isDigit( *inputLocation )){        // If @inputLocation already occupied
    return false;                         // return invalid move.
  }
  else if( isDigit( inputDigit )){        // if @inputDigit in range...

    *inputLocation = inputDigit;           // ...add it to board...
    return true;                           // ...and return valid move.

  }
  return false;                           // so return invalid move.
}

bool inRange( int index )    // check @index is within sudoku board
{
  if( index >= 0 && index <= 8 ){       
    return true;
  }
  return false;             // return false if index out of sudoku board range
}

bool isDigit( char boardPosition )
{
  if( boardPosition >= '1' && boardPosition <= '9'){ // check @boardPosition
    return true;                                     // is char digit
  }
  else{                                              // return false if not.
    return false;
  }
}

bool solve_board( char baseBoard[][9] )
{
  /* pCube holds the possible digits for each position
   * on the board. */
  char pCube[9][9][9];   
  char testBoard[9][9];               // Holds a copy of the initial board.
  bool processedPositions[9][9];       // Holds a map of processed locations

  
  generateLocationArray( processedPositions );       // sets values to false
  generatePossibilityCube( pCube );     // fill pCube will all possibilities 
  setTestBoard( baseBoard, testBoard );
  if( solved_board( baseBoard ))
  {
    return true;                     // return true if board already complete
  }

  for(int row = 0; row < 9; row++){
    for(int col = 0; col < 9; col++){ // Run through each board position ...

      if( isDigit( testBoard[row][col] )){ // ...seaching for blank positions...
        continue;
      }
      else{                               //... when found ...
        for( int seed='1'; seed <= '9'; seed++){

          generateLocationArray( processedPositions );
          generatePossibilityCube( pCube );

          testBoard[row][col] = seed;  // ... make a guess at correct value...

          // ...whilst all constraint sets not exausted ...
          while(!processedAllPositions(testBoard, processedPositions)){ 
          // ... eliminate values from pCube ...
            elimPossibles( testBoard, processedPositions , pCube );
            for(int r=0; r<9; r++){
              for(int c=0; c<9; c++){
                                // ... and add deduced positions to board. 
                successfulElimination( testBoard, pCube, r, c);
                  // ... reprocess.
              }}}

          // Once constraint sets exausted, check if board is solved.
          if( solved_board( testBoard )){ // if solved...

            setTestBoard( testBoard, baseBoard ); // ... update @baseBoard
            return true;
          }
  
          /* If not solved, the seed was incorrect. Or an deadend constraint
           * was picked. Reset, and try again.*/
          setTestBoard( baseBoard, testBoard ); 
        }}}}

  return false; // Board insolvable
}

void elimPossibles(char board[][9], bool procLoc[][9], char pCube[][9][9],
                   int row, int col)
{

  if( col < 9 && row < 9){                     // loop through entire board...
     

    //... and searched for unprocessed digits.
    if( (board[row][col] != '.') && (procLoc[row][col] == false)){ 
    
    // if unprocessed digit found...
      procLoc[row][col] = true; // ...mark position as processed 
      int indexToEliminate = (board[row][col] - 49); // ... and begin elimin.
      
      /*at current position, remove all possible digits from @pCube
       *  apart digit on board */
      setSuppliedVals( pCube, board, indexToEliminate, row, col ); 
    
      /* eliminate this correct digit from its corresponding row, column
       * and field in the @pCube */  
      elimRowPossibles( pCube, board, row, col, indexToEliminate );
      elimColPossibles( pCube, board, row, col, indexToEliminate );
      elimFieldPossibles( pCube, board, row, col, indexToEliminate );
  
                                                  // recurse to next position.
      elimPossibles( board, procLoc, pCube, row, col+1);

    }
    
    else{                 // if position already processed, or blank, move on.
            elimPossibles( board, procLoc, pCube, row, col+1 );
    }
  }

    else if( col == 9 && row < 9 ){
        elimPossibles( board, procLoc, pCube, row+1 ); // move to next row
    }
   // Now at end of board. Finished elimination processing. Exit recusion stack.
}

void elimRowPossibles( char pCube[][9][9], char board[][9], int row, int col,
                       int indexToEliminate, int rowIt )
{
  if( rowIt < 9 ){                   // For each position in row

    if(rowIt == row){ // Skip removal if at position where function was called
      elimRowPossibles( pCube, board, row, col, indexToEliminate, rowIt+1);
    } 
    else if(rowIt < 9){     // remove value at array location @indexToEliminate

      pCube[rowIt][col][indexToEliminate] = 0;
      elimRowPossibles( pCube, board, row, col, indexToEliminate, rowIt+1);
    }}
}

void elimColPossibles( char pCube[][9][9], char board[][9], int row, int col,
                       int indexToEliminate, int colIt )
{
  if( colIt < 9 ){                    // For each position in column

    if(colIt == col){ // Skip removal if at position where function was called
      elimColPossibles( pCube, board, row, col, indexToEliminate, colIt+1 );
    }
    else if( colIt < 9 ){   // remove value at array location @indexToEliminate

      pCube[row][colIt][indexToEliminate] = 0;
      elimColPossibles( pCube, board, row, col, indexToEliminate, colIt+1 );
    }}
}

void elimFieldPossibles( char pCube[][9][9], char board[][9], int row, int col,
                         int indexToEliminate )
{
  //find the field position
  int fieldRow = row % 3;
  int fieldCol = col % 3;
  
  /* Process each position in the field, removing the possibility
   * at @indexToEliminate */
  int  limitRow = row + (3 - fieldRow);
  int limitCol = col + (3 - fieldCol);

  for(int rloc = (row-fieldRow); rloc < limitRow; rloc++){
    for(int cloc = (col-fieldCol); cloc < limitCol; cloc++){

      if(rloc == row && cloc == col){
        continue;
      }
      else{   
        pCube[rloc][cloc][indexToEliminate] = 0;
      }}}
}

void setSuppliedVals( char pCube[][9][9], char board[][9], 
                      int correctIndex, int row, int col, 
                      int indexBaseCase )
{
  if( indexBaseCase < 9){ // At current possibility in @pCube 
    /* if not the digit suppied @board, eliminate digit*/
    if( indexBaseCase != correctIndex){ 
      pCube[row][col][indexBaseCase] = 0;  
    }

    setSuppliedVals( pCube, board, correctIndex, row, col, 
                         indexBaseCase+1 ); // iterate through posibility array
  }
}

bool processedAllPositions( char board[][9], bool processedPositions[][9] )
{
  /* Compare the current board, and processed locations. If digits are
   * found on board that have yet to undergo elimination process
   * constraint sets not exausted, and return false */

  for(int row=0; row < 9; row++){
    for(int col=0; col < 9; col++){
      if( (board[row][col] != '.') && (processedPositions[row][col] == false ))
      { 
        return false; // Return false if positions still need processing
      }}}

  return true; // Constraint sets exausted, no new positions can be found
}

bool successfulElimination( char board[][9], char pCube[][9][9], 
                            int row, int col )
{
  int counter = 0;
  char correctValue;

  for( int posVal=0; posVal < 9; posVal++ ){ // count the number of remaining
    if( pCube[row][col][posVal] != 0 ){      // possibilities at board location

      counter++;
      correctValue = pCube[row][col][posVal];
    
      // Also, check if the posibility cannot go anywhere else in the field...
      if( onlyViableFieldPosition( pCube, row, col, posVal )){

        updateBoard( board, row, col, correctValue );
        return true; // ... it has to go at current location
                     // so submit value to board.
      }}}

  if( counter == 1 ){ // if this is the only possibility left at location

    updateBoard( board, row, col, correctValue ); // submit it to board.
    return true;
  }

  return false; // Otherwise, there are more possibilities to eliminate
}

void setTestBoard( char baseBoard[][9], char testBoard[][9] )
{
  for(int r=0;r<9;r++){
    for(int c=0;c<9;c++){
      testBoard[r][c] = baseBoard[r][c]; // set @testboard to original
    }}
}

bool solved_board( char board[][9] )
{
  int rowSum = 0;
  int colSum = 0;
  for( int i=0; i<9; i++ ){
    for( int j=0; j<9; j++ ){

      colSum += (board[i][j] - 48); // sum column
      rowSum += (board[j][i] - 48); // transpose to sum row 

      /* If a row or column does not sum to 45, then the board
       * is incorrect */
      if( (j == 8 && colSum != 45) || (j == 8 && rowSum != 45 )){
        return false; // return board not solved
      }
      else if( j == 8 ){  // move to next row and col

        colSum = 0;
        rowSum = 0;
      }}}

  return true; // else, return board solved!!
}

void generateLocationArray( bool processedLocs[][9] )
{
  for( int r=0; r < 9; ++r ){ 
    for( int c=0; c < 9; ++c ){
      processedLocs[r][c] = false; // set each position to false
    }}
}

void generatePossibilityCube( char pCube[][9][9] )
{
  char posValue = '1';             // Set the first digit

  /* Assign a digit to each layer of pCube */
  for( int height=0; height < 9; height++ ){         
    for( int breadth=0; breadth < 9; breadth++ ){   
      for( int depth=0; depth < 9; depth++ ){
        pCube[depth][breadth][height] = posValue;
      }
    }
    posValue++;                   // increment digit with each layer
  }
}


char alphaToNum( char alphaRepresentation )
{
  return alphaRepresentation - 16;
}

void seed_board( char board[][9], int &r, int &c, char guessVal  )
{
  // r, c = 0
  for(; r<9; r++){
    for(; c<9; c++){
      if(! isDigit( board[r][c] )){     // find the next blank position
        board[r+1][c-1] = guessVal;     // and add seed
        return;
      }}}
}


void updateBoard( char board[][9], int row, int col, char correctVal )
{
    board[row][col] = correctVal; // add position to board
}

bool onlyViableFieldPosition( char pCube[][9][9], int row, int col, int posVal )
{
  //find the field position
  int fieldRow = row % 3;
  int fieldCol = col % 3;
  
  int  limitRow = row + (3 - fieldRow);
  int limitCol = col + (3 - fieldCol);
  bool onlyViablePosition = true;

  /* loop through the field, and see if the call position
   * is the only one containing the digit at @posVal */
  for(int rloc = (row-fieldRow); rloc < limitRow; rloc++ ){
    for(int cloc = (col-fieldCol); cloc < limitCol; cloc++ ){
      if(rloc == row && cloc == col){
        continue;
      }
      else if( pCube[row][col][posVal] == pCube[rloc][cloc][posVal] ){
        onlyViablePosition = false; 
      }}}
  
  return onlyViablePosition;         // false if same value appeared in field
}
