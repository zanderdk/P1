#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define NUM_VERTEX 5
#define MAX_WEIGHT 5
#define MAX_EDGES_PER_VERTEX 2
#define MAX_X 10
#define MAX_Y 10
#define NUM_FLOORS 1
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
    unsigned int degree; /* number of degrees */
    Edge **edges;
};

struct Graph {
    Vertex **vertices;
};

Graph makeGraph();
void createFloors(Graph *g);
void createFloor(Graph *g, int floorId);
void createVertices(Graph *g, int floorId, int *verticesCreatedOnFloor);
Vertex *createVertex(Graph *g, int floorId, int *verticesCreatedOnFloor);
unsigned int genId(int type, int floorId, int vertexNumFloor);
Edge **createEdges(Graph *g);
Edge *createEdge(Graph *g, Vertex *v);
Edge *createUniqueEdge(Edge **src, Graph *g);
int containsEdge(Edge **array, int size, Edge *target);
void addToArray(Edge **array, int size, Edge *toAdd);
void assignEdges(Graph *g);
Edge *createUniqueEdgeOrUseExisting(Graph *g, Vertex *v1);
void printXML(Graph *g, int numFloors);
int vertexHasEdgeConnected(Vertex *v, Edge *e);

int main(void) {
    srand(time(NULL));

    Graph g = makeGraph();

    printXML(&g, 2);
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

void printXML(Graph *g, int numFloors) {
    int i;
    int j;
    FILE *xml = fopen("simon.xml", "w");
    Vertex *v;
    int size = NUM_VERTEX * MAX_EDGES_PER_VERTEX;
    int edgeIdsPrinted[size];
    int arrayCounter = 0;


    xmlOpenTag("edges", xml);
    for (i = 0; i < NUM_VERTEX; i++) {
        v = g->vertices[i];
        for (j = 0; j < v->degree; j++) {

            Edge *e = v->edges[j];

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

            /*if (!edgeIsPrinted(edgeIdsPrinted, e->edgeId, size)) {
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
            }*/


        }
    }
    xmlCloseTag("edges", xml);

    xmlOpenTag("vertices", xml);



    for (i = 0; i < NUM_VERTEX; i++) {
        v = g->vertices[i];
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

        //edgesconnected = edgesConnected(g, v, edgesconnected, &sized);

        for (j = 0; j < v->degree; j++) {


            xmlOpenTag("edgeId", xml);
            xmlWriteInt("%d", v->edges[j]->edgeId, xml);
            xmlCloseTag("edgeId", xml);



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

void checkForNeighbors(Graph *g, Vertex **vp) {
    int i, j;
    for (i = 0; i < NUM_VERTEX; i++) {
        Vertex *v = g->vertices[i];
        for (j = 0; j < v->degree; j++) {

        }
    }
}

void crawlVertices(Graph *g) {
    int i;
    for (i = 0; i < NUM_VERTEX; i++) {

    }
}

Graph makeGraph() {

    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->vertices = (Vertex **) calloc(NUM_VERTEX, sizeof(Vertex));

    createFloors(g);
    //Edge **edges = createEdges(g);

    assignEdges(g);

    crawlVertices(g);

    //connectVerticesAndEdges(g, edges);

    return *g;

}

void assignEdges(Graph *g) {
    int i, j;
    Vertex *v;

    for (i = 0; i < NUM_VERTEX; i++) {
        v = g->vertices[i];
        printf("vertex id %d\n", v->vertexId);
        for (j = 0; j < v->degree; j++) {

            do {
                v->edges[j] = createUniqueEdgeOrUseExisting(g, v);
            } while (!vertexHasEdgeConnected(v, v->edges[j]));
            printf("edge id %d\n", v->edges[j]->edgeId);
        }
        printf("\n");
    }

}

int vertexHasEdgeConnected(Vertex *v, Edge *e) {
    int i;
    for (i = 0; i < v->degree; i++) {
        if (v->edges[i] != NULL && e != NULL && v->edges[i]->edgeId == e->edgeId) {
            printf("edgeid %d already connected\n", e->edgeId);
            return 1;
        }
    }
    return 0;
}

void connectVerticesAndEdges(Graph *g, Edge **edges) {
    int i, j;
    Vertex *v;

    for (i = 0; i < NUM_VERTEX; i++) {
        v = g->vertices[i];
        for (j = 0; j < v->degree; j++) {

        }
    }
}

void createFloors(Graph *g) {
    int i;
    for (i = 1; i <= NUM_FLOORS; i++) {
        createFloor(g, i);
    }
}

void createFloor(Graph *g, int floorId) {
    int verticesCreatedOnFloor = 1;
    createVertices(g, floorId, &verticesCreatedOnFloor);

}

void createVertices(Graph *g, int floorId, int *verticesCreatedOnFloor) {
    int i, j;

    for (i = 0; i < NUM_VERTEX; i++) {
        g->vertices[i] = createVertex(g, floorId, verticesCreatedOnFloor);
    }
}

Edge *createUniqueEdgeOrUseExisting(Graph *g, Vertex *v1) {
    static Edge *edgesCreated[NUM_VERTEX * MAX_EDGES_PER_VERTEX];
    static int edgeCounter = 1;
    int i, j, random, pos;

    Edge *e = (Edge *) malloc(sizeof(Edge));

    e->edgeId = genId(4, 0, edgeCounter);
    edgeCounter++;

    e->weight = rand() % MAX_WEIGHT + 1;

    e->vertex1 = v1;

    do {
        random = rand() % NUM_VERTEX;
        e->vertex2 = g->vertices[random];
    } while (e->vertex2->vertexId == v1->vertexId);

    pos = containsEdge(edgesCreated, NUM_VERTEX * MAX_EDGES_PER_VERTEX,
                       e);
    if (pos != -1) {
        return edgesCreated[pos];
    } else {
        addToArray(edgesCreated, NUM_VERTEX * MAX_EDGES_PER_VERTEX, e);
    }

    return e;


}

void addToArray(Edge **array, int size, Edge *toAdd) {
    int i;

    for (i = 0; i < size; i++) {
        if (array[i] == 0) {
            array[i] = toAdd;
            break;
        }
    }
}

int containsEdge(Edge **array, int size, Edge *target) {
    int i;

    int targetId1 = target->vertex1->vertexId;
    int targetId2 = target->vertex2->vertexId;

    for (i = 0; i < size; i++) {

        if (array[i] != NULL && (
                    (array[i]->vertex1->vertexId == targetId1
                     && array[i]->vertex2->vertexId == targetId2)
                    ||
                    (array[i]->vertex2->vertexId == targetId1
                     && array[i]->vertex1->vertexId == targetId2))) {
            return i;
        }
    }
    return -1;
}

Vertex *createVertex(Graph *g, int floorId, int *verticesCreatedOnFloor) {
    int type;
    int i;
    Vertex *v = (Vertex *) malloc(sizeof(Vertex));

    /* set x */
    int x = rand() % MAX_X + 1;
    v->x = x;

    /* set y */
    int y = rand() % MAX_Y + 1;
    v->y = y;

    /* randomly select number of edges */
    v->degree = rand() % MAX_EDGES_PER_VERTEX + 1;

    v->edges = (Edge **) calloc(v->degree, sizeof(Edge *));





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

    v->vertexId = genId(type, floorId, *verticesCreatedOnFloor);
    (*verticesCreatedOnFloor)++;

    return v;
}

unsigned int genId(int type, int floorId, int vertexNumFloor) {
    char buffer[48];

    snprintf(buffer, 48, "%d%.3d%d", type, floorId, vertexNumFloor);

    return atoi(buffer);
}

Edge **createEdges(Graph *g) {
    int i, j;
    Edge **edges = (Edge **) calloc(NUM_VERTEX * MAX_EDGES_PER_VERTEX, sizeof(Edge *));
    Vertex *v;

    for (i = 0; i < NUM_VERTEX; i++) {
        v = g->vertices[i];
        for (j = 0; j < v->degree; j++) {
            edges[i + j] = createEdge(g, v);
        }

    }

    return edges;
}

Edge *createEdge(Graph *g, Vertex *v) {
    static int edgeCounter = 0;
    int random;

    Edge *e = (Edge *) malloc(sizeof(Edge));


    e->weight = rand() % MAX_WEIGHT + 1;

    e->edgeId = genId(4, 0, edgeCounter);
    edgeCounter++;

    do {
        random = rand() % NUM_VERTEX;

        e->vertex1 = v;
        e->vertex2 = g->vertices[random];
    } while (e->vertex2->vertexId == v->vertexId);

    e = createUniqueEdge(&e, g);

    return e;
}

Edge *createUniqueEdge(Edge **src, Graph *g) {
    int j;
    int i;
    Vertex *v;
    Edge *e;
    int targetVertex1Id;
    int targetVertex2Id;


    int v1Id = (*src)->vertex1->vertexId;
    int v2Id = (*src)->vertex2->vertexId;

    for (i = 0; i < NUM_VERTEX; i++) {

        v = g->vertices[i];

        for (j = 0; j < v->degree; j++) {
            /* add vertex2 vertex to edges */

            e = v->edges[j];

            if (e->vertex1 != NULL && e->vertex2 != NULL ) {
                targetVertex1Id = e->vertex1->vertexId;
                targetVertex2Id = e->vertex2->vertexId;
            } else {
                break;
            }

            if ((targetVertex1Id == v1Id && targetVertex2Id == v2Id) || (targetVertex1Id == v2Id
                    && targetVertex2Id == v1Id)) {
                *src =  v->edges[j];
                return *src;
            }
        }
    }
    return *src;
}