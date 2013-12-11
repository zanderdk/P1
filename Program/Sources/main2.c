#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "XML.h"
#include "astar.h"
#include "dijkstra.h"

#define MBYTE 1024*1024
#define NUMBER_OF_EXITS 30


Vertex **GetExitVertecies(Vertex *start, int *c)
{
	int count = 0;
	int max = 10;
	Vertex **vp = calloc(10, sizeof(Vertex *));
	Vertex *v = start;

	do{
		v = v->nextVp;
		if(v->type > 1){
			vp[count] = v;
			count++;
		}

		if(count > max-2){
			max += 10;
			vp = realloc(vp, sizeof(Vertex *)*max);
		}


	}while(v->nextVp != NULL);

	
	return vp;
}

Path *OptimalPath(Vertex *start, Vertex *dest, Graph graph, int mode) {

	Path *buf;

    if (start->floorId == dest->floorId) {
        //return AStar(start, dest);
    } else {
        if (mode == 2) {


        } else if (mode) {



        } else {

        }
    }
}



int main(int argc, char const *argv[]) {

    FILE *fp = fopen(argv[1], "r");
    Graph *graph = readXml(fp);
    fclose(fp);
    char id1[10], id2[10];
    Vertex *v1, *v2;

    SourcePaths *noPref, *noStairs, *noElevators;

    /*  PreComputePaths(graph, &noPref, 0);
        PreComputePaths(graph, &noPref, 1);
        PreComputePaths(graph, &noPref, 2);*/

    printf("Graph has: \n Floors: %d\n Vertices: %d\n",
           graph->numOfFloors,
           graph->numOfVertices);
    int c;


    double t = DistBetween(GetVertexFromId("10011", graph), GetVertexFromId("10017", graph));
    printf("");
    /*

    while (1) {
        printf("Enter first Vertex id: \n");
        scanf("%9s", id1);
        printf("Enter secound Vertex id: \n");
        scanf("%9s", id2);

        v1 = GetVertexFromId("10011", graph);
        v2 = GetVertexFromId("10012", graph);



        break;
    }

	*/

    return 0;
}