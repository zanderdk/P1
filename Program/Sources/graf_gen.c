#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


#define NUM_VERTEX 3
#define MAX_WEIGHT 5
#define MAX_EDGES_PER_VERTEX 2
#define MAX_X 10
#define MAX_Y 10
#define MAX_FLOORS 2
#define VERTEX_STAIR_RATIO 20 /* f.x 20 means every 20th vertex is a stair */
#define VERTEX_ELEVATOR_RATIO 40 /* f.x 20 means every 20th vertex is an elevator */

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


Graph *makeGraph(void);
Vertex *createRandomVertex(Graph *g, int floorId, int vertexNumFloor);
void addVertexToGraph(Graph *g, Vertex *v, int i);
Edge *createWeightedEdge(Graph *g);
void addEdgeToVertex(Vertex *v, Edge *e, int i);
Vertex *getVertex(const Graph *g, int index);
void setConnectingVertexInEdges(Graph *g);
void printXML(Graph *g);
void xmlOpenTag(char *name, FILE *xml);
void xmlCloseTag(char *name, FILE *xml);
void xmlWriteInt(char *format, int var, FILE *xml);
void printForLatex(Graph *G);
void printVertices(FILE *f, Graph *g);
void printEdges(FILE *f, Graph *g);
void printMXML(Graph *g);
unsigned int genId(int type, int floorId, int vertexNumFloor);
void makeFloor(Graph *g, int floorId, int numVertices, int *verticesCreated);

int main(void) {
    srand(time(NULL));
    Graph *g = makeGraph();

    //printMXML(g);
    printXML(g);
    //printForLatex(g);
    //printGraph(g);
}

/*void printMXML(Graph *g) {


    mxml_node_t *xml;
    mxml_node_t *graph;
    mxml_node_t *vertex;
    mxml_node_t *xml_x;
    mxml_node_t *xml_y;
    mxml_node_t *xml_vertexId;
    mxml_node_t *xml_floor;
    mxml_node_t *xml_degree;
    mxml_node_t *xml_edges;
    mxml_node_t *xml_edge;
    mxml_node_t *xml_weight;
    mxml_node_t *xml_cv1id;
    mxml_node_t *xml_cv2id;

    xml = mxmlNewXML("1.0");
    graph = mxmlNewElement(xml, "graph");

    int i;
    int j;

    for (i = 0; i < NUM_VERTEX; i++) {
        Vertex *v = getVertex(g, i);
        int x = v->x;
        int y = v->y;
        int vertexId = v->vertexId;
        vertex = mxmlNewElement(graph, "vertex");
        xml_x = mxmlNewElement(vertex, "x");
        mxmlNewInteger(xml_x, x);

        xml_y = mxmlNewElement(vertex, "y");
        mxmlNewInteger(xml_y, y);

        xml_vertexId = mxmlNewElement(vertex, "vertexId");
        mxmlNewInteger(xml_vertexId, vertexId);

        xml_floor = mxmlNewElement(vertex, "floorId");
        mxmlNewInteger(xml_floor, v->floorId);

        xml_degree = mxmlNewElement(vertex, "degree");
        mxmlNewInteger(xml_degree, v->degree);

        xml_edges = mxmlNewElement(vertex, "edges");


        for (j = 0; j < v->degree; j++) {
            Edge *e = v->edges[j];

            xml_edge = mxmlNewElement(xml_edges, "edge");

            xml_weight = mxmlNewElement(xml_edge, "weight");
            mxmlNewInteger(xml_weight, e->weight);


            xml_cv1id = mxmlNewElement(xml_edge, "vertex1ID");
            mxmlNewInteger(xml_cv1id, e->vertex1->vertexId);

            xml_cv2id = mxmlNewElement(xml_edge, "vertex2ID");
            mxmlNewInteger(xml_cv2id, e->vertex2->vertexId);
        }



    }

    FILE *fp = fopen("graph.xml", "w");
    mxmlSaveFile(xml, fp, MXML_NO_CALLBACK);

    fclose(fp);
}*/


void printForLatex(Graph *g) {
    FILE *latex = fopen("graph.txt", "w");

    printVertices(latex, g);
    printEdges(latex, g);

    fclose(latex);
}

void printVertices(FILE *f, Graph *g) {
    char buffer[100];


    int i;

    for (i = 0; i < NUM_VERTEX; i++) {
        Vertex *v = getVertex(g, i);
        int x = v->x;
        int y = v->y;
        int vertexId = v->vertexId;
        sprintf(buffer, "\\Vertex[d=10,x=%d ,y=%d]{%d}\n", x, y, vertexId);
        fputs(buffer, f);
    }
}

void printEdges(FILE *f, Graph *g) {
    char buffer[100];


    int i;
    int j;

    for (i = 0; i < NUM_VERTEX; i++) {
        Vertex *v = getVertex(g, i);

        for (j = 0; j < v->degree; j++) {
            Edge *e = v->edges[j];
            int label = e->weight;
            int vertex1Id = e->vertex1->vertexId;
            int vertex2Id = e->vertex2->vertexId;
            sprintf(buffer, "\\Edge[label = $%d$](%d)(%d)\n", label, vertex1Id, vertex2Id);
            fputs(buffer, f);
        }
    }
}

void printXML(Graph *g) {
    int i;
    int j;
    FILE *xml = fopen("simon.xml", "w");
    Vertex *v;

    xmlOpenTag("graph", xml);

    xmlOpenTag("edges", xml);
    for (i = 0; i < NUM_VERTEX; i++) {
        v = getVertex(g, i);
        for (j = 0; j < v->degree; j++) {
            Edge *e = v->edges[j];
            xmlOpenTag("edge", xml);

            xmlOpenTag("edgeId", xml);
            xmlWriteInt("%d", e->edgeId, xml);
            xmlCloseTag("edgeId", xml);

            xmlOpenTag("weight", xml);
            xmlWriteInt("%d", e->weight, xml);
            xmlCloseTag("weight", xml);

            xmlOpenTag("vertex1ID", xml);
            xmlWriteInt("%d", e->vertex1->vertexId, xml);
            xmlCloseTag("vertex1ID", xml);

            xmlOpenTag("vertex2ID", xml);
            xmlWriteInt("%d", e->vertex2->vertexId, xml);
            xmlCloseTag("vertex2ID", xml);

            xmlCloseTag("edge", xml);
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

Graph *makeGraph(void) {
    int i;
    int numFloors;
    int numVerticesFloor;
    int verticesRemaining = NUM_VERTEX;
    int verticesCreated = 0;

    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->vertices = (Vertex **) malloc(sizeof(Vertex *) * NUM_VERTEX);

    numFloors = rand() % MAX_FLOORS + 1;
    numVerticesFloor = floor(  NUM_VERTEX / numFloors);

    for (i = 1; i < numFloors + 1; i++) {
        verticesRemaining -= numVerticesFloor;
        /* only use verticesremaining if it is smaller than numverticesfloor */
        makeFloor(g, i, (verticesRemaining < numVerticesFloor) == 1 ? verticesRemaining :
                  numVerticesFloor, &verticesCreated);
    }



    setConnectingVertexInEdges(g);

    return g;
}

void makeFloor(Graph *g, int floorId, int numVertices, int *verticesCreated) {
    int i;
    Vertex *v;

    for (i = 0; i < numVertices; ) {
        v = createRandomVertex(g, floorId, i + 1);

        addVertexToGraph(g, v, *verticesCreated);
        (*verticesCreated)++;
    }

}

void setConnectingVertexInEdges(Graph *g) {
    int j;
    int i;

    for (i = 0; i < NUM_VERTEX; i++) {

        Vertex *v = getVertex(g, i);

        for (j = 0; j < v->degree; j++) {
            /* add vertex2 vertex to edges */

            int random;
            Edge *e;
            e = v->edges[j];

            /* continue to getVertex until a vertex has been generated
               that is unique to v */
            do {
                random = rand() % NUM_VERTEX;

                e->vertex1 = v;
                e->vertex2 = getVertex(g, random);
            } while (e->vertex2->vertexId == v->vertexId);
        }
    }
}

Vertex *createRandomVertex(Graph *g, int floorId, int vertexNumFloor) {
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
        Edge *e = createWeightedEdge(g);
        addEdgeToVertex(v, e, i);
    }

    /* set x */
    int x = rand() % MAX_X + 1;
    v->x = x;

    /* set y */
    int y = rand() % MAX_Y + 1;
    v->y = y;

    int tempValue = rand() % VERTEX_STAIR_RATIO + VERTEX_ELEVATOR_RATIO;

    /* decide wether the type of the vertex is a stair, elevator or a vertex */
    if (tempValue == VERTEX_STAIR_RATIO - 1) {
        type = 3;
    } else if (tempValue == VERTEX_ELEVATOR_RATIO - 1) {
        type = 2;
    } else {
        type = 1;
    }

    v->vertexId = genId(type, floorId, vertexNumFloor);

    return v;
}

unsigned int genId(int type, int floorId, int vertexNumFloor) {
    char buffer[48];

    snprintf(buffer, 48, "%d%d%d", type, floorId, vertexNumFloor);

    return atoi(buffer);
}

void addVertexToGraph(Graph *g, Vertex *v, int i) {
    g->vertices[i] = v;
}

Edge *createWeightedEdge(Graph *g) {
    Edge *e = (Edge *) malloc(sizeof(Edge));

    int weight = rand() % MAX_WEIGHT + 1;
    e->weight = weight;

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
