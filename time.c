#include <math.h>
#include <utmp.h> 
#include <sys/ioctl.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <string.h>
#include <time.h>



char headline[128];
static double av[3];

char *sprint_uptime() {
    struct sysinfo info;

	FILE * ptrtime;
	char buffer[100];
	struct utmp *utmpstruct;
	int pos;
	struct tm *realtime;
	time_t realseconds;
	int numuser;

    int error = sysinfo(&info);

/* first get the current time */

	time(&realseconds);
	realtime = localtime(&realseconds);
    pos = sprintf(headline, " %02d:%02d:%02d up",
	realtime->tm_hour, realtime->tm_min, realtime->tm_sec);


    struct tm *runtime;
    runtime = gmtime( &info.uptime );
    pos += sprintf(headline + pos, "  %02d:%02d, ",realtime->tm_hour, realtime->tm_min);


/* count the number of users */

	numuser = 0;
	setutent();
	while ((utmpstruct = getutent())) {
		if ((utmpstruct->ut_type == USER_PROCESS) &&
		   (utmpstruct->ut_name[0] != '\0'))
			numuser++;
		}
	endutent();

	pos += sprintf(headline + pos, "%2d user%s, ", numuser, numuser == 1 ? "" : "s");


	ptrtime = fopen("/proc/loadavg","r");
	fgets(buffer,100,ptrtime);
	sscanf(buffer,"%lf %lf %lf",&av[0], &av[1], &av[2]);
	fclose(ptrtime);


	pos += sprintf(headline + pos, " load average: %.2f, %.2f, %.2f",
						 av[0], av[1], av[2]);

    return headline;
}


