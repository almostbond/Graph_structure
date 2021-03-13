// graph_final.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*
                                                ~~Some notes before using~~
        This is most for testing my incomplete shortest path function, so ffel free to ignore this.
* The graph need to have a connectivity of 1. That is to say no vertices can be left unconnected.
* The current algorithm that I implemented for traversing the graph, and finding the cheapest edges is pretty stupid.
  With the grpah that I currently have confirgured it can only traverse the graph from nodes A(0) and D(3).
  This is because the loves to back itself into a corner and then freak out because it can't go anywhere.

*/

#include <iostream>
#include <string>
#include "graph.h"


using namespace std;
// constructs our Graph class
Graph::Graph() {
    int index = 0;
    
    
    //initializes vertices.
    for (int i = 0; i < array_size; i++) {
        array_content[i] = new vertex;
        array_content[i]->vertex_name = "empty";
        array_content[i]->edge_ptr = NULL;
        array_content[i]->touched = false;
        array_content[i]->index = i;

       
    }   
}
// Constructs our testing class.
Graph_test::Graph_test() {}

void Graph::create_vertex(string name) {

    
    //for some reason index refuses to be equal zero upon construction so this is a little fix.
    if (index < 0) {
        index = 0;
    }
    //since my graph is not dynamic I limit the index to the size of the array.
    if (index == array_size) {
        cout << "max amount of vertices has been reached." << endl;
    }
    //otherwise the vertex is named and the index is incremented.
    else {
        cout << index << endl;
        array_content[index]->vertex_name = name;
        cout << "vertex "<< array_content[index]->vertex_name <<" created" << endl;
        index++;
    }
}

//I use a linked list to add new edges onto vertices.
void Graph::create_edge(int weight, int ipos, int fpos) {

    vertex* source = array_content[ipos];//our initial vertex
    vertex* destination = array_content[fpos];//The vertex we want to connect to.
    edge* next_edge = array_content[ipos]->edge_ptr;// initial edge of our source vertex.

    // a new edge is initialized.
    edge* new_edge = new edge;
    new_edge->edge_weight = weight;
    new_edge->edge_next = NULL;

    //logic to place the new edge in the appropriate spot.
    if (next_edge != NULL) {

        while (next_edge->edge_next != NULL) {
            next_edge = next_edge->edge_next;
        }
        next_edge->edge_next = new_edge; // the source vertex now has a new edge 
        new_edge->vertex_ptr = destination;// new edge now points towards the destination vertex
    }
    // else statement covers when the vertex does not have any current edges.
    else {

        source->edge_ptr = new_edge;
        new_edge->vertex_ptr = destination;
    }

    cout << "edge between " << array_content[ipos]->vertex_name << " and " << destination->vertex_name << " made" << endl;

}

// makes the graph undirected.
void Graph::add_edge(int weight, int ipos, int fpos) {

    create_edge(weight, ipos, fpos);
    create_edge(weight, fpos, ipos);

}

void Graph::print_adjacent(int sauce) {

    cout << "nodes adjacent to " << array_content[sauce]->vertex_name << endl;

    edge* source = array_content[sauce]->edge_ptr;
    // iterates through a nodes edges, if the edge points to a vertex it prints the vertex
    while (source != NULL) {

        if (source->vertex_ptr != NULL) {
            cout << source->vertex_ptr->vertex_name << " ";
        }
        source = source->edge_next;
    }
    cout << endl;
}

// I am making the assumption that there will always be a path between the initial vertex and the final.
void Graph::dijkstra(int ipos) {
    // I am giving up on implementing Dijkstra and prim using a hashtable.
    // this code is here simply to show that I tried before finding an alternative route.
    dijkstra_list_init();
    
    dijkstra_smallest(ipos);

    for (int i = 0; i < array_size; i++) {
    
        processing_list[i]->sum_of_path = INT_MAX;

    }


}


void Graph::dijkstra_list_init() {

    for (int i = 0; i < array_size; i++) {

        processing_list[i] = new node;
        processing_list[i]->vertex_index = i;
        processing_list[i]->sum_of_path = INT_MAX;
        processing_list[i]->previous = NULL;

    }

}

void Graph::dijkstra_add_weight(edge* edge, int pos) {
    node* current = processing_list[pos];

    int weight_be_added = edge->edge_weight;
    int vertex_index = edge->vertex_ptr->index;

    if (processing_list[vertex_index]->sum_of_path)
        processing_list[vertex_index]->sum_of_path += weight_be_added;

    
}

//checks to see if all vertices have been checked.
bool Graph::touch_check() {
    bool all_touched = true;
       
    // 
    for (int i = 0; i < array_size; ++i) {

        if (array_content[i]->touched == false) {
            all_touched = false;
        }
    }   
    return all_touched;
}

// finds the cheapest path with respect to a chosen node. assumes that vertex_ptr will never be NULL.
int Graph::dijkstra_smallest(int ipos) {   

    cout  << "adjacent edge values for " << array_content[ipos]->vertex_name << ": ";
    
    
    int smallest_weight = INT_MAX;
    edge* cheapest_edge = NULL;

    edge* source = array_content[ipos]->edge_ptr;

    bool all_touched = touch_check();

    if (all_touched == true) {

        cout << "hello!" << endl;
        return 0;
    }
    else {

        while (source != NULL) {

            if (source->vertex_ptr->touched != true) {
                cout << source->edge_weight << " ";
                // some function that takes in the edge weight and the node that that edge points to.

                //dijkstra_add_weight(source, ipos);

                if (smallest_weight > source->edge_weight) {

                    cheapest_edge = source;
                    smallest_weight = source->edge_weight;
                }                
            }
            source = source->edge_next;
        }
    }
    array_content[ipos]->touched = true;
    cout << endl;
    
    if (touch_check() == false) {        
        dijkstra_smallest(cheapest_edge->vertex_ptr->index);        
    } 
    
    return cheapest_edge->vertex_ptr->index;
}



void Graph_test::create_vertex_test() {
    
    create_vertex("A");
    create_vertex("B");
    create_vertex("C");
    create_vertex("D");
    create_vertex("E");
    //create_vertex("F");
    //create_vertex("G");
    //create_vertex("J");
   


}

void Graph_test::create_edge_test() {

    create_vertex_test();

    add_edge(6,0,1);// A-B
    add_edge(5,1,2);// B-C
    add_edge(1,0,3);// A-D
    add_edge(2,1,3);// B-D
    add_edge(1,3,4);// D-E
    add_edge(2,1,4);// B-E
    add_edge(5,2,4);// C-E

    print_adjacent(0);
    print_adjacent(3);
    print_adjacent(1);
    //print_adjacent(3);
    //print_adjacent(4);
   
}

void Graph_test::dijkstra_test() {
    create_edge_test();
    dijkstra(1);
    
    

}

int main()
{
    Graph tree;
    Graph_test test;

    //test.create_vertex_test();
    test.create_edge_test();
    //test.dijkstra_test();

    cout << "\nexit success.\n";
}

