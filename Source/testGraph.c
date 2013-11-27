#include <stdio.h>
#include <stdlib.h>

typedef struct Coordinate {
  int x;
  int y;
  int flr;
} Coordinate;

typedef struct Vertex {
  Coordinate location;
  char type;
  char id;
  int weight;
  struct Vertex *next;
} Vertex;

typedef struct AdjList {
  Vertex *startOfAdjList;
} AdjList;

typedef struct Graph {
  int numOfVertices;
  AdjList *array;
} Graph;

Vertex *addVertex(int id); //
void addEdge(Graph *graph, int source, int destination, int weight); // Adds an edge to an undirected graph
Graph *createGraph(int numOfVertices);
void printAdjList(Graph *graph);
void giveCoords(Graph *graph, Coordinate *coords);

int main(int argc, char const *argv[]) {
  Graph *graph = createGraph(5); // 5 Vertices
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
  newVertex->next = graph->array[source].startOfAdjList;
  newVertex->weight = weight;
  graph->array[source].startOfAdjList = newVertex;

  newVertex = addVertex(source);
  newVertex->next = graph->array[destination].startOfAdjList;
  newVertex->weight = weight;
  graph->array[destination].startOfAdjList = newVertex;
}

Graph *createGraph(int numOfVertices) {
  Graph *graph = (Graph *) malloc(sizeof(Graph));
  graph->numOfVertices = numOfVertices;
  graph->array = (AdjList *) malloc(numOfVertices * sizeof(AdjList));

  int i;
  for (i = 0; i < numOfVertices; ++i)
    graph->array[i].startOfAdjList = NULL;

  return graph;
}

void giveCoords(Graph *graph, Coordinate *coords) {
  int i;
  for (i = 0; i < graph->numOfVertices; ++i) {
    Vertex *pointerCrawl = graph->array[i].startOfAdjList;
    pointerCrawl->location.x = coords[i].x;
    pointerCrawl->location.y = coords[i].y;
    pointerCrawl->location.flr = coords[i].flr;
  }
}

void printAdjList(Graph *graph) {
  int i;
  for (i = 0; i < graph->numOfVertices; ++i) {
    Vertex *pointerCrawl = graph->array[i].startOfAdjList;
    printf("Vertex: %d (%d,%d,%d) connects to:\n", i, pointerCrawl->location.x, pointerCrawl->location.y, pointerCrawl->location.flr);
    while (pointerCrawl) {
      printf("%d with the weight of: %d\n", pointerCrawl->id, pointerCrawl->weight);
      pointerCrawl = pointerCrawl->next;
    }
    printf("\n");
  }
}

