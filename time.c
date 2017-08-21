#include <math.h>
#include <utmp.h> 
#include <sys/ioctl.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>




char headline[128];
static double av[3];

char *sprint_uptime() {
	FILE * ptrtime;
	char buffer[100];
	struct utmp *utmpstruct;
	int upminutes, uphours, updays;
	int pos;
	struct tm *realtime;
	time_t realseconds;
	int numuser;
	double uptime_secs, idle_secs;

/* first get the current time */

	time(&realseconds);
	realtime = localtime(&realseconds);
	pos = sprintf(headline, " %02d:%02d:%02d ",
	realtime->tm_hour, realtime->tm_min, realtime->tm_sec);

/* read and calculate the amount of uptime */

	ptrtime = fopen("/proc/uptime","r");
	fgets(buffer,100,ptrtime);
	sscanf(buffer,"%lf %lf",&uptime_secs,&idle_secs);
	fclose(ptrtime);


	updays = (int) uptime_secs / (60*60*24);
	strcat (headline, "up ");
	pos += 3;
	if (updays)
		pos += sprintf(headline + pos, "%d day%s, ", updays, (updays != 1) ? "s" : "");
	upminutes = (int) uptime_secs / 60;
	uphours = upminutes / 60;
	uphours = uphours % 24;
	upminutes = upminutes % 60;
	if(uphours)
		pos += sprintf(headline + pos, "%2d:%02d, ", uphours, upminutes);
	else
		pos += sprintf(headline + pos, "%d min, ", upminutes);

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


