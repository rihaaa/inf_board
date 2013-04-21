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
#include "text.h"

#include <wchar.h>

static FILE *f;
static int X, Y;
static int N;
static int Nmax;
static wchar_t str [150];

void initText(TWidget *Widget, TMain *Main) {
	wchar_t temp [150];
	Y = Main->mY + Widget->Y;
	X = Main->width + 1000;
	N = 1;
	Nmax = 1;
	f = fopen ( "data/text.dat", "r" );
	fwscanf (f, L"%ls", str);
	while(!feof(f))
	{
		fwscanf (f, L"%ls", temp);
		Nmax += 1;
	}
	fclose(f);
}

void drawText(TWidget *Widget, TMain *Main) {
	Fill(0, 255, 255, 1);
	Y = Main->mY + Widget->Y;
	X = X - 5;
	if(X <= -300) {
		if(Nmax == N){
			N = 0;
		}
		N+= 1;
		f = fopen ( "data/text.dat", "r" );
		int A = 1;
		while(A <= N) {
			A += 1;
			fwscanf (f, L"%ls", str);
		}
		X = Main->width + 1000;
		fclose(f);
	}
	
	TextEndW(X, Y, str, ComicTypeface, 40);
	/*
	if (X <= (Main->width - 50)){ 
		DoSnapshot(1221, 685, Main->mX, Main->mY, "screen.jpg");sleep(5);
	}
	*/
}