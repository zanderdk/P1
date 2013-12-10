#include <stdlib.h>

#include "graph.h"
#include "dijkstra.h"

void PreComputePaths(Graph *graph, SourcePaths *paths) {
    /* Allocate memory for the work vertices and setup the linked list */
    WorkVertex WorkVertices = malloc(graph->numOfVertices * sizeof(WorkVertex));
    WVLinkedList *wVLinkedListHead = malloc(graph->numOfVertices * sizeof(WVLinkedList));
    wVLinkedListHead->element = WorkVertices;
    wVLinkedListHead->next = wVLinkedListHead + sizeof(WVLinkedList);
    GetWorkingGraph(graph, wVLinkedListHead);

    /* Get all exit nodes in the graph */
    Vertex *exits[2048];
    GetAllExits(graph, exits);
}

void GetWorkingGraph(Graph *graph, WVLinkedList *head) {
    int i;
    Vertex *tempPtr;
    WVLinkedList *tempPtr2 = head;

    for (i = 0; i < graph->numOfFloors; ++i) {
        tempPtr = graph->floors[i]->vp;
        while (tempPtr != NULL) {
            tempPtr2->element->vertex = tempPtr;
            tempPtr2->next = tempPtr2 + sizeof(WVLinkedList);
            tempPtr2->next->element = tempPtr2->element + sizeof(WorkVertex);
            tempPtr2 = tempPtr2->next;
            tempPtr = vp->nextVp
        }
    }
}
void GetAllExits(Graph *graph, Vertex **exits) {
    int i;
    Vertex *tempPtr;
    Vertex **itPtr = exits;
    for (i = 0; i < graph->numOfFloors; ++i) {
        tempPtr = graph->floors[i]->vp;
        while (tempPtr != NULL) {
            if (tempPtr->type == 1 || tempPtr->type == 2) {
                *itPtr = tempPtr;
                itPtr++;
            }
        }
    }
}

void Dijkstra(WVLinkedList *workingGraph, WorkVertex *source) {

}