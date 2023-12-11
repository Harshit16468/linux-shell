#include "headers.h"

int getmostrecentpid()
{
    int c = -1; 
    FILE *a = fopen("/proc/loadavg", "r");
    if (a)
    {
        char *b = malloc(4096);
        if (!b)
        {
            fclose(a);
            return c; 
        }

        fread(b, 1, 4095, a);
        char *token = strtok(b, " ");
        for (int i = 0; i < 4 && token != NULL; i++)
        {
            token = strtok(NULL, " ");
        }

        if (token != NULL)
        {
            if (token[strlen(token) - 1] == '\n')
            {
                token[strlen(token) - 1] = '\0';
            }
            c = atoi(token);
        }

        free(b);
        fclose(a);
    }
    return c;
}

void die(const char *s)
{
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
 */
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}
void neonate(int t)
{
    if(t<=0){
        printf("invalid sleep time\n");
        return;
    }
    int a = fork();
    char c;
    enableRawMode();
    if (a == 0)
    {
        while (1)
        {
            fflush(stdout);
            printf("%d\n", getmostrecentpid());
            sleep(t);
        }
    }
    else
    {
    while(1){
        if (read(STDIN_FILENO, &c, 1) == 1)
        {
            if (c == 'X' || c == 'x')
            {
                kill(a, 9);
                break;
            }
        }
        }
        wait(NULL);
    }

    disableRawMode();

    return;
}
