#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "XML.h"
#include "astar.h"


int main(void) {

    FILE *xml = fopen("handcrafted.xml", "r");
    Graph *graph = readXml(xml);
    Floor *floors = graph->floors;
    fclose(xml);
    int i;



    Vertex *v1 = GetVertexFromId("10011", graph);
    Vertex *v2 = GetVertexFromId("10016", graph);

    printf("%d\n", v1->vertexId);
    printf("%d\n", v2->vertexId);

    Path *path;


    path = AStar(v1, v2);



    printf("%u\n", path->weight);

    for (i = 0; i < path->numVertices; i++) {

        printf("%d\n", path->pathVerticeIds[i]);
    }

    free(graph);
    free(path);

    return 0;
}