typedef struct WorkVertex WorkVertex;
typedef struct WVLinkedList WVLinkedList;

struct WorkVertex {
    Vertex *vertex;
    unsigned int dist;
    int visited;
    WorkVertex *previous;
};

struct WVLinkedList {
    WorkVertex workVertex;
    WVLinkedList *next;
};

void Dijkstra(WVLinkedList *workingGraph, WorkVertex *source, int mode);
void GetWorkingGraph(Graph *graph, WVLinkedList *head);
void GetAllExits(Graph *graph, WVLinkedList *workingGraph, WorkVertex **exits, unsigned int *count);
void SetPathsFromWGraph(WVLinkedList *workingGraph, WorkVertex **exits, int index, int count, SourcePaths *sourcePaths);
void BacktrackPath(WorkVertex *source, WorkVertex *goal, Path *path);
void ReversePath(Path *from, Path *to);
void SetNeighborWeights(WorkVertex *current, WVLinkedList **workingGraph, int mode);
WVLinkedList *WVLLLookup(WVLinkedList *workingGraph, Vertex *target, WVLinkedList ***previous);
void WVLLDelete(WVLinkedList **target, WVLinkedList **previous);
WVLinkedList *WVLLSearch(WVLinkedList *workingGraph);