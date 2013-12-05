#include "astar.h"
#include <math.h>
#include <stdlib.h>
#include <floats.h>

#define NO_SET 0
#define CLOSED_SET 1
#define OPEN_SET 2

void SetGValue(unsigned int value, WorkVertex *wv) {
    wv->g = value;
}

unsigned int GetGValue(WorkVertex *wv) {
    return wv->g;
}

double CalcHValue(Vertex *src, Vertex *goal) {
    int x1 = src->x;
    int y1 = src->y;
    int x2 = goal->x;
    int y2 = goal->y;
    return sqrt(pow(  (x1 - x2), 2) + pow( (y1 - y2), 2));
}

double SetHValue(double value, WorkVertex *wv) {
    wv->h = value;
}

double GetHValue(WorkVertex *wv) {
    return wv->h;
}

double CalcFValue(Vertex *src, Vertex *goal) {
    unsigned int g = wv->g;
    double h = CalcHValue(src, goal);
    return g + h;
}

void SetFValue(double f, WorkVertex *wv) {
    wv->f = f;
}

double GetFValue(WorkVertex *wv) {
    return wv->h;
}

void SetParentVertex(WorkVertex *child, WorkVertex *parent) {
    child->parentVertex->parent;
}

int AddToList(WorkVertex **list, int listSize, WorkVertex *wv) {
    int i;

    for (i = 0; i < listSize; i++) {
        /* If an entry in list is 0, nothing at that position has been set
         Therefore, set it */
        if (list[i] == 0) {
            list[i] = wv;
            return 1;
        }
    }
    return 0;
}

int RemoveFromList(WorkVertex **list, int listSize, WorkVertex *wv) {
    int i;
    unsigned int currentId;
    unsigned int targetId = wv->originVertex->vertexId;

    for (i = 0; i < listSize; i++) {
        currentId = list[i]->originVertex->vertexId;
        if (currentId == targetId) {
            list[i] = 0;
            return 1;
        }
    }
    return 0;
}

int InList(WorkVertex **list, int listSize, WorkVertex *wv) {
    int i;
    unsigned int currentId;
    unsigned int targetId = wv->originVertex->vertexId;

    for (i = 0; i < listSize; i++) {
        currentId = list[i]->originVertex->vertexId;
        if (currentId == targetId) {
            return 1;
        }
    }
    return 0;
}

double aStar(Vertex *Start, Vertex *dest) {
    int i;
    WorkVertex *wvStart;
    WorkVertex *current;
    unsigned int floorId = star->floorId;
    int numVertices = getNumVerticesOnFloor(floorId);

    WorkVertex **workVertices = (WorkVertex **) calloc(numVertices,
                                sizeof(WorkVertex *));

    /* create WorkVertex instance of start vertex and set to open list */
    wvStart = createWorkVertex(start);
    setSetMode(OPEN_SET, wvStart);

    /* calculate and set f value for start to destination vertex */
    SetFValue(CalcFValue(src, dest), wvStart);

    while (getVerticesInSet(2, workVertices, numVertices) != 0) {
        current = getVertexLowestFOpenSet(workVertices, numVertices);
        if (current->originVertex->vertexId == dest->vertexId) {
            reconstruct_path();
        }

        current->setMode = CLOSED_SET;

        for (i = 0; i < getNeighbors(current, workVertices, numVertices); i++) {
            printf("%d", i);
        }
    }
}

void addToWorkVertices(WorkVertex *wv, WorkVertex **workVertices, int numVertices) {
    int i;

    for (i = 0; i < numVertices; i++) {
        /* If an entry in array is 0, nothing at that position has been set
         Therefore, set it */
        if (workVertices[i] == 0) {
            workVertices[i] = wv;
        }
    }
}

int getNeighbors(WorkVertex *wv, WorkVertex **workVertices, int numVertices) {
    int numNeighbors = 0;
    WorkVertex *wv;
    Vertex *origin = wv->originVertex;
    int srcId = origin->vertexId;
    int srcFloor = origin->floorId;


    EdgePointer *ep = origin->ep;

    do {
        Edge *e = ep->edge;
        /* if vertexId is not same as srcId, create a workVertex based on that vertex
        if and only if srcVertex and vertex are on the same floor.
        This is because Astar should only work on 1 floor. */
        if (e->vertex1->vertexId != srcId && e->vertex1->floorId == srcFloor) {
            wv = createWorkVertex(vertex1);
            numNeighbors++;
        }
        /* if vertexId is not same as srcId, create a workVertex based on that vertex
                if and only if srcVertex and vertex are on the same floor.
                This is because Astar should only work on 1 floor. */
        else if (e->vertex2->vertexId != srcId && e->vertex2->floorId == srcFloor) {
            wv = createWorkVertex(vertex2);
            numNeighbors++;
        } else {
            printf("Could not create workvertex\n");
        }


        addToWorkVertices(wv, workVertices, numVertices);

        /* get next ep */
        ep = ep->nextEp;

    } while (ep != NULL);



    return numNeighbors;
}

WorkVertex *getVertexLowestFOpenSet(WorkVertex **workVertices, int numVertices) {
    int i;
    int indexLowestF;
    double curF;
    double lowestF = DBL_MAX;

    for (i = 0; i < numVertices; i++) {
        curF =  workVertices[i]->f;
        if (curF < lowestF) {
            lowestF = curF;
            indexLowestF = i;
        }
    }
    return workVertices[indexLowestF];
}

void setSetMode(int value, WorkVertex *wv) {
    wv->setSetMode = value;
}

int getVerticesInSet(int setMode, WorkVertex **workVertices, int numVertices) {
    int i;
    int numSet = 0;

    for (i = 0; i < numVertices; i++) {
        if (WorkVertices[i]->setMode == setMode) {
            numSet++;
        }
    }
    return numSet;
}

int isEmptyList(WorkVertex **list, int listSize) {
    int i;

    for (i = 0; i < listSize; i++) {
        if (list[i] != 0) {
            return 0;
        }
    }
    return 1;
}

WorkVertex *createWorkVertex(Vertex *src) {
    WorkVertex *wv;

    wv = (WorkVertex *) malloc(sizeof(WorkVertex));
    wv->originVertex = src;

    return wv;
}

WorkVertex *getConnWorkVertex(EdgePointer *ep, WorkVertex *wv) {
    Edge *e = ep->e;

    WorkVertex *wv1 = e->vertex1->
}

