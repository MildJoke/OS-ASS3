#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define NO_OF_PHILS 5
#define NO_OF_FORKS 5
#define TIME_T 1
#define DEADLOCK 0
#define NUM_PHILOSOPHERS 5
#define NUM_CHOPSTICKS 5
int nums[NO_OF_PHILS] = {0,1,2,3,4};


pthread_t philosopher[NUM_PHILOSOPHERS];
pthread_mutex_t chopstick[5];

void check_error_sem(int ret_val, int flag){
    if(ret_val){
        if(flag==0){
            printf("Encountered some error in sem_init()");
        }
        else if(flag==1){
            printf("Encountered some error in sem_wait()");
        }
        else if(flag==2){
            printf("Encountered some error in sem_post()");
        }
        else {
            printf("Encountered some error");
        }
        exit(1);
    }
}

void* start_thinking(void* philosopher){
    int phil_no = (*(int*)philosopher);
    if(DEADLOCK || phil_no+1<NO_OF_PHILS){
        {
            printf("Philosopher %d is thinking\n", phil_no+1);

            
            check_error_sem(pthread_mutex_lock(&chopstick[(phil_no)%NO_OF_FORKS]), 1);
            printf("Philosopher %d takes fork %d\n", phil_no+1, ((phil_no)%NO_OF_FORKS)+1);

            check_error_sem(pthread_mutex_lock(&chopstick[(phil_no+1)%NO_OF_FORKS]), 1);
            printf("Philosopher %d takes fork %d\n", phil_no+1, ((phil_no+1)%NO_OF_FORKS)+1);

            printf("Philosopher %d is eating\n", phil_no+1);
            sleep(TIME_T);

            check_error_sem(pthread_mutex_unlock(&chopstick[(phil_no)%NO_OF_FORKS]), 2);
            printf("Philosopher %d puts fork %d\n", phil_no+1, ((phil_no)%NO_OF_FORKS)+1);

            check_error_sem(pthread_mutex_unlock(&chopstick[(phil_no+1)%NO_OF_FORKS]), 2);
            printf("Philosopher %d puts fork %d\n", phil_no+1, ((phil_no+1)%NO_OF_FORKS)+1);
        }
    }
    else{
        {
            printf("Philosopher %d is thinking\n", phil_no+1);
           

            check_error_sem(pthread_mutex_lock(&chopstick[(phil_no+1)%NO_OF_FORKS]), 1);
            printf("Philosopher %d takes fork %d\n", phil_no+1, ((phil_no+1)%NO_OF_FORKS)+1);

            check_error_sem(pthread_mutex_lock(&chopstick[(phil_no)%NO_OF_FORKS]), 1);
            printf("Philosopher %d takes fork %d\n", phil_no+1, ((phil_no)%NO_OF_FORKS)+1);

            printf("Philosopher %d is eating\n", phil_no+1);
            sleep(TIME_T);

            check_error_sem(pthread_mutex_unlock(&chopstick[(phil_no+1)%NO_OF_FORKS]), 2);
            printf("Philosopher %d puts fork %d\n", phil_no+1, ((phil_no+1)%NO_OF_FORKS)+1);

            check_error_sem(pthread_mutex_unlock(&chopstick[(phil_no)%NO_OF_FORKS]), 2);
            printf("Philosopher %d puts fork %d\n", phil_no+1, ((phil_no)%NO_OF_FORKS)+1);
        }

    }
}

int main(){
      int i, status_message;
  void *msg;
    pthread_t phil_id[NO_OF_PHILS];

 for (i = 1; i <= NUM_CHOPSTICKS; i++)
  {
    status_message = pthread_mutex_init(&chopstick[i], NULL);
    // Check if the mutex is initialised successfully
    if (status_message == -1)
    {
      printf("\n Mutex initialization failed");
      exit(1);
    }
  }


    int status;
    for (int i = 0; i < NO_OF_PHILS; i++){
        status = pthread_create(&phil_id[i], NULL, start_thinking, &nums[i]);
        if(status){
            fprintf(stderr, "pthread_create: %s\n", strerror(status));
            return EXIT_FAILURE;
        }
    }
    
    for (int i = 0; i < NO_OF_PHILS; i++){
        status = pthread_join(phil_id[i], NULL);
        if(status){
            fprintf(stderr, "pthread_join: %s\n", strerror(status));
            return EXIT_FAILURE;
        }
    }
    
    return 0;
}