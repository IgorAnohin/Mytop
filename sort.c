#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <alloca.h>
#include <limits.h>
#define __USE_GNU
#include <stdlib.h>
#include <string.h>


#include "top.h"

enum {
    PID_Ascending, //0
    PID_Descending,
    User_Ascending,
    User_Descending,
    Pr_Ascending,
    Pr_Descending,
    Ni_Ascending,
    Ni_Descending,
    Virt_Ascending,
    Virt_Descending,
    Res_Ascending,
    Res_Descending,
    Shr_Ascending,
    Shr_Descending,
    S_Ascending,
    S_Descending,
    Cpu_Ascending,
    Cpu_Descending,
    Time_Ascending,
    Time_Descending,
    Command_Ascending,
    Command_Descending  //21
};



 
/* Byte-wise swap two items of size SIZE. */
#define SWAP(a, b, size)                                                      \
  do                                                                              \
    {                                                                              \
      size_t __size = (size);                                                      \
      char *__a = (a), *__b = (b);                                              \
      do                                                                      \
        {                                                                      \
          char __tmp = *__a;                                                      \
          *__a++ = *__b;                                                      \
          *__b++ = __tmp;                                                      \
        } while (--__size > 0);                                                      \
    } while (0)
 
int sorting(const void * x,const void * x1, void * arg) {
    data_top * P = (data_top *)x;
    data_top * P1 = (data_top *)x1;
    int flag = *(int*)arg;

    switch( flag) {
        case PID_Ascending:
            return (P->pid - P1->pid);
            break;
        case PID_Descending:
            return (P1->pid - P->pid);
            break;

        case User_Ascending:
            return (strcmp(P->user, P1->user) );
            break;
        case User_Descending:
            return (strcmp(P1->user, P->user) );
            break;

        case Pr_Ascending:
            return (P->pr - P1->pr);
            break;
        case Pr_Descending:
            return (P1->pr - P->pr);
            break;

        case Ni_Ascending:
            return (P->ni - P1->ni);
            break;
        case Ni_Descending:
            return (P1->ni - P->ni);
            break;

        case Virt_Ascending:
            return (P->virt - P1->virt);
            break;
        case Virt_Descending:
            return (P1->virt - P->virt);
            break;

        case Res_Ascending:
            return (P->res - P1->res);
            break;
        case Res_Descending:
            return (P1->res - P->res);
            break;

        case Shr_Ascending:
            return (P->shr - P1->shr);
            break;
        case Shr_Descending:
            return (P1->shr - P->shr);
            break;

        case S_Ascending:
            return (P->S - P1->S);
            break;
        case S_Descending:
            return (P1->S - P->S);
            break;

        case Cpu_Ascending:
            return (P->cpu - P1->cpu);
            break;
        case Cpu_Descending:
            return (P1->cpu - P->cpu);
            break;

        case Time_Ascending:
            return (P->stime - P1->stime);
            break;
        case Time_Descending:
            return (P1->stime - P->stime);
            break;

        case Command_Ascending:
            return (strcmp(P1->com, P->com) );
            break;
        case Command_Descending:
            return (strcmp(P->com, P1->com) );
            break;



    }

}



static void fastsort(char* low, char* hight,size_t size, __compar_d_fn_t cmp, void *arg)
{

    if ( low < hight  )
    {
            char *lo = low; char *hi = hight;

            char* mid = lo + size * ( (hi - lo) / size >> 1 );


            do {
                while ( (*cmp) ( (void*)mid, (void*)lo, arg) > 0)
                    lo += size;


                while ( (*cmp) ( (void*)hi,(void*)mid, arg) > 0)
                    hi -= size;

                if (lo <= hi) {
                    SWAP (lo,hi,size);
                    lo +=size;
                    hi -=size;

                }

            } while (lo <= hi);


            if (hi>low) fastsort(low, hi, size, cmp, arg);
            if (hight>lo) fastsort(lo, hight, size, cmp, arg);
    }
}


void quicksort(void *const pbase, size_t total_elems, size_t size,
                   __compar_d_fn_t cmp, void *arg)
{
    char * low = (char*)pbase;
    char * hight = &low[size * (total_elems - 1)];
    fastsort(low,hight,size,cmp,arg);
}










