/*
 * Graph_Definitions.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: BCimr
 */

#include "Graph.h"
#include "Linked_List.h"
#include "vector"
#include "Disjoint_Set.h"
#include "iostream"
#include "invalid_argument.h"


Graph::Graph( int size ) {
	m = size;

	if ( size <= 0 ) {
		throw invalid_argument();
	}

	for ( int i = 0; i < m; i++ ) {
		V.push_back(Linked_List( ));
		V[i].set_vertex(i);
	}

}

Graph::Graph( ) {
	m = 0;
}

Graph::Graph( const Graph& other ) {
	m = other.m;

	V.erase(V.begin(), V.end());
	V.reserve(m);

	E.erase(E.begin(), E.end());
	E.reserve(m);

	for ( long i = 0; i < m; i++ ) {
		V.push_back(other.V[i]);
	}

	for ( int i = 0; i < other.E.size(); i++ ) {
		E.push_back(other.E[i]);
	}
}

Graph& Graph::operator=( const Graph& other ) {
	Graph temp(other);
	std::swap(m, temp.m);
	std::swap(V, temp.V);
	std::swap(E, temp.E);

	return *this;
}

void Graph::clear( ) {
	E.erase(E.begin(), E.end());
	for ( long i = 0; i < m; i++ ) {
		V[i].~Linked_List();
		V[i] = Linked_List( );
		V[i].set_vertex( i );
	}
	return;
}

int Graph::edge_count( ) {
	return E.size();
}

int Graph::degree( int u ) {

	if ( ( u < m ) && ( u >= 0 ) ) {
		int deg = V[u].get_size();
		if ( V[u].search(u) != nullptr ) {
			deg++;
		}
		return deg;
	} else {
		throw invalid_argument();
	}
	return -1;
}

double Graph::mst( ) {
	double weight_sum{};
	long vertices[m] = {};
	std::vector<std::vector<double>> A;


	for ( int i = 0; i < m; i++ ) {
		vertices[i] = i;
	}

	Disjoint_Set Sets[m];
	for ( int i = 0; i < m; i++ ) {
		Sets[i] = Disjoint_Set( i );
		Sets[i].get_vertex()->set_p_last( Sets[i].get_vertex() );
	}

	if ( ( E.size() < m-1 ) || ( m == 0 ) ) {
		return -1;
	}
	E = this->merge_sort_edges( E, E.size() );


	for ( unsigned int i = 0; i < E.size(); i++ ) {
		int i1 = static_cast<int>(E[i][0]);
		int i2 = static_cast<int>(E[i][1]);

		Node* x = Sets[i1].get_vertex()->get_p_last();
		Node* y = Sets[i2].get_vertex()->get_p_last();


		if ( x != y ) {
			A.push_back(E[i]);
			Sets[i1].DS_union( Sets[i2] );
		}
	}

	Node* test = Sets[0].get_vertex()->get_p_last();
	int size{};

	while ( test != nullptr ) {
		size++;
		test = test->get_p_next();
	}


	if ( size == m ) {
		for ( int i = 0; i < A.size(); i++ ) {
			weight_sum += A[i][2];
		}

		return weight_sum;
	}

	return-1;
}

int Graph::remove( int u, int v ) {
	if ( ( ( u >= m ) || ( u < 0 ) ) || ( ( v >= m ) || ( v < 0 ) ) ) {
		throw invalid_argument();
	}

	if ( u == v ) {
		if ( V[u].remove( u ) ) {
			for ( int i = 0; i < E.size(); i++ ) {
				if ( E[i][0] == v ) {
					E.erase( E.begin()+i, E.begin()+i+1 );
					break;
				}
			}
			return 1;
		}
	}

	if ( ( V[u].remove( v ) ) && ( V[v].remove( u ) ) ) {
		int i = 0;
		for ( int i = 0; i < E.size(); i++ ) {
			if ( ( ( E[i][0] == v ) && ( E[i][1] == u ) ) || ( ( E[i][0] == u ) && ( E[i][1] == v ) ) ) {
				E.erase( E.begin()+i, E.begin()+i+1 );
				break;
			}
		}
		return 1;
	} else {
		return 0;
	}
}

bool Graph::insert( int u, int v, double w ) {
	if ( w <= 0 ) {
		throw invalid_argument();
	}
	if ( ( ( u >= m ) || ( u < 0 ) ) || ( ( v >= m ) || ( v < 0 ) ) ) {
		throw invalid_argument();
	} else {
		if ( ( u == v ) && ( V[u].search(u) == nullptr ) ) {
			Node* new_node_u = new Node( nullptr, nullptr, u, w );
			V[u].insert( new_node_u );

			std::vector<double> new_edge{};
			new_edge.push_back(u);
			new_edge.push_back(v);
			new_edge.push_back(w);
			E.push_back( new_edge );

			return true;
		} else if ( (u == v) && ( V[u].search(u) != nullptr ) ) {
			int i = 0;
			while ( ( E[i][0] != u ) || ( E[i][1] != u ) ) {
				i++;
			}
			E[i][2] = w;

		} else {

			if ( ( V[u].search(v) == nullptr ) && ( V[v].search(u) == nullptr ) ) {
				Node* new_node_v = new Node( nullptr, nullptr, v, w );
				Node* new_node_u = new Node( nullptr, nullptr, u, w );
				V[u].insert( new_node_v );
				V[v].insert( new_node_u );

				std::vector<double> new_edge{};
				new_edge.push_back(u);
				new_edge.push_back(v);
				new_edge.push_back(w);
				E.push_back( new_edge );

				return true;
			} else if ( ( V[u].search(v) != nullptr ) && ( V[v].search(u) != nullptr ) ) {
				int i = 0;
				while ( ( ( E[i][0] != u ) || ( E[i][1] != v ) ) && ( ( E[i][0] != v ) || ( E[i][1] != u ) ) ) {
					i++;
				}
				E[i][2] = w;
			}
		}

	}

}

int Graph::find( int u ) {
	for ( int i = 0; i < m; i++ ) {
		if ( V[i].get_vertex() == u ) {
			return i;
		}
	}

	return -1;
}

std::vector<std::vector<double>> Graph::merge_sort_edges( std::vector<std::vector<double>> E, int n ) {

	if ( n < 2 ) {
		return E;
	}

	std::vector<std::vector<double>> E1;
	std::vector<std::vector<double>> E2;

	int i = n/2;

	for ( int k = 0; k < i; k++ ) {
		E1.push_back(E[k]);
		E2.push_back(E[k+i]);
	}
	if ( n - 2*i > 0 ) {
		E2.push_back(E[2*i]);
	}

	E1 = this->merge_sort_edges( E1, i );
	E2 = this->merge_sort_edges( E2, n-i );
	E.clear();

	while ( !( E1.empty() ) || !( E2.empty() ) ) {
		if ( E1.empty() ) {
			E.push_back(E2[0]);
			E2.erase(E2.begin());
		} else if ( E2.empty() ) {
			E.push_back(E1[0]);
			E1.erase(E1.begin());
		} else {
			if ( E1[0][2] <= E2[0][2] ) {
				E.push_back(E1[0]);
				E1.erase(E1.begin());
			} else {
				E.push_back(E2[0]);
				E2.erase(E2.begin());
			}
		}
	}

	return E;

}



