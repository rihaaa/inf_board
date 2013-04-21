#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include <fcntl.h>
#include <math.h>
#include <sys/types.h>
#include <signal.h>
#include "VG/openvg.h"
#include "VG/vgu.h"
#include "fontinfo.h"
#include "shapes.h"

#include "../init.h"
#include "time.h"

static VGImage bg;

void initTime(TWidget *Widget, TMain *Main) {
	bg = createImageFromJpeg("skin/time.jpg");
}

void viewTime(TWidget *Widget, TMain *Main) {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	Fill(0, 0, 0, 1);
	char str[100];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%H:%M:%S", timeinfo);
	sprintf(str, "%s", buffer);
	TextMid(Widget->X+Main->mX+136, Widget->Y+Main->mY+72-20, str, SerifTypeface, 40);
	
	strftime(buffer, 80, "%d. %B", timeinfo);
	sprintf(str, "%s", buffer);
	TextMid(Widget->X+Main->mX+136, Widget->Y+Main->mY+36-10, str, SerifTypeface, 20);
}

void drawTime(TWidget *Widget, TMain *Main) {
	vgSetPixels(Widget->X+Main->mX, Widget->Y+Main->mY, bg, 0, 0, Main->width, Main->height);
	viewTime(Widget, Main);
}