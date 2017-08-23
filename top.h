

#define BAD_OPEN_DIR 						\
"Error: /proc must be mounted\n"				\
"  To mount /proc at boot you need an /etc/fstab line like:\n"	\
"      /proc   /proc   proc    defaults\n"			\
"  In the meantime, mount /proc /proc -t proc\n"


#define table_size 10000
#define max_user_name 32
#define max_command_name 128*1024





int sort_flag;
int count_proc;
int	quantity_sleep_proc;
int	quantity_run_proc;
int	quantity_stop_proc;
int quantity_zomb_proc;



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


//from sort.c
typedef int (*compar_d_fn_t)(const void *, const void *, void *);

extern void quicksort (void *const pbase, size_t total_elems, size_t size, compar_d_fn_t cmp, void *arg);
extern int sorting(const void * x,const void * x1, void * arg);
