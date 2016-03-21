/**
 * Adapted from Weiss 4th page 399
 * Dijkstra's algorithm
 * @author Jon Beck
 * @author Hieu Le
 * @version March 18th, 2016
 */

#include <iostream>
#include <vector>
#include <climits>
#include <list>
#include <queue>

typedef unsigned int uint;

using namespace std;

/**
 * Overloads the less-than operator to compare two unint-uint pairs by
 * their second elements.
 * @param a the first pair
 * @param b the second pair
 * @return the truth value of a < b on the second elements
 */
bool operator< ( const pair<uint, uint> & a, const pair<uint, uint> & b )
{
  return a.second < b.second;
}

/**
 * Computes the weight and prints out the shortest path from a source
 * vertex to all other vertices in a weighted digraph with non-negative
 * edge weights.
 * @param s the source vertex
 * @param graph the adjacency list representation fo the graph
 */
void dijkstra( uint s, const vector<list<pair<uint, uint> > > & graph )
{
  vector< uint > dist;
  vector< bool > known;
  vector< uint > path;
  const uint DUMMY = 0;
  for( uint i = 0; i < graph.size(); i++ )
  {
    dist.push_back( INT_MAX );
    known.push_back( false );
    path.push_back( DUMMY );
  }

  dist.at( s ) = 0;
  priority_queue<pair<uint, uint> > pq;
  pq.push( make_pair( s, 0 ) );

  while( !pq.empty() )
  {
    uint v = pq.top().first;
    pq.pop();

    if( !known.at( v ) )
    {
      known.at( v ) = true;
      for( auto iter = graph.at( v ).begin(); iter != graph.at( v ).end(); ++iter )
      {
	if( !known.at( iter->first ) && 
	    dist.at( iter->first ) > dist.at( v ) + iter->second )
	{
	  dist.at( iter->first ) = dist.at( v ) + iter->second;
	  pq.push( make_pair( iter->first, dist.at( iter-> first ) ) );
	  path.at( iter->first ) = v;
	}
      }
    }
  }

  cout << "The distance from " << s << " to:" << endl;
  for( uint i = 1; i < graph.size(); i++ )
  {
    cout << "  " << i << " is " << dist.at( i ) << endl;
  }

  cout << "The paths (backwards) are:" << endl;
  for( uint i = 1; i < graph.size(); i++ )
  {
    cout << "v" << i << ": ";
    uint previous = path.at( i );
    while( previous != DUMMY )
    {
      cout << previous << " ";
      previous = path.at( previous );
    }
    cout << endl;
  }
}

/**
 * The main program
 */
int main()
{
  vector<list<pair<uint, uint> > > graph;

  // The 0 position is an unused dummy, Weiss starts nodes at 1
  // In fact, this is just like an unreachable node
  list<pair<uint, uint> > v0list;
  graph.push_back( v0list );

  list<pair<uint, uint> > v1list;
  v1list.push_back( make_pair( 2, 2 ) );
  v1list.push_back( make_pair( 4, 1 ) );
  graph.push_back( v1list );

  list<pair<uint, uint> > v2list;
  v2list.push_back( make_pair( 4, 3 ) );
  v2list.push_back( make_pair( 5, 10 ) );
  graph.push_back( v2list );

  list<pair<uint, uint> > v3list;
  v3list.push_back( make_pair( 1, 4 ) );
  v3list.push_back( make_pair( 6, 5 ) );
  graph.push_back( v3list );

  list<pair<uint, uint> > v4list;
  v4list.push_back( make_pair( 3, 2 ) );
  v4list.push_back( make_pair( 5, 2 ) );
  v4list.push_back( make_pair( 6, 8 ) );
  v4list.push_back( make_pair( 7, 4 ) );
  graph.push_back( v4list );

  list<pair<uint, uint> > v5list;
  v5list.push_back( make_pair( 7, 6 ) );
  graph.push_back( v5list );

  list<pair<uint, uint> > v6list;
  graph.push_back( v6list );

  list<pair<uint, uint> > v7list;
  v7list.push_back( make_pair( 6, 1 ) );
  graph.push_back( v7list );

  uint source = 1;
  dijkstra( source, graph );

  return 0;
}







