#include "graph.h"

Graph *readXml(FILE *fp);
int readAtribute(char *name, FILE *fp);
void readDefaultAtributes(int *edges, int *vertices, int *floors, FILE *fp);
void error();
int reachChar(char t, FILE *fp);
void nextElement(char *name, FILE *fp);
int readToChar(char *name, char t, FILE *fp);
void readEdges(FILE *fp, Edge *edges, int numberOfEdges);
void readvertices(FILE *fp, Vertex *vertices, int numberOfvertices, Edge *ep, int numberOfEdges);
int nextElementValue(char *name, FILE *fp);
void assignEdge(EdgePointer **ep, EdgePointer *setEp, Edge *edge);
void crawlEdges(Edge **edges, Vertex *vertices, int numberOfEdges, int numberOfvertices);
void crawVertices(Vertex **vertices, int last, Floor **floor);
void getFloorAndtype(int id, int *floor, int *type);
void crawlFloors(Floor **floors, Vertex *vertices, int numberOfFloors, int numberOfvertices);
Edge readEdge(FILE *fp);
Vertex readVertex(FILE *fp, Edge *ep, int numberOfEdges, EdgePointer *EdgePointerStart);
Edge *getEp(Edge *ep, unsigned int id, int numberOfEdges);
