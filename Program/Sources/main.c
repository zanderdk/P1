#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main(int argc, char const *argv[]) {

    int choice;
    int srcId;
    int targetId;

    //Continues while loops, keeps prompting user
    while (1) {
        system("clear");

        printf("\nInput [srcId]: ");
        scanf("%d", &srcId);
        printf("\nInput [targetId]: ");
        scanf("%d", &targetId);
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
            optimal();
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