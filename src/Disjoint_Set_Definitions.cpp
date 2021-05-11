/*
 * Disjoint_Set_Definitions.cpp
 *
 *  Created on: Nov 15, 2020
 *      Author: BCimr
 */

#include "Linked_List.h"
#include "Disjoint_Set.h"
#include "Node.h"
#include "iostream"

Disjoint_Set::Disjoint_Set( long x ) {
	m = 1;
	vertex = new Node( nullptr, nullptr, x, 0 );
	vertex->set_p_last( vertex );

}

Disjoint_Set::Disjoint_Set( const Disjoint_Set& other ) {
	m = other.m;
	vertex = new Node( nullptr, nullptr, other.vertex->get_node(), 0);

}

Disjoint_Set& Disjoint_Set::operator=( const Disjoint_Set &other ) {
	m = other.m;
	vertex = new Node( nullptr, nullptr, other.vertex->get_node(), 0);

}

Disjoint_Set::~Disjoint_Set() {
	delete vertex;

}

Disjoint_Set::Disjoint_Set() {
	vertex = nullptr;
	m = 0;

}


bool Disjoint_Set::DS_union( Disjoint_Set &other ) {
	Node* x = vertex;
	Node* y = other.vertex;

	if ( x == y ) {
		return false;
	}

	other.m = 0;

	if ( x->get_p_last() != nullptr ) {
		x = x->get_p_last();
	}

	if ( y->get_p_last() != nullptr ) {
		y = y->get_p_last();
	}

	while ( x->get_p_next() != nullptr ) {
		x = x->get_p_next();
	}

	x->set_p_next( y );

	Node* p_temp2 = y;
	while ( p_temp2 != nullptr ) {
		m++;
		p_temp2->set_p_last( vertex->get_p_last() );
		p_temp2 = p_temp2->get_p_next();
	}

	return true;


}

Node* Disjoint_Set::find_set( Node* x ){
	return x->get_p_last();

}

Node* Disjoint_Set::get_vertex( ) {
	return vertex;

}


