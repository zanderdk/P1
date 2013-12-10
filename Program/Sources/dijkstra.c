#include <stdlib.h>

#include "graph.h"
#include "dijkstra.h"

void PreComputePaths(Graph *graph, SourcePaths **sourcePaths, unsigned int mode) {
    int i, i2;

    /* Allocate memory for the work vertices and setup the linked list */
    WVLinkedList *wVLinkedListHead = malloc(graph->numOfVertices * sizeof(WVLinkedList));
    wVLinkedListHead->next = wVLinkedListHead + sizeof(WVLinkedList);
    GetWorkingGraph(graph, wVLinkedListHead);

    /* Get all exit nodes in the graph */
    WorkVertex *exits[2048];
    unsigned int count = 0;
    GetAllExits(graph, wVLinkedListHead, exits, &count);

    /* Allocate memory for all paths */
    *sourcePaths = malloc(count * sizeof(SourcePaths));
    for (i = 0; i < count; ++i) {
        (*sourcePaths)[i].paths = malloc((count - 1) * sizeof(Path));
        (*sourcePaths)[i].numPaths = count - 1;
        for (i2 = 0; i2 < count - 1; ++i2) {
            (*sourcePaths)[i].paths[i2].pathVerticeIds = malloc(1024 * sizeof(unsigned int));
        }
    }

    /* Pre-compute paths for all exits in the graph */
    for (i = 0; i < count; ++i) {
        Dijkstra(wVLinkedListHead, exits[i], mode);
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
            tempPtr2->workVertex.dist = 0;
            tempPtr2->next = tempPtr2 + sizeof(WVLinkedList);
            tempPtr2 = tempPtr2->next;
            tempPtr = tempPtr->nextVp;
        }
    }
}
void GetAllExits(Graph *graph, WVLinkedList *workingGraph, WorkVertex **exits, unsigned int *count) {
    int i;
    Vertex *tempPtr;
    WVLinkedList *tempPtr2 = workingGraph;
    WorkVertex **itPtr = exits;

    for (i = 0; i < graph->numOfFloors; ++i) {
        tempPtr = graph->floors[i].vp;
        while (tempPtr != NULL) {
            if (tempPtr->type == 1 || tempPtr->type == 2) {
                while (tempPtr2->workVertex.vertex != tempPtr) {
                    tempPtr2 = tempPtr2->next;
                }
                *itPtr = &(tempPtr2->workVertex);
                itPtr++;
            }
        }
    };
}

void SetPathsFromWGraph(WVLinkedList *workingGraph, WorkVertex **exits, SourcePaths *paths) {

}

void Dijkstra(WVLinkedList *workingGraph, WorkVertex *source, int mode) {

}