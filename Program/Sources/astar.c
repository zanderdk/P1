#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "graph.h"
#include "astar.h"

#define NO_SET 0
#define CLOSED_SET 1
#define OPEN_SET 2

Path *AStar(Vertex *start, Vertex *dest) {
    int i;
    WorkVertex *wvStart;
    WorkVertex *current;
    WorkVertex **curNeighbors;
    WorkVertex *curNeighbor;
    Path *path;

    unsigned int tempG;
    double tempF;
    unsigned int verticesInPath = 0;
    //int numVertices = GetNumVerticesOnFloor(int floorId, Floor *graph);
    int numVertices = 7;

    WorkVertex **workVertices = (WorkVertex **) calloc(numVertices,
                                sizeof(WorkVertex *));

    /* Allocate current neighbors array */
    curNeighbors = (WorkVertex **) calloc(numVertices,
                                          sizeof(WorkVertex *));

    /* create WorkVertex instance of start vertex and set to open list */
    wvStart = CreateWorkVertex(start);
    SetSetMode(OPEN_SET, wvStart);
    AddToWorkVertices(wvStart, workVertices, numVertices);


    /* calculate and set f value for start to destination vertex */
    SetFValue(CalcFValue(wvStart, dest), wvStart);

    while (GetVerticesInSet(OPEN_SET, workVertices, numVertices) != 0) {
        /* set current vertex to the vertex in open set with lowest f value */
        current = GetVertexLowestFOpenSet(workVertices, numVertices);

        /* is at destination? if so, recontruct the path to get from start to destination */
        if (current->originVertex->vertexId == dest->vertexId) {
            path =  ReconstructPath(verticesInPath, current,
                                    numVertices);
            free(workVertices);
            free(curNeighbors);
            return path;
        }
        verticesInPath++;
        current->setMode = CLOSED_SET;
        int numNeighbors = GetNeighbors(current, workVertices, numVertices, curNeighbors);

        for (i = 0; i < numNeighbors; i++) {
            curNeighbor = curNeighbors[i];
            unsigned int weight = GetWeight(current, curNeighbor);

            tempG = GetGValue(current) + weight;

            tempF = tempG + DistBetween(curNeighbor->originVertex, dest);

            if (curNeighbor->setMode == CLOSED_SET && tempF >= GetFValue(curNeighbor)) {
                continue;
            }

            if (curNeighbor->setMode != OPEN_SET || tempF < GetFValue(curNeighbor)) {
                SetParentVertex(curNeighbor, current);
                SetGValue(tempG, curNeighbor);
                SetFValue(tempF, curNeighbor);
                if (curNeighbor->setMode != OPEN_SET) {
                    curNeighbor->setMode = OPEN_SET;
                }
            }

        }
    }

    /* this is only returned if failure */
    return path;
}

Path *ReconstructPath(unsigned int verticesInPath, WorkVertex *end,
                      int numVertices) {

    WorkVertex *parent;
    Path *path;
    path = (Path *) malloc(sizeof(Path) + verticesInPath * sizeof(unsigned int));
    int i = verticesInPath - 1;
    path->pathVerticeIds = (unsigned int *) path + sizeof(path);
    //path->pathVerticeIds = (unsigned int *) malloc(sizeof(int) * verticesInPath);
    path->numVertices = verticesInPath;
    parent = end->parentVertex;

    path->pathVerticeIds[i] = end->originVertex->vertexId;
    path->weight = end->g;
    i--;

    while (parent != NULL) {
        path->pathVerticeIds[i] = parent->originVertex->vertexId;
        parent = parent->parentVertex;
        i--;
    }

    return path;
}

WorkVertex *getFromWorkVertices(int targetId, WorkVertex **workVertices,
                                int numVertices) {
    int i;

    for (i = 0; i < numVertices; i++) {
        /* If an entry in array is 0, nothing at that position has been set
         Therefore, set it */
        if (workVertices[i] != NULL
                && workVertices[i]->originVertex->vertexId == targetId) {
            return workVertices[i];
        }
    }
    return NULL;
}

int GetNeighbors(WorkVertex *wv, WorkVertex **workVertices, int numVertices,
                 WorkVertex **outNeighborWorkVertex) {
    int numNeighbors = 0;
    Vertex *vertexFound;
    WorkVertex *existingWV;
    Vertex *origin = wv->originVertex;
    int srcId = origin->vertexId;
    int srcFloor = origin->floorId;


    EdgePointer *ep = origin->ep;

    do {
        Edge *e = ep->edge;
        if (e->vertex1->vertexId != srcId) {
            /* memory leak occurs here */
            vertexFound = e->vertex1;
            //outNeighborWorkVertex[numNeighbors] = CreateWorkVertex(e->vertex1);
        } else if (e->vertex2->vertexId != srcId) {
            /* memory leak occurs here */
            vertexFound = e->vertex2;
            //outNeighborWorkVertex[numNeighbors] = CreateWorkVertex(e->vertex2);
        } else {
            printf("Could not create workvertex\n");
        }

        existingWV = getFromWorkVertices(vertexFound->vertexId, workVertices, numVertices);
        if (existingWV != NULL && existingWV->setMode == CLOSED_SET) {
            /* before we continue, set next ep */
            ep = ep->nextEp;
            continue;
        } else if (existingWV != NULL && existingWV->setMode == OPEN_SET) {
            // AddToWorkVertices(outNeighborWorkVertex[numNeighbors], workVertices, numVertices);
        } else {
            existingWV = CreateWorkVertex(vertexFound);
        }
        outNeighborWorkVertex[numNeighbors] = existingWV;
        AddToWorkVertices(existingWV, workVertices, numVertices);

        numNeighbors++;

        /* get next ep */
        ep = ep->nextEp;

    } while (ep != NULL);
    return numNeighbors;
}

WorkVertex *CreateWorkVertex(Vertex *src) {
    WorkVertex *wv;

    wv = (WorkVertex *) malloc(sizeof(WorkVertex));
    wv->originVertex = src;

    return wv;
}

void SetGValue(unsigned int value, WorkVertex *wv) {
    wv->g = value;
}

unsigned int GetGValue(WorkVertex *wv) {
    return wv->g;
}

double DistBetween(Vertex *src, Vertex *goal) {
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
    double h = DistBetween(src->originVertex, goal);
    return g + h;
}

void SetFValue(double f, WorkVertex *wv) {
    wv->f = f;
}

double GetFValue(WorkVertex *wv) {
    return wv->f;
}

void SetParentVertex(WorkVertex *child, WorkVertex *parent) {
    child->parentVertex = parent;
}

unsigned int GetWeight(WorkVertex *src, WorkVertex *targetNeighbor) {
    unsigned int weight;
    int srcId = src->originVertex->vertexId;
    int targetId = targetNeighbor->originVertex->vertexId;

    EdgePointer *ep = src->originVertex->ep;

    do {
        Edge *e = ep->edge;

        if ((e->vertex1->vertexId == srcId && e->vertex2->vertexId == targetId)
                || (e->vertex1->vertexId == targetId && e->vertex2->vertexId == srcId)) {
            weight = e->weight;
            break;
        }
        ep = ep->nextEp;
    } while (ep != NULL);
    return weight;
}




int IsInWorkVertices(WorkVertex *wv, WorkVertex **workVertices, int numVertices) {
    int i;

    for (i = 0; i < numVertices; i++) {
        /* If an entry in array is 0, nothing at that position has been set
         Therefore, set it */
        if (workVertices[i] != NULL
                && workVertices[i]->originVertex->vertexId == wv->originVertex->vertexId) {
            return 1;
        }
    }
    return 0;
}

void AddToWorkVertices(WorkVertex *wv, WorkVertex **workVertices, int numVertices) {
    int i;

    for (i = 0; i < numVertices; i++) {
        /* If an entry in array is 0, nothing at that position has been set
         Therefore, set it */
        if (workVertices[i] == 0) {
            workVertices[i] = wv;
            break;
        }
    }
}

WorkVertex *GetVertexLowestFOpenSet(WorkVertex **workVertices, int numVertices) {
    int i;
    int indexLowestF;
    double curF;
    double lowestF = DBL_MAX;

    for (i = 0; i < numVertices; i++) {
        if (workVertices[i] == NULL || workVertices[i]->setMode != OPEN_SET) {
            continue;
        }
        curF =  workVertices[i]->f;
        if (curF < lowestF) {
            lowestF = curF;
            indexLowestF = i;
        }
    }
    return workVertices[indexLowestF];
}

void SetSetMode(int value, WorkVertex *wv) {
    wv->setMode = value;
}

int GetVerticesInSet(int setMode, WorkVertex **workVertices, int numVertices) {
    int i;
    int numSet = 0;

    for (i = 0; i < numVertices; i++) {
        if (workVertices[i] != 0 && workVertices[i]->setMode == setMode) {
            numSet++;
        }
    }
    return numSet;
}



