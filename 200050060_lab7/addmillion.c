#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int account_balance = 0;

pthread_mutex_t lock;

void *increment(void *arg)
{
    int m = (long)arg;
    while (m--)
    {
        pthread_mutex_lock(&lock);
        for (int i = 0; i < 1000000; i++)
        {
            account_balance++;
        }
        pthread_mutex_unlock(&lock);
    }
}

int main(int argc, char *argv[])
{

    clock_t start=clock();
    int threadNum;
    if (argc != 2)
    {
        printf("Incorrect usae\n");
        return 1;
    }
    threadNum = atoi(argv[1]);
    if (threadNum < 1)
    {
        printf("Num can be positive only\n");
        return 1;
    }
    pthread_t th[threadNum];
    int i;
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("Mutex init failed");
        return 1;
    }
    for (i = 0; i < threadNum; i++)
    {
        if (pthread_create(th + i, NULL, &increment, (void*)(2048 / threadNum)) != 0)
        {
            perror("Failed to create thread");
            return 1;
        }
        printf("Transaction %d has started\n", i);
    }
    for (i = 0; i < threadNum; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            return 2;
        }
        printf("Transaction %d has finished\n", i);
    }
    printf("Account Balance is : %d\n", account_balance);
    pthread_mutex_destroy(&lock);
    printf("Time spent: %ld ms\n", clock()-start);
    return 0;
}