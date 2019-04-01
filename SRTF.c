#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define rep(i, l, u) for (int i = l; i < u; i++)
#define print(m, n) printf("%s: %d\n", m, d)

int arrivalTime[4] = {0, 0, 2, 5},
    burstTime[4] = {3, 2, 1, 2},
    remainingTime[5] = {3, 2, 1, 2, 1000};

int time, remainingJobs = 4, smallest, i, prevJob = 0;

void *scheduler()
{
    for (time = 0; remainingJobs > 0; time++)
    {
        smallest = 5;
        rep(i, 0, 4)
        {
            if (arrivalTime[i] <= time && remainingTime[i] < remainingTime[smallest] && remainingTime[i] > 0)
                smallest = i;
        }
        if (prevJob != smallest)
        {
            printf("Job #%d: Prempted\n", prevJob);
            printf("Job #%d: Started\n", smallest);
        }
        remainingTime[smallest]--;
        if (remainingTime[smallest] == 0)
            remainingJobs--;
        prevJob = smallest;
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t schedule_thread;
    pthread_create(&schedule_thread, NULL, &scheduler, NULL);
    pthread_join(schedule_thread, NULL);
}