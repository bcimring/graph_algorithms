/*
 * Graph.h
 *
 *  Created on: Nov 14, 2020
 *      Author: BCimr
 */

#include "Linked_List.h"
#include "vector"
#include "iostream"


#ifndef GRAPH_H_
#define GRAPH_H_

class Graph {
private:


public:
	std::vector<Linked_List> V;
	std::vector<std::vector<double>> E;
	int m;

	Graph( int m );
	Graph( );
	Graph( const Graph& other );

	Graph& operator=( const Graph& other );
	void clear( );
	int edge_count( );
	int degree( int u );
	double mst( );
	int remove( int u, int v );
	bool insert( int u, int v, double w );
	int find( int u );
	std::vector<std::vector<double>> merge_sort_edges( std::vector<std::vector<double>> E, int n );

};



#endif /* GRAPH_H_ */


