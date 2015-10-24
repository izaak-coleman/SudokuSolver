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
  delete [] filename; // DRIVER LINE, REMOVE ME!!!!
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

char alphaToNum( char alphaRepresentation )
{
	return alphaRepresentation - 16;
}


bool make_move( const char *position, const char value, char board[][9] )
{
	int rowIndex, colIndex; 
	
	/* Converts both chars in @position into their
	 * corresponding array indices */
	rowIndex = alphaToNum((*position) - (1 + '0')); 
	colIndex = *(++position) - (1 + '0');         


	if( (!inRange(rowIndex)) && (!inRange(colIndex)) )// If move not in range...
	{
		return false; // return invalid move.
	}
	else if ( isDigit(board[rowIndex][colIndex]) ) // If position occupied...
	{
		return false; // return invalid move.
	}
	else // Otherwise move is valid...
	{
		board[rowIndex][colIndex] = value; // so input @value into board...
	}
	return true; // and return valid move.

}


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

//char* getPositionCoordinates()
{
}
