#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char const *argv[]) {

    int choice;
    int srcFloor, srcId;
    int destFloor, destId;

    //Continues while loops, keeps prompting user
    while (1) {
        system("clear");
        printf("1: Find optimal path\n"
               "2: Pre calculate paths\n"
               "3: Generate graph\n"
               "\n"
               "Choice: "
              );

        //Scanf for users input
        scanf("%d", &choice);
        //If user input a char not an int make sure to empty buffer
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            printf("\nInput [srcFloor,srcId]: ");
            scanf("%d,%d", &srcFloor, &srcId);
            printf("\nInput [destFloor,destId]: ");
            scanf("%d,%d", &destFloor, &destId);
            printf("Success!\n");
            break;
        case 2:
            PreCalc();
            break;
        case 3:
            GenGraph();
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