typedef struct WorkVertex WorkVertex;
typedef struct WVLinkedList WVLinkedList;

struct WorkVertex {
    Vertex *vertex;
    int dist;
    Vertex *previous;
};

struct WVLinkedList {
    WorkVertex *element
};

void GetAllExits(Graph *graph, Vertex *exits);
