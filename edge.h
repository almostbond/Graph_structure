#pragma once

#include "vertex.h"

struct edge{

	int edge_weight;

	edge* edge_next;
	struct vertex* vertex_ptr;

};