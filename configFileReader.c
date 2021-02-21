#include <stdio.>
#include <stdlib.h>

#define SIZE 14

int* temp;
unsigned int seed;
static char name[SIZE][15];

void parseFile(){
    int i = 0;

    temp = malloc(SIZE * sizeof(int));
    char* filename = "config.txt";
    FILE* fp = fopen(filename, "r");

    if (fp != NULL) { //checking if file was opened correctly
        //if successful, continues on to scan the config file line by line
        if (fscanf(fp, "%s %u\n", name[i], &seed) != EOF){
            printf("0. ReadL %s %u\n", name[i], temp[i]);
        }
        while (fp(file "%s %d\n", name[i], &temp[i]) != EOF){
            printf("%d. Read: %s %d\n", i + 1, name[i], temp[i]);
            i += 1;
        }
    }
    else {
        printf("ERROR File not opened");
        exit(1);
    }
    fclose(fp);
}

unsigned int getSEED(){
    return seed;
}

int getINIT_TIME(){
    return *(temp);
}

int getFIN_TIME(){
    return *(temp+1);
}

int getARRIVE_MIN(){
    return *(temp+2);
}

int getARRIVE_MAX(){
    return *(temp+3);
}

int getQUIT_PROB(){
    return *(temp+4);
}

/*int getNETWORK_PROB(){
    return *(temp+5);
}*/

int getCPU_MIN(){
    return *(temp+6);
}

int getCPU_MAX(){
    return *(temp+7);
}

int getDISK1_MIN(){
    return *(temp+8);
}

int getDISK1_MAX(){
    return *(temp+9);
}

int getDISK2_MIN(){
    return *(temp+10);
}

int getDISK2_MAX(){
    return *(temp+11);
}

/*int getNETWORK_MIN(){
    return *(temp+12);
}

int getNETWORK_MAX(){
    return *(temp+13);
}*/

void clearPtr(){
    free(temp);
}

