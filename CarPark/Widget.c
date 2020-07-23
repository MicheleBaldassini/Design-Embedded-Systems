#include "Widget.h"

unsigned char contains(const Widget *w, TPoint *point) {
	if ((point->x >= w->xl) && (point->x <= w->xl + w->xw)
			&& (point->y >= w->yt) && (point->y <= w->yt + w->yh)) {
		return 1;
	} else
		return 0;
}

unsigned char WPrint(Widget *w, void *s) {
	unsigned char *imgptr = 0;
	Text *txt;
	PState ps;
	switch (w->wt) {
	case TEXT:
		WClear(w);
		txt = txtinfo(w);
		LCD_SetTextColor(txt->color);
		LCD_SetFont(txt->font);
		LCD_DisplayStringXY(w->xl, w->yt, (char *) s);
		return 1;
	case PARK:
		ps = *(PState *) s;
		if (ps == FREE) {
			imgptr = getFree(parkinfo(w));
		} else if (ps == PARKED) {
			imgptr = getParked(parkinfo(w));
		} else if (ps == ACCEPTING) {
			imgptr = getWaitAccept(parkinfo(w));
		} else {
			return 0;
		}
		parkinfo(w)->state = ps;
		break;
	case IMAGE:
		imgptr = imginfo(w)->image;
		break;
	}
	if (imgptr != 0) {
		LCD_DrawPicture(w->xl, w->yt, w->xw, w->yh, imgptr);
		return 1;
	}
	return 0;
}

unsigned char WClear(Widget *w) {
	Text *txt = txtinfo(w);
	switch (w->wt) {
	case TEXT:
		if (txtinfo(w)->bmode == COLOR) {
			Color bg = *txtbgcol(txt);
			LCD_SetTextColor(bg);
			LCD_SetBackColor(bg);
			LCD_DrawFullRect(w->xl, w->yt, w->xw, w->yh);
		}
		if (txt->bmode == IMAGE1) {
			LCD_DrawPicture(w->xl, w->yt, w->xw, w->yh, txtbgimg(txt)->image);
		}
		return 1;
	case IMAGE:
	case PARK:
		LCD_DrawFullRect(w->xl, w->yt, w->xw, w->yh);
		return 1;
	}
	return 0;
}
