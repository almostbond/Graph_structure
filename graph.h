#pragma once
#include "vertex.h"
#include <string>
using namespace std;

class Graph {
private:

	struct node {

		int vertex_index;
		int sum_of_path;
		struct vertex* previous;


	};

	static const int array_size = 5;
	
	vertex* array_content[array_size];
	node* processing_list[array_size];
	int index;

	int dijkstra_smallest(int ipos);
	void dijkstra_list_init();
	void dijkstra_add_weight(edge* edge, int pos);
	
	


public:
	Graph();
	
	void create_vertex(string name);
	//void add_vertex(vertex* ptr);
	void create_edge(int weight, int ipos, int fpos);
	void add_edge(int weight, int ipos, int fpos);
	void print_adjacent(int source);

	void dijkstra(int ipos);

	bool touch_check();

};


class Graph_test : Graph {


public:
	Graph_test();
	void create_vertex_test();
	void create_edge_test();
	void dijkstra_test();

};