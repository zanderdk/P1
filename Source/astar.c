#include "astar.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#define NO_SET 0
#define CLOSED_SET 1
#define OPEN_SET 2

void SetGValue(unsigned int value, WorkVertex *wv) {
    wv->g = value;
}

unsigned int GetGValue(WorkVertex *wv) {
    return wv->g;
}

double distBetween(Vertex *src, Vertex *goal) {
    int x1 = src->x;
    int y1 = src->y;
    int x2 = goal->x;
    int y2 = goal->y;
    return sqrt(pow(  (x1 - x2), 2) + pow( (y1 - y2), 2));
}

void SetHValue(double value, WorkVertex *wv) {
    wv->h = value;
}

double GetHValue(WorkVertex *wv) {
    return wv->h;
}

double CalcFValue(WorkVertex *src, Vertex *goal) {
    unsigned int g = src->g;
    double h = distBetween(src->originVertex, goal);
    return g + h;
}

void SetFValue(double f, WorkVertex *wv) {
    wv->f = f;
}

double GetFValue(WorkVertex *wv) {
    return wv->h;
}

void SetParentVertex(WorkVertex *child, WorkVertex *parent) {
    child->parentVertex = parent;
}

double aStar(Vertex *start, Vertex *dest) {
    int i;
    WorkVertex *wvStart;
    WorkVertex *current;
    WorkVertex **curNeighbors;
    WorkVertex *curNeighbor;
    WorkVertex **outNeighborWorkVertex;

    unsigned int tempG;
    double tempF;
    unsigned int verticesInPath = 0;

    unsigned int floorId = start->floorId;
    //int numVertices = getNumVerticesOnFloor(floorId);
    int numVertices = 10;

    WorkVertex **workVertices = (WorkVertex **) calloc(numVertices,
                                sizeof(WorkVertex *));

    /* Allocate current neighbors array */
    curNeighbors = (WorkVertex **) calloc(numVertices,
                                          sizeof(WorkVertex *));

    outNeighborWorkVertex = (WorkVertex **) calloc(numVertices,
                            sizeof(WorkVertex *));

    /* create WorkVertex instance of start vertex and set to open list */
    wvStart = createWorkVertex(start);
    setSetMode(OPEN_SET, wvStart);

    /* calculate and set f value for start to destination vertex */
    SetFValue(CalcFValue(wvStart, dest), wvStart);

    while (getVerticesInSet(OPEN_SET, workVertices, numVertices) != 0) {
        current = getVertexLowestFOpenSet(workVertices, numVertices);
        if (current->originVertex->vertexId == dest->vertexId) {
            reconstruct_path(verticesInPath, current,
                             workVertices, numVertices,
                             outNeighborWorkVertex);
        }

        current->setMode = CLOSED_SET;

        for (i = 0; i < getNeighbors(current, workVertices, numVertices, curNeighbors);
                i++) {
            curNeighbor = curNeighbors[i];
            unsigned int weight = getWeight(current, curNeighbor, workVertices, numVertices,
                                            outNeighborWorkVertex);

            tempG = GetGValue(current) + weight;

            tempF = tempG + distBetween(curNeighbor->originVertex, dest);

            if (curNeighbor->setMode == CLOSED_SET && tempF >= GetFValue(curNeighbor)) {
                continue;
            }

            if (curNeighbor->setMode != OPEN_SET || tempF < GetFValue(curNeighbor)) {
                SetParentVertex(curNeighbor, current);
                verticesInPath++;
                SetGValue(tempG, curNeighbor);
                SetFValue(tempF, curNeighbor);
                if (curNeighbor->setMode != OPEN_SET) {
                    curNeighbor->setMode = OPEN_SET;
                }
            }

        }
    }

    /* this is only returned if failure */
    return 0;
}

Path *reconstruct_path(unsigned int verticesInPath, WorkVertex *end,
                       WorkVertex **workVertices, int numVertices,
                       WorkVertex **outNeighborWorkVertex) {
    WorkVertex *parent;
    int i = 0;
    Path *path = (Path *) malloc(sizeof(Path));
    path->pathVerticeIds = (unsigned int *) malloc(sizeof(int) * verticesInPath);


    do {
        parent = end->parentVertex;
        path->weight += getWeight(end, parent, workVertices, numVertices,
                                  outNeighborWorkVertex);

        path->pathVerticeIds[i] = parent->originVertex->vertexId;
        i++;
    } while (parent != NULL);

    return path;
}


unsigned int getWeight(WorkVertex *src, WorkVertex *targetNeighbor,
                       WorkVertex **workVertices,
                       int numVertices, WorkVertex **outNeighborWorkVertex) {
    int i;
    unsigned int curId;
    int numNeighbors = getNeighbors(src, workVertices, numVertices,
                                    outNeighborWorkVertex);


    WorkVertex *curNeighbor;
    int srcId = src->originVertex->vertexId;
    int targetId = targetNeighbor->originVertex->vertexId;


    EdgePointer *ep = src->originVertex->ep;

    for (i = 0; i < numNeighbors; i++) {
        Edge *e = ep->edge;
        /* if vertexId is not same as srcId, create a workVertex based on that vertex
        if and only if srcVertex and vertex are on the same floor.
        This is because Astar should only work on 1 floor. */
        if ((e->vertex1->vertexId == srcId && e->vertex2->vertexId == targetId)
                || (e->vertex2->vertexId == srcId && e->vertex1->vertexId == targetId)) {
            return e->weight;
        } else {
            /* get next ep */
            ep = ep->nextEp;
        }
    }
    /*only returned if error*/
    return 0;
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

int getNeighbors(WorkVertex *wv, WorkVertex **workVertices, int numVertices,
                 WorkVertex **outNeighborWorkVertex) {
    int numNeighbors = 0;
    WorkVertex *curWv;
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
            curWv = createWorkVertex(e->vertex1);
        }
        /* if vertexId is not same as srcId, create a workVertex based on that vertex
                if and only if srcVertex and vertex are on the same floor.
                This is because Astar should only work on 1 floor. */
        else if (e->vertex2->vertexId != srcId && e->vertex2->floorId == srcFloor) {
            curWv = createWorkVertex(e->vertex2);
        } else {
            printf("Could not create workvertex\n");
        }


        addToWorkVertices(wv, workVertices, numVertices);
        outNeighborWorkVertex[numNeighbors] = curWv;

        numNeighbors++;

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
    wv->setMode = value;
}

int getVerticesInSet(int setMode, WorkVertex **workVertices, int numVertices) {
    int i;
    int numSet = 0;

    for (i = 0; i < numVertices; i++) {
        if (workVertices[i]->setMode == setMode) {
            numSet++;
        }
    }
    return numSet;
}

WorkVertex *createWorkVertex(Vertex *src) {
    WorkVertex *wv;

    wv = (WorkVertex *) malloc(sizeof(WorkVertex));
    wv->originVertex = src;

    return wv;
}


