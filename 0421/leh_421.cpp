/** * nqueens * @author Jon Beck * @author Hieu Le * @version April 14th, 2016 */#include <cassert>#include <sstream>#include <iostream>#include <cstdlib>#include <iomanip>#include <climits>#include "matrix.h"// A utility directive to compute the absolute difference// between two numbers a and b#define abs_diff(a, b) ((a > b) ? (a - b) : (b - a))using namespace std;typedef unsigned int uint;/** * This function checks to see if the placement of a new queen on * the board is ok. It is ok if this new queen attacks no other queen.  * A return of true means no conflict. A return of false means the  * new queen attacks at least another queen. * This function works by checking if there is a previously placed  * queen lying on the same diagonals with the new queen. Diagonal  * check suffices since the new queen is guaranteed not to be on the * same row or column with any of the previously placed queens, courtesy * of prior checks in procedure r_backtrack. * The running time complexity of this procedure is O(n). * @param row the row number of the new queen * @param column the column number of the new queen * @param board the n x n chess board * @param queens the positions of all the queens on the board. If * queens[r] != INT_MAX, then there is a queen on row r and column * queens[r]. This takes advantage of the fact that each queen * can only occupy a unique row * @return the absence of a conflict with this new queen addition */bool ok( uint row, uint column, const Matrix< bool > & board, const uint * queens ){  uint n = board.numrows();  for( uint r = 0; r < n; r++ )  {    // If there is a queen on row r that isn't the newly added queen    if( queens[r] != UINT_MAX && r != row )    {      uint dr = abs_diff( r, row );      uint dc = abs_diff( queens[r], column );      // Two queens are on the same diagonal if their vertical and       // horizontal distances are equal      if( dr == dc )	return false;    }  }  // If we made it here, then the new queen conflicts with no other  // queen  return true;}/** * A simple procedure to output an ASCII art horizontal rule with plus * signs where the columns will intersect. */void hr( uint cols ){  cout << "    +";  for( uint col = 0; col < cols; col++ )    cout << "---+";  cout << endl;}/** * This function dumps the board to std output. * @param board the board whose arrangement to dump */void printBoard( const Matrix< bool > & board ){  hr( board.numrows() );  for( uint row = 0; row < board.numrows(); row++ )  {    cout << ' ' << setw(2) << board.numrows() - row << " |";    for( uint col = 0; col < board.numrows(); col++ )    {      if( board.at(row, col) )	cout << " X |";      else	cout << "   |";    }    cout << endl;    hr( board.numrows() );  }  cout << "     ";  for( uint col = 0; col < board.numrows(); col++ )    cout << ' ' << (char)( 'a' + col ) << "  ";  cout << endl;}/** * This is the recursive backtracking function. When called, k queens * have already been placed on the board in columns 0 .. k-1. We're * trying to place the next queen in column k. The function also keeps * track of the number of nodes visited. Here, a node is defined a * valid positioning of m queens on the first m columns for m = 0,...,n.  * A node is examined if it is actually recursed on. * @param k the column in which to place the current queen * @param board the board on which to place the queen * @param queens the positions of all previously placed queen. This * additional structure is created to avoid trying out all n cells on * column k. * @param nodesUntilFound the number of visited nodes until first * solution * @param nodesTotal the total number of visited nodes * @param found flag to indicate if a solution has been found */void r_backtrack( uint k, Matrix< bool > & board, uint * queens,                   uint & nodesUntilFound, uint & nodesTotal, bool & found ){  uint n = board.numrows();  // Increment the numbers of nodes visited  nodesTotal++;  if( !found )    nodesUntilFound++;  // Are we arriving at a possible arrangement?  if( k == n )  {    // If so, print and return to explore other solutions instead of     // quitting the program    printBoard( board );    found = true;    return;  }  // For each row in this column that has not been occupied by  // some other queen  for( uint row = 0; row < n; row++ )  {    // Avoid putting a queen on an occupied row    if( queens[row] == UINT_MAX )    {      // Put a queen here      board.at(row, k) = true;      queens[row] = k;      // Did that cause a conflict?      if( ok( row, k, board, queens ) )      {	// Keep going        r_backtrack( k + 1, board, queens, nodesUntilFound, nodesTotal, found );      }      // Untry the current attempt      board.at(row, k) = false;      queens[row] = UINT_MAX;    }  }}/** * Sets up the board and starts the backtracking algorithm at the * top of the search tree. */int main( int argc, char * argv[] ){  if( argc != 2 )  {    cout << "Usage: " << argv[0] << " n" << endl;    cout << "       where n is the number of queens to place" << endl;    cout << "       on an n x n chessboard, with 0 < n < 26" << endl;    exit( 2 );  }  assert( argc == 2 );  stringstream ss( argv[1] );  uint n;  ss >> n;  assert( n > 0 && n < 26 );  // Initialize a board with no queen  Matrix< bool > board( n, n );  uint queens[n];  for( uint row = 0; row < n; row++ )  {    for( uint col = 0; col < n; col++ )      board.at(row, col) = false;    queens[row] = UINT_MAX;  }  // Start with column 0  uint nodesUntilFound = 0;  uint nodesTotal = 0;  bool found = false;  r_backtrack( 0, board, queens, nodesUntilFound, nodesTotal, found );  if( !found )    cout << "No solution" << endl;  else    cout << nodesUntilFound << " nodes are visited until first solution." << endl;        cout << nodesTotal << " nodes are visited in total." << endl;  return 0;}