#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "XML.h"
#include "astar.h"
#include <time.h>


int main(void) {

    FILE *xml = fopen("handcrafted.xml", "r");
    Graph *graph = readXml(xml);
    Floor *floors = graph->floors;
    fclose(xml);
    int i;
    srand(time(NULL));
    int count = 0;
    while (count < 1000000) {

        char stid1[6] = "10011";
        char stid2[6] = "10016";

        /*do {
            stid1[4] = ((rand() % 6) + 1) + '0';
            stid2[4] = ((rand() % 6) + 2) + '0';
        } while (strcmp(stid2, stid1) == 0);*/


        //printf("%s \n", stid1);

        Vertex *v1 = GetVertexFromId(stid1, graph);
        Vertex *v2 = GetVertexFromId(stid2, graph);

        /*
                printf("%d\n", v1->vertexId);
                printf("%d\n", v2->vertexId);*/

        Path *path;

        path = AStar(v1, v2, graph->floors[0].amountOfVertecies);

        //printf("weight %d\n", path->weight);

        /*for (i = 0; i < path->numVertices; i++) {

            printf("%d\n", path->pathVerticeIds[i]);
        }*/

        //printf("%d \n", count++);
        count++;

        free(path);
        //sleep(1);
    }
    printf("finished\n");

    free(graph);


    return 0;
}