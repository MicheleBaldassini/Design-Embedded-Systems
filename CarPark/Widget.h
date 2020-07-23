#ifndef WIDGET_H_
#define WIDGET_H_

#include "fonts.h"
#include "./lcd-touch/Touch.h"

typedef enum {
	IMAGE, TEXT, BUTTON, PARK
} WidgetType;

typedef enum {
	COLOR, IMAGE1, NONE
} BackgroundMode;

typedef enum {
	FREE, PARKED, ACCEPTING
} PState;

typedef short int Color;

typedef struct {
	const unsigned char *image;
} Image;
#define imginfo(w) ((Image *)((w)->ws))

typedef struct {
	sFONT *font;
	Color color;
	BackgroundMode bmode;
	void *bg;
} Text;
#define txtinfo(w) ((Text *)((w)->ws))
#define txtbgcol(t) ((Color *)((t)->bg))
#define txtbgimg(t) ((Image *) ((t)->bg))

typedef struct {
	const unsigned char *image;
} Button;
#define btninfo(w) ((Button *)((w)->ws))
#define btnimg(b)	((Image *) ((b)->image))

typedef struct {
	PState state;
	const unsigned char *imageFree;
	const unsigned char *imageParked;
	const unsigned char *imageAccept;
} Park;
#define parkinfo(w)				((Park *)(w->ws))
#define getFree(p)				(p)->imageFree
#define getParked(p)			(p)->imageParked
#define getWaitAccept(p)		(p)->imageAccept

typedef struct {
	unsigned short int xl;
	unsigned short int yt;
	unsigned short int xw;
	unsigned short int yh;
	WidgetType wt;
	void *ws;
} Widget;

unsigned char OnTouch(const Widget ws[], unsigned int N, TPoint *press);
//unsigned char DrawInit(Widget ws[]);
unsigned char WPrint(Widget *w, void *s);
unsigned char WClear(Widget *w);

#endif /* BUTTON_H_ */
