/**
 * Test matrix.h.
 * @author Hieu Le
 * @version March 30th, 2016
 */

#include "matrix.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
typedef unsigned int uint;

int main()
{
  srand( time( NULL ) );
  Matrix< uint > mat( 3, 3 );
  for( uint i = 0; i < mat.numrows(); i++ )
  {
    for( uint j = 0; j < mat.numcols(); j++ )
    {
      mat.at( i, j ) = rand() % 10;
    }
  }

  for( uint i = 0; i < mat.numrows(); i++ )
  {
    for( uint j = 0; j < mat.numcols(); j++ )
    {
      cout << mat.at( i, j ) << " ";
    }
    cout << endl;
  }

  return 0;
}
