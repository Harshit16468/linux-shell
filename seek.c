#include "headers.h"

void printpaths(DIR *a, char *b, int flag1, int flag2, int flag3, char *path, int z, char *path1, int y)
{
    struct dirent *h = readdir(a);
    path[z] = '\0';
    if (flag2 == 0 && flag3 == 0)
    {
        while (h != NULL)
        {

            if (h->d_name[0] != '.' && h->d_name[strlen(h->d_name) - 1] != '~')
            {

                if (strncmp(h->d_name, b, strlen(b)) == 0 && (h->d_name[strlen(b)] == '.' || h->d_name[strlen(b)] == '\0'))
                {
                    if (h->d_type != DT_DIR)
                    {
                        printf("\033[1;32m%s/%s\033[0m\n", path, h->d_name);
                    }
                    else
                    {
                        printf("\033[1;34m%s/%s\033[0m\n", path, h->d_name);
                    }

                    jjk2 = h;
                    snprintf(jj, 4096, "%s/%s", path1, h->d_name);
                    ichinose += 1;
                }
                if (h->d_type == DT_DIR)
                {

                    path[z] = '/';
                    path1[y] = '/';
                    for (int i = 1; i < strlen(h->d_name) + 1; i++)
                    {
                        path[z + i] = h->d_name[i - 1];
                        path1[y + i] = h->d_name[i - 1];
                    }
                    path[z + strlen(h->d_name) + 1] = '\0';
                    path1[y + strlen(h->d_name) + 1] = '\0';
                    DIR *aa = opendir(path1);

                    printpaths(aa, b, flag1, flag2, flag3, path, z + strlen(h->d_name) + 1, path1, y + strlen(h->d_name) + 1);
                    path[z] = '\0';
                    path1[y] = '\0';
                }
            }
            h = readdir(a);
        }
    }
    else if (flag2 == 0 && flag3 == 1)
    {
        while (h != NULL)
        {
            if (h->d_name[0] != '.' && h->d_name[strlen(h->d_name) - 1] != '~')
            {
                if (strncmp(h->d_name, b, strlen(b)) == 0 && (h->d_name[strlen(b)] == '.' || h->d_name[strlen(b)] == '\0') && h->d_type == DT_DIR)
                {

                    printf("\033[1;34m%s/%s\033[0m\n", path, h->d_name);
                    jjk2 = h;
                    snprintf(jj, 4096, "%s/%s", path1, h->d_name);

                    ichinose += 1;
                }
                if (h->d_type == DT_DIR)
                {

                    path[z] = '/';
                    path1[y] = '/';
                    for (int i = 1; i < strlen(h->d_name) + 1; i++)
                    {
                        path[z + i] = h->d_name[i - 1];
                        path1[y + i] = h->d_name[i - 1];
                    }
                    path[z + strlen(h->d_name) + 1] = '\0';
                    path1[y + strlen(h->d_name) + 1] = '\0';
                    DIR *aa = opendir(path1);

                    printpaths(aa, b, flag1, flag2, flag3, path, z + strlen(h->d_name) + 1, path1, y + strlen(h->d_name) + 1);
                    path[z] = '\0';
                    path1[y] = '\0';
                }
            }
            h = readdir(a);
        }
    }
    else if (flag2 == 1 && flag3 == 0)
    {
        while (h != NULL)
        {

            if (h->d_name[0] != '.' && h->d_name[strlen(h->d_name) - 1] != '~')
            {
                if (strncmp(h->d_name, b, strlen(b)) == 0 && (h->d_name[strlen(b)] == '.' || h->d_name[strlen(b)] == '\0') && h->d_type != DT_DIR)
                {
                    printf("\033[1;32m%s/%s\033[0m\n", path, h->d_name);
                    jjk2 = h;
                    snprintf(jj, 4096, "%s/%s", path1, h->d_name);

                    ichinose += 1;
                }
                if (h->d_type == DT_DIR)
                {

                    path[z] = '/';
                    path1[y] = '/';
                    for (int i = 1; i < strlen(h->d_name) + 1; i++)
                    {
                        path[z + i] = h->d_name[i - 1];
                        path1[y + i] = h->d_name[i - 1];
                    }
                    path[z + strlen(h->d_name) + 1] = '\0';
                    path1[y + strlen(h->d_name) + 1] = '\0';
                    DIR *aa = opendir(path1);

                    printpaths(aa, b, flag1, flag2, flag3, path, z + strlen(h->d_name) + 1, path1, y + strlen(h->d_name) + 1);
                    path[z] = '\0';
                    path1[y] = '\0';
                }
            }
            h = readdir(a);
        }
    }

    return;
}

void seek1(ptrtoactivity act, char *token, char *current, char *b)
{
    char *token1 = strtok(token, " \n");
    char a[100];
    char q[4096];

    DIR *aa;
    struct stat sb;
    token1 = strtok(NULL, " \n");
    int g = 0;
    int h = 0;
    int e = 0;

    if (token1 != NULL && strstr(token1, "-d") != NULL)
    {
        g = 1;
        token1 = strtok(NULL, " \n");
        if (token1 != NULL && strstr(token1, "-f") != NULL)
        {
            printf("Invalid Flags\n");
            return;
        }
        else if (token1 != NULL && strstr(token1, "-e") != NULL)
        {

            e = 1;
            token1 = strtok(NULL, " \n");
        }
    }

    else if (token1 != NULL && strstr(token1, "-f") != NULL)
    {

        h = 1;
        token1 = strtok(NULL, " \n");
        if (token1 != NULL && strstr(token1, "-d") != NULL)
        {
            printf("Invalid Flags\n");
            return;
        }

        else if (token1 != NULL && strstr(token1, "-e") != NULL)
        {
            e = 1;
            token1 = strtok(NULL, " \n");
        }
    }
    else if (token1 != NULL && strstr(token1, "-e") != NULL)
    {
        e = 1;
        token1 = strtok(NULL, " \n");
        if (token1 != NULL && strstr(token1, "-d") != NULL)
        {

            g = 1;
            token1 = strtok(NULL, " \n");
        }
        else if (token1 != NULL && strstr(token1, "-f") != NULL)
        {

            h = 1;
            token1 = strtok(NULL, " \n");
        }
    }
    strcpy(q, token1);
    token1 = strtok(NULL, " \n");

    char to[4096];
    char to1[4096];
    to[0] = '.';
    to[1] = '\0';
    int f = 1;
    int uuu = 0;
    if (token1 == NULL || token1[0] == '\n')
    {
        aa = opendir(current);
        if (!aa)
        {
            perror("Not valid directory");
            return;
        }

        strcpy(to1, current);
        uuu = strlen(current);
    }
    else if (strstr(token1, "~") != NULL)
    {

        strcpy(to1, current);
        for (int i = 1; i < strlen(token1); i++)
        {
            to1[strlen(current) + i - 1] = token1[i];
        }
        aa = opendir(to1);
        if (!aa)
        {
            perror("Not valid directory");
            return;
        }

        uuu = strlen(current) + strlen(token1) - 1;
    }
    else
    {
        aa = opendir(token1);
        if (!aa)
        {
            perror("Not valid directory");
            return;
        }

        strcpy(to1, token1);
        uuu = strlen(token1);
    }
    printpaths(aa, q, 0, h, g, to, 1, to1, uuu);
    if (e == 1)
    {
        if (ichinose == 1)
        {
            if (jjk2->d_type == DT_DIR)
            {
                int y = chdir(jj);
                if (y < 0)
                {
                    perror("Missing permissions for task!");
                }
            }
            else
            {
                int ayanokouji = fork();
                if (ayanokouji == 0)
                {

                    char *horikita[4];
                    horikita[3] = NULL;
                    horikita[2] = (char *)malloc(4 + strlen(jj));
                    horikita[2][0] = 'c';
                    horikita[2][1] = 'a';
                    horikita[2][2] = 't';
                    horikita[2][3] = ' ';

                    for (int i = 4; i < 4 + strlen(jj); i++)
                    {
                        horikita[2][i] = jj[i - 4];
                    }
                    horikita[2][strlen(jj) + 4] = '\0';

                    horikita[1] = (char *)malloc(2);
                    strcpy(horikita[1], "-c");
                    horikita[0] = (char *)malloc(2);
                    strcpy(horikita[0], "sh");
                    execvp("/bin/bash", horikita);
                    perror("Missing permissions for task!");
                }
                else
                {

                    wait(NULL);
                }
            }
        }
    }
    if (ichinose == 0)
    {
        printf("No Match Found\n");
    }
}
