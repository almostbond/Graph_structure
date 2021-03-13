#pragma once

#include <string>
#include "edge.h"

using namespace std;

struct vertex {

	bool touched;
	int index;
	string vertex_name;
	struct edge* edge_ptr;


};