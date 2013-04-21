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
#include "photos.h"

static VGImage bg;

void initPhotos(TWidget *Widget, TMain *Main) {
	bg = createImageFromJpeg("skin/photos.jpg");
}

void drawPhotos(TWidget *Widget, TMain *Main) {
	vgSetPixels(Widget->X+Main->mX, Widget->Y+Main->mY, bg, 0, 0, Main->width, Main->height);
}