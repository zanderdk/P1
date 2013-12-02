#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vertex
{
	unsigned int id;
	unsigned int x, y;
	unsigned int floor;
	unsigned int type;
	EdgePointer *ep;
}Vertex;

typedef struct EdgePointer
{
	Edge *edge;
	EdgePointer *next;
}EdgePointer;

typedef struct Edge
{
	unsigned int id;
	unsigned int weight;
	Vertex *vertex1;
	Vertex *vertex2;
}Edge;

