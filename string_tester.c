#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "default_tests.h"
int main(int argc, char **argv){
    if(argc == 1){
        printf("AAA\n");
    }else{
        if(strcmp(argv[1], "default") == 0){
            default_tests();
        }
        if (strstr(argv[1], ".txt") != NULL){
            printf("BBB\n");
        }
    }
    return 0;
}