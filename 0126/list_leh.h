#ifndef LIST_LEH
#define LIST_LEH
#include <cassert>
#include <iostream>

using namespace std;
typedef unsigned int uint;

/**
 * A simplified generic singly linked list class to illustrate C++ concepts.
 * @author Hieu Le
 * @version 22 January 2016
 */
template< typename Object >
class List
{
  private:
   /*
    * A class to store data and provide a link to the next node in the list.
    */
    class Node
    {
      public:
        /**
         * The constructor.
         * @param data the data to be stored in this node
         */
        explicit Node( const Object & data )
            : data( data ), next( NULL ) {}

        Object data;
        Node * next;
    };

  public:
    /**
     * The constructor for an empty list.
     */
    List()
        : size( 0 ), first( NULL ), last( NULL ) {}

    /** 
     * The copy constructor.
     */
    List( const List & rhs ) = delete;

    /**
     * The move constructor.
     */
    List( List && rhs ) = delete;

    /**
     * The destructor that gets rid of everything that's in the list and
     * resets it to empty. If the list is already empty, do nothing.
     */
    ~List()
    {
        if( size != 0 )
        {
            Node * current = first;
            Node * temp;
            while( current != NULL )
            {
                temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    /**
     * The copy assignment operator.
     */
    List & operator= ( const List & rhs ) = delete;

    /**
     * The move assignment operator.
     */
    List & operator= ( List && rhs ) = delete;

    /**
     * Put a new element onto the beginning of the list.
     * @param item the data the new element will contain
     */
    void push_front( const Object & item )
    {
        Node * new_node = new Node( item );

        new_node->next = first;
        first = new_node;

        if( size == 0 )
        {
            last = new_node;
        }

        size++;
    }

    /**
     * Remove the element that's at the front of the list. Causes
     * an assertion error if the list is empty.
     */
    void pop_front()
    {
        assert( !is_empty() );
        Node * temp = first;

        if( size == 1 )
        {
            first = last = NULL;
        }
        else
        {
            first = first->next;
        }
        delete temp;
        size--;
    }

    /**
     * Accessor to return the data of the element at the front of the list.
     * Causes an assertion error if the list is empty.
     * @return the data in the front element
     */
    const Object & front() const
    {
        assert ( !is_empty() );
        return first->data;
    }

    /**
     * Accessor to determine whether the list is empty.
     * @return a boolean corresponding to the emptiness of the list
     */
    bool is_empty() const
    {
        return size == 0;
    }

    /**
     * Just for debugging, a helper accessor to dump the contents of the list
     * all on one line. Not for production use.
     */
    void dump() const
    {
        Node * current = first;

        for (uint i = 0; i < size; i++)
        {
            cout << current->data << ' ';
            current = current->next;
        }

        cout << endl;
    }

  private:
    uint size;
    Node * first;
    Node * last;
};

#endif

/**
  n           List 		 vector
10000		0:00.007	0:00.006
100000		0:00.019	0:00.010
1000000		0:00.134	0:00.041
10000000	0:01.244	0:00.390
100000000	0:12.458	0:03.483
1000000000	2:32.108	0:34.418
--------------------------------
System type: 
Darwin hieus-mbp.truman.edu 15.2.0 Darwin Kernel Version 15.2.0: 
Fri Nov 13 19:56:56 PST 2015; root:xnu-3248.20.55~2/RELEASE_X86_64 x86_64
*/

