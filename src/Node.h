/*
 * Node.h
 *
 *  Created on: Sep 15, 2020
 *      Author: BCimr
 */
#include "string"

#ifndef NODE_H_
#define NODE_H_

class Node {
private:
	Node* p_next;
	Node* p_last;
	double w;
	long v;

public:

	Node( Node* p_next, Node* p_last, long node, double weight );

	~Node( );

	Node* get_p_next();
	Node* get_p_last();

	void set_p_next( Node* new_p );
	void set_p_last( Node* new_p );

	double get_weight();

	long get_node();

	void set_weight( long new_w );

	void set_node( long new_node );
};

#endif /* Node_H_ */

