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
void elimPossibles(char board[][9], bool procLoc[][9], char pCube[][9][9],
                   int row, int col, char setBoard )
{
	if( col < 9 && row < 9 )
	{
    	if( (board[row][col] != '.') && (procLoc[row][col] == false))
    	{
    	    procLoc[row][col] = true; // being processing position
    	    int indexToEliminate = (board[row][col] - 49); // char to array pos
			
			/*clear all possibilities for positions given to us */
    	    setSuppliedVals( pCube, board, indexToEliminate, row, col ); 

    	    elimRowPossibles( pCube, board, row, col, indexToEliminate );
    	    elimColPossibles( pCube, board, row, col, indexToEliminate );
    	    elimFieldPossibles( pCube, board, row, col, indexToEliminate );

			elimPossibles( board, procLoc, pCube, row, col+1);
		}
		else
		{
            elimPossibles( board, procLoc, pCube, row, col+1 );
		}
	}
    else if( col == 9 && row < 9 )
    {
        elimPossibles( board, procLoc, pCube, row+1 );
    }
    // else, done, and return to caller
}

bool solve_board( char baseBoard[][9] )
{
	char pCube[9][9][9];
	char testBoard[9][9];
	bool processedPositions[9][9];

	
	generateLocationArray( processedPositions );
	generatePossibilityCube( pCube );
	setTestBoard( baseBoard, testBoard );
	if( solved_board( baseBoard ))
	{
		return true; // return true if board already complete
	}

	for(int row = 0; row < 9; row++)
	{
		for(int col = 0; col < 9; col++)
		{
			if( isDigit( testBoard[row][col] ))
			{
				continue;
			}
			else
			{
				for( int seed='1'; seed <= '9'; seed++)
				{
					generateLocationArray( processedPositions );
					generatePossibilityCube( pCube );

					testBoard[row][col] = seed;
        			while( ! processedAllPositions( testBoard, processedPositions )) { 
        				elimPossibles( testBoard, processedPositions , pCube /*r=0,c=0*/ );
  						for(int r=0; r < 9; r++)
  						{
  							for(int c=0; c<9; c++)
  							{
  								successfulElimination( testBoard, pCube, r, c);
  							}
  						}
        			}
					display_board( testBoard );
					if( solved_board( testBoard ) )
					{
						setTestBoard( testBoard, baseBoard ); // write correct board to base
						return true;
					}
					setTestBoard( baseBoard, testBoard );
				}
			}
		}
	}
	return false; // board insolveable
}
void setTestBoard( char baseBoard[][9], char testBoard[][9] )
{
	for(int r=0;r<9;r++)
	{
		for(int c=0;c<9;c++)
		{
			testBoard[r][c] = baseBoard[r][c];
		}
	}
}

void elimRowPossibles( char pCube[][9][9], char board[][9], int row, int col,
                       int indexToEliminate, int rowIt )
{
	if( rowIt < 9 )
	{
        if(rowIt == row) 
        {
            elimRowPossibles( pCube, board, row, col, 
                              indexToEliminate, rowIt+1);
        }
		else if(rowIt < 9) // Remove possibility
        {
            pCube[rowIt][col][indexToEliminate] = 0;
            elimRowPossibles( pCube, board, row, col,
                               indexToEliminate, rowIt+1);
        }
	}
}

void elimColPossibles( char pCube[][9][9], char board[][9], int row, int col,
                       int indexToEliminate, int colIt )
{
	if( colIt < 9 )
	{
        if(colIt == col)
        {
            /* If current row is row where @elimPossibles was called
             * skip elimination, move a column to the right */
            elimColPossibles( pCube, board, row, col,
                               indexToEliminate, colIt+1 );
        }
        else if( colIt < 9 ) // then remove possibility
        {
            pCube[row][colIt][indexToEliminate] = 0;
            elimColPossibles( pCube, board, row, col,
                              indexToEliminate, colIt+1 );
        }
	}
}

void elimFieldPossibles( char pCube[][9][9], char board[][9], int row, int col,
                         int indexToEliminate )
{
    //find the field position
    int fieldRow = row % 3;
    int fieldCol = col % 3;
    
    /* Process each position in the field, removing the possibility
     * at @indexToEliminate */
    int	limitRow = row + (3 - fieldRow);
	int limitCol = col + (3 - fieldCol);

    for(int rloc = (row-fieldRow); rloc < limitRow; rloc++ )
    {
        for(int cloc = (col-fieldCol); cloc < limitCol; cloc++ )
        {

            if(rloc == row && cloc == col)
            {
                continue;
            }
            else
            {   
                pCube[rloc][cloc][indexToEliminate] = 0;
            }
        }
    }
}

void setSuppliedVals( char pCube[][9][9], char board[][9], 
                      int correctIndex, int row, int col, 
                      int indexBaseCase )
{
    if( indexBaseCase < 9 ) // Whilst not at end of array
    {
        if( indexBaseCase != correctIndex ) // And not at correct value
        {
            pCube[row][col][indexBaseCase] = 0; // remove possibility
        }
        setSuppliedVals( pCube, board, correctIndex, row, col, 
                         indexBaseCase+1 ); // iterate through array
    }
}

bool processedAllPositions( char board[][9], bool processedPositions[][9] )
{
    /* Check board for chars that have not been processed
     * by @elimPossibles. */
    for(int row=0; row < 9; row++)
    {
        for(int col=0; col < 9; col++)
        {
            if( (board[row][col] != '.') && (processedPositions[row][col] == false ))
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

void seed_board( char board[][9], int &r, int &c, char guessVal  )
{
	// r, c = 0
	for(; r<9; r++)
	{
		for(; c<9; c++)
		{
			if(! isDigit( board[r][c] )) // if not a digit
			{
				board[r+1][c-1] = guessVal; // change seedboard
				return;
			}
		}
	}
}

bool make_move( const char *position, const char value, char board[][9] )
{
	int rowIndex, colIndex; 
    /* Check position points to no longer than a two char string. 
     * This stops invalid inputs such as "A10" evaluating to "A1". */ 
    if( *(position+2) != 0 )
    {
        return false;
    }

	/* Converts both chars in @position into their
	 * corresponding array indices */
	rowIndex = alphaToNum((*position) - (1 + '0')); 
	colIndex = *(++position) - (1 + '0');         

	if( (!inRange(rowIndex)) || (!inRange(colIndex)) )// If move not in range...
	{
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

bool onlyViableFieldPosition( char pCube[][9][9], int row, int col, int posVal )
{
    //find the field position
    int fieldRow = row % 3;
    int fieldCol = col % 3;
    
    int	limitRow = row + (3 - fieldRow);
	int limitCol = col + (3 - fieldCol);
	bool onlyViablePosition = true;

    for(int rloc = (row-fieldRow); rloc < limitRow; rloc++ )
    {
        for(int cloc = (col-fieldCol); cloc < limitCol; cloc++ )
        {

            if(rloc == row && cloc == col)
            {
                continue;
            }
			else if( pCube[row][col][posVal] == pCube[rloc][cloc][posVal] )
			{
				onlyViablePosition = false;
			}
        }
    }
	
	return onlyViablePosition;
}


bool successfulElimination( char board[][9], char pCube[][9][9], 
                            int row, int col )
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
			if( onlyViableFieldPosition( pCube, row, col, posVal ))
		    // if no other place where value can go in field	
			{
				updateBoard( board, row, col, correctValue );
				return true; // submit value to board.
			}
        }
    }

    if( counter == 1 ) // if only one possibility left...
    {
        updateBoard( board, row, col, correctValue ); // submit it to board.
        return true;
    }

    return false; // signal multiple possibilities left
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

