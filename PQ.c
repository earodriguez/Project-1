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

    if(heap == NULL || start == NULL || end == NULL){
        printf("Memory allocation failure");
        exit(1);
    }

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

int cmp(const void *x, const void *y){

    cpuEvent* a = (cpuEvent*) x;
    cpuEvent* b = (cpuEvent*) y;
    return (a -> time) - (b -> time)
}


