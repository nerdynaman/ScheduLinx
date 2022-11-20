#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sched.h>
#include <sys/resource.h>


struct timespec ts4, ts4E, ts1S, ts1E, ts2S, ts2E, ts3S, ts3E;
int main(){
    for (int i = 0; i < 6; i++){
        int p1, p2;
        p1 = (i+1)*10;
        p2 = (i+1)*2;
        // printf("enter priority for process: ");
        // scanf("%d", &p1);
        // printf("enter nice value for process: ");
        // scanf("%d", &p2);
        struct task_struct *task;
        clock_gettime(CLOCK_REALTIME, &ts1S);
        pid_t a = fork();
        if (a == 0){
            // setting priority and nice value
            int b = setpriority(PRIO_PROCESS, 0, p2);
            if (b == -1){
                printf("Error in setting priority of a\n");
            }

            // checking manually if priority and nice value is set properly

            // int a = getpriority(PRIO_PROCESS, 0);
            // printf("set prio: %d", b);
            // printf("nice value: %d", a);
            // fflush(stdout);
            
            // method to set scheduler and nice value, right now we are keeping SCHED_OTHER as scheduler which is default scheduler

            // struct sched_param param;
            // param.sched_priority = 40;
            // int scheduler = sched_setscheduler(0, SCHED_OTHER, &param);
            // int niceVal = nice(p2);

            // if (niceVal == -1){
            //     printf("nice value not set");
            // }
            // if (scheduler == -1){
            //     printf("Error in setting scheduler of a\n");
            // }

            // int prio = sched_get_priority_max(SCHED_OTHER);
            // printf("priority of a: %d\n", prio);
            // fflush(stdout);

            // prio = sched_get_priority_min(SCHED_OTHER);
            // printf("priority of a: %d\n", prio);
            // fflush(stdout);

            // int policy = sched_getscheduler(0);
            // printf("policy A: %d\n", policy);
            // fflush(stdout);
            
            //here we are executing the script which compiles kernel module but script ".sh" can be replaced by any other script
            int res = execl("trA.sh", NULL); 
            exit(0);
        }
        else if (a > 0){
            clock_gettime(CLOCK_REALTIME, &ts2S);
            pid_t b = fork();
            if (b == 0){
                struct sched_param param;
                param.sched_priority = p1;
                int lol = sched_setscheduler(0, SCHED_FIFO, &param);
                if (lol == -1){
                    printf("Error in setting scheduler of b\n");
                }
                // int policy = sched_getscheduler(0);
                // printf("policy B: %d\n", policy);
                // fflush(stdout);
                int res = execl("trB.sh", NULL);
                exit(0);
            }
            else if (b > 0){
                clock_gettime(CLOCK_REALTIME, &ts3S);
                pid_t c = fork();
                if (c == 0){
                    struct sched_param param;
                    param.sched_priority = p1;
                    int lol = sched_setscheduler(0, SCHED_RR, &param);
                    if (lol == -1){
                        printf("Error in setting scheduler of c\n");
                    }
                    // int policy = sched_getscheduler(0);
                    // printf("policy C: %d\n", policy);
                    // fflush(stdout);
                    int res = execl("trC.sh", NULL);
                    exit(0);
                }
                else if (c > 0){
                    // printf("waiting for child processes to finish\n");
                    // printf("a: %d, b: %d, c: %d\n", a, b, c);
                    int a1 = 0 , b1 = 0, c1 = 0;
                    int flagA = 0, flagB = 0, flagC = 0;
                    while(1){
                        if (a1 == 0){
                            a1 = waitpid(a, NULL, WNOHANG);
                            if (a1 > 0){
                                clock_gettime(CLOCK_REALTIME, &ts1E);
                                FILE *fp = fopen("data.txt", "a");
                                fputs("A", fp);
                                float t = ((float)(ts1E.tv_sec - ts1S.tv_sec))+ (ts1E.tv_nsec - ts1S.tv_nsec)/1000000000.0;
                                fprintf(fp, "%f ", t);
                                // fputs("\n", fp);
                                fclose(fp);
                            }
                        }
                        if (b1 == 0){
                            b1 = waitpid(b, NULL, WNOHANG);
                            if (b1 > 0){
                                clock_gettime(CLOCK_REALTIME, &ts2E);
                                FILE *fp = fopen("data.txt", "a");
                                fputs("B", fp);
                                float t = ((float)(ts2E.tv_sec - ts2S.tv_sec))+ (ts2E.tv_nsec - ts2S.tv_nsec)/1000000000.0;
                                fprintf(fp, "%f ", t);
                                // fputs("\n", fp);
                                fclose(fp);
                            }
                        }
                        if (c1 == 0){
                            c1 = waitpid(c, NULL, WNOHANG);
                            if (c1 > 0){
                                clock_gettime(CLOCK_REALTIME, &ts3E);
                                FILE *fp = fopen("data.txt", "a");
                                fputs("C", fp);
                                float t = ((float)(ts3E.tv_sec - ts3S.tv_sec))+ (ts3E.tv_nsec - ts3S.tv_nsec)/1000000000.0;
                                fprintf(fp, "%f ", t);
                                // fputs("\n", fp);
                                fclose(fp);
                            }
                        }
                        if (a1 > 0 && flagA != 1){
                            // printf("time A end: %.9f\n", (((float)(ts1E.tv_sec - ts1S.tv_sec))+ (ts1E.tv_nsec - ts1S.tv_nsec)/1000000000.0));
                            flagA = 1;
                        }
                        if (b1 > 0 && flagB != 1){
                            // printf("time B end: %.9f\n", (((float)(ts2E.tv_sec - ts2S.tv_sec))+ (ts2E.tv_nsec - ts2S.tv_nsec)/1000000000.0));
                            flagB = 1;
                        }
                        if (c1 > 0 && flagC != 1){
                            // printf("time C end: %.9f\n", (((float)(ts3E.tv_sec - ts3S.tv_sec))+ (ts3E.tv_nsec - ts3S.tv_nsec)/1000000000.0));
                            flagC = 1;
                        }
                        if (a1 >0 && b1 > 0 && c1 > 0){
                            // printf("a1: %d, b1: %d, c1: %d\n", a1, b1, c1);
                            break;
                        }
                    }
                    FILE *fp = fopen("data.txt", "a");
                    fprintf(fp, "%d %d \n", p1, p2);
                    fclose(fp);
                    // clock_gettime(CLOCK_REALTIME, &ts4E);
                    // printf("time D end: %.9f\n", (((float)(ts4E.tv_sec - ts4.tv_sec))+ (ts4E.tv_nsec - ts4.tv_nsec)/1000000000.0));
                }
                else{
                    // ERROR
                }
            }
            else{
                // ERROR
            }
        }
        else{
            // ERROR
        }
    }
    return 0;
}