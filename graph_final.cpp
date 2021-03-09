// graph_final.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*
a function to add a new vertex to the graph (perhaps add_vertex(vertex_name))

a function to add a new edge between two vertices of the graph(perhaps add_edge(source, destination) or source.add_edge(destination))

a function for a shortest path algorithm(perhaps shortest_path(source, destination))

a function for a minimum spanning tree algorithm(example min_span_tree()).
*/

#include <iostream>
#include <string>
#include "graph.h"

using namespace std;

Graph::Graph() {
    int graph_index = 0;
    
    
    
    for (int i = 0; i < array_size; i++) {
        array_content[i] = new vertex;
        array_content[i]->vertex_name = "empty";
        array_content[i]->edge_ptr = NULL;
    }
    
}

Graph_test::Graph_test() {}

void Graph::create_vertex(string name) {

    //cout << "vertex being created" << endl;
    //for some reason index refuses to be equal zero upon construction so this is a little fix.
    if (index < 0) {
        index = 0;
    }
    if (index == 10) {
        cout << "max amount of vertices has been reached." << endl;
    }
    else {
        cout << index << endl;
        array_content[index]->vertex_name = name;
        cout << "vertex "<< array_content[index]->vertex_name <<" created" << endl;
        index++;
    }
}


void Graph::create_edge(int weight, int ipos, int fpos) {

    vertex* source = array_content[ipos];
    vertex* destination = array_content[fpos];
    edge* next_edge = array_content[ipos]->edge_ptr;

    edge* new_edge = new edge;
    new_edge->edge_weight = weight;
    new_edge->edge_next = NULL;

    if (next_edge != NULL) {
        
        while (next_edge->edge_next != NULL) {
            next_edge = next_edge->edge_next;
        }
        next_edge->edge_next = new_edge;
        new_edge->vertex_ptr = destination;
    }
    else {

        source->edge_ptr = new_edge;
        new_edge->vertex_ptr = destination;
    }    

    cout << "edge between "<< array_content[ipos]->vertex_name << " and " << destination->vertex_name<<" made" << endl;

}

void Graph::add_edge(int weight, int ipos, int fpos) {

    create_edge(weight, ipos, fpos);
    create_edge(weight, fpos, ipos);

}

void Graph::print_adjacent(int sauce) {

    cout << "nodes adjacent to " << array_content[sauce]->vertex_name << endl;
    
    edge* source = array_content[sauce]->edge_ptr;

    while (source != NULL) {

        if (source->vertex_ptr != NULL) {
            cout << source->vertex_ptr->vertex_name << " ";
        }
        source = source->edge_next;
    }
    cout << endl;
}


void Graph::dijkstra(int ipos, int fpos) {

    dijkstra_helper(ipos, fpos);

}

edge* Graph::dijkstra_helper(int ipos, int fpos) {
   
    cout << "adjacent edge values for "<< array_content[ipos]->vertex_name << ": ";
    
    int smallest_weight = 100;

    edge* source = array_content[ipos]->edge_ptr;

    while (source != NULL) {

        if (source->vertex_ptr != NULL) {
            cout << source->edge_weight << " ";

            if (smallest_weight > source->edge_weight) {
                smallest_weight = source->edge_weight;
            }
            
        }
        source = source->edge_next;
    }
    cout << endl;




}

void Graph_test::create_vertex_test() {
    
    create_vertex("A");
    create_vertex("B");
    create_vertex("C");
    create_vertex("D");
    create_vertex("E");
    create_vertex("F");
    create_vertex("G");
    create_vertex("J");
   


}

void Graph_test::create_edge_test() {

    create_vertex_test();

    add_edge(1,0,1);// A-B
    add_edge(2,1,2);// B-C
    add_edge(3,0,3);// A-D
    add_edge(4,1,3);// B-D
    add_edge(5,3,4);// D-E
    add_edge(6,1,4);// B-E
    add_edge(7,2,4);// C-E

    print_adjacent(0);
    print_adjacent(1);
    print_adjacent(2);
    print_adjacent(3);
    print_adjacent(4);
   
}

void Graph_test::dijkstra_test() {
    create_edge_test();
    dijkstra(0,2);


}

int main()
{
    Graph tree;
    Graph_test test;

    //test.create_vertex_test();
    //test.create_edge_test();
    test.dijkstra_test();

    cout << "\nexit success.\n";
}

