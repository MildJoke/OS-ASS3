#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int check_error(int val, int mark)
{
    if (val)
    {
        printf("value error");
        exit(1);
    }
    return 0;
}

void main()

{
    int FD, FD2;
    struct sockaddr_un address;

    int id;
    int largest;
    char buffer[1100], str[21];
    clock_t timed;
    srand((unsigned)time(&timed));
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < 50)
    {
        j = 0;
        while (j < 20)
        {
            printf("");
            str[j] = 'A' + rand() % 26;

            j++;
        }
        str[j] = '\0';
        strcpy(buffer + i * (21), str);
        i++;
    }
    buffer[i * (21)] = '\0';

    FD = socket(AF_UNIX, SOCK_STREAM, 0);
    FD2 = socket(AF_UNIX, SOCK_STREAM, 0);

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "socket");
    if (connect(FD, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        perror("encountered error while connecting!");
        exit(0);
    }

    id = 0;
    while (id < 50)
    {

        i = 0;
        while (i < 5 && id < 50)
        {
            sprintf(str, "%d:%s", id, buffer + id * (21));

            if (send(FD, str, strlen(str) + 1, 0) == -1)
            {
                exit(0);
            }
            i++;
            id++;
        }

        if (recv(FD, &largest, sizeof(int), 0) == -1)
        {
            exit(0);
        }
        printf("largest ID: %d\n", id);
        sleep(1);
    }
    close(FD);

    FD2 = socket(AF_UNIX, SOCK_STREAM, 0);

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "socket2");
    return;
}