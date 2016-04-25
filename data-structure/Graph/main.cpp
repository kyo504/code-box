#include "Graph.h"
#include <cstdio>

int main(int argc, char* argv[])
{
	Graph gp;

	gp.GraphInit(7);

	gp.AddEdge(A, B);
	gp.AddEdge(A, D);
	gp.AddEdge(B, C);
	gp.AddEdge(D, C);
	gp.AddEdge(D, E);
	gp.AddEdge(E, F);
	gp.AddEdge(E, G);


	gp.ShowGraphEdgeInfo();

	gp.DFSShowGraphVertex(A);
	printf("\n");
	gp.DFSShowGraphVertex(C);
	printf("\n");
	gp.DFSShowGraphVertex(E);
	printf("\n");
	gp.DFSShowGraphVertex(G);
	printf("\n");
}