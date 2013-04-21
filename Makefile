inf_board: inf_board.c includes/openvg/oglinit.o
	@rm -f inf_board 
	gcc   -Wall -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -Iincludes/openvg -o  inf_board modules/title.c modules/time.c modules/bells.c modules/week.c modules/lesson.c modules/calendar.c modules/termo.c modules/photos.c modules/text.c inf_board.c includes/openvg/libshapes.o includes/openvg/oglinit.o -L/opt/vc/lib -lGLESv2 -ljpeg
