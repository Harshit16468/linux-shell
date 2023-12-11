#include "headers.h"
#include "foreground.h"
int background_c(ptrtoactivity *activity, char *t, ptrtobackground *y)
{
    pid_t a = fork();
    if (a == 0)
    {

        char *b[4];
        b[0] = (char *)malloc(sizeof(char) * 2);

        strcpy(b[0], "/bin/bash");
        b[1] = (char *)malloc(sizeof(char) * 2);
        strcpy(b[1], "-c");
        b[3] = NULL;
        b[2] = (char *)malloc(sizeof(char) * strlen(t));
        strcpy(b[2], t);
        setpgid(0, 0);

        if (execvp("/bin/bash", b) == -1)
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        return -1;
    }
    else
    {

        *activity = activities(*activity, 0, a, t);
        printf("%d\n", a);
        ptrtobackground u = (ptrtobackground)malloc(sizeof(background));
        u->name = (char *)malloc(sizeof(char) * strlen(t));
        u->next = NULL;
        strcpy(u->name, t);
        u->pid = a;
        ptrtobackground t = *y;
        if (*y == NULL)
        {
            *y = u;
            return 0;
        }
        while (t->next != NULL)
        {
            t = t->next;
        }
        t->next = u;

        return 0;
    }
}
