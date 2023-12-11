#include "headers.h"
ptrtoactivity activities(ptrtoactivity activity, int flag, int pid, char *name)
{
    if (flag == 0)
    {
        if (strcmp(name, "\n") == 0)
        {
            return activity;
        }
        if (name[strlen(name) - 1] == '\n')
        {
            name[strlen(name) - 1] = '\0';
        }
        if (strlen(name) == 0)
        {
            return activity;
        }
        if (activity == NULL)
        {
            activity = (ptrtoactivity)malloc(sizeof(activity));
            activity->name = (char *)malloc(sizeof(char) * strlen(name) + 1);

            strcpy(activity->name, name);

            activity->pid = pid;
            activity->next = NULL;
            return activity;
        }
        else if (activity != NULL)
        {
            ptrtoactivity j = activity;
            ptrtoactivity previous = activity;
            while (j != NULL)
            {
                if (j->pid > pid)
                {
                    ptrtoactivity u = (ptrtoactivity)malloc(sizeof(activity));
                    u->name = (char *)malloc(sizeof(char) * strlen(name) + 1);
                    strcpy(u->name, name);
                    u->pid = pid;
                    u->next = NULL;
                    if (j == activity)
                    {
                        u->next = activity;
                        activity = u;
                    }
                    else
                    {
                        previous->next = u;
                        u->next = j;
                    }
                    return activity;
                }
                if (j != activity)
                {
                    previous = previous->next;
                }
                j = j->next;
            }
            ptrtoactivity u = (ptrtoactivity)malloc(sizeof(activity));
            u->name = (char *)malloc(sizeof(char) * strlen(name) + 1);
            strcpy(u->name, name);
            u->pid = pid;
            u->next = NULL;
            previous->next = u;

            return activity;
        }
    }
    else
    {
        ptrtoactivity j = activity;
        char state;
        while (j != NULL)
        {
            char *a = malloc(4096);
            char *b = malloc(4096);
            snprintf(a, 4096, "/proc/%d/stat", j->pid);
            int space = 0;
            FILE *ptr = fopen(a, "r");

            if (ptr != NULL)
            {
                fgets(b, 4096, ptr);
                for (int l = 0; l < strlen(b); l++)
                {
                    if (b[l] == ' ')
                    {
                        space += 1;
                        if (space == 3)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (space == 2)
                        {
                            state = b[l];
                        }
                    }
                }

                if (state == 'T')
                {

                    printf("%d : %s - Stopped\n", j->pid, j->name);
                }
                else
                {
                    printf("%d : %s - Running\n", j->pid, j->name);
                }
            }
            free(a);
            free(b);

            j = j->next;
        }
        return NULL;
    }
}