#include <stdio.h>
#include <stdlib.h>

#define SIZE 15

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
            printf("0. Read: %s %u\n", name[i], temp[i]);
        }
        while (fscanf(fp, "%s %d\n", name[i], &temp[i]) != EOF){
            printf("%d. Read: %s %d\n", i + 1, name[i], temp[i]);
            i += 1;
        }
    }
    else {
        printf("ERROR File not opened\n");
        exit(1);
    }
    printf("Config scanned successfully\n");
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

int getNETWORK_PROB(){
    return *(temp+6);
}

int getCPU_MIN(){
    return *(temp+7);
}

int getCPU_MAX(){
    return *(temp+8);
}

int getDISK1_MIN(){
    return *(temp+9);
}

int getDISK1_MAX(){
    return *(temp+10);
}

int getDISK2_MIN(){
    return *(temp+11);
}

int getDISK2_MAX(){
    return *(temp+12);
}

int getNETWORK_MIN(){
    return *(temp+13);
}

int getNETWORK_MAX(){
    return *(temp+14);
}

void clearPtr(){
    free(temp);
}

