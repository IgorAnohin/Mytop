#ifndef _top_h
#define _top_h

#define __USE_POSIX
#include <limits.h>



typedef struct {

    long int pr;
    long int userid;
    long int pid;
    long int virt;
    long int res;
    long int utime;
    long int stime;
    long int start_time;
    long int ni;
    long int mem;
    long int shr;

    char user[LOGIN_NAME_MAX];
    char com[NAME_MAX];
    char S;

    float cpu;


} data_top;

#endif
