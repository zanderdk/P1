#include <stdio.h>
#include <stdlib.h>
#include "lala.h"

#define nOfVs 10

int main(int argc, char const *argv[]) {
    Graph *graph = createGraph(nOfVs); // 5 Vertices
    Coordinate coords[8]; // 5 Vertices
    coords[0].x = 3;
    coords[0].y = 6;
    coords[0].flr = 7;
    coords[1].x = 4;
    coords[1].y = 3;
    coords[1].flr = 2;
    coords[2].x = 7;
    coords[2].y = 1;
    coords[2].flr = 2;
    coords[3].x = 6;
    coords[3].y = 1;
    coords[3].flr = 4;
    coords[4].x = 2;
    coords[4].y = 1;
    coords[4].flr = 8;

    addEdge(graph, 0, 1, 3);
    addEdge(graph, 1, 2, 4);
    addEdge(graph, 1, 3, 2);
    addEdge(graph, 2, 3, 3);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 4, 0, 4);
    addEdge(graph, 4, 5, 1);
    addEdge(graph, 5, 6, 1);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 7, 8, 1);
    addEdge(graph, 8, 9, 1);
    giveCoords(graph, coords);

    /*
      O----(3)----1
      |           | \
      |           | (4)
      |           |   \
     (4)         (2)   2
      |           |   /
      |           | (3)
      |           | /
      4----(2)----3
    */

    printAdjList(graph);

    Path *path = (Path *) malloc(sizeof(Path));

    path->pathVertexIds = (int *) malloc(nOfVs * sizeof(int));

    int i;
    for (i = 0; i < nOfVs ; ++i ) {
        path->pathVertexIds[i] = 999;
    }

    int source = 2;
    int target = 7;

    int numOfPath = Dijkstra(graph, source, target, path);

    printf("From %d ", source);

    PrintList(path->pathVertexIds, numOfPath);

    printf("-> %d ", target);

    printf("Cost: %d\n\n", path->weight);

    return 0;
}

Vertex *addVertex(int id) {
    Vertex *newVertex = (Vertex *) malloc(sizeof(Vertex));
    newVertex->id = id;
    newVertex->next = NULL;
    return newVertex;
}

void addEdge(Graph *graph, int source, int destination, int weight) {

    Vertex *newVertex = addVertex(destination);
    newVertex->next = graph->array[source].head;
    newVertex->weight = weight;
    graph->array[source].head = newVertex;

    newVertex = addVertex(source);
    newVertex->next = graph->array[destination].head;
    newVertex->weight = weight;
    graph->array[destination].head = newVertex;
}

Graph *createGraph(int numOfVertices) {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->numOfVertices = numOfVertices;
    graph->array = (AdjList *) malloc(numOfVertices * sizeof(AdjList));

    int i;
    for (i = 0; i < numOfVertices; ++i)
        graph->array[i].head = NULL;

    return graph;
}

void giveCoords(Graph *graph, Coordinate *coords) {
    int i;
    for (i = 0; i < graph->numOfVertices; ++i) {
        Vertex *pCrawl = graph->array[i].head;
        pCrawl->location.x = coords[i].x;
        pCrawl->location.y = coords[i].y;
        pCrawl->location.flr = coords[i].flr;
    }
}

void printAdjList(Graph *graph) {
    int i;
    for (i = 0; i < graph->numOfVertices; ++i) {
        Vertex *pCrawl = graph->array[i].head;
        printf("Vertex: %d (%d,%d,%d) connects to:\n", i, pCrawl->location.x, pCrawl->location.y, pCrawl->location.flr);
        while (pCrawl) {
            printf("%d with the weight of: %d\n", pCrawl->id, pCrawl->weight);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

