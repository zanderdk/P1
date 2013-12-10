#include <stdlib.h>

#include "dijkstra.h"

void PreComputePaths(Graph *graph, SourcePaths **paths, unsigned int mode) {
    /* Allocate memory for the work vertices and setup the linked list */
    WVLinkedList *wVLinkedListHead = malloc(graph->numOfVertices * sizeof(WVLinkedList));
    wVLinkedListHead->next = wVLinkedListHead + sizeof(WVLinkedList);
    GetWorkingGraph(graph, wVLinkedListHead);

    /* Get all exit nodes in the graph */
    WorkVertex *exits[2048];
    WorkVertex **exitsPtr = exits;
    unsigned int count = 0;
    GetAllExits(graph, wVLinkedListHead, exits, &count);

    /* Allocate memory for all paths */


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
                *itPtr = tempPtr2;
                itPtr++;
            }
        }
    };
}

void SetPathsFromWGraph(WVLinkedList *workingGraph, WorkVertex **exits, SourcePaths *paths) {

}

void Dijkstra(WVLinkedList *workingGraph, WorkVertex *source, int mode) {

}