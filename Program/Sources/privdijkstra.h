typedef struct WorkVertex WorkVertex;
typedef struct WVLinkedList WVLinkedList;

struct WorkVertex {
    Vertex *vertex;
    unsigned int dist;
    WorkVertex *previous;
};

struct WVLinkedList {
    WorkVertex workVertex;
    WVLinkedList *next;
};

void Dijkstra(WVLinkedList *workingGraph, WorkVertex *source, int mode);
void GetWorkingGraph(Graph *graph, WVLinkedList *head);
void GetAllExits(WVLinkedList *workingGraph, WorkVertex **exits);
void SetPathsFromWGraph(WorkVertex **exits, int index, int count, SourcePaths *sourcePaths);
void BacktrackPath(WorkVertex *source, WorkVertex *goal, Path *path);
void ReversePath(Path *from, Path *to);
void SetNeighborWeights(WorkVertex *current, WVLinkedList *workingGraph, int mode);
WVLinkedList **WVLLLookup(WVLinkedList **workingGraph, Vertex *target);
WVLinkedList *WVLLGetLowest(WVLinkedList *workingGraph);
void WVLLDelete(WVLinkedList **targetPtr);