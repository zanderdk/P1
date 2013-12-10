#define NUM_VERTEX 100
#define MAX_WEIGHT 5
#define MAX_EDGES_PER_VERTEX 2
#define MAX_X 10
#define MAX_Y 10
#define MAX_FLOORS 1
#define VERTEX_STAIR_RATIO 7 /* how many percent should be stairs */
#define VERTEX_ELEVATOR_RATIO 5 /* how many percent should be elevators */

typedef struct Vertex Vertex;
typedef struct Edge Edge;
typedef struct Graph Graph;

struct Edge {
    unsigned int weight;
    unsigned int edgeId;
    Vertex *vertex1;
    Vertex *vertex2;
};

struct Vertex {
    unsigned int vertexId;
    unsigned int x;
    unsigned int y;
    unsigned int type;
    unsigned int degree; /* number of degrees */
    Edge **edges;
};

struct Graph {
    Vertex **vertices;
};


Graph *makeGraph(int *edgeCounter, int *numFloors);
Vertex *createRandomVertex(Graph *g, int floorId, int vertexNumFloor,
                           int *edgeCounter);
void addVertexToGraph(Graph *g, Vertex *v, int i);
Edge *createWeightedEdge(Graph *g, int *edgeCounter);
void addEdgeToVertex(Vertex *v, Edge *e, int i);
Vertex *getVertex(const Graph *g, int index);
void setConnectingVertexInEdges(Graph *g);
void printXML(Graph *g, int edgeCounter, int numFloors);
void xmlOpenTag(char *name, FILE *xml);
void xmlCloseTag(char *name, FILE *xml);
void xmlWriteInt(char *format, int var, FILE *xml);
void printForLatex(Graph *G);
void printVertices(FILE *f, Graph *g);
void printEdges(FILE *f, Graph *g);
void printMXML(Graph *g);
unsigned int genId(int type, int floorId, int vertexNumFloor);
void makeFloor(Graph *g, int floorId, int numVertices, int *verticesCreated,
               int *edgeCounter);
void makeIdsNotSuck(Graph *g, Edge **src);
int edgeWithSameVerticesAlreadyCreated(Edge **eSrc, Graph *g, Vertex *v1,
                                       Vertex *v2);
int *edgesConnected(Graph *g, Vertex *v, int *array, int *size);
int Contains(int *array, int id, int size);