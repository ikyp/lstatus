#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <X11/Xlib.h>

#define TIME_BUFF_SIZE 30
#define S_BUFF         12
#define C_BUFF         3
#define TOTAL_BUFF     63
#define STATUS         "/sys/class/power_supply/BAT0/status"
#define CAPACITY       "/sys/class/power_supply/BAT0/capacity"

static const char * time_now(void)
{
	static time_t t;
	static struct tm *now;
	static char time_buffer[TIME_BUFF_SIZE];

	t   = time(NULL);
	now = localtime(&t);
	if (now == NULL) {
		fputs("Localtime Function Error!\n", stderr);
		exit(EXIT_FAILURE);
	}

	if (strftime(time_buffer, TIME_BUFF_SIZE, "%F %A %I:%M %p", now) == 0) {
		fputs("Strftime Function Error!\n", stderr);
		exit(EXIT_FAILURE);
	}

	return time_buffer;
}

static const char * bat_status(void)
{
	static char status[S_BUFF];
	FILE *fs;

	if ((fs = fopen(STATUS, "r")) == NULL) {
		fputs("Fopen Function Error: ", stderr);
		exit(EXIT_FAILURE);
	}

	if (fscanf(fs, "%s", status) <= 0) {
		perror("Fscanf Function Error: ");
		exit(EXIT_FAILURE);
	}
	fclose(fs);

	return status;	
}

static const char * bat_percent(void)
{
	static char percent[C_BUFF];
	FILE *fp;

	if ((fp = fopen(CAPACITY, "r")) == NULL) {
		fputs("Fopen Function Error: ", stderr);
	        exit(EXIT_FAILURE);
	}

	if (fscanf(fp, "%s", percent) <= 0) {
		fputs("Fscanf Function Error: ", stderr);
		exit(EXIT_FAILURE);
	}
	fclose(fp);

	return percent;
}
  

int main(void)
{
	static char total_msg[TOTAL_BUFF];
	
	static Display *dpy;
	if (!(dpy = XOpenDisplay(NULL))) {
		fputs("dwmstatus: cannot open display.\n", stderr);
		exit(EXIT_FAILURE);
	}

	if (access(STATUS, F_OK) == 0) {
		for (;;sleep(1)) {
			snprintf(total_msg, TOTAL_BUFF, "%s Status: %s Power: %s%%", time_now(), bat_status(), bat_percent());
			XStoreName(dpy, DefaultRootWindow(dpy), total_msg);
			XSync(dpy, False);
		}
	} else {
		for (;;sleep(1)) {
			XStoreName(dpy, DefaultRootWindow(dpy), time_now());
			XSync(dpy, False);
		}
	}

	XCloseDisplay(dpy);

        return EXIT_SUCCESS;
}
