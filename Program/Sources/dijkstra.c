#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "graph.h"
#include "privdijkstra.h"

#define INITIAL_COST 5

void printasd(WVLinkedList *head) {
    WVLinkedList *temp = head;
    do {
        printf("%d:%d - %u - %p\n", temp->workVertex.vertex->vertexId, temp->workVertex.vertex->type, temp->workVertex.dist, temp->workVertex.previous);
    } while ((temp = temp->next));
}

int PreComputePaths(Graph *graph, SourcePaths **sourcePaths, unsigned int mode) {
    int i, i2;
    int unsigned count = 0, ids[2048];
    Vertex *tempPtr;

    /* Count number of exits in the graph */
    for (i = 0; i < graph->numOfFloors; i++) {
        tempPtr = graph->floors[i].vp;
        while (tempPtr != NULL) {
            if (tempPtr->type > 1) {
                ids[count] = tempPtr->vertexId;
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
        (*sourcePaths)[i].sourceId = ids[i];
        for (i2 = 0; i2 < count - 1; ++i2) {
            (*sourcePaths)[i].paths[i2].pathVerticeIds = malloc(1024 * sizeof(unsigned int));
        }
    }

    /* APSP */
    for (i = 0; i < count; i++) {
        /* Allocate memory for the work vertices and setup the linked list */
        WVLinkedList *workingGraph = calloc(graph->numOfVertices, sizeof(WVLinkedList));;
        GetWorkingGraph(graph, workingGraph);

        //printasd(workingGraph);

        /* Get pointers to all exit nodes in the graph */
        WorkVertex *exits[2048];
        GetAllExits(workingGraph, exits);

        /* Pre-compute and save paths from a source to all other vertices */
        Dijkstra(workingGraph, exits[i], mode);
        SetPathsFromWGraph(exits, i, count, *sourcePaths);
        free(workingGraph);
    }

    return count;
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
            if (tempPtr->nextVp == NULL && i == graph->numOfFloors - 1) {
                break;
            }
            tempPtr2->next = tempPtr2 + 1;
            tempPtr2 = tempPtr2->next;

        } while ((tempPtr = tempPtr->nextVp));
        tempPtr2->next = NULL;
    }
}

void GetAllExits(WVLinkedList *workingGraph, WorkVertex **exits) {
    int temp = 0;
    WVLinkedList *tempPtr = workingGraph;
    while (tempPtr != NULL) {
        if (tempPtr->workVertex.vertex->type > 1) {
            exits[temp] = &(tempPtr->workVertex);
            temp++;
        }
        tempPtr = tempPtr->next;
    }
}

void SetPathsFromWGraph(WorkVertex **exits, int index, int count, SourcePaths *sourcePaths) {
    int i, i2;
    for (i = 0, i2 = 0; i < count - 1; i++, i2++) {
        if (index == i2) {
            i2++;
        }
        BacktrackPath(exits[index], exits[i2], &(sourcePaths[index]).paths[i]);
        (sourcePaths[index]).paths[i].targetId = exits[i2]->vertex->vertexId;
    }
}

void BacktrackPath(WorkVertex *source, WorkVertex *goal, Path *path) {
    int counter = 0;
    Path tempPath;
    tempPath.pathVerticeIds = malloc(1024 * sizeof(unsigned int));
    WorkVertex *workPtr = goal;
    do {
        tempPath.pathVerticeIds[counter] = workPtr->vertex->vertexId;
        counter++;
        workPtr = workPtr->previous;
    } while (workPtr->vertex->vertexId != source->vertex->vertexId);
    path->targetId = source->vertex->vertexId;
    path->pathVerticeIds = realloc(path->pathVerticeIds, counter * sizeof(unsigned int));
    tempPath.numVertices = counter;
    tempPath.weight = goal->dist;
    ReversePath(&tempPath, path);
    free(tempPath.pathVerticeIds);
}

void ReversePath(Path *from, Path *to) {
    int i;
    to->numVertices = from->numVertices;
    to->weight = from->weight;
    for (i = 0; i < from->numVertices; ++i) {
        to->pathVerticeIds[i] = (from->pathVerticeIds)[from->numVertices - i - 1];
    }
    to->pathVerticeIds = realloc(to->pathVerticeIds, to->numVertices * sizeof(unsigned int));
}

void Dijkstra(WVLinkedList *workingGraph, WorkVertex *source, int mode) {
    WorkVertex *current = source;
    current->dist = 0;
    WVLinkedList **tempPtr;
    do {
        SetNeighborWeights(current, workingGraph, mode);
        tempPtr = WVLLLookup(&workingGraph, current->vertex);
        WVLLDelete(tempPtr);
        current = &WVLLSearch(workingGraph)->workVertex;
    } while (workingGraph);
}

void SetNeighborWeights(WorkVertex *current, WVLinkedList *workingGraph, int mode) {
    int temp = 0, counter = 0;
    EdgePointer *epPtr = current->vertex->ep;
    WVLinkedList **wvllPtr;
    WorkVertex *tempPtr;
    do {
        /* Find the WVLinkedList element corresponding to the vertex pointed to by the edge */
        if (epPtr->edge->vertex1 != current->vertex) {
            wvllPtr = WVLLLookup(&workingGraph, epPtr->edge->vertex1);
        } else if (epPtr->edge->vertex2 != current->vertex) {
            wvllPtr = WVLLLookup(&workingGraph, epPtr->edge->vertex2);
        } else {
            printf("FATAL DIJKSTRA ERROR!\n");
        }

        /* Calculate the tentative distance to the vertex taking mode and special vertices into account */
        temp += epPtr->edge->weight + current->dist;
        if (wvllPtr->workVertex.vertex->type == 3 && current->vertex->type == 1) {
            temp += INITIAL_COST;
        } else if (wvllPtr->workVertex.vertex->type == 2 && current->vertex->type == 2) {
            counter++;
            tempPtr = current;
            while (tempPtr->previous->vertex->type == 2) {
                counter++;
                tempPtr = tempPtr->previous;
            }
            temp += epPtr->edge->weight * (counter - 1);
        }
        if (mode == 1 && (*wvllPtr)->workVertex.vertex->type - 1 == 1) {
            temp *= 100;
        } else if (mode == 2 && (*wvllPtr)->workVertex.vertex->type - 1 == 2) {
            temp *= 100;
        }

        /* Check if the calculated tentative distance is lower than the currently saved tentative distance.
         * Re-assign the distance and previous pointer if it is lower */
        if ((*wvllPtr)->workVertex.dist == -1 || temp < (*wvllPtr)->workVertex.dist) {
            (*wvllPtr)->workVertex.dist = temp;
            (*wvllPtr)->workVertex.previous = current;
        }
    } while ((epPtr = epPtr->nextEp));
}

WVLinkedList **WVLLLookup(WVLinkedList **workingGraph, Vertex *target) {
    WVLinkedList **current = workingGraph;
    while ((*current)->workVertex.vertex != target && (*current)->next) {
        current = &((*current)->next);
    }
    return current;
}

void WVLLDelete(WVLinkedList **targetPtr) {
    *targetPtr = (*targetPtr)->next;
}

WVLinkedList *WVLLSearch(WVLinkedList *workingGraph) {
    WVLinkedList *tempPtr = workingGraph, *retPtr = workingGraph;
    while (tempPtr) {
        if (tempPtr->workVertex.dist < retPtr->workVertex.dist) {
            retPtr = tempPtr;
        }
        tempPtr = tempPtr->next;
    }
    return retPtr;
}