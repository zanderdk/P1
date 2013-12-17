#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "XML.h"
#include "astar.h"
#include "dijkstra.h"

/**
return 0 for no valid route.
return 1 for a route can be found using one floor
return 2 for a route can be found crossing floors
*/

int validate(char *str1, char *str2, Vertex **vp1, Vertex **vp2, Graph *graph) {
    *vp1 = GetVertexFromId(str1, graph);
    *vp2 = GetVertexFromId(str2, graph);

    if ((*vp1) == NULL || (*vp2) == NULL)
        return 0;

    int max = graph->numOfFloors;
    if ((*vp1)->floorId <= max || (*vp2)->floorId <= max) {
        if ((*vp1)->floorId == (*vp2)->floorId)
            return 1;
        else
            return 2;
    }

    return 0;
}

void printPath(Path *path) {
    int i;
    printf("number of vertices: %d, total weight: %d \n",
           path->numVertices,
           path->weight);

    for (i = 0; i < path->numVertices; i++) {
        printf("%d \n", path->pathVerticeIds[i]);
    }
}

Path *recreconstruct(Path *p1, Path *p2, Path *p3, int t) {
    int ids;

    if (t == 1)
        ids = p1->numVertices + p2->numVertices + p3->numVertices;
    else if (t == 2)
        ids = p2->numVertices + p3->numVertices;
    else if (t == 3)
        ids = p2->numVertices;
    else
        ids = p1->numVertices + p2->numVertices;

    int size = ids * sizeof(int) + sizeof(Path);
    Path *ret = malloc(size);
    int *weights = (int *)(ret + 1);

    int i, j;
    int count = 0;
    int tcount = 0;

    ret->numVertices = ids;

    if (t == 3)
        ret->targetId = p2->targetId;
    else if (t == 2)
        ret->targetId = p3->targetId;
    else
        ret->targetId = p1->targetId;

    if (t == 1)
        ret->weight = p1->weight + p2->weight + p3->weight;
    else if (t == 2)
        ret->weight = p2->weight + p3->weight;
    else if (t == 3)
        ret->weight = p2->weight;
    else
        ret->weight = p1->weight + p2->weight;

    ret->pathVerticeIds = weights;

    if (t != 2 && t != 3)
        for (i = 0; i < p1->numVertices; i++) {
            weights[i] = p1->pathVerticeIds[i];
            count++;
        }

    tcount = count;

    for (i = 0; i < p2->numVertices; i++) {
        weights[tcount + i] = p2->pathVerticeIds[i];
        //printf("%d\n", tcount + i);
        count++;
    }

    tcount = count;

    if (t != 0 && t != 3) {
        for (i = 0; i < p3->numVertices; i++) {
            weights[tcount + i] = p3->pathVerticeIds[i];
            count++;
        }
    }

    free(p1);
    free(p3);

    return ret;
}

Path *findOptimalPath(Vertex *scr, Vertex *dst, int mode, int sameFloor, Graph *graph, SourcePaths *srcPath, int paths) {
    Path *buf;
    Vertex *bufVp;
    SourcePaths *sp;
    Path *Lbuf;

    int count = 0;
    int i, j, k;
    int state = 1;

    int exits;
    unsigned currentCost;

    unsigned int record = (unsigned int)(-1);
    Path *recPath1;
    Path *recPath2;
    Path *recPath3;


    if (sameFloor == 1) {
        int floor = scr->floorId - 1;
        return AStar(scr, dst, graph->floors[floor].amountOfVertecies);
    } else if (sameFloor == 2) {
        int startFloor = scr->floorId - 1;
        int endFloor = dst->floorId - 1;
        //printf("%d \n", endFloor);


        for (i = 0; i < paths; i++) {
            sp = &srcPath[i];
            if (GetFloor(sp->sourceId) - 1 == startFloor) {

                exits = sp->sourceId;
                bufVp = GetVertexFromIdInt(exits, graph);

                if (scr->type == 1) {
                    buf = AStar(scr, bufVp, graph->floors[startFloor].amountOfVertecies);
                    currentCost = buf->weight;
                } else
                    state = 2;


                for (j = 0; j < sp->numPaths; j++) {

                    if (scr->type > 1 && dst->type > 1)
                        state = 3;


                    if ((GetFloor(sp->paths[j].targetId) - 1) == endFloor) {

                        Vertex *source = GetVertexFromIdInt(sp->paths[j].targetId, graph);

                        if (source->vertexId == dst->vertexId && state != 3) {
                            recPath1 = buf;
                            recPath2 = &(sp->paths[j]);
                            recPath3 = NULL;
                            return recreconstruct(recPath1, recPath2, recPath3, 0);
                        }

                        if (state != 3)
                            Lbuf = AStar(source, dst, graph->floors[endFloor].amountOfVertecies);

                        currentCost += Lbuf->weight;
                        currentCost += sp->paths[j].weight;

                        if (currentCost < record) {
                            recPath1 = buf;
                            recPath2 = &(sp->paths[j]);
                            recPath3 = Lbuf;
                        }
                    }
                }

            }
        }

        return recreconstruct(recPath1, recPath2, recPath3, state);

    }

}


int main(int argc, char const *argv[]) {
    Graph *graph;
    SourcePaths *All, *noStairs, *noElevators;
    int countAll, countNoSrairs, countNoElevators;
    Vertex *scr, *dst;
    int success = 0;
    int mode = 0;
    Path *route;
    char idStr1[10], idStr2[10];
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
            printf("Enter first verted id: \n");
            scanf("%s", idStr1);
            printf("Enter Next verted id: \n");
            scanf("%s", idStr2);
            printf("Enter mode: \n");
            scanf("%d", &mode);
            success = validate(idStr1, idStr2, &scr, &dst, graph);
        } else {
            strncpy(idStr1, argv[2], 10);
            strncpy(idStr2, argv[3], 10);
            sscanf(argv[4], "%d", &mode);
            success = validate(argv[2], argv[3], &scr, &dst, graph);
            flag = 1;
        }

        if (success >= 1) {
            printf("Getting most optimal path from %s to %s \n", idStr1, idStr2);

            if (mode == 0)
                route = findOptimalPath(scr, dst, mode, success, graph, All, countAll);
            else if (mode == 1)
                route = findOptimalPath(scr, dst, mode, success, graph, noStairs, countNoSrairs);
            else
                route = findOptimalPath(scr, dst, mode, success, graph, noElevators, countNoElevators);

            printPath(route);

            //free(route);

        } else {
            printf("route cant be found, check Vertex ids.\n");
        }


    } while (1);

    return 0;
}