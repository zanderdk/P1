#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
/*#include "dijkstra.h"*/
#include "privdijkstra.h"

void printasd(WVLinkedList *head) {
    WVLinkedList *temp = head;
    do {
        printf("%d:%d - edge: %d - %u - %u - %p\n", temp->workVertex.vertex->vertexId, temp->workVertex.vertex->type, temp->workVertex.vertex->ep->edge->edgeId,  temp->workVertex.dist, temp->workVertex.visited, temp->workVertex.previous);
    } while ((temp = temp->next));
}

void PreComputePaths(Graph *graph, SourcePaths **sourcePaths, unsigned int mode) {
    int i, i2;

    /* Allocate memory for the work vertices and setup the linked list */
    WVLinkedList *tmp = calloc(graph->numOfVertices, sizeof(WVLinkedList));
    WVLinkedList *workingGraph = tmp;

    //workingGraph->next = workingGraph + sizeof(WVLinkedList);
    GetWorkingGraph(graph, workingGraph);

    /* Get all exit nodes in the graph */
    WorkVertex *exits[2048];
    unsigned int count = 0;
    GetAllExits(graph, workingGraph, exits, &count);



    // Allocate memory for all paths
    *sourcePaths = malloc(count * sizeof(SourcePaths));
    for (i = 0; i < count; ++i) {
        (*sourcePaths)[i].paths = malloc((count - 1) * sizeof(Path));
        (*sourcePaths)[i].numPaths = count - 1;
        (*sourcePaths)[i].sourceId = (exits[i])->vertex->vertexId;
        for (i2 = 0; i2 < count - 1; ++i2) {
            (*sourcePaths)[i].paths[i2].pathVerticeIds = malloc(1024 * sizeof(unsigned int));
        }
    }


    //Pre-compute paths for all exits in the graph
    for (i = 0; i < count; i++) {
        Dijkstra(workingGraph, exits[i], mode);
        SetPathsFromWGraph(workingGraph, exits, i, count, *sourcePaths);
        ResetWorkingGraph(workingGraph);
    }

    free(tmp);
}

void GetWorkingGraph(Graph *graph, WVLinkedList *head) {
    int i;
    Vertex *tempPtr;
    WVLinkedList *tempPtr2 = head;

    for (i = 0; i < graph->numOfFloors; i++) {
        tempPtr = graph->floors[i].vp;
        do {
            tempPtr2->workVertex.vertex = tempPtr;
            tempPtr2->workVertex.dist = -1;
            tempPtr2->workVertex.visited = 0;
            tempPtr2->next = tempPtr2 + 1;

        } while ((tempPtr = tempPtr->nextVp) && (1, tempPtr2 = tempPtr2->next));
        tempPtr2->next = NULL;
    }
}


void GetAllExits(Graph *graph, WVLinkedList *workingGraph, WorkVertex **exits, unsigned int *count) {
    int i;
    Vertex *tempPtr;
    WVLinkedList *tempPtr2 = workingGraph;

    for (i = 0; i < graph->numOfFloors; i++) {
        tempPtr = graph->floors[i].vp;
        while (tempPtr != NULL) {
            if (tempPtr->type > 1) {
                do {
                    //printf("%d\n", tempPtr2->workVertex.vertex->vertexId);

                    if (tempPtr2->workVertex.vertex == tempPtr) {
                        exits[*count] = &(tempPtr2->workVertex);
                        (*count)++;
                        break;
                    }

                    tempPtr2 = tempPtr2->next;
                } while (tempPtr2->next != NULL);
            }


            tempPtr = tempPtr->nextVp;
        }
    }

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
        workPtr = workPtr->previous;
    } while (workPtr->vertex->vertexId != source->vertex->vertexId);
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
    printasd(workingGraph);
    WorkVertex *current = source;
    current->dist = 0;
    WVLinkedList **tempPtr, *tempPtr2;
    do {
        current->visited = 1;
        printf("\n");
        printf("current %d\n", current->vertex->vertexId);
        tempPtr2 = WVLLLookup(workingGraph, current->vertex, &tempPtr);
        printf("%p %p %p %p %p\n", tempPtr, *tempPtr, (**tempPtr).workVertex.vertex, (**tempPtr).workVertex.previous, (**tempPtr).next);
        //printf("%d\n", tempPtr2->workVertex.vertex->vertexId);
        //printf("%d\n", (*tempPtr)->workVertex.vertex->vertexId);
        WVLLInsertSort(&workingGraph, tempPtr2, &tempPtr);
        SetNeighborWeights(current, &workingGraph, mode);
        printasd(workingGraph);
        current = &(workingGraph->workVertex);
    } while (!workingGraph->workVertex.visited);
}

void WVLLInsertSort(WVLinkedList **workingGraph, WVLinkedList *target, WVLinkedList ***previous) {
    printf("%p %p %p %p %p\n", *previous, **previous, (* **previous).workVertex.vertex, (* **previous).workVertex.previous, (* **previous).next);
    WVLLDelete(&target, *previous);
    WVLinkedList **wvllPtr = workingGraph;
    while (*wvllPtr && Comparer(target, *wvllPtr) > 0) {
        wvllPtr = &((*wvllPtr)->next);
    }
    WVLLInsert(&target, wvllPtr);
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
        if (mode == 0) {
            temp = epPtr->edge->weight + current->dist;
        } else if (mode == 1 && wvllPtr->workVertex.vertex->type - 1 == 1) {
            temp = epPtr->edge->weight + current->dist * 100;
        } else if (mode == 2 && wvllPtr->workVertex.vertex->type - 1 == 2) {
            temp = epPtr->edge->weight + current->dist * 100;
        }
        if (!wvllPtr->workVertex.visited && (wvllPtr->workVertex.dist == -1 || temp < wvllPtr->workVertex.dist)) {
            wvllPtr->workVertex.dist = temp;
            wvllPtr->workVertex.previous = current;
            WVLLInsertSort(workingGraph, wvllPtr, &prevPtr);
        }
    } while ((epPtr = epPtr->nextEp));
}

WVLinkedList *WVLLLookup(WVLinkedList *workingGraph, Vertex *target, WVLinkedList ***previous) {
    WVLinkedList *current = workingGraph;
    *previous = &workingGraph;
    while (current->workVertex.vertex != target) {
        *previous = &(current->next);
        current = current->next;
    }
    return current;
}

int Comparer(WVLinkedList *wvll1, WVLinkedList *wvll2) {
    if (wvll1->workVertex.visited != wvll2->workVertex.visited) {
        return (wvll1->workVertex.visited) ? 1 : -1;
    } else if (wvll1->workVertex.dist != wvll2->workVertex.dist) {
        return (wvll1->workVertex.dist > wvll2->workVertex.dist) ? 1 : -1;
    } else {
        return -1;
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