#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int arrn[5] = {0, 1, 2, 3, 4};
sem_t forks[5];

int check_error_sem(int val, int mark)
{
    if (val)
    {
        printf("error");
        exit(1);
    }
    return 0;
}

int *start_thinking(void *philosophers)
{
    int *philosopher = (int *)philosophers;
    
    if (*philosopher < 4)
    {
        printf("Philosopher %d is thinking\n", *philosopher + 1);

        sem_wait(&forks[(*philosopher) % 5]);
        printf("Philosopher %d takes fork %d\n", *philosopher + 1, ((*philosopher) % 5) + 1);

        sem_wait(&forks[(*philosopher + 1) % 5]);
        printf("Philosopher %d takes fork %d\n", *philosopher + 1, ((*philosopher + 1) % 5) + 1);

        printf("Philosopher %d is eating\n", *philosopher + 1);
        sleep(2);

        sem_post(&forks[(*philosopher) % 5]);
        printf("Philosopher %d puts fork %d\n", *philosopher + 1, ((*philosopher) % 5) + 1);

        sem_post(&forks[(*philosopher + 1) % 5]);
        printf("Philosopher %d puts fork %d\n", *philosopher + 1, ((*philosopher + 1) % 5) + 1);
    }
    
    else
    {

        printf("Philosopher %d is thinking\n", *philosopher + 1);

        sem_wait(&forks[(*philosopher + 1) % 5]);
        printf("Philosopher %d takes fork %d\n", *philosopher + 1, ((*philosopher + 1) % 5) + 1);

        sem_wait(&forks[(*philosopher) % 5]), 1;
        printf("Philosopher %d takes fork %d\n", *philosopher + 1, ((*philosopher) % 5) + 1);

        printf("Philosopher %d is eating\n", *philosopher + 1);

        sem_post(&forks[(*philosopher + 1) % 5]);
        printf("Philosopher %d puts fork %d\n", *philosopher + 1, ((*philosopher + 1) % 5) + 1);

        sem_post(&forks[(*philosopher) % 5]);
        printf("Philosopher %d puts fork %d\n", *philosopher + 1, ((*philosopher) % 5) + 1);
    }
    
}

int main()
{
    pthread_t phil_id[5];
    int i=0;
    
    while(i<5)
    {
        sem_init(&forks[i], 0, 1);
        i++;
    }
    i=0;
    while(i<5)
    {
        pthread_create(&phil_id[i], NULL, start_thinking, &arrn[i]);
        i++;
    }
    i=0;
    while(i<5)
    {
        pthread_join(phil_id[i], NULL);
        i++;
    }
}