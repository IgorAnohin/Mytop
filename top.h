

#define BAD_OPEN_DIR 						\
"Error: /proc must be mounted\n"				\
"  To mount /proc at boot you need an /etc/fstab line like:\n"	\
"      /proc   /proc   proc    defaults\n"			\
"  In the meantime, mount /proc /proc -t proc\n"


#define table_size 10000



//from memory.c
extern void meminfo();
extern unsigned kb_main_total;
extern unsigned kb_main_free;
extern unsigned kb_main_used;
extern unsigned kb_main_buffers;
extern unsigned kb_main_cached;
extern unsigned kb_swap_total;
extern unsigned kb_swap_free;
extern unsigned kb_swap_used;

//from time.c
extern char headline[128];
extern char *sprint_uptime();




int
       sort_flag,
	   count_proc,
	   quantity_sleep_proc,
	   quantity_run_proc,
	   quantity_stop_proc,
	   quantity_zomb_proc;



typedef struct Parameters {

long int
	pr,
	userid,
	pid,
	virt,
	res,
	utime,
	stime,
    start_time,
	ni,	
	mem,
   	shr;

char user[150];
char com[1500];
char S;

float cpu;


} data_top;


//from sort.c
typedef int (*compar_d_fn_t)(const void *, const void *, void *);

extern void sort (void *const pbase, size_t total_elems, size_t size, compar_d_fn_t cmp, void *arg);
extern int sorting(const void * x,const void * x1, void * arg);
