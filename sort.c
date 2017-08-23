#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <alloca.h>
#include <limits.h>
#define __USE_GNU
#include <stdlib.h>
#include <string.h>


 
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










