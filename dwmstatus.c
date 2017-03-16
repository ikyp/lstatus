#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <X11/Xlib.h>

#define TIME_BUFF_SIZE 33

static Display *dpy;

static void set_status(char *str)
{
	XStoreName(dpy, DefaultRootWindow(dpy), str);
	XSync(dpy, False);
}

static char * time_now(void)
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

int main(void)
{
	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "dwmstatus: cannot open display.\n");
		return 1;
	}

	for (;;sleep(59)) {
		set_status(time_now());
	}

	XCloseDisplay(dpy);

	return 0;
}
