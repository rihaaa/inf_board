#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include <fcntl.h>
#include <math.h>
#include <sys/types.h>
#include <signal.h>
#include <wchar.h>
#include <locale.h>

#include "VG/openvg.h"
#include "VG/vgu.h"
#include "fontinfo.h"
#include "shapes.h"

#include "init.h"
#include "modules/title.h"
#include "modules/time.h"
#include "modules/bells.h"
#include "modules/week.h"
#include "modules/lesson.h"
#include "modules/calendar.h"
#include "modules/termo.h"
#include "modules/photos.h"
#include "modules/text.h"

static VGImage background_image;

void initMain(TMain *Main, int width, int height) {
	Main->work = 1;
	background_image = createImageFromJpeg("skin/background.jpg");
	Main->width = width;
	Main->height = height;
	Main->mX = 29;
	Main->mY = 20;
}

const int widget_count = 9;

TWidget Widgets[9] = {
  {0, 1, 0, 0, 0, initTitle, drawTitle},
  {1, 1, 0, 0, 0, initTime, drawTime},
  {2, 1, 0, 0, 0, initBells, drawBells},
  {3, 1, 0, 0, 0, initWeek, drawWeek},
  {4, 1, 0, 0, 0, initLesson, drawLesson},
  {5, 1, 0, 0, 0, initCalendar, drawCalendar},
  {6, 1, 0, 0, 0, initTermo, drawTermo},
  {7, 1, 0, 0, 0, initPhotos, drawPhotos},
  {8, 1, 0, 0, 0, initText, drawText}
};

void loadConf(void)
{
	int i = 0;
	FILE *f;
	
	f = fopen( "data/config.dat", "r" );
	while(!feof(f))
	{
		fscanf(f, "%i %i %i %i %i", &Widgets[i].id, &Widgets[i].state, &Widgets[i].X, &Widgets[i].Y, &Widgets[i].cell);
		i++;
	}
	fclose(f);
}

int main()
{
	setlocale(LC_ALL, "");
	int width, height;
	int i = 0;
	width = 640; height = 480;
	init(&width, &height);
	
	loadConf();
	
	TMain Main;
	
	initMain(&Main, width, height);

	for(i = 0; i <= (widget_count - 1); i++){
		Widgets[i].init( &Widgets[i], &Main );
	}
	
	while(Main.work >= 1) {
		Start(width, height);
		vgSetPixels(Main.mX, Main.mY, background_image, 0, 0, width, height);
		
		loadConf();
		
		for(i = 0; i <= (widget_count -1); i++){
			if(Widgets[i].state == 1){
				Widgets[i].draw( &Widgets[i], &Main );
			}
		}
		End();
		usleep(10000);
	}
	finish();
	exit(0);
	return 0;
}
