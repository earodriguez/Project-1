#include <stdio.h>
#include <stdlib.h>

//node struct used for the queue "object"
typedef struct Node {
    int curPos;
    int seq[10];
    int size;
} Node;

void queueInit(Node *queue) { //initializes all queue elements to 0

    if (queue == NULL){ //If the queue does not exist, exit prematurely
        return;
    }

    queue-> size = 10;
    queue-> curPos = 0;

    for (int i = 0; i < queue -> size; i++){
        (queue -> seq)[i] = 0;
    }
}


int queueAdd(Node *queue, int deviceSeq) {//Adds an element from a given job/device to the queue

    int size = queue -> size;
    int *devSeq = queue -> seq;

    if(queue -> curPos == size){ //If the current queue is full, exit prematurely
        return 0;
    }

    devSeq[queue -> curPos] = deviceSeq;
    queue -> curPos += 1;
    return 1;
}

void queueMoveUp(int *queSeq, int *size){

    //Modifies the current sequence by essentially moving up all the
    //elements by one, then setting the last element to 0 and ticking the size down
    //by one
    for (int i = 0; i < *size - 1; i++){
        queSeq[i] = queSeq[i + 1];
    }
    queSeq[*size - 1] = 0;
    *size -= 1;
}

int queueRm(Node *queue) {

    if (queue == NULL){
    return 0;
    }

    int rmEle = queue -> seq[0];
    queueMoveUp(queue -> seq, &queue -> curPos);
    return rmEle;
}

void queuePrint(Node *queue){
    
    for (int i = 0; i < queue -> size; i++){
    printf("Job: %d\t\n", queue -> seq[i]);
    }

}
