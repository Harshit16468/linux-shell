#ifndef __ACTIVITY_H
#define __ACTIVITY_H
typedef struct activity * ptrtoactivity;
struct activity{
    char * name;
    int pid;
    ptrtoactivity next;
};

ptrtoactivity activities(ptrtoactivity activity,int flag,int pid,char * name);
#endif