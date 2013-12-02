#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Floor
{
	unsigned int floor;
	Vertex *vp;
	Floor *fp;
}Floor;

typedef struct Vertex
{
	unsigned int id;
	unsigned int x, y;
	unsigned int type;
	unsigned int floor;
	EdgePointer *ep;
	Vertex *vp;
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

 
