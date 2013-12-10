#include <stdlib.h>

#include "graph.h"
#include "dijkstra.h"

void PreComputePaths(Graph *graph, SourcePaths *paths, int mode) {
    int i;

    /* Allocate memory for the work vertices and setup the linked list */
    WVLinkedList *wVLinkedListHead = malloc(graph->numOfVertices * sizeof(WVLinkedList));
    wVLinkedListHead->next = wVLinkedListHead + sizeof(WVLinkedList);
    GetWorkingGraph(graph, wVLinkedListHead);

    /* Get all exit nodes in the graph */
    WorkVertex *exits[2048];
    WorkVertex **exitsPtr = exits;
    GetAllExits(graph, exits);

    /* Pre-compute paths for all exits in the graph */
    while (exitsPtr != NULL) {
        Dijkstra(wVLinkedListHead, *exitsPtr, mode);
        exitsPtr++;
    }
}

void GetWorkingGraph(Graph *graph, WVLinkedList *head) {
    int i;
    Vertex *tempPtr;
    WVLinkedList *tempPtr2 = head;

    for (i = 0; i < graph->numOfFloors; ++i) {
        tempPtr = graph->floors[i]->vp;
        while (tempPtr != NULL) {
            tempPtr2->workVertex.vertex = tempPtr;
            tempPtr2->workVertex.dist = tempPtr;
            tempPtr2->next = tempPtr2 + sizeof(WVLinkedList);
            tempPtr2 = tempPtr2->next;
            tempPtr = vp->nextVp
        }
    }
}
void GetAllExits(Graph *graph, WVLinkedList *workingGraph, WorkVertex **exits) {
    int i;
    Vertex *tempPtr;
    WVLinkedList *tempPtr2 = workingGraph;
    Vertex **itPtr = exits;

    for (i = 0; i < graph->numOfFloors; ++i) {
        tempPtr = graph->floors[i]->vp;
        while (tempPtr != NULL) {
            if (tempPtr->type == 1 || tempPtr->type == 2) {
                while (tempPtr2->workVertex.vertex != tempPtr) {
                    tempPtr2 = tempPtr2->head;
                }
                *itPtr = tempPtr2;
                itPtr++;
            }
        }
    }
    *itPtr = NULL;
}

void Dijkstra(WVLinkedList *workingGraph, WorkVertex *source, int mode) {

}