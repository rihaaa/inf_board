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
#include "calendar.h"

#include <wchar.h>

static VGImage bg;
static VGImage calendar_cache;

char *cache_file = "data/calendar_cache.jpg";

void initCalendar(TWidget *Widget, TMain *Main) {
	bg = createImageFromJpeg("skin/calendar.jpg");
	makeCalendarCache(Widget, Main);
	calendar_cache = createImageFromJpeg(cache_file);
}

void fillMonth(int month) {
	if(month == 0) Fill(0, 255, 0, 1);
	if(month == 1) Fill(34, 139, 34, 1);
	if(month == 2) Fill(65, 105, 225, 1);
	if(month == 3) Fill(0, 0, 255, 1);
	if(month == 4) Fill(34, 139, 34, 1);
	if(month == 5) Fill(0, 0, 255, 1);
	if(month == 6) Fill(0, 255, 0, 1);
	if(month == 7) Fill(0, 0, 255, 1);
	if(month == 8) Fill(0, 255, 0, 1);
	if(month == 9) Fill(0, 0, 255, 1);
	if(month == 10) Fill(0, 255, 0, 1);
	if(month == 11) Fill(0, 0, 255, 1);
}

void makeCalendarCache(TWidget *Widget, TMain *Main) {
	vgSetPixels(Widget->X+Main->mX, Widget->Y+Main->mY, bg, 0, 0, Main->width, Main->height);
	int x_interval = 25;
	int y_interval = 15;
	int font_size = 10;
	int month_start = 1;//Jan 0 ~ Dec 11
	
	int x_inc = 0;
	int y_inc = 0;
	int week_num_x_inc = 10;
	int month_names_x_inc = 10;
	time_t now = time(NULL);
    struct tm * timeinfo = localtime( &now );
	char str[5];
    int m, i, j;
	wchar_t* month[] = { L"janvāris", L"februāris", L"marts", L"aprīlis", L"maijs", L"jūnijs", L"jūlijs", L"augusts", L"septembris", L"oktobris", L"novembris", L"decembris"};
    
    //year = 2013;
    //timeinfo->tm_year = year-1900; //years numerated from 1900
	int today_m = timeinfo->tm_mon;
	int today_d = timeinfo->tm_mday;
	
	timeinfo->tm_mon = month_start;
 
    m = -1;
	int week = 0;
	while(m < (month_start + 5) ) {
		for(i = 1; i < 33; i++) {   
			timeinfo->tm_mday = i;
			mktime (timeinfo);
	
			if(timeinfo->tm_mon > m) { 
				//конец месяца
				y_inc = 0;
				for(j = 1; j < (timeinfo->tm_wday); j++)
					y_inc -= y_interval;
				if (m >= month_start) { 
					fillMonth(m);
					TextMidW(Widget->X+Main->mX+50+month_names_x_inc, Widget->Y+Main->mY+10, month[m], ComicTypeface, font_size);
					month_names_x_inc += 110;
				}
				fillMonth(timeinfo->tm_mon);
				m++;
				break;
			}
			if (m==11 && timeinfo->tm_mon ==0) { 
				//конец года
				m++;
				break;
			}
			fillMonth(timeinfo->tm_mon);
			if((today_m == timeinfo->tm_mon) && (today_d == timeinfo->tm_mday)){
				Fill(160, 32, 240, 1);
			}
			sprintf(str, "%4d", timeinfo->tm_mday);
			Text(Widget->X+Main->mX+5+x_inc, Widget->Y+Main->mY+120+y_inc, str, ComicTypeface, font_size);
			y_inc -= y_interval;
			if(timeinfo->tm_wday==0) {
				//конец недели
				y_inc = 0; 
				x_inc += x_interval;
				week++;
				if(week <= 16) {
					sprintf(str, "%i", week);
				}
				else{
					sprintf(str, "%i", week-16);
				}
				if(week == 21){
					sprintf(str, "%s", "B");
				}
				
				if((timeinfo->tm_mday == 31) && (timeinfo->tm_mon == 2)){
					week--;
					sprintf(str, "%s", "B");
				}
				
				Fill(178, 34, 34, 1);
				Text(Widget->X+Main->mX+5+week_num_x_inc, Widget->Y+Main->mY+140, str, ComicTypeface, font_size);
				week_num_x_inc += x_interval;
			}
		}
	}
	DoSnapshot(565, 160, Widget->X+Main->mX, Widget->Y+Main->mY, cache_file);
}

void drawCalendar(TWidget *Widget, TMain *Main) {
	time_t now = time(NULL);
	struct tm *tnow = localtime( &now );
	int time_mix = tnow->tm_hour*3600 + tnow->tm_min*60 + tnow->tm_sec;
	if(time_mix == 3600){
		makeCalendarCache(Widget, Main);
		calendar_cache = 0;
		calendar_cache = createImageFromJpeg(cache_file);
	}
	vgSetPixels(Widget->X+Main->mX, Widget->Y+Main->mY, calendar_cache, 0, 0, Main->width, Main->height);
}