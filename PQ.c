//Erik Rodriguez
//Priority Queue

#include <stdio.h>
#include <stdlib.h>

#define ARRIVAL
#define CPU_BEGIN
#define DISK_ARRIVAL
#define DISK1_BEGIN
#define DISK2_BEGIN
#define NETWORK_BEGIN

#define DISK1_FINISH
#define DISK2_FINISH
#define NETWORK_FINISH
#define CPU_FINISH

#define END

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
    priQue* heap = malloc(sizeof(PQueue));
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

    start -> job = 0;
    start -> time = 0;
    start -> type = 1;

    end -> job = 0;
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
    return (a -> time) - (b -> time)
}

//Returns 1 if queue is full, 0 if not
int isFull(priQueue* heap){

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

    cpuEvent* rm = heap -> event
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
    printf("JOB-SEQ: %-2d, TIME:%-5d type:%-2d\n", heap -> event -> jobSeq, heap -> event -> time,
                                                   heap -> event -> type);
    heap -> event++;
    }
}



















