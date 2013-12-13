#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "XML.h"
#include "astar.h"
#include "dijkstra.h"

#define MBYTE 1024*1024
#define NUMBER_OF_EXITS 30


int main(int argc, char const *argv[]) {

    FILE *fp = fopen(argv[1], "r");
    Graph *graph = readXml(fp);
    fclose(fp);
    SourcePaths *test;
    int i;
    printf("Graph has: \n Floors: %d\n Vertices: %d\n",
           graph->numOfFloors,
           graph->numOfVertices);

    PreComputePaths(graph, &test, 0);

    for(i = 0; i < test->paths[0].numVertices; i++)
        printf("%u\n", *(test->paths[0].pathVerticeIds));

    return 0;
}