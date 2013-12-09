typedef struct WorkVertex WorkVertex;
typedef struct WVLinkedList WVLinkedList;

struct WorkVertex {
    Vertex *vertex;
    int dist;
    Vertex *previous;
};

struct WVLinkedList {
    WorkVertex *element;
    WVLinkedList *next;
};

void Dijkstra(WVLinkedList *workingGraph, WorkVertex *source);
void GetWorkingGraph(Graph *graph, WVLinkedList *head);
void GetAllExits(Graph *graph, Vertex *exits);
