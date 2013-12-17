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

Path *recreconstruct(Path *p1, Path *p2, Path *p3) {
    int ids = p1->numVertices + p2->numVertices + p3->numVertices - 1;
    int size = ids * sizeof(int) + sizeof(Path);
    Path *ret = malloc(size);
    int *weights = (int *)(ret + 1);

    int i, j;
    int count = 0;
    int tcount = 0;

    ret->numVertices = ids;
    ret->targetId = p1->targetId;
    ret->weight = p1->weight + p2->weight + p3->weight;
    ret->pathVerticeIds = weights;

    for (i = 0; i < p1->numVertices; i++) {
        weights[i] = p1->pathVerticeIds[i];
        count++;
    }
    tcount = count;

    for (i = 0; i < p2->numVertices; i++) {
        weights[tcount + i] = p2->pathVerticeIds[i];
        count++;
    }

    tcount = count;

    for (i = 0, j = p3->numVertices - 2; j >= 0; i++, j--) {
        weights[tcount + i] = p3->pathVerticeIds[j];
        count++;
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
                buf = AStar(scr, bufVp, graph->floors[startFloor].amountOfVertecies);
                currentCost = buf->weight;

                for (j = 0; j < sp->numPaths; j++) {
                    Vertex *source = GetVertexFromIdInt(sp->paths->targetId, graph);
                    Lbuf = AStar(dst, source, graph->floors[endFloor].amountOfVertecies);

                    currentCost += Lbuf->weight;
                    currentCost += sp->paths[j].weight;
                    if (currentCost < record) {
                        recPath1 = buf;
                        recPath2 = &(sp->paths[j]);
                        recPath3 = Lbuf;
                    } else {
                        free(buf);
                        free(Lbuf);
                    }
                }

            }
        }

        return recreconstruct(recPath1, recPath2, recPath3);

    }

}


int main(int argc, char const *argv[]) {
    Graph *graph;
    SourcePaths *All, *noStairs, *noElevators;
    int countAll, countNoSrairs, countNoElevators;
    Vertex *scr, *dst;
    int success = 0;
    Path *route;
    char idStr1[10], idStr2[10];

    FILE *fp = fopen(argv[1], "r");
    graph = readXml(fp);
    fclose(fp);

    printf("Graph has: \n Floors: %d\n Vertices: %d\n",
           graph->numOfFloors,
           graph->numOfVertices);

    countAll = PreComputePaths(graph, &All, 0);
    countNoSrairs = PreComputePaths(graph, &noStairs, 1);
    countNoElevators = PreComputePaths(graph, &noElevators, 2);

    if (argc < 4) {
        printf("Enter first verted id: \n");
        scanf("%9s", idStr1);
        printf("Enter Next verted id: \n");
        scanf("%9s", idStr2);
        success = validate(idStr1, idStr2, &scr, &dst, graph);
    } else {
        strncpy(idStr1, argv[2], 10);
        strncpy(idStr2, argv[3], 10);
    }

    success = validate(argv[2], argv[3], &scr, &dst, graph);

    if (success >= 1)
        printf("Getting most optimal path from %s to %s \n", idStr1, idStr2);
    else {
        printf("route cant be found, check Vertex ids.\n");
        exit(1);
    }

    route = findOptimalPath(scr, dst, 0, success, graph, All, countAll);

    printPath(route);

    free(route);

    return 0;
}