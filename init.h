extern VGImage createImageFromJpeg(const char *);

struct TWidget;
struct TMain;

typedef void (*Tinit)(struct TWidget *Widget, struct TMain *Main);
typedef void (*Tdraw)(struct TWidget *Widget, struct TMain *Main);

typedef struct TWidget {
	int id;
	int state;
	int X;
	int Y;
	int cell;
	Tinit  init;
	Tdraw  draw;
} TWidget;

typedef struct TMain{
	int work;
	int width;
	int height;
	int mX;
	int mY;
} TMain;