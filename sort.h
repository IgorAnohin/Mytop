#ifndef _sort_h
#define _sort_h

#define __USE_GNU
#include <stdlib.h>

void quicksort (void *const pbase, size_t total_elems, size_t size, __compar_d_fn_t cmp, void *arg);

#endif
