#include <iostream>
#include <sstream>

typedef unsigned int uint;
using namespace std;

/**
 * An analysis of an algorithm to find the largest
 * power of 2 less than or equal to non-negative
 * integer n.
 * @author Hieu Le
 * @version 9 February 2016
 */

/**
 * Computes the largest of 2 less than or equal to
 * a non-negative integer.
 * @param n the non-negative integral input
 * @param opCount a reference to the number of 
 * basic operations
 * @return the maximum power of 2 not exceeding n
 */
uint find_max_power( uint n, uint & opCount )
{
  uint i = n;
  uint j = i & (i - 1);
  opCount++;

  while ( j != 0 )
  {
    i = j;
    j = i & (i - 1);
    opCount++;
  }

  return i;
}

/**
 * The main method.
 * @param argc the number of input tokens
 * @param argv the array of input tokens
 * @return the program status
 */
int main( int argc, char * argv[] )
{
  if ( argc != 2 )
  {
    cerr << "Usage: " << argv[0] << " n where n is a " <<
      "non-negative integer" << endl;
    return 1;
  }

  stringstream ss( argv[1] );
  uint n;
  ss >> n;

  uint opCount = 0;
  uint result = find_max_power( n, opCount );

  // Output the result
  cout << "The highest power of 2 in " << n <<  " is " <<
     result << "." << endl;
  cerr << n << " " << opCount << endl;

  return 0;
}
