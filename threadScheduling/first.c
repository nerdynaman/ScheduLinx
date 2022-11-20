#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

struct num {
    int a;
    int priority;
    int nice;
};

float A[] = {0,0,0,0,0,0};
float B[] = {0,0,0,0,0,0};
float C[] = {0,0,0,0,0,0};

void *countA(void *arg)
{
    struct timespec ts1, ts2;
    clock_gettime(CLOCK_REALTIME, &ts1);
    struct num *n = (struct num *)arg;
    int a = n->a;
    int priority = n->priority;
    struct sched_param param;
    param.sched_priority = priority;
    pthread_setschedparam(pthread_self(), SCHED_OTHER, &param);
    setpriority(PRIO_PROCESS, 0, n->nice);
   
    // below code is for checking the priority and nice value are set or not
   
    // int niceVal = getpriority(PRIO_PROCESS, 0);
    // printf("nice value a: %d\n", niceVal);
   
    // int policy = sched_getscheduler(0);
    // printf("policy A: %d\n", policy);
    // fflush(stdout);
   
    long long int i;
    for (i = 1; i < 4294967297; i++){
    }
    clock_gettime(CLOCK_REALTIME, &ts2);
    float time = (ts2.tv_sec - ts1.tv_sec) + (ts2.tv_nsec - ts1.tv_nsec)/1000000000.0;
    A[a] = time;
    return NULL;
}

void *countB(void *arg){
    struct timespec ts1, ts2;
    clock_gettime(CLOCK_REALTIME, &ts1);
    struct num *n = (struct num *)arg;
    int a = n->a;
    int priority = n->priority;
    struct sched_param param;
    param.sched_priority = priority;
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
    
    // below code is for checking the priority and nice value are set or not
    
    // int policy = sched_getscheduler(0);
    // printf("policy B: %d\n", policy);

    // int niceVal = getpriority(PRIO_PROCESS, 0);
    // printf("nice value b: %d\n", niceVal);
    fflush(stdout);
    
    long int i;
    for (i = 1; i < 4294967297; i++){
    }
    clock_gettime(CLOCK_REALTIME, &ts2);
    float time = (ts2.tv_sec - ts1.tv_sec) + (ts2.tv_nsec - ts1.tv_nsec)/1000000000.0;
    B[a] = time;
    return NULL;
}

void *countC(void* arg){
    struct timespec ts1, ts2;
    clock_gettime(CLOCK_REALTIME, &ts1);
    struct num *n = (struct num *)arg;
    int a = n->a;
    int priority = n->priority;
    struct sched_param param;
    param.sched_priority = priority;
    pthread_setschedparam(pthread_self(), SCHED_RR, &param);
    
    // below code is for checking the priority and nice value are set or not
    
    // int policy = sched_getscheduler(0);
    // printf("policy C: %d\n", policy);

    // int niceVal = getpriority(PRIO_PROCESS, 0);
    // printf("nice value C: %d\n", niceVal);
    // fflush(stdout);
    long int i;
    for (i = 1; i < 4294967297; i++){
    }
    clock_gettime(CLOCK_REALTIME, &ts2);
    float time = (ts2.tv_sec - ts1.tv_sec) + (ts2.tv_nsec - ts1.tv_nsec)/1000000000.0;
    C[a] = time;
    return NULL;
}

int main(){
    FILE *fp;
    fp = fopen("output.txt", "w");
    fclose(fp);
    for (int i = 1 ; i < 7 ; i++){
        pthread_t thread1, thread2, thread3;
        int iret1, iret2, iret3;
        struct sched_param param;
        // param.sched_priority = i*10;
        printf("enter priority: ");
        scanf("%d", &param.sched_priority);
        struct num *num1 = (struct num *)malloc(sizeof(struct num));
        printf("enter nice: ");
        scanf("%d", &num1->nice);
        num1->a = i-1;
        num1->priority = param.sched_priority;
        iret1 = pthread_create(&thread1, NULL, countA, num1);
        iret2 = pthread_create(&thread2, NULL, countB, num1);
        iret3 = pthread_create(&thread3, NULL, countC, num1);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        pthread_join(thread3, NULL);
        //results here will be stored in a file
        FILE *fp = fopen("output.txt", "a");
        fprintf(fp, "A%f B%f C%f %d %d\n", A[i-1], B[i-1], C[i-1], param.sched_priority, num1->nice);
        // close fp
        fclose(fp);
    }
    
    // results for comparing the time taken by each thread
    for (int i = 0 ; i < 6 ; i++){
        // fprintf(fp, "%f %f %f 
        // printf("A = %.9f\n", A[i]);
        // printf("B = %.9f\n", B[i]);
        // printf("C = %.9f\n", C[i]);
        // printf("\n");
    }
    return 0;
}
