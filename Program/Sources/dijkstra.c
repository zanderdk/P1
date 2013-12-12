#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
/*#include "dijkstra.h"*/
#include "privdijkstra.h"

void PreComputePaths(Graph *graph, SourcePaths **sourcePaths, unsigned int mode) {
    int i, i2;

    /* Allocate memory for the work vertices and setup the linked list */
    WVLinkedList *workingGraph = malloc(graph->numOfVertices * sizeof(WVLinkedList));
    workingGraph->next = workingGraph + sizeof(WVLinkedList);
    GetWorkingGraph(graph, workingGraph);

    /* Get all exit nodes in the graph */
    WorkVertex *exits[2048];
    unsigned int count = 0;
    GetAllExits(graph, workingGraph, exits, &count);

    /* Allocate memory for all paths */
    *sourcePaths = malloc(count * sizeof(SourcePaths));
    for (i = 0; i < count; ++i) {
        (*sourcePaths)[i].paths = malloc((count - 1) * sizeof(Path));
        (*sourcePaths)[i].numPaths = count - 1;
        (*sourcePaths)[i].sourceId = (exits[i])->vertex->vertexId;
        for (i2 = 0; i2 < count - 1; ++i2) {
            (*sourcePaths)[i].paths[i2].pathVerticeIds = malloc(1024 * sizeof(unsigned int));
        }
    }

    /* Pre-compute paths for all exits in the graph */
    for (i = 0; i < count; ++i) {
        Dijkstra(workingGraph, exits[i], mode);
        SetPathsFromWGraph(workingGraph, exits, i, count, *sourcePaths);
        ResetWorkingGraph(workingGraph);
    }
}

void GetWorkingGraph(Graph *graph, WVLinkedList *head) {
    int i;
    Vertex *tempPtr;
    WVLinkedList *tempPtr2 = head;

    for (i = 0; i < graph->numOfFloors; ++i) {
        tempPtr = graph->floors[i].vp;
        while (tempPtr != NULL) {
            tempPtr2->workVertex.vertex = tempPtr;
            tempPtr2->workVertex.dist = -1;
            tempPtr2->workVertex.visited = 0;
            tempPtr2->next = tempPtr2 + sizeof(WVLinkedList);
            tempPtr2 = tempPtr2->next;
            tempPtr = tempPtr->nextVp;
        }
    }
    tempPtr2->next = NULL;
}
void GetAllExits(Graph *graph, WVLinkedList *workingGraph, WorkVertex **exits, unsigned int *count) {
    int i;
    Vertex *tempPtr;
    WVLinkedList *tempPtr2 = workingGraph;

    for (i = 0; i < graph->numOfFloors; ++i) {
        tempPtr = graph->floors[i].vp;
        while (tempPtr != NULL) {
            if (tempPtr->type == 1 || tempPtr->type == 2) {
                while (tempPtr2->workVertex.vertex != tempPtr) {
                    tempPtr2 = tempPtr2->next;
                }
                exits[*count] = &(tempPtr2->workVertex);
                (*count)++;;
            }
        }
    };
}

void SetPathsFromWGraph(WVLinkedList *workingGraph, WorkVertex **exits, int index, int count, SourcePaths *sourcePaths) {
    int i;
    for (i = index + 1; i < count; ++i) {
        BacktrackPath(exits[index], exits[i], &((sourcePaths[i]).paths[index]));
        ReversePath(&((sourcePaths[i]).paths[index]), &((sourcePaths[index]).paths[i - 1]));
        (sourcePaths[index]).paths[i - 1].targetId = exits[i]->vertex->vertexId;
    }
}

void BacktrackPath(WorkVertex *source, WorkVertex *goal, Path *path) {
    int counter = 0;
    WorkVertex *workPtr = goal;
    path->weight = goal->dist;
    path->targetId = source->vertex->vertexId;
    do {
        path->pathVerticeIds[counter] = workPtr->vertex->vertexId;
        counter++;
    } while ((workPtr = workPtr->previous)->vertex->vertexId != source->vertex->vertexId);
    path->numVertices = counter;
    path->pathVerticeIds = realloc(path->pathVerticeIds, counter * sizeof(unsigned int));
}

void ReversePath(Path *from, Path *to) {
    int i;
    to->numVertices = from->numVertices;
    to->weight = from->weight;
    for (i = 0; i < from->numVertices; ++i) {
        to->pathVerticeIds[i] = from->pathVerticeIds[from->numVertices - i];
    }
    to->pathVerticeIds = realloc(to->pathVerticeIds, to->numVertices * sizeof(unsigned int));
}

void Dijkstra(WVLinkedList *workingGraph, WorkVertex *source, int mode) {
    WorkVertex *current = source;
    current->dist = 0;
    do {
        SetNeighborWeights(current, &workingGraph, mode);
        current->visited = 1;
    } while (!workingGraph->workVertex.visited);
}

void SetNeighborWeights(WorkVertex *current, WVLinkedList **workingGraph, int mode) {
    int temp = 0;
    Vertex *vertex = current->vertex;
    EdgePointer *epPtr = vertex->ep;
    WVLinkedList *wvllPtr, **prevPtr = workingGraph;
    do {
        if (epPtr->edge->vertex1 != vertex) {
            wvllPtr = WVLLLookup(*workingGraph, epPtr->edge->vertex1, &prevPtr);
        } else if (epPtr->edge->vertex2 != vertex) {
            wvllPtr = WVLLLookup(*workingGraph, epPtr->edge->vertex2, &prevPtr);
        } else {
            printf("FATAL ERROR!\n");
        }

        if (!wvllPtr->workVertex.visited && (wvllPtr->workVertex.dist == -1 || (temp = (mode + 1 == wvllPtr->workVertex.vertex->type) ?
                                             ((epPtr->edge->weight + current->dist) * 100) : (epPtr->edge->weight + current->dist)) < wvllPtr->workVertex.dist)) {
            wvllPtr->workVertex.dist = temp;
            wvllPtr->workVertex.previous = current;
            WVLLInsertSort(workingGraph, wvllPtr, prevPtr);
        }
    } while ((epPtr = epPtr->nextEp));
}

WVLinkedList *WVLLLookup(WVLinkedList *workingGraph, Vertex *target, WVLinkedList ***previous) {
    WVLinkedList *current = workingGraph;
    while (current->workVertex.vertex != target) {
        *previous = &(current->next);
        current = current->next;
    }
    return current;
}

void WVLLInsertSort(WVLinkedList **workingGraph, WVLinkedList *target, WVLinkedList **previous) {
    WVLLDelete(&target, previous);
    WVLinkedList **wvllPtr = workingGraph;
    while (Comparer(target, *wvllPtr) > 0 && (wvllPtr = &((*wvllPtr)->next))) {};
    WVLLInsert(&target, wvllPtr);
}

int Comparer(WVLinkedList *wvll1, WVLinkedList *wvll2) {
    if (wvll2->workVertex.visited || (wvll1->workVertex.dist == wvll2->workVertex.dist) || (wvll2->workVertex.dist == -1) || (wvll1->workVertex.dist < wvll2->workVertex.dist)) {
        return -1;
    } else {
        return 1;
    }
}

void WVLLDelete(WVLinkedList **target, WVLinkedList **previous) {
    *previous = (*target)->next;
}

void WVLLInsert(WVLinkedList **target, WVLinkedList **previous) {
    (*target)->next = *previous;
    *previous = *target;
}

void ResetWorkingGraph(WVLinkedList *workingGraph) {
    WVLinkedList *tempPtr = workingGraph;
    do {
        tempPtr->workVertex.dist = -1;
        tempPtr->workVertex.visited = 0;
    } while ((tempPtr = tempPtr->next));
}