#include <stdio.>
#include <stdlib.h>

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
        while (fscanf(file "%s %d\n", name[i], &temp[i]) != EOF){
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
