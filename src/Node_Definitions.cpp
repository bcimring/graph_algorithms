/*
 * Linked_List.cpp
 *
 *  Created on: Sep 11, 2020
 *      Author: BCimr
 */

#include "iostream"
#include "Node.h"
#include "string"

Node::Node( Node* p_next, Node* p_last, long other_node, double weight ):
p_next( p_next ), p_last( p_last ), v( other_node ), w( weight ) {

}

Node::~Node( ) {

}

Node* Node::get_p_next() {
	return p_next;
}

Node* Node::get_p_last() {
	return p_last;
}

void Node::set_p_next( Node* new_p ) {
	p_next = new_p;
}

void Node::set_p_last( Node* new_p ) {
	p_last = new_p;
}

double Node::get_weight() {
	return w;
}

long Node::get_node() {
	return v;
}

void Node::set_weight( long new_weight ) {
	w = new_weight;
	return;
}

void Node::set_node( long new_node ) {
	v = new_node;
	return;
}

