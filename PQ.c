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

    int job;
    int type;
    int time;
}cpuEvent;

typedef struct priorityQueue{

    cpuEvent* event;
    int size;
    int maxSize;
}priQue;

priQue* initPriorityQueue(){

    
}
