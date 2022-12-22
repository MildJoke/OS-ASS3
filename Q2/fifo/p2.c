#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define STRING_LENGTH 10
#define NUM_STRINGS 50
int main()
{

    char **msgs = malloc(1100);

    int fd = open("myfifo1", O_WRONLY);
    int fd2 = open("myfifo2", O_WRONLY);
    if (fd < 0)
    {
        perror("Failed to open FIFO for writing");
        return 1;
    }

    int i, j;

    for (int i = 0; i < NUM_STRINGS; i++)
    {

        char *str = malloc((STRING_LENGTH + 1) * sizeof(char));

        for (int j = 0; j < STRING_LENGTH; j++)
        {
            str[j] = 'a' + rand() % 26;
        }

        str[STRING_LENGTH] = '\0';
        msgs[i] = str;
        printf("%d %s\n", i + 1, str);
    }

    char *message = malloc(1100);

    for (int i = 4; i < 50; i = i + 5)
    {
        fd = open("myfifo1", O_WRONLY);
        write(fd, msgs[i], strlen(msgs[i]) + 1);
        sleep(1);
        close(fd);
    }
    char buffer[1024];
    int n = read(fd, buffer, sizeof(buffer));
    for (int i = 0; i < 50; i = i + 5)
    {
        n = read(fd, buffer, sizeof(buffer));
    }
    for (int i = 4; i < 50; i = i + 5)
    {
        printf("recieved back : %d : %s\n", i + 1, msgs[i]);
        sleep(1);
    }
    return 0;
}#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define STRING_LENGTH 10
#define NUM_STRINGS 50
int main()
{

    char **msgs = malloc(1100);

    int fd = open("myfifo1", O_WRONLY);
    int fd2 = open("myfifo2", O_WRONLY);
    if (fd < 0)
    {
        perror("Failed to open FIFO for writing");
        return 1;
    }

    int i, j;

    for (int i = 0; i < NUM_STRINGS; i++)
    {

        char *str = malloc((STRING_LENGTH + 1) * sizeof(char));

        for (int j = 0; j < STRING_LENGTH; j++)
        {
            str[j] = 'a' + rand() % 26;
        }

        str[STRING_LENGTH] = '\0';
        msgs[i] = str;
        printf("%d %s\n", i + 1, str);
    }

    char *message = malloc(1100);

    for (int i = 4; i < 50; i = i + 5)
    {
        fd = open("myfifo1", O_WRONLY);
        write(fd, msgs[i], strlen(msgs[i]) + 1);
        sleep(1);
        close(fd);
    }
    char buffer[1024];
    int n = read(fd, buffer, sizeof(buffer));
    for (int i = 0; i < 50; i = i + 5)
    {
        n = read(fd, buffer, sizeof(buffer));
    }
    for (int i = 4; i < 50; i = i + 5)
    {
        printf("recieved back : %d : %s\n", i + 1, msgs[i]);
        sleep(1);
    }
    return 0;
}#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define STRING_LENGTH 10
#define NUM_STRINGS 50
int main()
{

    char **msgs = malloc(1100);

    int fd = open("myfifo1", O_WRONLY);
    int fd2 = open("myfifo2", O_WRONLY);
    if (fd < 0)
    {
        perror("Failed to open FIFO for writing");
        return 1;
    }

    int i, j;

    for (int i = 0; i < NUM_STRINGS; i++)
    {

        char *str = malloc((STRING_LENGTH + 1) * sizeof(char));

        for (int j = 0; j < STRING_LENGTH; j++)
        {
            str[j] = 'a' + rand() % 26;
        }

        str[STRING_LENGTH] = '\0';
        msgs[i] = str;
        printf("%d %s\n", i + 1, str);
    }

    char *message = malloc(1100);

    for (int i = 4; i < 50; i = i + 5)
    {
        fd = open("myfifo1", O_WRONLY);
        write(fd, msgs[i], strlen(msgs[i]) + 1);
        sleep(1);
        close(fd);
    }
    char buffer[1024];
    int n = read(fd, buffer, sizeof(buffer));
    for (int i = 0; i < 50; i = i + 5)
    {
        n = read(fd, buffer, sizeof(buffer));
    }
    for (int i = 4; i < 50; i = i + 5)
    {
        printf("recieved back : %d : %s\n", i + 1, msgs[i]);
        sleep(1);
    }
    return 0;
}