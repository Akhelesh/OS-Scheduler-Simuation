#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define rep(i, l, u) for (int i = l; i < u; i++)

int arrivalTime[4] = {0, 0, 2, 5},
    burst1[4] = {3, 2, 1, 2},
    burst2[4] = {2, 1, 2, 1},
    IO[4] = {2, 4, 3, 2};

int minBurst(int arr[])
{
    int i, min = 1000, j = 0;
    rep(i, 0, 4)
    {
        if (arr[i] < min)
        {
            min = arr[i];
            j = i
        }
    }
    return j;
}

void scheduler()
{
    int mBurst = minBurst(burst1);
}