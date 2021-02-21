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
void getConfig();

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
    srand(getSEED());
    cpuEvent* task;
    priQue* eveQue = initPriorityQueue();

    queueInit(&QUE_CPU);
    queueInit(&QUE_DISK1);
    queueInit(&QUE_DISK2);
    queueInit(&QUE_NETWORK);

    FILE* log = fopen("log.txt", "w");
    fclose(log);

    cpuEvent job1;
    job1.seq = 1;
    job1.type = ARRIVAL;
    job1.time = 0;
    pushToQue(eveQue, &job1);

    while(isEmpty(eveQue) && (GTIME < FIN_TIME)){

    task = popEve(eveQue);
        switch (task -> type){
            case ARRIVAL:
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
                GTIME = task->time;
                PROC_DISK(task, eveQue);
                break;

            case 11:
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
}

void PROC_ARRIVE(cpuEvent* task, priQue* eveQue){
    FILE* fp = fopen("log.txt", "a");
    fprintf(fp, "At time %-7d Job%-3d arrives\n", task->time, task->seq);
    fclose(fp);
    printf("At time %-5d Job%-7d arrives\n", task->time, task->seq);
    queueAdd(&QUE_CPU, task -> seq);

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
        cpuEvent taskFin;
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

            pushToQue(eveQue, &diskTask);
        }
        else{
            cpuEvent allFin;
            allFin.seq = task -> seq;
            allFin.time = task -> time;
            allFin.type = END;
            pushToQue(eveQue, &allFin);
        }
        CPU_STATE = IDLE;
        printf("At time %-7d job%-3d finishes at CPU\n", GTIME, task -> seq );
        fprintf(fp, "At time %-7d job%-3d finishes at CPU\n", GTIME, task -> seq);

    }
    if( (QUE_CPU.curPos>=1) && (CPU_STATE) == IDLE){
        int seqPop = queueRm(&QUE_CPU);
        printf("At time %-7d job%-3d begins at CPU\n",task -> time, seqPop );
        fprintf(fp, "At time %-7d job%-3d begins at CPU\n",task -> time, seqPop);
        cpuEvent jobBegin;
        jobBegin.seq = seqPop;
        jobBegin.time = GTIME;
        jobBegin.type = CPU_BEGIN; 

        pushToQue(eveQue, &jobBegin);

        CPU_STATE = BUSY;
    }
    fclose(fp);
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
            queueAdd(&QUE_DISK2, task->seq);
        }
        else{
            queueAdd(&QUE_DISK1, task->seq);
        }
    }
    else{
        if(DISK1_STATE == IDLE && DISK2_STATE == BUSY){
            queueAdd(&QUE_DISK1, task-> seq);
        }
        if(DISK2_STATE == IDLE && DISK1_STATE == BUSY){
            queueAdd(&QUE_DISK2, task -> seq);
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
        cpuEvent jobBegin;
        jobBegin.seq = rmSeq;
        jobBegin.time = GTIME;
        jobBegin.type = DISK1_BEGIN;

        pushToQue(eveQue, &jobBegin);
        DISK1_STATE = BUSY;
    }
    if((QUE_DISK2.curPos >= 1) && (DISK2_STATE == IDLE)){
        // 1. pop out the 1st one
        int rmSeq = queueRm(&QUE_DISK2);
        printf("At time %-7d job%-3d begins at Disk2\n",task -> time, rmSeq );
        fprintf(fp, "At time %-7d job%-3d begins at Disk2\n",task -> time, rmSeq);
        // 2. create disk begins
        cpuEvent jobBegin;
        jobBegin.seq = rmSeq;
        jobBegin.time = GTIME;
        jobBegin.type = DISK2_BEGIN;

        pushToQue(eveQue, &jobBegin);
        DISK2_STATE = BUSY;
    }
    fclose(fp);
}
void getConfig(){
    parseFile();
    INI_TIME = getINIT_TIME();
    FIN_TIME = getFIN_TIME();
    ARRIVE_MIN = getARRIVE_MIN();
    ARRIVE_MAX = getARRIVE_MAX();
    QUIT_PROB = getQUIT_PROB();
    CPU_MIN = getCPU_MIN();
    CPU_MAX = getCPU_MIN();
    DISK1_MIN = getDISK1_MIN();
    DISK1_MAX = getDISK1_MAX();
    DISK2_MIN = getDISK2_MIN();
    DISK2_MAX = getDISK2_MAX();
}





















