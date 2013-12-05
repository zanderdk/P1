typedef struct Coordinate {
    int x;
    int y;
    int flr;
} Coordinate;

typedef struct Vertex {
    Coordinate location;
    char type;
    unsigned int id;
    unsigned int weight;
    struct Vertex *next;
} Vertex;

typedef struct AdjList {
    Vertex *head;
} AdjList;

typedef struct Graph {
    unsigned int numOfVertices;
    AdjList *array;
} Graph;

Vertex *addVertex(int id); //
void addEdge(Graph *graph, int source, int destination, int weight); // Adds an edge to an undirected graph
Graph *createGraph(int numOfVertices);
void printAdjList(Graph *graph);
void giveCoords(Graph *graph, Coordinate *coords);