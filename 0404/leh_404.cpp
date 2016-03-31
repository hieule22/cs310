/**
 * Calculate the optimum number of coins to make an amount of money.
 * @author Jon Beck
 * @author Hieu Le
 * @version March 30th, 2016
 */
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
#include "matrix.h"

using namespace std;
typedef unsigned int uint;

// Set infinity to one less than the maximum so we can add one to
// infinity and not overflow around to zero
const uint INF = UINT_MAX - 1;

/**
 * The recursive, memoized optimum function for making an amount
 * of money using coins.
 * @param i the index of the denomination vector
 * @param a the amount of money we are trying to make
 * @param denom the vector of coin denomination, denom[0] is always 1
 * @param memo the memoization table; rows is indexed by i, columns 
 * is indexed by the amount of money
 * @return the optimum (minimum) number of coins to make this amount,
 * using coin denominations at or below i
 */
uint opt( uint i, uint a, const vector< uint > & denom, Matrix< uint > & memo )
{
  // Base cases are built into the memo table with entries of INF
  if( memo.at(i, a) != INF )
    return memo.at(i, a);

  if( a < denom.at(i) )
  {
    memo.at(i, a) = opt( i - 1, a, denom, memo );
    return memo.at(i, a);
  }

  memo.at(i, a) = min( opt( i, a - denom.at(i), denom, memo ) + 1,
		       opt( i - 1, a, denom, memo ) );
  return memo.at(i, a);
}

/**
 * The recursive method to find an optimal combination of coins.
 * @param i the index of the denomination vector
 * @param a the amount of money we are trying to make
 * @param denom the vector of coin denominations
 * @param memo the memo table
 * @param denomCount the numbers of coins for each denomination
 */
void findOpt( uint i, uint a, const vector< uint > & denom, 
	      const Matrix< uint > & memo, vector< uint > & denomCount )
{
  // Base cases: Amount equals 0 or there are only pennies left to fill
  if( a == 0 )
    return;
  if( i == 0 )
  {
    denomCount.at( i ) += a;
    return;
  }

  if( a < denom.at( i ) || memo.at( i - 1, a ) == memo.at( i , a ) )
  {
    findOpt( i - 1, a, denom, memo, denomCount );
  }
  else
  {
    denomCount.at( i )++;
    findOpt( i, a - denom.at(i), denom, memo, denomCount );
  }
}

/**
 * Gets the amount of money to be made from the command line.
 * Sets up the denominations and memo table.
 * Prints the results.
 */
int main( int argc, char * argv [] )
{
  if( argc != 2 )
  {
    cerr << "Usage: " << argv[0] << " a where a is the amount of money"
	 << endl;
    return 1;
  }

  stringstream ss( argv[1] ); // Get the command line parameter
  uint amount = 0;
  ss >> amount;

  vector< uint > denom{1, 6, 10};
  Matrix< uint > memo( denom.size(), amount + 1 );
  for( uint row = 1; row < denom.size(); row++ )
    for( uint col = 1; col <= amount; col++ )
      memo.at( row, col ) = INF;

  for( uint row = 0; row < denom.size(); row++ )
    memo.at( row, 0 ) = 0;

  for( uint col = 0; col <= amount; col++ )
    memo.at( 0, col ) = col;

  uint result = opt( denom.size() - 1, amount, denom, memo );

  cout << "Using denominations";
  for( uint i = 0; i < denom.size(); i++ )
    cout << " " << denom.at(i);

  cout << endl << "The optimal number of coins for " <<
    amount << " is " << result << endl;

  cout << endl << "The completed memo table: " << endl << endl;

  for( uint row = 0; row < memo.numrows(); row++ )
  {
    for( uint col = 0; col < memo.numcols(); col++ )
    {
      if ( memo.at( row, col ) == INF )
	cout << "  -";
      else
	cout << setw( 3 ) << memo.at( row, col );
    }
    cout << endl;
  }

  // Print out one minimum combination of coins
  vector< uint > denomCount;
  for( uint i = 0; i < denom.size(); i++ )
    denomCount.push_back( 0 );

  findOpt( denom.size() - 1, amount, denom, memo, denomCount );

  cout << endl << "Coins used:" << endl;
  for( uint i = 0; i < denom.size(); i++ )
  {
    cout << denom.at(i) << ": " << denomCount.at( i ) << endl;
  }

  return 0;
}
