/**
 * A simple framework to implement a first-child, right-sibling
 * tree with unlimited children per node.
 * @author Hieu Le
 * @version 18 February 2016
 */

#include <iostream>
#include <queue>
using namespace std;

/**
 * A simple tree_node class.
 */
class tree_node
{
public:
  /**
   * Constructs a tree_node object.
   * @param data the character stored at this node
   * @param first_child a pointer to the first child of this node
   * @param right_sibling a pointer to the right sibling of this node
   */
  tree_node( char data, tree_node * first_child, tree_node * right_sibling )
    : data( data ), first_child( first_child ), right_sibling( right_sibling )
  {}

  /**
   * Returns the data stored at this node.
   * @return the character stored at this node
   */ 
  char get_data() const
  {
    return data;
  }

  /**
   * Returns the leftmost child of this node.
   * @return a pointer to the first child
   */
  tree_node * get_first_child() const
  {
    return first_child;
  }

  /**
   * Returns the right sibling of this node.
   * @return a pointer to the next sibling
   */
  tree_node * get_right_sibling() const
  {
    return right_sibling;
  }

private:
  char data;
  tree_node * first_child;
  tree_node * right_sibling;
};

/**
 * A utility function to print the content of a tree node.
 * @param node a pointer to the tree node
 */
void visit( tree_node * node )
{
  cout << node->get_data() << ' ';
}

/**
 * A recursive function to perform preorder traversal
 * on a tree or subtree rooted at a particular node.
 * @param node a pointer to the tree's root
 */
void preorder( tree_node * node )
{
  if( node != nullptr )
  {
    visit( node );
    preorder( node->get_first_child() );
    preorder( node->get_right_sibling() );
  }
}

/**
 * An iterative function to perform level order traversal
 * on a tree rooted at a particular node.
 * @param root a pointer to the tree's root
 */
void levelorder( tree_node * root )
{
  if( root == nullptr )
    return;

  // Store pointers to the next node to visit in a queue
  queue< tree_node * > frontier;
  frontier.push( root );

  while( !frontier.empty() )
  {
    tree_node * current = frontier.front();
    visit( current );
    frontier.pop();

    // Add all children of current to the queue
    tree_node * child = current->get_first_child();
    while( child != nullptr )
    {
      frontier.push( child );
      child = child->get_right_sibling();
    }
  }
}

/**
 * The main function.
 */
int main()
{
  tree_node * q = new tree_node{ 'Q', nullptr, nullptr };
  tree_node * p = new tree_node{ 'P', nullptr, q };
  tree_node * o = new tree_node{ 'O', nullptr, p };
  tree_node * n = new tree_node{ 'N', nullptr, nullptr };
  tree_node * m = new tree_node{ 'M', nullptr, n };
  tree_node * l = new tree_node{ 'L', nullptr, nullptr };
  tree_node * k = new tree_node{ 'K', nullptr, l };
  tree_node * j = new tree_node{ 'J', nullptr, k };
  tree_node * i = new tree_node{ 'I', o, nullptr };
  tree_node * h = new tree_node{ 'H', nullptr, i };
  tree_node * g = new tree_node{ 'G', nullptr, h };
  tree_node * f = new tree_node{ 'F', m, nullptr };
  tree_node * e = new tree_node{ 'E', j, nullptr };
  tree_node * d = new tree_node{ 'D', g, e };
  tree_node * c = new tree_node{ 'C', nullptr, d };
  tree_node * b = new tree_node{ 'B', f, c };
  tree_node * a = new tree_node{ 'A', b, nullptr };

  cout << "Preorder: ";
  preorder( a );
  cout << endl;

  cout << "Level order: ";
  levelorder( a );
  cout << endl;

  delete a;
  delete b;
  delete c;
  delete d;
  delete e;
  delete f;
  delete g;
  delete h;
  delete i;
  delete j;
  delete k;
  delete l;
  delete m;
  delete n;
  delete o;
  delete p;
  delete q;

  return 0;
}
