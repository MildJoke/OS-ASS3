#include <stdio.h>
#include <pthread.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t forks[5];
pthread_mutex_t sauceBowls[2];
pthread_t philosophers[5];

int *check_error_sem(int v, int mark)
{
    if (v)
    {
        if (mark == 0)
        {
            printf("error in sem_init()");
        }
        else if (mark == 1)
        {
            printf("error in sem_wait()");
        }
        else if (mark == 2)
        {
            printf("error in sem_post()");
        }
        else
        {
            printf("error!");
        }
        exit(1);
    }
    return &mark;
}

int *StartThinking(void *arguments)
{
    int *id = (int *)arguments;
    while(1)
    {
    printf("Philosopher %d is thinking\n", *id + 1);

    if (*id % 2 == 0)
    {
        check_error_sem(pthread_mutex_lock(&forks[*id]), 1);
        printf("Philosopher %d picked up the first fork.\n", *id + 1);

        check_error_sem(pthread_mutex_lock(&forks[(*id + 1) % 5]), 1);
        printf("Philosopher %d picked up the second fork.\n", *id + 1);
    }
    else if (*id % 2 == 1)
    {

        check_error_sem(pthread_mutex_lock(&forks[(*id + 1) % 5]), 1);
        printf("Philosopher %d picked up the first fork.\n", *id + 1);

        check_error_sem(pthread_mutex_lock(&forks[*id]), 1);
        printf("Philosopher %d picked up the second fork.\n", *id + 1);
    }


    check_error_sem(pthread_mutex_lock(&sauceBowls[*id % 2]), 1);
    printf("Philosopher %d picked up the bowl #%d.\n", *id + 1, *id % 2 + 1);

    printf("Philosopher %d is eating\n", *id + 1);
    sleep(1);

    check_error_sem(pthread_mutex_unlock(&sauceBowls[*id % 2]), 1);
    printf("Philosopher %d puts down bowl #%d.\n", *id + 1, (*id % 2) + 1);

    check_error_sem(pthread_mutex_unlock(&forks[*id]), 1);
    printf("Philosopher %d puts down the first fork.\n", *id + 1);

    check_error_sem(pthread_mutex_unlock(&forks[(*id + 1) % 5]), 1);
    printf("Philosopher %d puts down the second fork.\n", *id + 1);

    }
    return &id;
    
}

int main()
{
    int i = 0;
    int args[5];
    while (i < 5)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    i = 0;
    while (i < 2)
    {
        pthread_mutex_init(&sauceBowls[i], NULL);
        i++;
    }
    i = 0;
    while (i < 5)
    {
        args[i] = i;
        pthread_create(&philosophers[i], NULL, StartThinking, &args[i]);
        i++;
    }
    i = 0;
    while (i < 5)
    {
        pthread_join(philosophers[i++], NULL);
    }
    return 0;
}