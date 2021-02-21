//Erik Rodriguez
//Priority Queue

#include <stdio.h>
#include <stdlib.h>

#define ARRIVAL 1
#define CPU_BEGIN 2
#define DISK_ARRIVAL 3
#define DISK1_BEGIN 4 
#define DISK2_BEGIN 5
//#define NETWORK_BEGIN 6

#define DISK1_FINISH 7
#define DISK2_FINISH 8
//#define NETWORK_FINISH 9 
#define CPU_FINISH 10

#define END 11

typedef struct eventStruct {

    int seq;
    int type;
    int time;
}cpuEvent;

typedef struct priorityQueue{

    cpuEvent* event;
    int size;
    int max;
}priQue;

priQue* initPriorityQueue(){

    //Initialization of the priority queue heap and cpu beginning and ending events
    priQue* heap = malloc(sizeof(priQue));
    cpuEvent* start = malloc(sizeof(cpuEvent));
    cpuEvent* end = malloc(sizeof(cpuEvent));

    //simple malloc check, used moreso for debugging
    if(heap == NULL || start == NULL || end == NULL){
        printf("Memory allocation failure");
        exit(1);
    }

    //These are the values that the heap and events get initialized with
    heap -> max = 10;
    heap -> size = 2;

    start -> seq = 0;
    start -> time = 0;
    start -> type = 1;

    end -> seq = 0;
    end -> time = 10000;
    end -> type = 8;

    heap -> event = start;
    heap -> event[1] = *end;

    return heap;    
}

//time comparison/difference function
int compare(const void *x, const void *y){

    cpuEvent* a = (cpuEvent*) x;
    cpuEvent* b = (cpuEvent*) y;
    return (a -> time) - (b -> time);
}

//Returns 1 if queue is full, 0 if not
int isFull(priQue* heap){

    if(heap -> max == heap -> size){
    return 1;
    }
    return 0;
}

//Pushes an event to the PQ, PQ takes its time and sets it as its own to "advance" time
//qsort is an array sorting function, used to sort the heap after changes are made
void pushToQue(priQue* heap, cpuEvent* eve){

    if(isFull(heap)){
        return;
    }

    int time = eve -> time;
    heap -> size += 1;
    heap -> event[heap -> size - 1] = *eve;
    qsort(heap -> event, heap -> size, sizeof(cpuEvent), compare);
}

//Pops the top element in the heap, IE removes it
cpuEvent* popEve(priQue* heap){

    cpuEvent* rm = heap -> event;
    heap -> event = &heap -> event[1];
    heap -> size -= 1;
    return rm;
}

//Function to clear the whole PQ, used moreso for debugging
void clearPriQue(priQue* heap){
    free(heap);
}

//Simple check to see if the heap is empty (0 indicates empty)
int isEmpty(priQue* heap){

    return heap -> size;
}

//Prints the current queue event
void printQue(priQue* heap){

    for(int i = 0; i < heap -> size; i++){
    printf("JOB-SEQ: %-2d, TIME:%-5d type:%-2d\n", heap -> event -> seq, heap -> event -> time,
                                                   heap -> event -> type);
    heap -> event++;
    }
}



















