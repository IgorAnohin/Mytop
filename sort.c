#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#include "top.h"

#define PID 0
#define Pid 1
#define USER 2
#define User 3
#define PR 4
#define Pr 5
#define NI 6
#define Ni 7
#define VIRT 8
#define Virt 9
#define RES 10
#define Res 11
#define SHR 12
#define Shr 13
#define SS 14
#define Ss 15
#define CPU 16
#define Cpu 17
#define TIME 18
#define Time 19
#define COMMAND 20
#define Command 21





int sorting(const void * x,const void * x1) {
    parametrs * P = (parametrs *)x;
    parametrs * P1 = (parametrs *)x1;

    switch(sort_flag) {
        case PID:
            return (P->pid > P1->pid);
            break;
        case Pid:
            return (P->pid < P1->pid);
            break;

        case USER:
            return (strcmp(P->user, P1->user) );
            break;
        case User:
            return (!strcmp(P->user, P1->user) );
            break;

        case PR:
            return (P->pr > P1->pr);
            break;
        case Pr:
            return (P->pr < P1->pr);
            break;

        case NI:
            return (P->ni > P1->ni);
            break;
        case Ni:
            return (P->ni < P1->ni);
            break;

        case VIRT:
            return (P->virt > P1->virt);
            break;
        case Virt:
            return (P->virt < P1->virt);
            break;

        case RES:
            return (P->res > P1->res);
            break;
        case Res:
            return (P->res < P1->res);
            break;

        case SHR:
            return (P->shr > P1->shr);
            break;
        case Shr:
            return (P->shr < P1->shr);
            break;

        case SS:
            return (P->S > P1->S);
            break;
        case Ss:
            return (P->S < P1->S);
            break;

        case CPU:
            return (P->cpu > P1->cpu);
            break;
        case Cpu:
            return (P->cpu < P1->cpu);
            break;

        case TIME:
            return (P->stime > P1->stime);
            break;
        case Time:
            return (P->stime < P1->stime);
            break;

        case COMMAND:
            return (strcmp(P->com, P1->com) );
            break;
        case Command:
            return (!strcmp(P->com, P1->com) );
            break;



    }

}

//    qsort(solution,count_proc, sizeof(parametrs),sorting);

void mysort(){







}
