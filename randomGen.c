#include <stdio.h>

int randNum (int min, int max){

    if( (max - min) < 0 || max < 0 || min < 0){
        printf("Random parameters invalid");
    }
    return rand() % (max - min + 1) + min;
}


int probGet (int prob){ //Calculates the chance of a process going to disk/network

    // returns 0 for false, 1 for true
    if(prob < 0 || prob > 100){
        printf("randNum: probability parameter invalid");
        exit(1);
    }

    int i = randNum(1, 100);

    if(i <= prob){
        return 0;
    }
    return 1;
}
