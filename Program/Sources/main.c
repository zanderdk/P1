#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define MBIT 1048576
#define NUMBER_OF_EXITS 30

path RunAStar();
Path optimal(char *srcId, char *targetId);

int main(int argc, char const *argv[]) {

    FILE *inputfile = fopen("handcrafted.xml", "r");

    Floor *floors = readXml(inputfile);
    fclose(inputfile);


    int choice;
    char srcId[];
    char targetId[];

    Path *paths = (Path *)malloc(MBIT);

    Path *aStarPath = (Path *)malloc(sizeof(Path));

    Vertex *vertices = (vertex *)malloc(sizeof(30 * Vertex *));


    //Continues while loops, keeps prompting user
    while (1) {
        system("clear");

        printf("\nInput [srcId]: ");
        scanf("%.9s", &srcId);
        printf("\nInput [targetId]: ");
        scanf("%.9s", &targetId);
        printf("Success!\n");

        printf("1: Find optimal path preferring stairs\n"
               "2: Find optimal path preferring elevator\n"
               "3: Find optimal path\n"
               "\n"
               "Choice: "
              );

        //Scanf for users input
        scanf("%d", &choice);
        //If user input a char not an int make sure to empty buffer
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            elevator();
            break;
        case 2:
            stairs();
            break;
        case 3:
            optimal(srcId, targetId);
            break;
        default:
            printf("Unexpected input\n");
        }

        printf("Press any key to continue\n");
        while (getchar() != '\n');
        getchar();
    }

    return 0;
}

int optimal(char *srcId, char *targetId) {
    Vertex *start = GetVertexFromId(srcId);
    Vertex *target = GetVertexFromId(targetId);
    int type, i, id, exits[NUMBER_OF_EXITS];

    if ((strncmp(srcId += sizeof(char), targetId += sizeof(char), 3)) == 0) {
        aStar(start, target, *aStarPath);
        PrintPath(aStartPath); //mangler!
    } else {
        for (i = 0; i < floors[start.floorId - 1].amountOfVertices; ++i) {
            type = floors[start.floorId - 1].vp->type;
            if (type == 2 || type == 3) {
                exits[i++] = id;
            }

        }
        for (i = 0; i < NUMBER_OF_EXITS; ++i) {

        }
        aStar(start,)
    }
}

