#include "headers.h"
void execution(char *input, ptrtobackground g, ptrtoactivity act, char *current, char *a)
{
   int shellid = getpid();
   char inputr[4096];
   int inputrindex = 0;
   int outputrindex = 0;
   int f = 0;
   int f1 = 0;
   int flag = 0;
   char delim[] = ";";

   char outputr[4096];
   int pipe1 = 0;
   int pipe2 = 0;
   int ao = 0;
   int go = 0;
   for (int i = 0; i < strlen(input); i++)
   {
      if (input[i] == '|')
      {
         pipe1 = 1;
         pipe2 += 1;
      }
      else if (input[i] == ' ')
      {
         continue;
      }
      else if (input[i] == '\n')
      {
         continue;
      }

      else
      {
         pipe1 = 0;
      }
   }
   if (pipe1 == 1)
   {
      perror("Invalid use of pipe");
      return;
   }

   int a1;
   int original_stdin = dup(0);
   int original_stdout = dup(1);
   outputr[outputrindex] = '\0';
   char *hh = NULL;
   char *hhh1 = NULL;
   char *tokenss = strtok_r(input, "|", &hhh1);
   int p[pipe2][2];
   for (int i = 0; i < pipe2; i++)
   {
      pipe(p[i]);
   }
   int yj = 0;
   while (tokenss != NULL)
   {
      if (yj == 0)
      {
         for (int i = 0; i < strlen(tokenss); i++)
         {
            if (tokenss[i] == '<')
            {
               ao = i;

               f = 1;
               i++;
               while (tokenss[i] == ' ')
               {
                  i++;
               }
               while (tokenss[i] != ' ' && tokenss[i] != '\n')
               {
                  inputr[inputrindex++] = tokenss[i];
                  i++;
               }
            }
         }
         inputr[inputrindex] = '\0';

         if (f == 1)
         {
            int fg = open(inputr, O_RDONLY);
            if (fg == -1)
            {
               perror("NO such file found");
               return;
            }
            dup2(fg, 0);
            close(fg);
         }
      }
      if (yj == pipe2)
      {
         for (int i = 0; i < strlen(tokenss); i++)
         {

            if (tokenss[i] == '>')
            {
               go = i;
               i++;

               f1 = 1;
               if (tokenss[i] == '>')
               {
                  i++;
                  f1 = 2;
               }
               while (tokenss[i] == ' ')
               {
                  i++;
               }
               while (tokenss[i] != ' ' && tokenss[i] != '\n')
               {
                  outputr[outputrindex++] = tokenss[i];
                  i++;
               }
            }
         }
         outputr[outputrindex] = '\0';
      }
      if (yj == 0 && yj != pipe2)
      {

         dup2(p[yj][1], STDOUT_FILENO);
         close(p[yj][1]);
      }
      else if (yj != pipe2)
      {

         dup2(p[yj - 1][0], STDIN_FILENO);
         close(p[yj - 1][0]);

         dup2(p[yj][1], STDOUT_FILENO);
         close(p[yj][1]);
      }
      else
      {
         dup2(p[yj - 1][0], STDIN_FILENO);
         close(p[yj - 1][0]);

         dup2(original_stdout, STDOUT_FILENO);
      }
      if (f1 != 0)
      {
         if (f1 == 1)
         {
            int fg1 = open(outputr, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fg1, 1);
            close(fg1);
         }
         else
         {
            int fg1 = open(outputr, O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fg1, 1);
            close(fg1);
         }
      }

      if (f == 1 && f1 != 0)
      {
         if (ao > go)
         {
            tokenss[go] = '\0';
         }
         else
         {
            tokenss[ao] = '\0';
         }
         f = 0;
         f1 = 0;
      }
      else if (f == 1)
      {
         tokenss[ao] = '\0';
         f = 0;
      }
      else if (f1 != 0)
      {
         tokenss[go] = '\0';
         f1 = 0;
      }
      char *token = strtok_r(tokenss, delim, &hh);
      char **b;
      b = (char **)malloc(sizeof(char *) * 4);
      b[0] = (char *)malloc(sizeof(char) * strlen("/bin/bash"));

      strcpy(b[0], "/bin/bash");
      b[1] = (char *)malloc(sizeof(char) * 2);
      strcpy(b[1], "-c");
      b[3] = NULL;
      while (token != NULL)
      {

         time_t start, end;
         start = time(NULL);
         int jj = 0;
         int ggj = 0;
         b[2] = (char *)malloc(sizeof(char) * strlen(token));
         strcpy(b[2], token);
         if (strstr(b[2], "&") != NULL)
         {
            jj = 1;
            char *arr = (char *)malloc(strlen(token));

            int fill = 0;
            for (int i = 0; i < strlen(token); i++)
            {
               if (token[i] == '\n')
               {
                  break;
               }
               else if (token[i] == '&')
               {
                  arr[fill] = '\0';

                  int b = background_c(&act, arr, &g);
                  if (b == -1)
                  {
                     ptrtobackground io = g;
                     while (io != NULL)
                     {
                        if (strcmp(arr, io->name) == 0)
                        {
                           io->killed = -1;
                        }
                        io = io->next;
                     }
                  }
                  strcpy(arr, "\0");
                  fill = 0;
               }
               else
               {
                  arr[fill++] = token[i];
               }
            }

            arr[fill] = '\0';
            if (fill != 0)
            {
               if (strcmp(arr, " ") != 0)
               {
                  int t = fork();
                  if (t == 0)
                  {
                     strcpy(b[2], arr);
                     ggj = fill;
                     setpgid(0, 0);
                     int a = execvp("/bin/bash", b);
                  }
                  else
                  {
                     act = activities(act, 0, t, b[2]);
                     processid = t;
                     strcpy(nameofprocess, b[2]);
                     nameofprocess[strlen(b[2])] = '\0';

                     int status;
                     waitpid(t, &status, WUNTRACED);
                     strcpy(b[2], token);
                  }
               }
            }
         }
         else if (strstr(b[2], "neonate") != NULL)
         {
            char *token2 = strtok(b[2], " ");
            token2 = strtok(NULL, " ");
            token2 = strtok(NULL, " ");

            neonate(atoi(token2));
         }

         else if (strstr(b[2], "ping") != NULL)
         {
            int pid = -1;
            int signaln = -1;
            for (int index = 0; index < strlen(b[2]); index++)
            {
               if (pid == -1 && b[2][index] >= 48 && b[2][index] <= 57)
               {
                  int pidindex = index + 1;
                  while (b[2][pidindex] <= 57 && b[2][pidindex] >= 48)
                  {
                     pidindex++;
                  }
                  pid = 0;
                  int kl = 1;
                  for (int l = pidindex - 1; l > index - 1; l--)
                  {
                     pid += (b[2][l] - 48) * kl;
                     kl *= 10;
                  }
                  index = pidindex - 1;
               }
               else if (signaln == -1 && b[2][index] >= 48 && b[2][index] <= 57)
               {
                  int signalindex = index + 1;
                  while (b[2][signalindex] <= 57 && b[2][signalindex] >= 48)
                  {
                     signalindex++;
                  }
                  signaln = 0;
                  int kl = 1;
                  for (int l = signalindex - 1; l > index - 1; l--)
                  {
                     signaln += (b[2][l] - 48) * kl;
                     kl *= 10;
                  }
                  signaln = signaln % 32;
               }
               else
               {
                  return;
               }
            }
            if (kill(pid, 0) == -1)
            {
               perror("Invalid process id");
            }
            else
            {
               kill(pid, signaln);
            }
         }
         else if (strstr(b[2], "activities") != NULL)
         {
            activities(act, 1, 0, "\0");
         }
         else if (strstr(b[2], "seek") != NULL)
         {

            seek1(act, token, current, a);
         }

         else if ((strstr(b[2], "warp")) != NULL)
         {

            warp(b[2], current, a);
         }
         else if ((strstr(b[2], "peek")) != NULL)
         {

            peek(b[2], current, a);
         }
         else if (strstr(b[2], "exit") != NULL)
         {
            flag = 1;
            break;
         }
         else if (strstr(b[2], "iMan") != NULL)
         {
            iman(b[2]);
         }

         else if (strstr(b[2], "proclore") != NULL)
         {
            char *token1 = strtok(token, " \n");
            token1 = strtok(NULL, " \n");
            if (token1 == NULL)
            {
               proclore(current, -1);
            }
            else
            {
               int num = atoi(token1);
               proclore(current, num);
            }
         }
         else if (strstr(b[2], "fg"))
         {
            int pid = -1;
            for (int index = 0; index < strlen(b[2]); index++)
            {
               if (pid == -1 && b[2][index] >= 48 && b[2][index] <= 57)
               {
                  int pidindex = index + 1;
                  while (b[2][pidindex] <= 57 && b[2][pidindex] >= 48)
                  {
                     pidindex++;
                  }
                  pid = 0;
                  int kl = 1;
                  for (int l = pidindex - 1; l > index - 1; l--)
                  {
                     pid += (b[2][l] - 48) * kl;
                     kl *= 10;
                  }
                  break;
               }
            }

            if (kill(pid, 0) == 0)
            {
               ptrtoactivity kll = act;
               ptrtoactivity previous = act;
               int uflag = 0;
               while (kll != NULL)
               {
                  if (kll->pid == pid)
                  {
                     uflag = 1;
                     if (kll == act)
                     {
                        act = act->next;
                        break;
                     }
                     previous->next = kll->next;
                     break;
                  }
                  if (kll != act)
                  {
                     previous = previous->next;
                  }
                  kll = kll->next;
               }
               if (uflag == 0)
               {
                  perror("Invalid process id");
                  break;
               }
               else
               {
                  int status;
                  processid = pid;
                  strcpy(nameofprocess, b[2]);
                  nameofprocess[strlen(b[2])] = '\0';
                  kill(pid, SIGCONT);
                  tcsetpgrp(shellid, pid);

                  waitpid(pid, &status, WUNTRACED);

                  tcsetpgrp(shellid, getpgrp());
               }
            }
            else
            {

               perror("Invalid process id");
               break;
            }
         }
         else if (strstr(b[2], "bg"))
         {
            int pid = -1;
            for (int index = 0; index < strlen(b[2]); index++)
            {
               if (pid == -1 && b[2][index] >= 48 && b[2][index] <= 57)
               {
                  int pidindex = index + 1;
                  while (b[2][pidindex] <= 57 && b[2][pidindex] >= 48)
                  {
                     pidindex++;
                  }
                  pid = 0;
                  int kl = 1;
                  for (int l = pidindex - 1; l > index - 1; l--)
                  {
                     pid += (b[2][l] - 48) * kl;
                     kl *= 10;
                  }
                  break;
               }
            }
            if (kill(pid, 0) == 0)
            {
               kill(pid, SIGCONT);
            }
            else
            {
               perror("Invalid process id");
               continue;
            }
         }

         else
         {

            int t = fork();
            if (t == 0)
            {
               setpgid(0, 0);
               execvp("/bin/bash", b);
            }
            else
            {

               processid = t;
               strcpy(nameofprocess, b[2]);
               nameofprocess[strlen(b[2])] = '\0';
               int status;
               waitpid(t, &status, WUNTRACED);
            }
         }
         free(b[2]);
         token = strtok_r(NULL, delim, &hh);
      }

      tokenss = strtok_r(NULL, "|", &hhh1);
      yj += 1;
   }
   dup2(original_stdin, 0);
   dup2(original_stdout, 1);
}
