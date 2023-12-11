#include "headers.h"
void proclore(char *current, int pid)
{
    if (pid == -1)
    {
        pid = getpid();
    }
    char a[4096];
    snprintf(a, 4096, "/proc/%d/stat", pid);
    FILE *ptr;
    ptr = fopen(a, "r");
    if (!ptr)
    {
        perror("Invalid process id");
        return;
    }
    char p[3];
    char b[4096];
    long int vm;
    int pg = -1;
    char path[4096] = "/0";
    char *info[25];
    fgets(b, 4096, ptr);
    char *token = strtok(b, " ");
    info[0] = (char *)malloc(strlen(token));
    strcpy(info[0], token);
    int i = 1;

    token = strtok(NULL, " ");
    while (i < 25)
    {

        info[i] = (char *)malloc(strlen(token));
        strcpy(info[i++], token);
        token = strtok(NULL, " ");
    }

    fclose(ptr);
    strcpy(p, info[2]);
    vm = atoi(info[22]);

    char path1[4096];
    snprintf(path1, sizeof(path1), "/proc/%d/exe", pid);
    int len = readlink(path1, path, sizeof(path) - 1);
    if (len != -1)
    {
        path[len] = '\0';
    }
    if (strstr(path, current) != NULL)
    {
        path[0] = '~';

        for (int i = 0; i < len; i++)
        {
            if (i < strlen(current))
            {
                continue;
            }
            else
            {
                path[i - strlen(current) + 1] = path[i];
            }
        }
        path[len - strlen(current) + 1] = '\0';
    }
    int pgid = atoi(info[4]);

    int terminal_pgid = atoi(info[7]);
    printf("pid : %d\n", pid);
    printf("process status : %s%c\n", p, (pgid == terminal_pgid) ? '+' : ' ');
    printf("Process Group : %d\n", pgid);
    printf("Virtual memory : %lu\n", vm);
    printf("executable path : %s\n", path);
}
