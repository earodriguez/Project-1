//Erik Rodriguez
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#include"PQ.c"
#include"queue.c"
#include"randomGen.c"
#include"configFileReader.c"

#define IDLE 0
#define BUSY 1
#define QUEUE_SIZE 10

int CPU_STATE = 0;
int TIME = 0;
int DISK1_STATUS = 0;
int DISK2_STATUS = 0;
int NETWORK_STATUS = 0;

int INI_TIME;
int FIN_TIME;
int ARRIVE_MIN;
int ARRIVE_MAX;
int QUIT_PROB;
int NETWORK_PROB;
int CPU_MIN;
int CPU_MAX;
int DISK1_MIN;
int DISK1_MAX;
int DISK2_MIN;
int DISK2_MAX;
int NETWORK_MIN;
int NETWORK_MAX;

Node QUE_CPU;
Node QUE_DISK1;
Node QUE_DISK2;
Node QUE_NETWORK;

int main(){

    parseFile();
    srand(getSeed());
    cpuEvent* task;
    priQue* eveQue = initPriorityQueue()

    queueInit(&queue_CPU);
    queueInit(&queue_DISK1):
    queueInit(&queue_DISK2);
    queueInit(&queue_NETWORK);

    FILE* fileOut = fopen("log.txt", "w");
    fclose(fileOut);

    cpuEvent job1;
    job1.seq = 1;
    job1.type = ARRIVAL;
    job1.time = 0;
    push(eveQue, &job1);


}
