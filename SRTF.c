#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define rep(i, l, u) for (int i = l; i < u; i++)
#define print(m, n) printf("%s: %d\n", m, n)
#define printA()                         \
    for (int i = 0; i < 5; i++)          \
    {                                    \
        printf("%d ", remainingTime[i]); \
    }                                    \
    printf("\n");

int arrivalTime[4] = {0, 0, 2, 5},
    burstTime[4] = {3, 2, 1, 2},
    remainingTime[5] = {3, 2, 1, 2, 1000};

int TIME, remainingJobs = 4, smallest, i, prevJob = 1;

void *scheduler()
{
    for (TIME = 0; remainingJobs > 0; TIME++)
    {
        smallest = 4;
        printA();
        for (i = 0; i < 4; i++)
        {
            if ((arrivalTime[i] <= TIME) && (remainingTime[i] < remainingTime[smallest]) && (remainingTime[i] > 0))
                smallest = i;
            printf("TIMe -> %d Smallest ###### %d\n", TIME, smallest);
        }
        print("SMALLEST-> ", smallest);
        // if (remainingTime[prevJob] == remainingTime[smallest])
        // smallest = prevJob;
        if (prevJob != smallest)
        {
            printf("TIME: %d Job #%d: PREEMPT\n", TIME, prevJob);
            printf("TIME: %d Job #%d: START\n", TIME, smallest);
        }
        remainingTime[smallest]--;
        printf("TIME %d RT: Job %d T %d\n", TIME, smallest, remainingTime[smallest]);
        // printA();
        if (remainingTime[smallest] == 0)
        {
            remainingJobs--;
            printf("RT: Job %d T %d\n", smallest, remainingTime[smallest]);
            printf("TIME: %d Job %d: END\n", TIME, smallest);
        }
        prevJob = smallest;
    }
    printf("TIME: %d All Jobs Finished\n", TIME);
    pthread_exit(NULL);
}

int main()
{
    pthread_t schedule_thread;
    pthread_create(&schedule_thread, NULL, &scheduler, NULL);
    pthread_join(schedule_thread, NULL);
}