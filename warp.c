#include "headers.h"
void warp(char *token, char *current, char *b)
{

  char *token1 = strtok(token, " ");
  char a[4096];
  strcpy(a, current);

  token1 = strtok(NULL, " ");
  int i = 0;
  while (token1 != NULL)
  {
    if (token1[strlen(token1) - 1] == '\n')
    {
      token1[strlen(token1) - 1] = '\0';
    }
    if (strcmp(token1, "\n") == 0)
    {
      break;
    }
    else if (token1[0] == '\n' || token1[0] == '\0')
    {
      break;
    }
    i += 1;
    getcwd(a, 4096);
    int y;
    if (strstr(token1, "~") != NULL)
    {
      if (strstr(token1, "~/") != NULL)
      {
        char e[4096];
        int flag = 0;
        int hho = 0;
        for (int i = 0; i < strlen(token1); i++)
        {
          if (token1[i] == '~')
          {

            flag = 1;
            strcpy(e, current);
          }
          else if (flag == 1)
          {

            e[strlen(current) + hho] = token1[i];
            hho++;
          }
        }
        y = chdir(e);
      }
      else
      {
        y = chdir(current);
      }
    }
    else if (strstr(token1, "-") != NULL)
    {
      if (strstr(token1, "-/") != NULL)
      {
        char e[4096];
        int flag = 0;
        int hho = 0;
        for (int i = 0; i < strlen(token1); i++)
        {
          if (token1[i] == '-')
          {

            flag = 1;
            strcpy(e, b);
          }
          else if (flag == 1)
          {

            e[strlen(b) + hho] = token1[i];
            hho++;
          }
        }
        y = chdir(e);
      }
      else
      {
        y = chdir(b);
      }
    }
    else
    {
      y = chdir(token1);
    }
    if (y == 0)
    {
      strcpy(b, a);
    }
    else
    {
      perror("Invalid directory");
    }

    getcwd(a, 4096);

    printf("%s\n", a);

    token1 = strtok(NULL, " ");
  }

  if (i == 0)
  {
    getcwd(a, 4096);
    chdir(current);

    printf("%s\n", current);
    strcpy(b, a);
  }
}