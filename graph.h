#pragma once
#include "vertex.h"
#include <string>
using namespace std;

class Graph {
private:


	static const int array_size = 10;
	
	vertex* array_content[array_size];
	
	int index;

	void dijkstra_helper(int ipos, int fpos);


public:
	Graph();
	
	void create_vertex(string name);
	//void add_vertex(vertex* ptr);
	void create_edge(int weight, int ipos, int fpos);
	void add_edge(int weight, int ipos, int fpos);
	void print_adjacent(int source);

	void dijkstra(int ipos, int fpos);


};


class Graph_test : Graph {


public:
	Graph_test();
	void create_vertex_test();
	void create_edge_test();
};