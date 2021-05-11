/*
 * Linked_List.h
 *
 *  Created on: Sep 26, 2020
 *      Author: BCimr
 */
#include "Node.h"
#include "string"

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

class Linked_List {

private:
	Node* p_head;
	Node* p_tail;
	long vertex;
	long size;

public:

	Linked_List( long size, long nodes[], double weights[] , long i );
	Linked_List( int i );
	Linked_List( );
	Linked_List( const Linked_List& other );

	~Linked_List();

	Linked_List& operator=( const Linked_List &other );

	bool operator==( Linked_List other );

	long get_size();

	Node* get_head();

	void set_head( Node* new_head );

	Node* get_tail();

	void set_tail( Node* new_tail );

	Node* search( long key );

	bool remove( long to_delete );

	bool insert( Node* to_insert );

	bool is_empty();

	long get_vertex();

	void set_vertex( int i );

};

#endif /* LINKED_LIST_H_ */
