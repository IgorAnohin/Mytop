#ifndef _sort_h
#define _sort_h

typedef int (*compar_d_fn_t)(const void *, const void *, void *);

extern void quicksort (void *const pbase, size_t total_elems, size_t size, compar_d_fn_t cmp, void *arg);
extern int sorting(const void * x,const void * x1, void * arg);

#endif
