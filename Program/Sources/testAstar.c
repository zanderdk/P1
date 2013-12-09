#include <stdlib.h>
#include <stdio.h>
#include "XML.h"
#include "astar.h"


int main(void) {

    FILE *xml = fopen("handcrafted.xml", "r");

    Floor *floors = readXml(xml);
    fclose(xml);




    Vertex *v1 = floors[0].vp;
    Vertex *v2 = v1->nextVp->nextVp->nextVp->nextVp->nextVp;

    printf("%d\n", v1->vertexId);
    printf("%d\n", v2->vertexId);

    Path *path = (Path *) malloc(sizeof(Path));

    AStar(v1, v2, path);

    printf("%d\n", path->weight);

    for (int i = 0; i < path->numVertices; i++) {

        printf("%d\n", path->pathVerticeIds[i]);
    }



    return 0;
}