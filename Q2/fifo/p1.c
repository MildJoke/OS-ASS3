#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main()
{

    int fd = open("myfifo1", O_RDONLY);
    int fd2 = open("myfifo2", O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to open FIFO for reading");
        return 1;
    }

    char buffer[1024];
    int n = read(fd, buffer, sizeof(buffer));
    if (n < 0)
    {
        perror("Failed to read from FIFO");
        return 1;
    }

    for (int i = 4; i < 51; i = i + 5)
    {
        n = read(fd, buffer, sizeof(buffer));
        printf("Received message: %d : %.*s\n", i + 1, n, buffer);
        sleep(1);
    }

    close(fd);

    for (int i = 0; i < 50; i = i + 5)
    {
        write(fd, buffer, strlen(buffer) + 1);
    }
    return 0;
}
