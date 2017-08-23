#pragma once
#ifndef _sort_h
#define _sort_h

#include <stdlib.h>
#define __COMPAR_FN_T
#define __USE_GNU
typedef int (*__compar_d_fn_t)(const void *, const void *, void *);

void quicksort (void *const pbase, size_t total_elems, size_t size, __compar_d_fn_t cmp, void *arg);

#endif
