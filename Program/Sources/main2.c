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
    int i, i2, i3;
    printf("Graph has: \n Floors: %d\n Vertices: %d\n",
           graph->numOfFloors,
           graph->numOfVertices);

    PreComputePaths(graph, &test, 0);

    getchar();
    for (i = 0; i < 11; i++) {
        printf("                 -----------------------------------\n");
        for (i2 = 0; i2 < 10; ++i2) {
            printf("From: %u\nTo: %u\n", test[i].sourceId, test[i].paths[i2].targetId);
            for (i3 = 0; i3 < test[i].paths[i2].numVertices; ++i3) {
                printf("%u\n", test[i].paths[i2].pathVerticeIds[i3]);
            }
            printf("\n");
        }
    }

    return 0;
}