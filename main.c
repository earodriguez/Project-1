//Erik Rodriguez

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

//File imports
#include"PQ.c"
#include"queue.c"
#include"randomGen.c"
#include"configFileReader.c"

//Global definitions
#define IDLE 0
#define BUSY 1
#define QUEUE_SIZE 10

void PROC_ARRIVE (cpuEvent* task, priQue* eveQue);
void PROC_CPU (cpuEvent* task, priQue* eveQue);
void PROC_DISK(cpuEvent* task, priQue* eveQue);
void readFile();

//Global variables
int CPU_STATE = 0;
int GTIME = 0;
int DISK1_STATE = 0;
int DISK2_STATE = 0;
//int NETWORK_STATE = 0;

int INI_TIME;
int FIN_TIME;
int ARRIVE_MIN;
int ARRIVE_MAX;
int QUIT_PROB;
//int NETWORK_PROB;
int CPU_MIN;
int CPU_MAX;
int DISK1_MIN;
int DISK1_MAX;
int DISK2_MIN;
int DISK2_MAX;
//int NETWORK_MIN;
//int NETWORK_MAX;

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

    while(isEmpty(eveQue) && (GTIME < FIN_TIME)){

    task = pop(eveQue);
        switch (task -> type){
            case ARRIVAL;
                GTIME = task -> time;
                PROC_CPU(task, eveQue);
                break;

            case CPU_BEGIN:
                PROC_CPU(task, eveQue);
                break;

            case CPU_FINISH:
                GTIME = task->time;
                PROC_CPU(task, eveQue);
                break;

            case DISK_ARRIVAL:
                GTIME = task->time;
                PROC_DISK(task, eveQue);
                break;

            case DISK1_BEGIN:
            case DISK2_BEGIN:
                PROC_DISK(task, eveQue);
                break;

            case DISK1_FINISH:
            case DISK2_FINISH:
                timeGlobal = task->time;
                PROC_DISK(task, EventQueue);
                break;

            case 7:
            {
                FILE* fp = fopen("log.txt", "a");
                fprintf(fp, "At time %-7d Job%-3d exits\n", GTIME, task -> seq);
                fclose(fp);
                printf("At time %-7d Job%-3d exits\n", GTIME, task-> seq);
                break;
            }
        }
    }
    
    clearPriQue(eveQue);
    clearPtr();
    return 1;

void PROC_ARRIVE(cpuEvent* task, priQue* eveQue){
    FILE* fp = fopen("log.txt", "a");
    fprintf(fp, "At time %-7d Job%-3d arrives\n", task->time, task->seq);
    fclose(fp);
    printf("At time %-5d Job%-7d arrives\n", task->time, task->seq);
    queueAdd(&queue_CPU, task->seq);

    cpuEvent nextJob;
    nextJob.seq = task -> seq + 1;
    nextJob.type = ARRIVAL; 
    nextJob.time = randNum(CPU_MIN, CPU_MAX) + GTIME;
    
    pushToQue(eveQue, &nextJob);
}

void PROC_CPU(cpuEvent* task, priQue* eveQue){

    FILE* fp = fopen("log.txt", "a");

    if(task -> type == ARRIVAL){
        PROC_ARRIVE(task, eveQue);
    }

    if(task -> type == CPU_BEGIN){ 
        cpuEvent task_fin;
        taskFin.seq = task -> seq;
        taskFin.time = randNum(CPU_MIN, CPU_MAX) + GTIME;
        taskFin.type = CPU_FINISH;
        
        pushToQue(eveQue, &taskFin);
    }

    if(task -> type == CPU_FINISH){ 
        if(probGet(QUIT_PROB) == 0){
            cpuEvent diskTask;
            diskTask.seq = task -> seq;
            diskTask.time = task -> time;
            diskTask.type = DISK_ARRIVAL;

            push(eveQue, &diskTask);
        }
        else{
            cpuEvent allFin;
            allFin.seq = task -> seq;
            allFin.time = task -> time;
            allFin.type = END;
            pushToQue(eveQue, &allFin);
        }
        CPU_STATE = IDLE;
        printf("At time %-7d job%-3d finishes at CPU\n",GTIME, task -> seq );
        fprintf(file, "At time %-7d job%-3d finishes at CPU\n" GTIME, task -> seq);

    }
    if( (queue_CPU.current>=1) && (CPU_STATE) == IDLE){
        int seqPop = queueRm(&queue_CPU);
        printf("At time %-7d job%-3d begins at CPU\n",task -> time, seqPop );
        fprintf(file, "At time %-7d job%-3d begins at CPU\n",task -> time, seqPop);
        cpuEvent jobBegin;
        jobBegin.seq = seqPop;
        jobBegin.time = timeGlobal;
        jobBegin.type = CPU_BEGIN; 

        pushToQue(eveQue, &jobBegin);

        CPU_STATE = BUSY;
    }
    fclose(fP);
}

void PROC_ARRIVE_DISK(cpuEvent* task, priQue* eveQue){
    FILE* fp = fopen("log.txt", "a");
    fprintf(fp, "At time %-7d Job%-3d arrives at Disk\n", task -> time, task -> seq);
    fclose(fp);
    printf("At time %-7d Job%-3d arrives at Disk\n", task -> time, task -> seq);
    int size1 = QUE_DISK1.curPos;
    int size2 = QUE_DISK2.curPos;
    
    if(DISK1_STATE == IDLE && DISK2_STATE == IDLE){
        if(size1 > size2){
            enQueue(&QUE_DISK2, task->seq);
        }
        else{
            enQueue(&QUE_DISK1, task->seq);
        }
    }
    else{
        if(DISK1_STATE == IDLE && DISK2_STATE == BUSY){
            enQueue(&QUE_DISK1, task-> seq);
        }
        if(DISK2_STATE == IDLE && DISK1_STATE == BUSY){
            enQueue(&QUE_DISK2, task -> seq);
        }
    }

}

void PROC_DISK(cpuEvent* task, priQue* eveQue){
    FILE* fp = fopen("log.txt", "a");

    // // CPU arrival
    switch (task -> type)
    {
    
    case DISK_ARRIVAL:
        PROC_ARRIVE_DISK(task, eveQue);
        break;
    
    case DISK1_BEGIN :
    {
        cpuEvent taskFin1;
        taskFin1.seq = task -> seq;
        taskFin1.time = randNum(DISK1_MIN, DISK1_MAX) + GTIME;
        taskFin1.type = DISK1_FINISH;
        pushToQue(eveQue, &taskFin1);

        break;
    }

    case DISK2_BEGIN :
    {
        cpuEvent taskFin2;
        taskFin2.seq = task -> seq;
        taskFin2.time = randNum(DISK2_MIN, DISK2_MAX) + GTIME;
        taskFin2.type = DISK2_FINISH;
        pushToQue(eveQue, &taskFin2);

        break;
    }

    case DISK1_FINISH:
        printf("At time %-7d Job%-3d finishes at Disk1\n", task -> time, task -> seq);
        fprintf(fp, "At time %-7d Job%-3d finishes at Disk1\n", task -> time, task -> seq);
        queueAdd(&QUE_CPU, task -> seq);
        DISK1_STATE = IDLE;
        break;

    case DISK2_FINISH:
        printf("At time %-7d Job%-3d finishes at Disk2\n", task -> time, task -> seq);
        fprintf(fp, "At time %-7d Job%-3d finishes at Disk2\n", task -> time, task -> seq);
        queueAdd(&QUE_CPU, task -> seq);
        DISK2_STATE = IDLE;
        break;
    }

    if((QUE_DISK1.curPos >= 1) && (DISK1_STATE == IDLE)){
        // 1. pop out the 1st one
        int rmSeq = queueRm(&QUE_DISK1);
        printf("At time %-7d job%-3d begins at Disk1\n",task -> time, rmSeq );
        fprintf(fp, "At time %-7d job%-3d begins at Disk1\n",task -> time, rmSeq);
        // 2. create disk begins
        Event jobBegin;
        jobBegin.seq = rmSeq;
        job_begin.time = GTIME;
        job_begin.type = DISK1_BEGIN;

        pushToQue(eveQue, &jobBegin);
        DISK1_STATE = BUSY;
    }
    if((QUE_DISK2.current >= 1) && (DISK2_STATE == IDLE)){
        // 1. pop out the 1st one
        int rmSeq = queueRm(&QUE_DISK2);
        printf("At time %-7d job%-3d begins at Disk2\n",task -> time, rmSeq );
        fprintf(fp, "At time %-7d job%-3d begins at Disk2\n",task -> time, rmSeq);
        // 2. create disk begins
        Event jobBegin;
        jobBegin.seq = rmSeq;
        job_begin.time = GTIME;
        job_begin.type = DISK2_BEGIN;

        pushToQue(eveQue, &jobBegin);
        DISK2_STATE = BUSY;
    }
    fclose(fp);
}
void parseFile(){
    readFile();
    INI_TIME = getIniTime();
    FIN_TIME = getFinTime();
    ARRIVE_MIN = getArrivalMin();
    ARRIVE_MAX = getArrivalMax();
    QUIT_PROB = getQuitProb();
    CPU_MIN = getCPUMin();
    CPU_MAX = getCPUMax();
    DISK1_MIN = getDisk1Min();
    DISK1_MAX = getDisk1Max();
    DISK2_MIN = getDisk2Min();
    DISK2_MAX = getDisk2Max();
}



}





















