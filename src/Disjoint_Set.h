/*
 * Disjoint_Set.h
 *
 *  Created on: Nov 14, 2020
 *      Author: BCimr
 */
#include "Linked_List.h"

#ifndef DISJOINT_SET_H_
#define DISJOINT_SET_H_

class Disjoint_Set {
private:
	int m;
	Node* vertex;

public:

	Disjoint_Set( long x );
	Disjoint_Set();
	Disjoint_Set( const Disjoint_Set& other );
	~Disjoint_Set();
	Disjoint_Set& operator=( const Disjoint_Set &other);

	bool DS_union( Disjoint_Set &y );

	Node* find_set( Node* x );
	Node* get_vertex( );

};



#endif /* DISJOINT_SET_H_ */
