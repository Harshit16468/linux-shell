#include "headers.h"

void prompt(char *a, int y, char *b)
{
    char c[4096];
    char d[4096];
    getcwd(c, 4096);
    char arr[4096];
    int yy = 0;

    gethostname(d, 4096);
    char e[4096];
    int j = 0;
    if (strstr(c, a) != NULL)
    {
        for (int i = 0; i < strlen(c); i++)
        {
            if (i == 0)
            {
                e[i] = '~';
                j += 1;
            }
            else if (i < strlen(a))
            {
                continue;
            }
            else
            {
                e[i - strlen(a) + 1] = c[i];
                j++;
            }
        }
        e[j] = '\0';
        if (b[strlen(b) - 1] == '\n')
        {
            b[strlen(b) - 1] = '\0';
        }

        if (y == -1)
        {
            printf("<%s@%s:%s> ", getlogin(), d, e);
        }
        else
        {
            for (int i = 0; i < strlen(b); i++)
            {
                if (yy == 0 && b[i] == ' ')
                {
                    continue;
                }
                else if (b[i] == ' ')
                {
                    break;
                }
                else
                {
                    arr[yy++] = b[i];
                }
            }
            arr[yy] = '\0';

            printf("<%s@%s:%s %s:%d> ", getlogin(), d, e, arr, y);
        }
    }

    else
    {
        if (y == -1)
        {
            printf("<%s@%s:%s> ", getlogin(), d, c);
        }
        else
        {

            for (int i = 0; i < strlen(b); i++)
            {
                if (yy == 0 && b[i] == ' ')
                {
                    continue;
                }
                else if (b[i] == ' ')
                {
                    break;
                }
                else
                {
                    arr[yy++] = b[i];
                }
            }
            arr[yy] = '\0';

            printf("<%s@%s:%s %s:%d> ", getlogin(), d, c, arr, y);
        }
    }
}
