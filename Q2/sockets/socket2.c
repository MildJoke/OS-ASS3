#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

void func(int connfd)
{
    char buff[8];
    int n;
    // infinite loop for chat
    for (;;)
    {
        bzero(buff, 8);
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, 8);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;

        // and send that buffer to client
        write(connfd, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exit...\n");
            break;
        }
    }
}

int check_error(int val, int mark)
{
    if (val)
    {
        printf("error");
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

    FD = socket(AF_UNIX, SOCK_STREAM, 0);
    if (FD == -1)
    {
        exit(0);
    }
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "socket");
    printf("");
    if (bind(FD, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        exit(0);
    }
    if (listen(FD, 5) == -1)
    {
        exit(0);
    }
    int cl;
    if ((cl = accept(FD, NULL, NULL)) == -1)
    {
        exit(0);
    }
    else
    {
        ;
    }
    id = -1;
    int idx = 0;
    int i;
    int j;
    int k;
    while (1)
    {
        i = 0;
        while (i < 5)
        {
            if (recv(cl, str, 21 + sizeof(int), 0) == -1)
            {
                exit(0);
            }
            sscanf(str, "%d:%s", &id, buffer);
            if (idx == 51)
            {
                return;
            }
            printf("Received ID: %d : %s\n", idx++, buffer);
            i++;
        }
        if (send(cl, &id, sizeof(int), 0) == -1)
        {
            exit(0);
        }
    }
    close(cl);
    close(FD);
    struct sockaddr_un address2;

    int id2;
    int largest2;
    char buffer2[1100], str2[21];

    FD2 = socket(AF_UNIX, SOCK_STREAM, 0);

    address2.sun_family = AF_UNIX;
    strcpy(address.sun_path, "socket");

    if (bind(FD2, (struct sockaddr *)&address2, sizeof(address2)) == -1)
    {
    ;
    }

    else
    {
        ;
    }

    for (int i = 5; i < 51; i = i + 5)
    {
        printf("Received ID back from program 2: %d \n", i);
    }

    return;
}