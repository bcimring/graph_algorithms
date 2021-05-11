/*
 * kruskaltest.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: BCimr
 */

#include "iostream"
#include "string"
#include "iomanip"
#include "Graph.h"
#include "invalid_argument.h"

void display( Graph G ) {
	std::cout << std::endl;
	std::cout << "Graph Size: " << G.m << std::endl;
	std::cout << "Edges: " << std::endl;
	for ( int i = 0; i < G.E.size(); i++ ) {
		std::cout << G.E[i][0] << '\t' << G.E[i][1] << '\t' << G.E[i][2] << std::endl;
	}
	std::cout << std::endl;
}

bool in_str( std::string txt, char m ) {
	for ( unsigned int i = 0; i < txt.length(); i++ ) {
		if ( txt[i] == m ) {
			return true;
		}
	}
	return false;
}

double str2double( std::string string ) {
	double result{};
	bool dec_flag = false;
	bool neg_flag = false;
	double div{1.0};
	if ( string[0] == '-' ) {
		neg_flag = true;
		string = string.substr( 1, string.length() - 1 );
	}
	for ( int i = 0; i < string.length(); i++ ) {
		if ( string[i]-46 == 0 ) {
			dec_flag = true;
		} else if (string[i] == '\n') {
			break;
		} else {
			result = result*10 + string[i]-48;
			if ( dec_flag ) {
				div *= 10;
			}
		}
	}
	if ( neg_flag ) {
		return -result/div;
	}
	return result/div;
}

int main() {
	std::string line {};
	bool instantiated = false;
	Graph G = Graph();

	while ( !std::cin.eof() )  {
		getline(std::cin, line);

		if ( line == "exit" ) {
			G.clear();
			return 0;
		}

		if ( line[line.size()-1] == '\r' ) {
			line = line.substr(0, line.size()-1);
		}

		int graph_init = line.find("n")+1;
		int insert_idx = line.find("i")+1;
		int delete_idx = line.find("d")+1;
		int deg_idx = line.find("degree")+1;
		int ec_idx = line.find("edge_count")+1;
		int clear_idx = line.find("clear")+1;
		int mst_idx = line.find("mst")+1;
		int exit_idx = line.find("exit")+1;

		if (graph_init == 1) {
			long s_elem{}, e_elem{}, m{};
			s_elem = 2;
			e_elem = line.size();
		    m = str2double( line.substr( s_elem, e_elem-s_elem ) );

		    // init the graph
		    try {
		    	G = Graph( m );
		    	std::cout << "success" << std::endl;
		    } catch (invalid_argument) {
		    	std::cout << "invalid argument" << std::endl;
		    }

		} else if (insert_idx == 1) {
			int u{},v{};
			double w{};

			// parse all elements
			long s_elem{}, e_elem{};
			s_elem = 2;
			e_elem = line.find( ";", 0 );
			u = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			s_elem = 0;
			e_elem = line.find( ";", 0 );
			v = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			s_elem = 0;
			e_elem = line.find( ";", 0 );
		    w = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			// insert into graph

			try {
				bool inserted = G.insert( u, v, w );
				std::cout << "success" << std::endl;

			} catch (invalid_argument) {
		    	std::cout << "invalid argument" << std::endl;
			}

		} else if ( ( delete_idx == 1 ) && ( deg_idx != 1 ) ) {
			int u{},v{};

			// parse all elements
			long s_elem{}, e_elem{};
			s_elem = 2;
			e_elem = line.find( ";", 0 );
			u = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			s_elem = 0;
			e_elem = line.find( ";", 0 );
			v = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			// delete element

			try {
				int del = G.remove(u, v);
				if ( del == 1 ) {
					std::cout << "success" << std::endl;
				} else if ( del == 0 ) {
					std::cout << "failure" << std::endl;
				}
			} catch (invalid_argument) {
				std::cout << "invalid argument" << std::endl;
			}

		} else if ( deg_idx == 1 ){
			int u{};

			long s_elem = 7;
			long e_elem = line.size();
			u = str2double( line.substr( s_elem, e_elem-s_elem ) );

			// degree of u

			try {
				int degree = G.degree(u);
				std::cout << "degree of " << u << " is " << degree << std::endl;
			} catch (invalid_argument) {
				std::cout << "invalid argument" << std::endl;
			}


		} else if (ec_idx == 1) {
			int edge_count = G.edge_count();

			std::cout << "edge count is " << edge_count << std::endl;

		} else if (clear_idx == 1) {
			G.clear();
			instantiated = false;
			std::cout << "success" << std::endl;

		} else if (mst_idx == 1) {
			double w = G.mst();
			if ( w != -1 ) {
				std::cout << std::fixed;
				std::cout << std::setprecision(2);
				std::cout << "mst " << w << std::endl;
			} else {
				std::cout << "not connected" << std::endl;
			}

		} else if (exit_idx == 1) {
			G.clear();
			break;

		} else {
			std::cout << "failure" << std::endl;
		}
		//display(G);
	}


	return 0;

}



