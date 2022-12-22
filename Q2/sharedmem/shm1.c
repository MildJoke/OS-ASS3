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
int main() {
 
  key_t key;
  int shmid;

     key = ftok("shmfile", 'R');
    shmid = shmget(key,1024,0666 | IPC_CREAT);

  char *message = shmat(shmid, NULL, 0);
  if (message == (char*)-1) {
  
    exit(1);
  }

  for(int i=4;i<50;i=i+5){
    printf("largest Recieved : %d : %s\n",i+1, message);
    sleep(1);
  
  }
  if (shmdt(message) < 0) {
    
    exit(1);
  }

  if (shmctl(shmid, IPC_RMID, NULL) < 0) {
    
    exit(1);
  }

  return 0;
}
