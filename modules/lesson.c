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
#include <wchar.h>

#include "../init.h"
#include "lesson.h"

static VGImage bg;

/*
int tm_sec; 	Секунды от начала минуты - [0,60][1]
int tm_min; 	Минуты от начала часа - [0,59]
int tm_hour; 	Часы от полуночи - [0,23]
int tm_mday; 	Число месяца - [1,31]
int tm_mon; 	Месяцы после января - [0,11]
int tm_year; 	Года с 1900
int tm_wday; 	Дни с воскресенья - [0,6]
int tm_yday; 	Дни с первого января - [0,365]
int tm_isdst; 	Признак летнего времени
*/
//$ sudo date 0418083013

typedef struct TLessons {
	int id;
	int type;
	int start;
	int end;
	int length;
} TLessons;


TLessons Lessons[100];

int lesson_array_count = 0;

void loadLessons(void)
{
	int i = 1;
	lesson_array_count = 0;
	FILE *f;
	
	f = fopen( "data/lessons.dat", "r" );
	while(!feof(f))
	{
		fscanf(f, "%i %i %i %i %i", &Lessons[i].id, &Lessons[i].type, &Lessons[i].start, &Lessons[i].end, &Lessons[i].length);
		i++;
		lesson_array_count++;
	}
	fclose(f);
}

void initLesson(TWidget *Widget, TMain *Main) {
	bg = createImageFromJpeg("skin/lesson.jpg");
	loadLessons();
}

void viewLesson(TWidget *Widget, TMain *Main){
	int l_number = 0;
	wchar_t* l_text = L"-";
	time_t now = time(NULL);
	struct tm *tnow = localtime( &now );
	
	int time_mix = 0;
	time_mix = tnow->tm_hour*3600 + tnow->tm_min*60 + tnow->tm_sec;
	
	//id, type, start, end, len
	int i = 0;
	char l_numb[5];
	
	char timer_left[10];
	
	int time_diff, d_min, d_sec = 0;
	
	for(i = 1; i <= (lesson_array_count + 1); i++){
		if((time_mix >= Lessons[i].start) && (time_mix < Lessons[i].end)) {
			if(time_mix < (Lessons[i].end - 3000)) time_diff = Lessons[i].end - 3000 - time_mix;
			else time_diff = Lessons[i].end - time_mix;
	
			l_number = i;
			l_text = L"pāris";
			if((time_mix >= (Lessons[i].start + Lessons[i].length)) && (time_mix < (Lessons[i].end - Lessons[i].length))) {
				time_diff = Lessons[i].end - Lessons[i].length - time_mix;
				l_text = L"starpbrīdis";
			}
		}
		if((time_mix >= Lessons[(i - 1)].end) && (time_mix < Lessons[i].start)) {
			time_diff = Lessons[i].start - time_mix;
			l_text = L"starpbrīdis";
		}
	}
	if(time_mix < (Lessons[1].start - 1800)){
		time_diff = 0;
		l_text = L"-";
	}
	if((time_mix >= (Lessons[1].start - 1800)) && (time_mix < Lessons[1].start)){
		time_diff = Lessons[1].start - time_mix;
	}
	d_min = time_diff / 60;
	d_sec = time_diff % 60;

	sprintf(timer_left, "%02i:%02i", d_min, d_sec);
	
	Fill(50, 205, 50, 1);
	if(time_diff < 60) Fill(255, 0, 0, 1);
	TextMid(Widget->X+Main->mX+135, Widget->Y+Main->mY+30-15, timer_left, TimesTypeface, 30);
	
	Fill(0, 0, 0, 1);
	if(l_number > 0) {
		sprintf(l_numb, "%i.", l_number);
		TextMid(Widget->X+Main->mX+135, Widget->Y+Main->mY+120-25, l_numb, TimesTypeface, 50);
	}
	else{
		TextMid(Widget->X+Main->mX+135, Widget->Y+Main->mY+120-25, "-", TimesTypeface, 50);
	}
	TextMidW(Widget->X+Main->mX+135, Widget->Y+Main->mY+70-10, l_text, TimesTypeface, 20);
	/*
	if((time_mix >= 830) && (time_mix < 1005)) {
		l_number = "1.";
		l_text = "paris";
	}*/
}

void drawLesson(TWidget *Widget, TMain *Main) {
	vgSetPixels(Widget->X+Main->mX, Widget->Y+Main->mY, bg, 0, 0, Main->width, Main->height);
	viewLesson(Widget, Main);
}
