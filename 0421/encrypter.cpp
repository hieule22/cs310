#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
typedef unsigned int uint;

int main()
{
  string infile_dir, outfile_dir, key;
  cout << "Enter input file directory: ";
  cin >> infile_dir;
  cout << "Enter output file directory: ";
  cin >> outfile_dir;
  cout << "Enter key: ";
  cin >> key;

  ifstream infile( infile_dir );
  ofstream outfile( outfile_dir );
  uint n = key.size();
  char c;
  uint i = 0;
  while( infile.get(c) )
  {
    outfile << (char)( c ^ key[i] );
    i = (i + 1) % n;
  }  

  infile.close();
  outfile.close();
}
