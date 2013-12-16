#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
#include "privdijkstra.h"

void PreComputePaths(Graph *graph, SourcePaths **sourcePaths, unsigned int mode) {
    int i, i2, unsigned count = 0;
    Vertex *tempPtr;

    /* Count number of exits in the graph */
    for (i = 0; i < graph->numOfFloors; i++) {
        tempPtr = graph->floors[i].vp;
        while (tempPtr != NULL) {
            if (tempPtr->type > 1) {
                count++;
            }
            tempPtr = tempPtr->nextVp;
        }
    }

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

    /* APSP */
    for (i = 0; i < count; i++) {
        /* Allocate memory for the work vertices and setup the linked list */
        WVLinkedList *workingGraph = calloc(graph->numOfVertices, sizeof(WVLinkedList));;
        GetWorkingGraph(graph, workingGraph);

        /* Get pointers to all exit nodes in the graph */
        WorkVertex *exits[2048];
        GetAllExits(graph, workingGraph, exits, &count);

        /* Pre-compute and save paths from a source to all other vertices */
        Dijkstra(workingGraph, exits[i], mode);
        SetPathsFromWGraph(exits, i, count, *sourcePaths);
        free(workingGraph);
    }
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

void GetAllExits(Graph *graph, WVLinkedList *workingGraph, WorkVertex **exits) {
    int i, temp;
    Vertex *tempPtr;
    WVLinkedList *tempPtr2 = workingGraph;

    for (i = 0; i < graph->numOfFloors; i++) {
        tempPtr = graph->floors[i].vp;
        while (tempPtr != NULL) {
            if (tempPtr->type > 1) {
                do {
                    if (tempPtr2->workVertex.vertex == tempPtr) {
                        exits[temp] = &(tempPtr2->workVertex);
                        temp++;
                        break;
                    }
                    tempPtr2 = tempPtr2->next;
                } while (tempPtr2->next != NULL);
            }
            tempPtr = tempPtr->nextVp;
        }
    }
}

void SetPathsFromWGraph(WorkVertex **exits, int index, int count, SourcePaths *sourcePaths) {
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
    WorkVertex *current = source;
    current->dist = 0;
    WVLinkedList *tempPtr, **tempPtr2;
    do {
        SetNeighborWeights(current, workingGraph, mode);
        tempPtr = WVLLLookup(&workingGraph, current->vertex, &tempPtr2);
        WVLLDelete(tempPtr, tempPtr2);
        current = WVLLSearch(workingGraph);
    } while (workingGraph);
}

void SetNeighborWeights(WorkVertex *current, WVLinkedList *workingGraph, int mode) {
    int temp = 0;
    EdgePointer *epPtr = current->vertex->ep;
    WVLinkedList *wvllPtr, **igPtr;
    do {
        /* Find the WVLinkedList element corresponding to the vertex pointed to by the edge */
        if (epPtr->edge->vertex1 != vertex) {
            wvllPtr = WVLLLookup(workingGraph, epPtr->edge->vertex1, &igPtr);
        } else if (epPtr->edge->vertex2 != vertex) {
            wvllPtr = WVLLLookup(workingGraph, epPtr->edge->vertex2, &igPtr);
        } else {
            printf("FATAL ERROR!\n");
        }

        /* Calculate the tentative distance to the vertex taking the mode into account */
        if (mode == 0) {
            temp = epPtr->edge->weight + current->dist;
        } else if (mode == 1 && wvllPtr->workVertex.vertex->type - 1 == 1) {
            temp = epPtr->edge->weight + current->dist * 100;
        } else if (mode == 2 && wvllPtr->workVertex.vertex->type - 1 == 2) {
            temp = epPtr->edge->weight + current->dist * 100;
        }

        /* Check if the calculated tentative distance is lower than the currently saved tentative distance.
         * Re-assign the distance and previous pointer if it is lower */
        if (wvllPtr->workVertex.dist == -1 || temp < wvllPtr->workVertex.dist) {
            wvllPtr->workVertex.dist = temp;
            wvllPtr->workVertex.previous = current;
        }
    } while ((epPtr = epPtr->nextEp));
}

WVLinkedList *WVLLLookup(WVLinkedList **workingGraph, Vertex *target, WVLinkedList ***previous) {
    WVLinkedList *current = *workingGraph;
    *previous = workingGraph;
    while (current->workVertex.vertex != target) {
        *previous = &(current->next);
        current = current->next;
    }
    return current;
}

void WVLLDelete(WVLinkedList *target, WVLinkedList **previous) {
    *previous = target->next;
}

WVLinkedList *WVLLSearch(WVLinkedList *workingGraph) {
    WVLinkedList tempPtr = workingGraph, retPtr = workingGraph;
    while (tempPtr) {
        if (tempPtr->workVertex.dist < retPtr->workVertex.dist) {
            retPtr = tempPtr;
        }
        tempPtr = tempPtr->next
    }
    return retPtr;
}