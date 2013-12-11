typedef struct WorkVertex WorkVertex;
typedef struct WVLinkedList WVLinkedList;

struct WorkVertex {
    Vertex *vertex;
    unsigned int dist;
    int visited;
    Vertex *previous;
};

struct WVLinkedList {
    WorkVertex workVertex;
    WVLinkedList *next;
};

void Dijkstra(WVLinkedList *workingGraph, WorkVertex *source, int mode);
void GetWorkingGraph(Graph *graph, WVLinkedList *head);
void GetAllExits(Graph *graph, WVLinkedList *workingGraph, WorkVertex **exits, unsigned int *count);
void SetPathsFromWGraph(WVLinkedList *workingGraph, WorkVertex **exits, SourcePaths *paths);
void SetNeighborWeights(WorkVertex *current, WVLinkedList *workingGraph);
WorkVertex *WVLLLookup(WVLinkedList *workingGraph, Vertex *target);