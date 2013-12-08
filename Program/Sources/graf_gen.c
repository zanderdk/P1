#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


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

int main(void) {
    srand(time(NULL));

    int edgeCounter = 1;
    int numFloors;

    Graph *g = makeGraph(&edgeCounter, &numFloors);

    printXML(g, edgeCounter, numFloors);
}




int edgeIsPrinted(int *array, int id, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (array[i] == id) {
            return 1;
        }
    }
    return 0;
}

void addToEdgeIsPrinted(int **array, int id, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (*array[i] == id) {

        }
    }
}

void printXML(Graph *g, int edgeCounter, int numFloors) {
    int i;
    int j;
    FILE *xml = fopen("simon.xml", "w");
    Vertex *v;
    int size = NUM_VERTEX * MAX_EDGES_PER_VERTEX;
    int edgeIdsPrinted[size];
    int arrayCounter = 0;


    xmlOpenTag("edges", xml);
    for (i = 0; i < NUM_VERTEX; i++) {
        v = getVertex(g, i);
        for (j = 0; j < v->degree; j++) {

            Edge *e = v->edges[j];

            if (!edgeIsPrinted(edgeIdsPrinted, e->edgeId, size)) {
                xmlOpenTag("edge", xml);

                xmlOpenTag("edgeId", xml);
                xmlWriteInt("%d", e->edgeId, xml);
                xmlCloseTag("edgeId", xml);

                xmlOpenTag("weight", xml);
                xmlWriteInt("%d", e->weight, xml);
                xmlCloseTag("weight", xml);

                xmlOpenTag("vertexId1", xml);
                xmlWriteInt("%d", e->vertex1->vertexId, xml);
                xmlCloseTag("vertexId1", xml);

                xmlOpenTag("vertexId2", xml);
                xmlWriteInt("%d", e->vertex2->vertexId, xml);
                xmlCloseTag("vertexId2", xml);

                xmlCloseTag("edge", xml);
                edgeIdsPrinted[arrayCounter] = e->edgeId;
                arrayCounter++;
            }


        }
    }
    xmlCloseTag("edges", xml);

    xmlOpenTag("vertices", xml);



    for (i = 0; i < NUM_VERTEX; i++) {
        v = getVertex(g, i);
        xmlOpenTag("vertex", xml);

        xmlOpenTag("vertexId", xml);
        xmlWriteInt("%d", v->vertexId, xml);
        xmlCloseTag("vertexId", xml);

        xmlOpenTag("coord", xml);

        xmlOpenTag("x", xml);
        xmlWriteInt("%d", v->x, xml);
        xmlCloseTag("x", xml);

        xmlOpenTag("y", xml);
        xmlWriteInt("%d", v->y, xml);
        xmlCloseTag("y", xml);

        xmlCloseTag("coord", xml);


        xmlOpenTag("edges", xml);

        int *edgesconnected = (int *) calloc(MAX_EDGES_PER_VERTEX, sizeof(int));
        int sized = 0;

        edgesconnected = edgesConnected(g, v, edgesconnected, &sized);

        for (j = 0; j < size; j++) {

            if (edgesconnected[j] != 0) {
                xmlOpenTag("edgeId", xml);
                xmlWriteInt("%d", edgesconnected[j], xml);
                xmlCloseTag("edgeId", xml);
            }


        }

        xmlCloseTag("edges", xml);
        xmlCloseTag("vertex", xml);

    }


    xmlCloseTag("vertices", xml);
    xmlCloseTag("graph", xml);

    fclose(xml);

    xml = fopen("simon.xml", "r");

    FILE *real = fopen("realtest.xml", "w");

    char buffer[1024];
    sprintf(buffer, "<graph edges=\"%d\" vertices=\"%d\" floors=\"%d\">",
            arrayCounter, NUM_VERTEX, numFloors);
    fputs(buffer, real);

    while (fgets(buffer, 1024, xml) != NULL) {
        fputs(buffer, real);
    }


    fclose(real);

}

int containsInt(int *array, int size, int target) {
    int i;

    for (i = 0; i < size; i++) {
        if (array[i] == target) {
            return 1;
        }
    }
    return 0;
}

int *edgesConnected(Graph *g, Vertex *v, int *array, int *size) {
    int i, j, k;
    Vertex *v1;
    Edge *e;

    for (i = 0; i < NUM_VERTEX; i++) {
        v1 = getVertex(g, i);
        for (j = 0; j < v1->degree; j++) {
            e = v1->edges[j];
            if (e->vertex1->vertexId == v->vertexId || e->vertex2->vertexId == v->vertexId) {
                if (!containsInt(array, *size, e->edgeId)) {
                    array[j] = e->edgeId;
                    (*size)++;
                }

            }
        }
    }
    return array;
}

void xmlWriteInt(char *format, int var, FILE *xml) {
    char buffer[100];
    sprintf(buffer, format, var);
    fputs(buffer, xml);
}

void xmlCloseTag(char *name, FILE *xml) {
    char buffer[100];
    sprintf(buffer, "</%s>", name);
    fputs(buffer, xml);
}

void xmlOpenTag(char *name, FILE *xml) {
    char buffer[100];
    sprintf(buffer, "<%s>", name);
    fputs(buffer, xml);
}

Graph *makeGraph(int *edgeCounter, int *numFloors) {

    int i;
    int j;
    Vertex *v;
    Edge *e;
    int numVerticesFloor;
    int verticesRemaining = NUM_VERTEX;
    int verticesCreated = 0;
    int numVertices;


    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->vertices = (Vertex **) calloc(NUM_VERTEX, sizeof(Vertex *));

    *numFloors = rand() % MAX_FLOORS + 1;
    numVerticesFloor = floor(  NUM_VERTEX / *numFloors);

    for (i = 1; i < *numFloors + 1; i++) {
        numVertices = verticesRemaining - numVerticesFloor < 0 ? verticesRemaining :
                      numVerticesFloor;

        makeFloor(g, i, numVertices, &verticesCreated, edgeCounter);
        verticesRemaining -= numVerticesFloor;
    }

    setConnectingVertexInEdges(g);


    return g;
}

void makeFloor(Graph *g, int floorId, int numVertices, int *verticesCreated,
               int *edgeCounter) {
    int i;
    Vertex *v;

    for (i = 0; i < numVertices; i++) {
        v = createRandomVertex(g, floorId, i + 1, edgeCounter);

        addVertexToGraph(g, v, *verticesCreated);
        (*verticesCreated)++;
    }

}

void setConnectingVertexInEdges(Graph *g) {
    int j;
    int i;
    int random;
    Vertex *v;
    Edge *e;

    for (i = 0; i < NUM_VERTEX; i++) {

        v = getVertex(g, i);

        for (j = 0; j < v->degree; j++) {
            /* add vertex2 vertex to edges */

            e = v->edges[j];

            /* continue to getVertex until a vertex has been generated
               that is unique to v */
            do {
                random = rand() % NUM_VERTEX;

                e->vertex1 = v;
                e->vertex2 = getVertex(g, random);
            } while (e->vertex2->vertexId == v->vertexId);

            edgeWithSameVerticesAlreadyCreated(&(v->edges[j]), g, e->vertex1, e->vertex2);


        }
    }
}

int edgeWithSameVerticesAlreadyCreated(Edge **eSrc, Graph *g, Vertex *v1,
                                       Vertex *v2) {
    int j;
    int i;
    Vertex *v;
    Edge *e;
    int targetVertex1;
    int targetVertex2;



    int v1Id = v1->vertexId;
    int v2Id = v2->vertexId;

    for (i = 0; i < NUM_VERTEX; i++) {

        v = getVertex(g, i);

        for (j = 0; j < v->degree; j++) {
            /* add vertex2 vertex to edges */

            e = v->edges[j];

            if (e->vertex1 != NULL && e->vertex2 != NULL ) {
                targetVertex1 = e->vertex1->vertexId;
                targetVertex2 = e->vertex2->vertexId;
            } else {
                break;
            }



            if ((targetVertex1 == v1Id && targetVertex2 == v2Id) || (targetVertex1 == v2Id
                    && targetVertex2 == v1Id)) {
                *eSrc =  v->edges[j];
                return 1;
            }
        }
    }
    return 0;
}

Edge *edgeIsCreated(Graph *g, int edgeCounter) {
    int i;
    int j;
    int targetId = genId(4, 0, edgeCounter);
    Vertex *v;
    Edge *e;
    for (i = 0; i < NUM_VERTEX; i++) {
        v = getVertex(g, i);
        if (v != NULL) {
            for (j = 0; j < v->degree; j++) {
                e = v->edges[j];
                if (e != 0 && e->edgeId == targetId) {
                    return e;
                }
            }
        }
    }
    return 0;
}

Vertex *createRandomVertex(Graph *g, int floorId, int vertexNumFloor,
                           int *edgeCounter) {
    int i;
    int type;
    Vertex *v = (Vertex *) malloc(sizeof(Vertex));

    /* randomly select number of edges */
    int numEdges = rand() % MAX_EDGES_PER_VERTEX + 1;

    /* set degree */
    v->degree = numEdges;

    v->edges = (Edge **) malloc(sizeof(Edge *) * numEdges);

    /* create edges */
    for (i = 0; i < numEdges; i++) {
        Edge *e;
        //e = edgeIsCreated(g, *edgeCounter);
        e = 0;

        if (e == 0) {
            e = createWeightedEdge(g, edgeCounter);
            addEdgeToVertex(v, e, i);
        } else {
            addEdgeToVertex(v, e, i);
        }
    }

    /* set x */
    int x = rand() % MAX_X + 1;
    v->x = x;

    /* set y */
    int y = rand() % MAX_Y + 1;
    v->y = y;

    double random = ((double) rand() / RAND_MAX) * 100;

    int smallest = VERTEX_STAIR_RATIO < VERTEX_ELEVATOR_RATIO ? VERTEX_STAIR_RATIO :
                   VERTEX_ELEVATOR_RATIO;
    int biggest = VERTEX_STAIR_RATIO > VERTEX_ELEVATOR_RATIO ? VERTEX_STAIR_RATIO :
                  VERTEX_ELEVATOR_RATIO;

    /* decide wether the type of the vertex is a stair, elevator or a vertex */
    if (random < smallest) {
        type = 3; /* stairs */
    } else if (random < biggest + smallest) {
        type = 2; /* elevator */
    } else {
        type = 1; /* normal */
    }

    v->vertexId = genId(type, floorId, vertexNumFloor);

    return v;
}

unsigned int genId(int type, int floorId, int vertexNumFloor) {
    char buffer[48];

    snprintf(buffer, 48, "%d%.3d%d", type, floorId, vertexNumFloor);

    return atoi(buffer);
}

void addVertexToGraph(Graph *g, Vertex *v, int i) {
    g->vertices[i] = v;
}

Edge *createWeightedEdge(Graph *g, int *edgeCounter) {
    Edge *e = (Edge *) calloc(1, sizeof(Edge));

    int weight = rand() % MAX_WEIGHT + 1;
    e->weight = weight;

    e->edgeId = genId(4, 0, *edgeCounter);
    (*edgeCounter)++;

    return e;
}

void addEdgeToVertex(Vertex *v, Edge *e, int i) {
    v->edges[i] = e;
}

Vertex *getVertex(const Graph *g, int index) {
    return g->vertices[index];
}

int getWeight(Vertex *v1, Vertex *v2) {
    int i;
    int degree = v1->degree;
    for (i = 0; i < degree; i++) {
        Edge *e = v1->edges[i];
        if (e->vertex2->vertexId == v2->vertexId) {
            return e->weight;
        }
    }

    return 0;
}
