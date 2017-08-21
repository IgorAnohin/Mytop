#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <alloca.h>
#include <limits.h>
#include <stdlib.h>
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

//for qsort
typedef struct
  {
    char *lo;
    char *hi;
  } stack_node;



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

#define MAX_THRESH 4
#define STACK_SIZE        (8 * sizeof(size_t))
#define PUSH(low, high)        ((void) ((top->lo = (low)), (top->hi = (high)), ++top))
#define        POP(low, high)        ((void) (--top, (low = top->lo), (high = top->hi)))
#define        STACK_NOT_EMPTY        (stack < top)
 //////////////////////////////////////////////////////////////////


int sorting(const void * x,const void * x1, void * arg) {
    data_top * P = (data_top *)x;
    data_top * P1 = (data_top *)x1;
    int flag = *(int*)arg;

    switch( flag) {
        case PID:
            return (P->pid < P1->pid);
            break;
        case Pid:
            return (P->pid > P1->pid);
            break;

        case USER:
            return (!strcmp(P->user, P1->user) );
            break;
        case User:
            return (strcmp(P->user, P1->user) );
            break;

        case PR:
            return (P->pr < P1->pr);
            break;
        case Pr:
            return (P->pr > P1->pr);
            break;

        case NI:
            return (P->ni < P1->ni);
            break;
        case Ni:
            return (P->ni > P1->ni);
            break;

        case VIRT:
            return (P->virt < P1->virt);
            break;
        case Virt:
            return (P->virt > P1->virt);
            break;

        case RES:
            return (P->res < P1->res);
            break;
        case Res:
            return (P->res > P1->res);
            break;

        case SHR:
            return (P->shr < P1->shr);
            break;
        case Shr:
            return (P->shr > P1->shr);
            break;

        case SS:
            return (P->S < P1->S);
            break;
        case Ss:
            return (P->S > P1->S);
            break;

        case CPU:
            return (P->cpu < P1->cpu);
            break;
        case Cpu:
            return (P->cpu > P1->cpu);
            break;

        case TIME:
            return (P->stime < P1->stime);
            break;
        case Time:
            return (P->stime > P1->stime);
            break;

        case COMMAND:
            return (!strcmp(P->com, P1->com) );
            break;
        case Command:
            return (strcmp(P->com, P1->com) );
            break;



    }

}

//    qsort(solution,count_proc, sizeof(parametrs),sorting);
/*
static int partition(parametrs * mass, int lower, int higher){
    int average = (lower+higher)/2;
    void * mid = &mass[average];
    int i = lower;
    int j = higher;
    while (i < j) {
        while (sorting( (void*)(&mass[i]),mid) > 0 )
            i++;
        while (!sorting( (void *)(&mass[j]),mid) > 0 )
            j--;
        if (i <= j) {
            parametrs temp;
            temp = mass[i];
            mass[i] = mass[j];
            mass[j] = temp;
        }
    }
    return (i + 1);

}

void myqsort(parametrs * mas, int lower, int higher){
    if (lower < higher) {
        int middle = partition(mas,lower,higher);
        myqsort(mas,lower,middle-1);
        myqsort(mas,middle,higher);
    }
}
*/
void myqsort (void *const pbase, size_t total_elems, size_t size, compar_d_fn_t cmp, void *arg) {

    char *base_ptr = (char *) pbase;
    const size_t max_thresh = MAX_THRESH * size;

      if (total_elems > MAX_THRESH)
        {
          char *lo = base_ptr;
          char *hi = &lo[size * (total_elems - 1)];
          stack_node stack[STACK_SIZE];
          stack_node *top = stack;

          PUSH (NULL, NULL);

          while (STACK_NOT_EMPTY)
            {
              char *left_ptr;
              char *right_ptr;

              /* Select median value from among LO, MID, and HI. Rearrange
                 LO and HI so the three values are sorted. This lowers the
                 probability of picking a pathological pivot value and
                 skips a comparison for both the LEFT_PTR and RIGHT_PTR in
                 the while loops. */

              char *mid = lo + size * ((hi - lo) / size >> 1);

              if ((*cmp) ((void *) mid, (void *) lo, arg) < 0)
                SWAP (mid, lo, size);
              if ((*cmp) ((void *) hi, (void *) mid, arg) < 0)
                SWAP (mid, hi, size);
              else
                goto jump_over;
              if ((*cmp) ((void *) mid, (void *) lo, arg) < 0)
                SWAP (mid, lo, size);
            jump_over:;

              left_ptr  = lo + size;
              right_ptr = hi - size;

              /* Here's the famous ``collapse the walls'' section of quicksort.
                 Gotta like those tight inner loops!  They are the main reason
                 that this algorithm runs much faster than others. */
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

              /* Set up pointers for next iteration.  First determine whether
                 left and right partitions are below the threshold size.  If so,
                 ignore one or both.  Otherwise, push the larger partition's
                 bounds on the stack and continue sorting the smaller one. */

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

      /* Once the BASE_PTR array is partially sorted by quicksort the rest
         is completely sorted using insertion sort, since this is efficient
         for partitions below MAX_THRESH size. BASE_PTR points to the beginning
         of the array to sort, and END_PTR points at the very last element in
         the array (*not* one beyond it!). */

    #define min(x, y) ((x) < (y) ? (x) : (y))

      {
        char *const end_ptr = &base_ptr[size * (total_elems - 1)];
        char *tmp_ptr = base_ptr;
        char *thresh = min(end_ptr, base_ptr + max_thresh);
        char *run_ptr;

        /* Find smallest element in first threshold and place it at the
           array's beginning.  This is the smallest array element,
           and the operation speeds up insertion sort's inner loop. */

        for (run_ptr = tmp_ptr + size; run_ptr <= thresh; run_ptr += size)
          if ((*cmp) ((void *) run_ptr, (void *) tmp_ptr, arg) < 0)
            tmp_ptr = run_ptr;

        if (tmp_ptr != base_ptr)
          SWAP (tmp_ptr, base_ptr, size);

        /* Insertion sort, running from left-hand-side up to right-hand-side.  */

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
}










