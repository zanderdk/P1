#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "XML.h"
#include "astar.h"
#include "dijkstra.h"
#include "main_help.h"

int main(int argc, char *argv[]) {
    Graph *graph;
    SourcePaths *All, *noStairs, *noElevators;
    int countAll, countNoSrairs, countNoElevators;
    Vertex *scr, *dst;
    int success = 0;
    int mode = NO_MODE;
    Path *route;
    char idStr1[ID_CHAR_SIZE], idStr2[ID_CHAR_SIZE];
    int flag = 0;

    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Cant read file.\n");
        exit(1);
    }

    graph = readXml(fp);
    fclose(fp);

    printf("Graph has: \n Floors: %d\n Vertices: %d\n",
           graph->numOfFloors,
           graph->numOfVertices);

    countAll = PreComputePaths(graph, &All, 0);
    countNoSrairs = PreComputePaths(graph, &noStairs, 1);
    countNoElevators = PreComputePaths(graph, &noElevators, 2);


    do {
        if (argc < 5 || flag) {
            printf("Enter start vertex id: \n");
            scanf("%s", idStr1);
            printf("Enter destination vertex id: \n");
            scanf("%s", idStr2);
            printf("Enter mode.\n"
                   "0: path may contain both stairs and elevators.\n"
                   "1: path may not contain stairs.\n"
                   "2: path may not contain elevators.\n");
            scanf("%d", &mode);
            success = validate(idStr1, idStr2, &scr, &dst, graph);
        } else {
            strncpy(idStr1, argv[2], ID_CHAR_SIZE);
            strncpy(idStr2, argv[3], ID_CHAR_SIZE);
            sscanf(argv[4], "%d", &mode);
            success = validate(argv[2], argv[3], &scr, &dst, graph);
            flag = 1;
        }

        if (success >= 1) {
            printf("Getting most optimal path from %s to %s. \n", idStr1, idStr2);

            if (mode == NO_MODE)
                route = findOptimalPath(scr, dst, mode, success, graph, All, countAll);
            else if (mode == NO_STAIRS)
                route = findOptimalPath(scr, dst, mode, success, graph, noStairs, countNoSrairs);
            else if (mode == NO_ELEVATORS)
                route = findOptimalPath(scr, dst, mode, success, graph, noElevators,
                                        countNoElevators);
            else {
                printf("Wrong mode.\n");
            }
            printPath(route);

            free(route);

        } else {
            printf("route cant be found, check Vertex ids.\n");
        }


    } while (1);

    return 0;
}