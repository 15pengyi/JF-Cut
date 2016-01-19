GridCut is a C++ library of fast max-flow/min-cut solvers optimized for
grid graphs. The library is header-only and doesn't need to be compiled
separately. There is a single header file for each supported grid topology.
The header file contains class template which encapsulates the graph data
structure and solver specialized for the particular grid topology. In order
to start using GridCut, you just have to add the "./include" directory to your
compiler's include path and #include the desired header file in your code.

Following solvers are available in the ./include/GridCut directory:
 GridGraph_2D_4C.h     sequential solver for  4-connected 2D grid
 GridGraph_2D_4C_MT.h  parallel   solver for  4-connected 2D grid
 GridGraph_2D_8C.h     sequential solver for  8-connected 2D grid 
 GridGraph_3D_6C.h     sequential solver for  6-connected 3D grid 
 GridGraph_3D_6C_MT.h  parallel   solver for  6-connected 3D grid
 GridGraph_3D_26C.h    sequential solver for 26-connected 3D grid 

The first example in the ./examples directory demonstrates the basic usage
of the GridCut interface. For more details, see the comments in the public
interface declarations of each class.

To compute the maximum flow, first create an instance of the GridGraph class.
For example, an instance of 4-connected 2D grid graph where both maximum
flow and capacities of all edges are represented with ints can be created in
this way:

  typedef GridGraph_2D_4C<int,int,int> GraphType;
  GraphType* graph = new GraphType(myGridWidth,myGridHeight);


The newly created graph instance contains all grid nodes and edges.
Capacity of each edge is intialized to zero. To set the capacities of edges
connecting the node at coordinates (x,y) with terminals, call:

  graph->set_terminal_cap(graph->node_id(x,y),
                          capacityOfMyEdgeFromSource,
                          capacityOfMyEdgeToSink);


The set_terminal_cap function can be called at most once per each node.
Note that the graph->node_id(x,y) returns the index corresponding to the node
with coordinates (x,y). Capacities of edges between neighboring nodes can be
set up using the set_neighbor_cap function. For example, to set the capacity
of an edge between node (x,y) and node (x+1,y), call:
  
  graph->set_neighbor_cap(graph->node_id(x,y),+1,0,myCapacity);


Similarly, to set the capacity of an edge between node (x,y) and (x,y+1), call:

  graph->set_neighbor_cap(graph->node_id(x,y),0,+1,myCapacity);


Once all capacities are set, the maximum flow is computed by invoking:

  graph->compute_maxflow();


After the maxflow is computed the mincut parition can be determined by querying
each node for its membership to one of the source/sink segments. To query the
membership of a node at coordinates (x,y), call:

  graph->get_segment(graph->node_id(x,y));


The function returns 0 when the node is in the source segment or 1 when it is
in the sink segment.
