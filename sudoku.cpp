#include <cstdlib> // std::exit()
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
/////////////////////////////////////// My functions /////////////
bool is_complete( char board[][9] )
{
	for(int row=0; row < 9; ++row)
	{
		for(int col=0; col < 9; ++col) // For each position on board...
		{
		 	if (! isDigit( board[row][col] )) // check if position is digit...
			{
				return false; // if position is not digit, board not complete.
			}	
		}
	}
	return true; // if true returned board is complete
}


bool solve_board (char board[][9] )
{
    if ( solved_board( board )) // if board already complete
    {
        return true; // return completion signal
    }
    /* @pCube stores an array of possible values for each
     * position on the @board, these values get replaced
     * with 0 when they are logically eliminated by
     * @deleteIncorrectValues */

    char pCube[9][9][9];

    /* @processedLocations stores a 2d array position 
     * correlated to @board. Positions are set to false
     * untill @deleteIncorrectValues is called on 
     * corresponding position in @board */

    bool processedLocations[9][9];

    generatePossibilityCube( pCube );
    generateLocationArray( processedLocations );

    // while eliminating board posibilities is not exausted...
    while( ! processedAllPositions( board, processedLocations ))
    {
        //... logicaly remove possible values for each position from @pCube
        elimPossibles( board, processedLocations, pCube /*r=0,c=0*/ );
        
    }

    if( solved_board( board )) // if board is now complete
    {
        return true;  // return completion signal
    }
    else // Board requires guesswork then more elimination.
    {

        char guessValue = '1'; 
        do 
        {
            // add a seed value to board at a position and try and solve.
            seedBoard( guessValue ); 
            while( ! processedAllPositions( board, processedLocations ))
            { 
                elimPossibles( board, processedLocations, pCube /*r=0,c=0*/ );
            }
        guessValue++; // try another seed value
        } // whilst not solved.
        while( ! solved_board( board ) || guessValue <= '9' ); 


        if( solved_board( board )) // After trying all seed values, if solved...
        {
            return true; // return completion signal
        }
        else // board is insolvable
        {
            cout << "Insolvable Board!!!" << endl;
            return false; // 
        }
    }
}

void elimPossibles(char board[][9], bool procLoc[][9], char pCube[][9][9],
                   int row=0, int col=0, char setBoard='n')
{
    if( (board[row][col] != ' ') && (procLoc[row][col] == false))
    {
        procLoc[row][col] = true; // being processing position
        int indexToEliminate = (board[row][col] - 49); // char to array pos

        if (setBoard == 'y') // if first ever round of elimination
        {
            setSuppliedVals( pCube, indexToEliminate ); 
        }

        elimRowPossibles( pCube, row, col, indexToEliminate );
        elimColPossibles( pCube, row, col, indexToEliminate );
        elimFieldPossibles( pCube, row, col, indexToEliminate );


        if( col < 9 && row < 9 )
        {
            elimPossibles( board, procLoc, pCube, row, col+1 );
        }
        else if( col == 9 && row < 9 )
        {
            elimPossibles( board, procLoc, pCube, row+1 /*col=0*/ );
        }
    }

    // else, done, and return to caller
}

void elimRowPossibles( char pCube[][9][9], int row, int col,
                       int indexToEliminate, int rowIt=0 )
{}
void elimColPossibles( char pCube[][9][9], int row, int col,
                       int indexToEliminate, int colIt=0 )
{}
void elimRowPossibles( char pCube[][9][9], int row, int col,
                       int indexToEliminate )
{}

bool processedAllPositions( char board[][9], bool processedPositions[][9] )
{
    /* Check board for chars that have not been processed
     * by @elimPossibles. */
    for(int row=0; row < 9; row++)
    {
        for(int col=0; col < 9; col++)
        {
            if( (board[row][col] != 0) && (processedPositions[row][col] == false ))
            {
                return false; // Return false if positions still need processing
            }
        }
    }
    return true; // Return true if elimination process exausted 
}


bool solved_board( char board[][9] )
{
    int rowSum = 0;
    int colSum = 0;
    for( int i=0; i<9; i++ ) 
    {
        for( int j=0; j<9; j++ )
        {
            colSum += (board[i][j] - 48); // sum column
            rowSum += (board[j][i] - 48); // transpose to sum row 

            /* If a row or column does not sum to 45, then the board
             * is incorrect */
            if( (j == 8 && colSum != 45) || (j == 8 && rowSum != 45 ))
            {
                return false; // return board is not correct.
            }
            else if( j == 8 ) // move to next row and col
            {
                colSum = 0;
                rowSum = 0;
            }
        }
    }
    // else, board is solved!
    return true;
}

void generateLocationArray( bool processedLocs[][9] )
{
    for( int r=0; r < 9; ++r )
    {
        for( int c=0; c < 9; ++c )
        {
            processedLocs[r][c] = false;
        }
    }
}

void generatePossibilityCube( char pCube[][9][9] )
{
    char posValue = '1'; // Set the first digit possibility

    for( int height=0; height < 9; height++ ) // for each index...
    {
        for( int breadth=0; breadth < 9; breadth++ )
        {
            for( int depth=0; depth < 9; depth++ )
            {
                pCube[depth][breadth][height] = posValue; // assign a digit
            }
        }
        posValue++; // move up a height layer, so move up a digit
    }
}

bool save_board( const char *outputFileName, char board[][9] )
{
    ofstream saveFile;
    saveFile.open( outputFileName );
    if( saveFile.fail() )
    {
        return false;
    }

    int row=0, col=0;
    for( ; row < 9; ++row ) // for each position on board...
    {
        col = 0; // reset col

        for( ; col < 9; ++col )
        {
            if( board[row][col] == ' ' ) // write '.' for empty position...
            {
                saveFile << '.';
            }
            else // or write the digit to file.
            {
                saveFile << board[row][col];
            }
        }

        saveFile << "\n"; 
    }

    if( !saveFile.fail() && row == 9 && col == 9 ) // if write complete...
    {
        return true; // return valid successfull write.
    }
    
    // else the board write did not complete...
    return false; // so return unsuccessfull write.
}

char alphaToNum( char alphaRepresentation )
{
	return alphaRepresentation - 16;
}


bool make_move( const char *position, const char value, char board[][9] )
{
	int rowIndex, colIndex; 
    /* Check position points to no longer than a two char string. 
     * This stops invalid inputs such as "A10" evaluating to "A1". */ 
    if( *(position+2) != 0 )
    {
        cout << "Too long position" << endl;
        return false;
    }

	/* Converts both chars in @position into their
	 * corresponding array indices */
	rowIndex = alphaToNum((*position) - (1 + '0')); 
	colIndex = *(++position) - (1 + '0');         

	if( (!inRange(rowIndex)) || (!inRange(colIndex)) )// If move not in range...
	{
        cout << "Do we get here?" << endl;
		return false; // return invalid move.
	}
	else // position is in range.
	{
		return inputValueToBoard( value, &board[rowIndex][colIndex] );
	}

}

bool inputValueToBoard( char inputDigit, char* position )
{
	if ( isDigit( *position ) ) // If position occupied by a digit...
	{
		return false; // return invalid move.
	}
    else if( isDigit( inputDigit ) ) // if @inputDigit in range...
    {
        *position = inputDigit; // add it to board ...
        return true; // and return valid move.
    }
    // else inputDigit not in range...
    return false; // so return invalid move.

}

void updateBoard( char board[][9], int row, int col, char correctVal )
{
    board[row][col] = correctVal;
}

void successfulElimination( char board[][9], char pCube[][9][9], int row, int col )
{
    int counter = 0;
    char correctValue;

    /* count remaining possibilities */
    for( int posVal=0; posVal < 9; posVal++ )
    {
        if( pCube[row][col][posVal] != 0 )
        {
            counter++;
            correctValue = pCube[row][col][posVal];
        }
    }

    if( counter == 1 ) // if only one possibility left...
    {
        updateBoard( board, row, col, correctValue ); // submit it to board.
    }
}






bool inRange( int index )
{
	if( index >= 0 && index <= 8 )
	{
		return true;
	}
	// else, @index is not in sudoku board range
	return false; 
}
bool isDigit( char boardPosition )
{
	/* check @boardPosition is digit */
	if( boardPosition >= '1' && boardPosition <= '9' )
	{
		return true;
	}
	else // @boardPosition is not a digit character
	{
		return false;
	}
}

///////////// DRIVER FUNCTIONS TO BE REMOVED

char* getFileName()
{
	char* fileName;
	fileName = new char[MAX_FILE_NAME_LENGTH];

	cout << "Enter sudoku board file name > ";
	cin.getline( fileName, MAX_FILE_NAME_LENGTH );

	return fileName; // return the pointer to use at argument for @load_board
}

char* getPositionCoordinates()
{
    char* position; // create pointer
    position = new char[10]; // create char array on heap
    cout << "Please enter position > ";
    cin.getline( position, 3 );
    return position;
}

char getPositionValue()
{
    char value;
    cout << "Please enter value for position > ";
    cin.get(value);
    return value;
}
