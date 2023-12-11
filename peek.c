#include "headers.h"
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
int compare_dirents(const struct dirent **a, const struct dirent **b)
{
  return strcmp((*a)->d_name, (*b)->d_name);
}

void peek(char *token, char *current, char *b)
{
  char *token1 = strtok(token, " ");
  char a[100];
  char q[4096];

  DIR *aa;
  struct dirent **d;
  int num;

  struct stat sb;
  token1 = strtok(NULL, " ");
  int g = 0;
  int h = 0;
  if (token1 != NULL && strstr(token1, "-a") != NULL)
  {
    g = 1;
    if (token != NULL && strstr(token1, "l") != NULL)
    {
      h = 1;
    }
    token1 = strtok(NULL, " ");
    if (token1 != NULL && strstr(token1, "-l") != NULL)
    {
      h = 1;
      token1 = strtok(NULL, " ");
    }
  }

  if (token1 != NULL && strstr(token1, "-l") != NULL)
  {

    h = 1;
    if (token != NULL && strstr(token1, "a") != NULL)
    {
      g = 1;
    }
    token1 = strtok(NULL, " ");
    if (token1 != NULL && strstr(token1, "-a") != NULL)
    {
      g = 1;
      token1 = strtok(NULL, " ");
    }
  }
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
        num = scandir(e, &d, NULL, compare_dirents);
      }
      else
      {
        num = scandir(current, &d, NULL, compare_dirents);
        if (num < 0)
        {
          perror("Invalid directoy");
          return;
        }
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
        num = scandir(e, &d, NULL, compare_dirents);
        if (num < 0)
        {
          perror("Invalid directoy");
          return;
        }
      }
      else
      {
        num = scandir(b, &d, NULL, compare_dirents);
        if (num < 0)
        {
          perror("Invalid directoy");
          return;
        }
      }
    }
    else
    {
      num = scandir(token1, &d, NULL, compare_dirents);
      if (num < 0)
      {
        perror("Invalid directoy");
        return;
      }
    }
    if (g == 0 && h == 0)
    {

      for (int i = 0; i < num; i++)
      {

        if (d[i]->d_name[0] != '.' && d[i]->d_name[strlen(d[i]->d_name) - 1] != '~')
        {
          if (d[i]->d_type == DT_DIR)
          {
            printf(" \033[1;34m%s\033[0m\n", d[i]->d_name);
          }
          else
          {
            if (stat(d[i]->d_name, &sb) == 0 && sb.st_mode & S_IXUSR)
            {
              printf(" \033[1;32m%s\033[0m\n", d[i]->d_name);
            }
            else
            {

              printf(" \033[1;37m%s\033[0m\n", d[i]->d_name);
            }
          }
        }
      }
    }
    else if (g == 1 && h == 0)
    {
      for (int i = 0; i < num; i++)
      {
        if (d[i]->d_type == DT_DIR)
        {
          printf(" \033[1;34m%s\033[0m\n", d[i]->d_name);
        }
        else
        {
          if (stat(d[i]->d_name, &sb) == 0 && sb.st_mode & S_IXUSR)
          {
            printf(" \033[1;32m%s\033[0m\n", d[i]->d_name);
          }
          else
          {

            printf(" \033[1;37m%s\033[0m\n", d[i]->d_name);
          }
        }
      }
    }
    else if (g == 0 && h == 1)
    {

      int total = 0;
      for (int i = 0; i < num; i++)
      {
        stat(d[i]->d_name, &sb);
        total += sb.st_blocks;
      }
      printf("Total:%d\n", total);
      for (int i = 0; i < num; i++)
      {
        stat(d[i]->d_name, &sb);
        if (d[i]->d_name[0] != '.' && d[i]->d_name[strlen(d[i]->d_name) - 1] != '~')
        {
          printf((S_ISDIR(sb.st_mode)) ? "d" : "-");
          printf((sb.st_mode & S_IRUSR) ? "r" : "-");
          printf((sb.st_mode & S_IWUSR) ? "w" : "-");
          printf((sb.st_mode & S_IXUSR) ? "x" : "-");
          printf((sb.st_mode & S_IRGRP) ? "r" : "-");
          printf((sb.st_mode & S_IWGRP) ? "w" : "-");
          printf((sb.st_mode & S_IXGRP) ? "x" : "-");
          printf((sb.st_mode & S_IROTH) ? "r" : "-");
          printf((sb.st_mode & S_IWOTH) ? "w" : "-");
          printf((sb.st_mode & S_IXOTH) ? "x" : "-");
          printf(" %ld", sb.st_nlink);
          struct passwd *p = getpwuid(sb.st_uid);
          struct group *w = getgrgid(sb.st_gid);
          if (p)
            printf(" %s", p->pw_name);
          if (w)
            printf(" %s", w->gr_name);
          printf(" %ld", sb.st_size);

          strftime(a, 100, "%b %d %H:%M", localtime(&sb.st_mtime));
          printf(" %s", a);

          if (d[i]->d_type == DT_DIR)
          {

            printf(" \033[1;34m%s\033[0m\n", d[i]->d_name);
          }
          else
          {
            if (sb.st_mode & S_IXUSR)
            {
              printf(" \033[1;32m%s\033[0m\n", d[i]->d_name);
            }
            else
            {

              printf(" \033[1;37m%s\033[0m\n", d[i]->d_name);
            }
          }
        }
      }
    }
    else
    {

      int total = 0;

      for (int i = 0; i < num; i++)
      {
        stat(d[i]->d_name, &sb);
        total += sb.st_blocks;
      }
      printf("Total:%d\n", total);
      for (int i = 0; i < num; i++)
      {
        stat(d[i]->d_name, &sb);
        printf((S_ISDIR(sb.st_mode)) ? "d" : "-");
        printf((sb.st_mode & S_IRUSR) ? "r" : "-");
        printf((sb.st_mode & S_IWUSR) ? "w" : "-");
        printf((sb.st_mode & S_IXUSR) ? "x" : "-");
        printf((sb.st_mode & S_IRGRP) ? "r" : "-");
        printf((sb.st_mode & S_IWGRP) ? "w" : "-");
        printf((sb.st_mode & S_IXGRP) ? "x" : "-");
        printf((sb.st_mode & S_IROTH) ? "r" : "-");
        printf((sb.st_mode & S_IWOTH) ? "w" : "-");
        printf((sb.st_mode & S_IXOTH) ? "x" : "-");
        printf(" %ld", sb.st_nlink);
        struct passwd *p = getpwuid(sb.st_uid);
        struct group *w = getgrgid(sb.st_gid);
        if (p)
          printf(" %s", p->pw_name);
        if (w)
          printf(" %s", w->gr_name);
        printf(" %ld", sb.st_size);

        strftime(a, 100, "%b %d %H:%M", localtime(&sb.st_mtime));
        printf(" %s", a);

        if (d[i]->d_type == DT_DIR)
        {

          printf(" \033[1;34m%s\033[0m\n", d[i]->d_name);
        }
        else
        {
          if (sb.st_mode & S_IXUSR)
          {
            printf(" \033[1;32m%s\033[0m\n", d[i]->d_name);
          }
          else
          {

            printf(" \033[1;37m%s\033[0m\n", d[i]->d_name);
          }
        }
      }
    }

    token1 = strtok(NULL, " ");
  }
  if (i == 0)
  {
    getcwd(q, 4096);
    num = scandir(q, &d, NULL, compare_dirents);
    if (num < 0)
    {
      perror("Invalid directoy");
      return;
    }

    if (g == 0 && h == 0)
    {

      for (int i = 0; i < num; i++)
      {
        if (d[i]->d_name[0] != '.' && d[i]->d_name[strlen(d[i]->d_name) - 1] != '~')
        {
          if (d[i]->d_type == DT_DIR)
          {
            printf(" \033[1;34m%s\033[0m\n", d[i]->d_name);
          }
          else
          {
            if (stat(d[i]->d_name, &sb) == 0 && sb.st_mode & S_IXUSR)
            {
              printf(" \033[1;32m%s\033[0m\n", d[i]->d_name);
            }
            else
            {

              printf(" \033[1;37m%s\033[0m\n", d[i]->d_name);
            }
          }
        }
      }
    }
    else if (g == 1 && h == 0)
    {
      for (int i = 0; i < num; i++)
      {
        if (d[i]->d_type == DT_DIR)
        {
          printf(" \033[1;34m%s\033[0m\n", d[i]->d_name);
        }
        else
        {
          if (stat(d[i]->d_name, &sb) == 0 && sb.st_mode & S_IXUSR)
          {
            printf(" \033[1;32m%s\033[0m\n", d[i]->d_name);
          }
          else
          {

            printf(" \033[1;37m%s\033[0m\n", d[i]->d_name);
          }
        }
      }
    }
    else if (g == 0 && h == 1)
    {

      int total = 0;
      for (int i = 0; i < num; i++)
      {
        stat(d[i]->d_name, &sb);
        total += sb.st_blocks;
      }
      printf("Total:%d\n", total);

      for (int i = 0; i < num; i++)
      {
        stat(d[i]->d_name, &sb);
        if (d[i]->d_name[0] != '.' && d[i]->d_name[strlen(d[i]->d_name) - 1] != '~')
        {
          printf((S_ISDIR(sb.st_mode)) ? "d" : "-");
          printf((sb.st_mode & S_IRUSR) ? "r" : "-");
          printf((sb.st_mode & S_IWUSR) ? "w" : "-");
          printf((sb.st_mode & S_IXUSR) ? "x" : "-");
          printf((sb.st_mode & S_IRGRP) ? "r" : "-");
          printf((sb.st_mode & S_IWGRP) ? "w" : "-");
          printf((sb.st_mode & S_IXGRP) ? "x" : "-");
          printf((sb.st_mode & S_IROTH) ? "r" : "-");
          printf((sb.st_mode & S_IWOTH) ? "w" : "-");
          printf((sb.st_mode & S_IXOTH) ? "x" : "-");
          printf(" %ld", sb.st_nlink);
          struct passwd *p = getpwuid(sb.st_uid);
          struct group *w = getgrgid(sb.st_gid);
          if (p)
            printf(" %s", p->pw_name);
          if (w)
            printf(" %s", w->gr_name);
          printf(" %ld", sb.st_size);

          strftime(a, 100, "%b %d %H:%M", localtime(&sb.st_mtime));
          printf(" %s", a);

          if (d[i]->d_type == DT_DIR)
          {

            printf(" \033[1;34m%s\033[0m\n", d[i]->d_name);
          }
          else
          {
            if (sb.st_mode & S_IXUSR)
            {
              printf(" \033[1;32m%s\033[0m\n", d[i]->d_name);
            }
            else
            {

              printf(" \033[1;37m%s\033[0m\n", d[i]->d_name);
            }
          }
        }
      }
    }
    else
    {
      int total = 0;
      for (int i = 0; i < num; i++)
      {
        stat(d[i]->d_name, &sb);
        total += sb.st_blocks;
      }
      printf("Total:%d\n", total);

      for (int i = 0; i < num; i++)
      {
        stat(d[i]->d_name, &sb);

        printf((S_ISDIR(sb.st_mode)) ? "d" : "-");
        printf((sb.st_mode & S_IRUSR) ? "r" : "-");
        printf((sb.st_mode & S_IWUSR) ? "w" : "-");
        printf((sb.st_mode & S_IXUSR) ? "x" : "-");
        printf((sb.st_mode & S_IRGRP) ? "r" : "-");
        printf((sb.st_mode & S_IWGRP) ? "w" : "-");
        printf((sb.st_mode & S_IXGRP) ? "x" : "-");
        printf((sb.st_mode & S_IROTH) ? "r" : "-");
        printf((sb.st_mode & S_IWOTH) ? "w" : "-");
        printf((sb.st_mode & S_IXOTH) ? "x" : "-");
        printf(" %ld", sb.st_nlink);
        struct passwd *p = getpwuid(sb.st_uid);
        struct group *w = getgrgid(sb.st_gid);
        if (p)
          printf(" %s", p->pw_name);
        if (w)
          printf(" %s", w->gr_name);
        printf(" %ld", sb.st_size);

        strftime(a, 100, "%b %d %H:%M", localtime(&sb.st_mtime));
        printf(" %s", a);

        if (d[i]->d_type == DT_DIR)
        {

          printf(" \033[1;34m%s\033[0m\n", d[i]->d_name);
        }
        else
        {
          if (sb.st_mode & S_IXUSR)
          {
            printf(" \033[1;32m%s\033[0m\n", d[i]->d_name);
          }
          else
          {

            printf(" \033[1;37m%s\033[0m\n", d[i]->d_name);
          }
        }
      }
    }
  }
}