#include "headers.h"
#include "assert.h"

int ichinose;
struct dirent *jjk2;
char jj[4096];
int shellid = -1;
int processid = -1;
ptrtobackground g = NULL;
ptrtoactivity act = NULL;
char nameofprocess[4096];

int flagcontrolc = 0;
void handle_sigint(int sig)
{
   if (processid == -1)
   {
      fflush(stdin);
      putchar('\n');
      return;
   }
   else
   {
      kill(processid, 9);
      putchar('\n');
   }
}
void handle_sigquit(int sig, ptrtoactivity act)
{
   if (processid == -1)
   {
   }
   else
   {
      kill(processid, 9);
   }
   ptrtoactivity h = act;
   while (h != NULL)
   {
      kill(h->pid, 9);
      h = h->next;
   }
}
void handle_sigstp(int sig)
{
   if (processid == -1)
   {
      return;
   }
   else
   {
      kill(processid, SIGSTOP);
      kill(processid, SIGTSTP);
      nameofprocess[strlen(nameofprocess) - 1] = '\0';
      ptrtoactivity kn = (ptrtoactivity)malloc(sizeof(struct activity));
      ptrtobackground u = (ptrtobackground)malloc(sizeof(background));
      u->name = (char *)malloc(sizeof(char) * strlen(nameofprocess));
      strcpy(u->name, nameofprocess);
      u->next = NULL;
      u->pid = processid;
      ptrtobackground t = g;
      if (g == NULL)
      {
         g = u;
      }
      else
      {
         while (t->next != NULL)
         {
            t = t->next;
         }
         t->next = u;
      }
      kn->name = (char *)malloc(sizeof(char) * strlen(nameofprocess));
      strcpy(kn->name, nameofprocess);
      kn->next = NULL;
      kn->pid = processid;
      if (act == NULL)
      {
         act = kn;
         return;
      }
      ptrtoactivity mm = act;
      while (mm->next != NULL)
      {
         mm = mm->next;
      }
      mm->next = kn;
      return;
   }
}
int main()
{
   char delim[] = ";";
   char *current = (char *)malloc(sizeof(char) * 4096);
   char *a = (char *)malloc(sizeof(char) * 4096);
   getcwd(current, 4096);
   struct sigaction sa;
   char fghandler[4096];
   int fgg = 0;
   sa.sa_handler = handle_sigint;
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = 0;
   if (sigaction(SIGINT, &sa, NULL) == -1)
   {
      perror("sigaction");
      exit(1);
   }
   signal(SIGTSTP, handle_sigstp);
   strcpy(a, current);
   shellid = getpid();
   int gg = 0;
   char *k = (char *)malloc(sizeof(char) * 4096);
   a[strlen(current)] = '/';
   a[strlen(current) + 1] = 'p';
   a[strlen(current) + 2] = '.';
   a[strlen(current) + 3] = 't';
   a[strlen(current) + 4] = 'x';
   a[strlen(current) + 5] = 't';
   int mbappe = -1;
   char messi[4096];
   char ronaldo[4096];
   FILE *ptr = fopen(a, "r");
   if (ptr != NULL)
   {
      char b;
      while (b != EOF)
      {
         b = fgetc(ptr);
         if (b == '\n')
         {
            gg += 1;
         }
         if (gg == 15)
         {
            break;
         }
      }
   }
   int status;

   while (1)
   {
      processid = -1;

      flagcontrolc = 0;
      ichinose = 0;
      jjk2 = NULL;
      prompt(current, mbappe, messi);
      mbappe = -1;
      int flag = 0;
      char input[4096];

      input[0] = '\0';
      fgets(input, 4096, stdin);
      if (feof(stdin))
      {
         ptrtoactivity f = act;
         while (f != NULL)
         {
            kill(f->pid, 9);
            f = f->next;
         }
         printf("\n");
         break;
      }
      int f = 0;
      int f1 = 0;
      char inputr[4096];
      int inputrindex = 0;
      int outputrindex = 0;

      char outputr[4096];
      ptrtobackground hhh = g;
      ptrtobackground prev = g;

      while (hhh != NULL)
      {
         int jkk = waitpid(hhh->pid, &status, WNOHANG);
         if (jkk > 0)
         {
            if (WIFEXITED(status))
            {
               if (!WEXITSTATUS(status))
               {

                  printf("%s exited normally(%d)\n", hhh->name, hhh->pid);
                  if (hhh == g)
                  {
                     g = g->next;
                  }
                  else
                  {
                     prev->next = hhh->next;
                     free(hhh);
                  }
               }

               else
               {
                  printf("%s exited abnormally(%d)\n", hhh->name, hhh->pid);
                  if (hhh == g)
                  {
                     g = g->next;
                  }
                  else
                  {
                     prev->next = hhh->next;
                     free(hhh);
                  }
               }
            }

            if (hhh != g)
            {
               prev = prev->next;
            }
         }
         else if (jkk < 0 && hhh->killed != -1)
         {
            printf("%s exited normally(%d)\n", hhh->name, hhh->pid);
            if (hhh == g)
            {
               g = g->next;
            }
            else
            {
               prev->next = hhh->next;
               free(hhh);
            }
         }
         if (hhh == NULL)
         {
            break;
         }
         else
         {
            hhh = hhh->next;
         }
      }
      char inputforpastevents[4096];
      strcpy(inputforpastevents, input);

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
         continue;
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
                  perror("NO such input file found");
                  break;
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

            int dupf = dup2(p[yj][1], STDOUT_FILENO);

            if (dupf == -1)
            {
               perror("dup");
               break;
            }

            close(p[yj][1]);
         }
         else if (yj != pipe2)
         {

            int dupf = dup2(p[yj - 1][0], STDIN_FILENO);
            if (dupf == -1)
            {
               perror("dup");
               break;
            }
            close(p[yj - 1][0]);

            dupf = dup2(p[yj][1], STDOUT_FILENO);
            if (dupf == -1)
            {
               perror("dup");
               break;
            }
            close(p[yj][1]);
         }
         else
         {
            if (yj > 0)
            {
               int dupf = dup2(p[yj - 1][0], STDIN_FILENO);
               if (dupf == -1)
               {
                  perror("dup");
                  break;
               }
               close(p[yj - 1][0]);
            }
            dup2(original_stdout, STDOUT_FILENO);
         }
         if (f1 != 0)
         {
            if (f1 == 1)
            {
               int fg1 = open(outputr, O_WRONLY | O_CREAT | O_TRUNC, 0644);
               int dupf = dup2(fg1, 1);
               if (dupf == -1)
               {
                  perror("dup");
                  break;
               }
               close(fg1);
            }
            else
            {
               int fg1 = open(outputr, O_WRONLY | O_CREAT | O_APPEND, 0644);
               int dupf = dup2(fg1, 1);
               if (dupf == -1)
               {
                  perror("dup");
                  break;
               }
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
                        strcpy(ronaldo, b[2]);
                        ronaldo[fill] = '\0';
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
                     continue;
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
            else if (strstr(b[2], "pastevents") != NULL)
            {
               pastevents(act, g, &gg, current, b[2], 0);
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
                  ptrtobackground klll = g;
                  ptrtobackground previous1 = g;
                  while (klll != NULL)
                  {
                     if (klll->pid == pid)
                     {
                        if (klll == g)
                        {
                           g = g->next;
                           break;
                        }
                        previous1->next = klll->next;
                        break;
                     }
                     if (klll != g)
                     {
                        previous1 = previous1->next;
                     }
                     klll = klll->next;
                  }
                  if (uflag == 0)
                  {
                     perror("Invalid process id");
                  }
                  else
                  {
                     int status;
                     processid = pid;
                     strcpy(nameofprocess, b[2]);
                     fgg = 1;
                     strcpy(fghandler, kll->name);
                     fghandler[strlen(fghandler)] = '\n';
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
            end = time(NULL);
            mbappe = difftime(end, start);
            if (mbappe > 2)
            {
               if (jj == 1 && ggj != 0)
               {
                  strcpy(messi, ronaldo);
                  messi[ggj] = '\0';
               }
               else
               {

                  strcpy(messi, token);

                  messi[strlen(token)] = '\0';
               }
            }
            else
            {
               mbappe = -1;
            }
            token = strtok_r(NULL, delim, &hh);
         }
         if (flag == 1)
         {
            break;
         }
         yj += 1;

         tokenss = strtok_r(NULL, "|", &hhh1);
      }

      dup2(original_stdin, 0);
      dup2(original_stdout, 1);

      if (flag == 1)
      {
         break;
      }
      if (strstr(inputforpastevents, "pastevents") == NULL || strstr(inputforpastevents, "execute") != NULL)
      {
         if (fgg == 1)
         {
            pastevents(act, g, &gg, current, fghandler, 1);
            fgg = 0;
         }
         else
         {
            pastevents(act, g, &gg, current, inputforpastevents, 1);
         }
      }
   }
   free(current);
   free(a);
   free(k);
}
