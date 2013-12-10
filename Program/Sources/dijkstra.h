#include "graph.h"
typedef struct WorkVertex WorkVertex;
typedef struct WVLinkedList WVLinkedList;

struct WorkVertex {
    Vertex *vertex;
    int dist;
    Vertex *previous;
};

struct WVLinkedList {
    WorkVertex workVertex;
    WVLinkedList *next;
};

void PreComputePaths(Graph *graph, SourcePaths **paths, unsigned int mode);
void Dijkstra(WVLinkedList *workingGraph, WorkVertex *source, int mode);
void GetWorkingGraph(Graph *graph, WVLinkedList *head);
void GetAllExits(Graph *graph, WVLinkedList *workingGraph, WorkVertex **exits, unsigned int *count);
void SetPathsFromWGraph(WVLinkedList *workingGraph, WorkVertex **exits, SourcePaths *paths);