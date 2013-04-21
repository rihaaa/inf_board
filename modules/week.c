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
#include "week.h"

static VGImage bg;

static int year_week;
static int week_array[53];

static int first_week_days = 6;
static int first_study_week = 5;

void initWeek(TWidget *Widget, TMain *Main) {
	bg = createImageFromJpeg("skin/week.jpg");

	int i, j = 0;
	for(i = 1; i <= 53; i++){
		week_array[i] = 0;
	}
	for(i = first_study_week; i <= first_study_week+16; i++){
		week_array[i] = 1;
		if(week_array[i-1] == 1){ week_array[i] = 2;}
		if(j == 8){
			week_array[i] = 0;
		}
		j++;
	}
}

void viewWeek(TWidget *Widget, TMain *Main) {
	char str[5];
	
	time_t now = time(NULL);
	struct tm *tnow = localtime( &now );
	
	year_week = (tnow->tm_yday - first_week_days) / 7 + 1;

	if(((tnow->tm_yday - first_week_days) % 7) > 0){
		year_week += 1;
	}
	sprintf(str, "%d", week_array[year_week]);
	Fill(0, 255, 255, 1);
	TextMid(Widget->X+Main->mX+135, Widget->Y+Main->mY+80-40, str, ComicTypeface, 80);
}//270 x 160

void drawWeek(TWidget *Widget, TMain *Main) {
	vgSetPixels(Widget->X+Main->mX, Widget->Y+Main->mY, bg, 0, 0, Main->width, Main->height);
	viewWeek(Widget, Main);
}
