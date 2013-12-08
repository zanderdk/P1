#include "XML.h"
#include "astar.h"

int main(void) {
    FILE *xml = fopen("realtest.xml", "r");

    Floor *floors = readXml(xml);
    fclose(xml);




    Vertex *v1 = floors[0].vp;
    Vertex *v2 = v1->nextVp;

    printf("%d\n", v1->vertexId);
    printf("%d\n", v2->vertexId);

    Path *path = aStar(v1, v2);

    printf("%d\n", path->weight);

    for (int i = 0; i < path->numVertices; i++) {
        if (path->pathVerticeIds[i] != 0) {
            printf("%d <-", path->pathVerticeIds[i]);
        }


    }



    return 0;
}