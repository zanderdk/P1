#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Vertex *GetVertexFromId(char *idStr, Graph *graph) {
    Floor *floors = graph->floors;
    int floor = 0;
    int unsigned id = 0;
    char floorStr[4];
    memset(floorStr, 0, 4);
    sscanf(idStr, "%u", &id);

    idStr++;

    strncpy(floorStr, idStr, 3);
    sscanf(floorStr, "%d", &floor);
    floor--;

    return NextVertex(floors[floor].vp, id);
}

Vertex *GetVertexFromIdInt(int id, Graph *graph) {
    char str[10];
    memset(str, 0, 10);
    sprintf(str, "%d", id);
    return GetVertexFromId(str, graph);
}

int GetFloor(int vertedId) {
    int floor;
    char str[11]; //int max char size + \0.
    char floorStr[4]; //max floor id size + \0.
    memset(str, 0, 11);
    sprintf(str, "%d", vertedId);

    strncpy(floorStr, &str[1], 3);
    floorStr[3] = 0;
    sscanf(floorStr, "%d", &floor);
    return floor;
}

Vertex *NextVertex(Vertex *vp, int id) {
    if (vp->vertexId == id)
        return vp;
    else if (vp->nextVp != NULL)
        return NextVertex(vp->nextVp, id);

    return NULL;
}

int CountVertices(int floorId, Graph *graph) {
    Floor *floors = graph->floors;
    int count = 0;
    Vertex *vp = floors[floorId - 1].vp;
    do {
        count++;
        vp = vp->nextVp;
    } while (vp != NULL);
    return count;
}