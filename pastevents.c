#include "headers.h"

void replaceSubstring(char *original, const char *substring, const char *replacement)
{
    char result[4096];
    int i, j, k;
    int origLen = strlen(original);
    int subLen = strlen(substring);
    int repLen = strlen(replacement);

    for (i = 0, j = 0; i < origLen;)
    {
        if (strstr(&original[i], substring) == &original[i])
        {
            strcpy(&result[j], replacement);
            j += repLen;
            i += subLen;
        }
        else
        {
            result[j++] = original[i++];
        }
    }
    result[j] = '\0';

    strcpy(original, result);
}
void removeLeadingSpaces(char *str)
{
    int i, j = 0;
    int len = strlen(str);
    bool leadingSpace = true;

    for (i = 0; i < len; i++)
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r')
        {
            leadingSpace = false;
        }

        if (!leadingSpace)
        {
            str[j++] = str[i];
        }
    }

    str[j] = '\0';
}
void pastevents(ptrtoactivity act, ptrtobackground back, int *yy, char *current, char *t, int flag)
{
    char a[4096];
    strcpy(a, current);
    a[strlen(current)] = '/';
    a[strlen(current) + 1] = 'p';
    a[strlen(current) + 2] = '.';
    a[strlen(current) + 3] = 't';
    a[strlen(current) + 4] = 'x';
    a[strlen(current) + 5] = 't';
    a[strlen(current) + 6] = '\0';

    FILE *f = fopen(a, "a+");
    fclose(f);

    char b[4096];
    int j = 0;

    if (flag == 0)
    {
        char *token1 = strtok(t, " ");
        token1 = strtok(NULL, " ");
        int u = 0;
        while (token1 != NULL)
        {
            if (strstr(token1, "purge") != NULL)
            {
                FILE *f = fopen(a, "w");
                u += 1;

                fclose(f);
                *yy = 0;
                return;
            }
            else if (strstr(token1, "execute") != NULL)
            {
                u += 1;

                token1 = strtok(NULL, " ");
                int ay = 0;
                if (strstr(token1, "16") != NULL)
                {
                    ay = 16;
                }
                else if (strstr(token1, "15") != NULL)
                {
                    ay = 15;
                }
                else if (strstr(token1, "14") != NULL)
                {
                    ay = 14;
                }
                else if (strstr(token1, "13") != NULL)
                {
                    ay = 13;
                }
                else if (strstr(token1, "12") != NULL)
                {
                    ay = 12;
                }
                else if (strstr(token1, "11") != NULL)
                {
                    ay = 11;
                }
                else if (strstr(token1, "10") != NULL)
                {
                    ay = 10;
                }
                else if (strstr(token1, "9") != NULL)
                {
                    ay = 9;
                }
                else if (strstr(token1, "8") != NULL)
                {
                    ay = 8;
                }
                else if (strstr(token1, "7") != NULL)
                {
                    ay = 7;
                }
                else if (strstr(token1, "6") != NULL)
                {
                    ay = 6;
                }
                else if (strstr(token1, "5") != NULL)
                {
                    ay = 5;
                }
                else if (strstr(token1, "4") != NULL)
                {
                    ay = 4;
                }
                else if (strstr(token1, "3") != NULL)
                {
                    ay = 3;
                }
                else if (strstr(token1, "2") != NULL)
                {
                    ay = 2;
                }
                else if (strstr(token1, "1") != NULL)
                {
                    ay = 1;
                }
                int i = 1;
                FILE *f = fopen(a, "r");

                fseek(f, 0, SEEK_SET);
                int k = 0;
                while (k < *yy - ay + 1)
                {
                    fgets(b, 4096, f);
                    k++;
                }
                b[strlen(b) - 1] = '\0';
                fclose(f);
                execution(b, back, act, current, a);

                return;
            }
        }
        if (u == 0)
        {
            int kk = 0;
            FILE *f = fopen(a, "r");
            while (kk < *yy)
            {
                fgets(b, 4096, f);

                printf("%s", b);
                kk += 1;
            }
        }
    }
    else
    {
        if (strstr(t, "execute") != NULL)
        {

            int ay = 0;
            if (strstr(t, "execute 16") != NULL)
            {
                ay = 16;
            }
            else if (strstr(t, "execute 15") != NULL)
            {
                ay = 15;
            }
            else if (strstr(t, "execute 14") != NULL)
            {
                ay = 14;
            }
            else if (strstr(t, "execute 13") != NULL)
            {
                ay = 13;
            }
            else if (strstr(t, "execute 12") != NULL)
            {
                ay = 12;
            }
            else if (strstr(t, "execute 11") != NULL)
            {
                ay = 11;
            }
            else if (strstr(t, "execute 10") != NULL)
            {
                ay = 10;
            }
            else if (strstr(t, "execute 9") != NULL)
            {
                ay = 9;
            }
            else if (strstr(t, "execute 8") != NULL)
            {
                ay = 8;
            }
            else if (strstr(t, "execute 7") != NULL)
            {
                ay = 7;
            }
            else if (strstr(t, "execute 6") != NULL)
            {
                ay = 6;
            }
            else if (strstr(t, "execute 5") != NULL)
            {
                ay = 5;
            }
            else if (strstr(t, "execute 4") != NULL)
            {
                ay = 4;
            }
            else if (strstr(t, "execute 3") != NULL)
            {
                ay = 3;
            }
            else if (strstr(t, "execute 2") != NULL)
            {
                ay = 2;
            }
            else if (strstr(t, "execute 1") != NULL)
            {
                ay = 1;
            }

            FILE *f = fopen(a, "r+");
            fseek(f, 0, SEEK_SET);

            int ky = *yy - ay + 1;
            j = 0;
            while (j < ky)
            {
                fgets(b, 4096, f);

                j += 1;
            }
            char ui[10];
            sprintf(ui, "%d", ay);
            replaceSubstring(t, "pastevents", " ");
            replaceSubstring(t, "purge", " ");
            replaceSubstring(t, "execute", " ");
            if (b[strlen(b) - 1] == '\n')
            {
                b[strlen(b) - 1] = '\0';
            }
            replaceSubstring(t, ui, b);
            removeLeadingSpaces(t);
        }
        if (t[strlen(t) - 1] == '\n' && t[strlen(t) - 2] == '\n')
        {
            t[strlen(t) - 1] = '\0';
        }

        if (strcmp(t, "\n") == 0)
        {
            return;
        }

        FILE *f = fopen(a, "r+");
        fseek(f, 0, SEEK_SET);
        j = 0;
        while (j < *yy)
        {
            fgets(b, 4096, f);

            j += 1;
        }

        if (strcmp(b, t) == 0)
        {
            return;
        }
        else
        {

            if (*yy < 15)
            {
                fseek(f, 0, SEEK_END);
                fprintf(f, "%s", t);
                *yy += 1;
                fclose(f);
                return;
            }

            else
            {
                int cc = 0;
                fseek(f, 0, SEEK_SET);

                char *ap = fgets(b, 4096, f);
                char *aa[15];
                int ii = 0;

                while (ap != NULL)
                {

                    ap = fgets(b, 4096, f);
                    aa[ii] = (char *)malloc(strlen(b) + 1);
                    strcpy(aa[ii], b);

                    ii++;
                }
                ii = 14;

                aa[ii] = (char *)malloc(strlen(t) + 1);
                strcpy(aa[ii], t);

                fclose(f);
                f = fopen(a, "w");
                for (int i = 0; i < 15; i++)
                {
                    fprintf(f, "%s", aa[i]);
                }
                fclose(f);
            }
        }
    }
}
