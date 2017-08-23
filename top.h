#ifndef _top_h
#define _top_h



#define max_user_name 32
#define max_command_name 128*1024


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

char user[max_user_name];
char com[max_command_name];
char S;

float cpu;


} data_top;

#endif
