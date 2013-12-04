#include "astar.h"
#include "graph.h"

double DistanceVertices(Vertex *v1, Vertex *v2) {
    int x1 = v1->x;
    int y1 = v1->y;
    int x2 = v2->x;
    int y2 = v2->y;

    return sqrt(pow(  (x1 - x2), 2) + pow( (y1 - y2), 2));
}