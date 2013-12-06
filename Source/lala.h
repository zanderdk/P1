#include "testGraph.h"

int SmallestDist(unsigned int *dist, unsigned int *visited, unsigned int V);
int Contains(unsigned int *list, unsigned int id,  unsigned int V);
void InsertIntoList(unsigned int *list, unsigned int id, unsigned int V);
void RemoveFromList(unsigned int *list, unsigned int id, unsigned int V);
int IsEmpty(int *list, unsigned int V);
void PrintList(unsigned int *list, unsigned int V);
int Dijkstra(Graph *graph, int sourceId, int targetId, int *pathList);