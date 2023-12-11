#ifndef __FOREGROUND_H
#define __FOREGROUND_H
typedef struct background background;
typedef background * ptrtobackground;
struct background{
    int pid;
    char * name;
    int killed;
    ptrtobackground next;
};
int background_c(ptrtoactivity* activity,char *t, ptrtobackground *y);

#endif