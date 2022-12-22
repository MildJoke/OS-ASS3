#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LENGTH 10
#define NUM_STRINGS 50

int main()
{

  srand(time(NULL));

  key_t key;
  int shmid;
  char **msgs = malloc(1100);
  key = ftok("shmfile", 'R');
  shmid = shmget(key, 1024, 0666 | IPC_CREAT);

  char *message = shmat(shmid, NULL, 0);

  int i, j;

  for (int i = 0; i < NUM_STRINGS; i++)
  {

    char *str=malloc((STRING_LENGTH+1)*sizeof(char));

    for (int j = 0; j < STRING_LENGTH; j++)
    {
      str[j] = 'a' + rand() % 26;
    }

    str[STRING_LENGTH] = '\0';
    msgs[i]=str;
    printf("%d %s\n", i+1, str);

  }

  for (int i = 0; i < 50; i=i+5)
  {
    sprintf(message,"%s",msgs[i]);
    sleep(1);
  }

  for(int i=5;i<50;i=i+5){
    printf("received back : %d \n",i);
    sleep(1);
  }

  return 0;
}
