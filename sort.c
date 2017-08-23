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
 
//typedef int (*__compar_d_fn_t) (const void *, const void *, void *);

#define MAX_THRESH 4
 
/* Stack node declarations used to store unfulfilled partition obligations. */
typedef struct
  {
    char *lo;
    char *hi;
  } stack_node;
 

#define STACK_SIZE        (CHAR_BIT * sizeof(size_t))
#define PUSH(low, high)        ((void) ((top->lo = (low)), (top->hi = (high)), ++top))
#define POP(low, high)        ((void) (--top, (low = top->lo), (high = top->hi)))

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

//    qsort(solution,count_proc, sizeof(parametrs),sorting);



void quicksort (void *const pbase, size_t total_elems, size_t size,
            __compar_d_fn_t cmp, void *arg)

{
  char *base_ptr = (char *) pbase;
 
  const size_t max_thresh = MAX_THRESH * size;
 
 
  if (total_elems > MAX_THRESH)
    {
      char *lo = base_ptr;
      char *hi = &lo[size * (total_elems - 1)];
      stack_node stack[STACK_SIZE];
      stack_node *top = stack;
 
      PUSH (NULL, NULL);
 
      while (stack < top)
        {
          char *left_ptr;
          char *right_ptr;
 
          //small element
          char *mid = lo + size * ((hi - lo) / size >> 1);
 
          if ( (*cmp) ((void *) mid, (void *) lo, arg) < 0)
            SWAP (mid, lo, size);
          if ( (*cmp) ((void *) hi, (void *) mid, arg) < 0)
            SWAP (mid, hi, size);
          
 
          left_ptr  = lo + size;
          right_ptr = hi - size;
 

          do
            {
              while ((*cmp) ((void *) left_ptr, (void *) mid, arg) < 0)
                left_ptr += size;
 
              while ((*cmp) ((void *) mid, (void *) right_ptr, arg) < 0)
                right_ptr -= size;
 
              if (left_ptr < right_ptr)
                {
                  SWAP (left_ptr, right_ptr, size);
                  if (mid == left_ptr)
                    mid = right_ptr;
                  else if (mid == right_ptr)
                    mid = left_ptr;
                  left_ptr += size;
                  right_ptr -= size;
                }
              else if (left_ptr == right_ptr)
                {
                  left_ptr += size;
                  right_ptr -= size;
                  break;
                }
            }
          while (left_ptr <= right_ptr);
 
 
          if ((size_t) (right_ptr - lo) <= max_thresh)
            {
              if ((size_t) (hi - left_ptr) <= max_thresh)
                /* Ignore both small partitions. */
                POP (lo, hi);
              else
                /* Ignore small left partition. */
                lo = left_ptr;
            }
          else if ((size_t) (hi - left_ptr) <= max_thresh)
            /* Ignore small right partition. */
            hi = right_ptr;
          else if ((right_ptr - lo) > (hi - left_ptr))
            {
              /* Push larger left partition indices. */
              PUSH (lo, right_ptr);
              lo = left_ptr;
            }
          else
            {
              /* Push larger right partition indices. */
              PUSH (left_ptr, hi);
              hi = right_ptr;
            }
        }
    }
 

 
#define min(x, y) ((x) < (y) ? (x) : (y))
 

    char *const end_ptr = &base_ptr[size * (total_elems - 1)];
    char *tmp_ptr = base_ptr;
    char *thresh = min(end_ptr, base_ptr + max_thresh);
    char *run_ptr;
 
    
    //smallest element
    for (run_ptr = tmp_ptr + size; run_ptr <= thresh; run_ptr += size)
      if ((*cmp) ((void *) run_ptr, (void *) tmp_ptr, arg) < 0)
        tmp_ptr = run_ptr;
 
    if (tmp_ptr != base_ptr)
      SWAP (tmp_ptr, base_ptr, size);
 

    //insert sort
    run_ptr = base_ptr + size;
    while ((run_ptr += size) <= end_ptr)
      {
        tmp_ptr = run_ptr - size;
        while ((*cmp) ((void *) run_ptr, (void *) tmp_ptr, arg) < 0)
          tmp_ptr -= size;
 
        tmp_ptr += size;
        if (tmp_ptr != run_ptr)
          {
            char *trav;
 
            trav = run_ptr + size;
            while (--trav >= run_ptr)
              {
                char c = *trav;
                char *hi, *lo;
 
                for (hi = lo = trav; (lo -= size) >= tmp_ptr; hi = lo)
                  *hi = *lo;
                *hi = c;
              }
          }
      }

}








