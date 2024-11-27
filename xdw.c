/*
	xdw -- simple drawing program for X11.
*/


#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>


/* line widths. */
#define W1 2
#define W2 5
#define W3 10
#define W4 20
#define W5 30
#define W6 40
#define W7 50
#define W8 75
#define W9 110
#define W0 150

/* line width keys. */
#define W1K XK_1
#define W2K XK_2
#define W3K XK_3
#define W4K XK_4
#define W5K XK_5
#define W6K XK_6
#define W7K XK_7
#define W8K XK_8
#define W9K XK_9
#define W0K XK_0

/* colour values. */
#define RED 0xD10000
#define GRN 0x1BD40B
#define BLU 0x0020D6
#define SKY 0x7D9BFF
#define YEL 0xF3F700
#define ORA 0xFF7300
#define OCH 0xCC7722
#define PUP 0xA60F92
#define GRY 0x8F8F8F
#define PIN 0xFF8FC1
#define FST 0x336E18
#define BLK 0x000000
#define BWN 0x804204
#define MAR 0x5A0F14
#define NUD 0xFFF694

/* colour keys. */
#define REDK XK_r
#define GRNK XK_g
#define BLUK XK_b
#define SKYK XK_k
#define YELK XK_y
#define ORAK XK_o
#define OCHK XK_h
#define PUPK XK_p
#define GRYK XK_e
#define PINK XK_i
#define FSTK XK_f
#define BLKK XK_a
#define BWNK XK_w
#define MARK XK_m
#define NUDK XK_u

/* a key for taking a new sheet for drawing. */
#define NEWK XK_grave


/* flag for terminating the program. */
char quit = 0;

/* current colour (eraser is not a colour). */
unsigned long ccol = 0x000000;

/* previous x and y of a pointer. */
int prex = -1;
int prey = -1;


void die(char* msg, ...) {
	va_list args;
	va_start(args, msg);
	dprintf(2, msg, args);
	va_end(args);
	exit(1);
}

void drwline(Display* dpl, Drawable w, GC gc,
	     int x1, int y1, int x2, int y2) {
	XDrawLine(dpl, w, gc, x1, y1, x2, y2);
	prex = x2;
	prey = y2;
}

void setlw(Display* dpl, GC gc, unsigned int wid) {
	XSetLineAttributes(dpl, gc, wid, LineSolid, CapRound, JoinRound);
}

/* set foreground colour. */
void setfg(Display* dpl, GC gc, unsigned long col) {
	XSetForeground(dpl, gc, col);
	ccol = col;
}

/* handle key. */
void hkey(Display* dpl, Drawable w, GC gc, KeySym keysym) {
	switch (keysym) {
		case XK_q: {
			quit = 1;
			break;
		}
		case NEWK: {
			XClearWindow(dpl, w);
			break;
		}
		case W1K: {
			setlw(dpl, gc, W1);
			break;
		}
		case W2K: {
			setlw(dpl, gc, W2);
			break;
		}
		case W3K: {
			setlw(dpl, gc, W3);
			break;
		}
		case W4K: {
			setlw(dpl, gc, W4);
			break;
		}
		case W5K: {
			setlw(dpl, gc, W5);
			break;
		}
		case W6K: {
			setlw(dpl, gc, W6);
			break;
		}
		case W7K: {
			setlw(dpl, gc, W7);
			break;
		}
		case W8K: {
			setlw(dpl, gc, W8);
			break;
		}
		case W9K: {
			setlw(dpl, gc, W9);
			break;
		}
		case W0: {
			setlw(dpl, gc, W0);
			break;
		}
		case REDK: {
			setfg(dpl, gc, RED);
			break;
		}
		case GRNK: {
			setfg(dpl, gc, GRN);
			break;
		}
		case BLUK: {
			setfg(dpl, gc, BLU);
			break;
		}
		case SKYK: {
			setfg(dpl, gc, SKY);
			break;
		}
		case YELK: {
			setfg(dpl, gc, YEL);
			break;
		}
		case ORAK: {
			setfg(dpl, gc, ORA);
			break;
		}
		case OCHK: {
			setfg(dpl, gc, OCH);
			break;
		}
		case PUPK: {
			setfg(dpl, gc, PUP);
			break;
		}
		case GRYK: {
			setfg(dpl, gc, GRY);
			break;
		}
		case PINK: {
			setfg(dpl, gc, PIN);
			break;
		}
		case FSTK: {
			setfg(dpl, gc, FST);
			break;
		}
		case BLKK: {
			setfg(dpl, gc, BLK);
			break;
		}
		case BWNK: {
			setfg(dpl, gc, BWN);
			break;
		}
		case MARK: {
			setfg(dpl, gc, MAR);
			break;
		}
		case NUDK: {
			setfg(dpl, gc, NUD);
			break;
		}
	}
}


int main() {
	Display* dpl = XOpenDisplay(0);
	if (!dpl) die("[xdw]: can't open a display.\n");

	Window w = XCreateSimpleWindow(dpl, XDefaultRootWindow(dpl), 0, 0,
	                    650, 500, 0, 0, 0xFFFFFFFF);


	XClassHint* clshnt = XAllocClassHint();
	clshnt -> res_name = "xdw";
	clshnt -> res_class = "xdw";
	XSetClassHint(dpl, w, clshnt);
	XFree(clshnt);

	XStoreName(dpl, w, "xdw");

	Atom wmdel = XInternAtom(dpl, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(dpl, w, &wmdel, 1);

	XGCValues* gcv = 0;
	GC gc = XCreateGC(dpl, w, 0, gcv);
	setlw(dpl, gc, W3);

	XSelectInput(dpl, w,
		 PointerMotionMask|KeyPressMask
		|Button1MotionMask|ButtonPressMask | ButtonReleaseMask);
	XMapWindow(dpl, w);
	XSync(dpl, False);
	
	XEvent xev;

	while(!quit) {
		while(XPending(dpl)) {
			XNextEvent(dpl, &xev);
			
			switch(xev.type) {
				case MotionNotify: {
					XMotionEvent xmev = xev.xmotion;
					switch (xmev.state) {
						case Button1MotionMask: {
							XSetForeground(dpl, gc, ccol);
							drwline(dpl, w, gc, prex, prey, xmev.x, xmev.y);
							break;
						}
						case Button3MotionMask: {
							XSetForeground(dpl, gc, 0xFFFFFF);
							drwline(dpl, w, gc, prex, prey, xmev.x, xmev.y);
							break;
						}
						default: {
							prex = xmev.x;
							prey = xmev.y;
							break;
						}
					}
					break;
				}
				case KeyPress: {
					XKeyEvent xkev = xev.xkey;
					unsigned int keysym = XKeycodeToKeysym(dpl, xkev.keycode, 0);
					hkey(dpl, w, gc, keysym);
				}
				case ClientMessage: {
					if (xev.xclient.data.l[0] == wmdel) {
						quit = 1;
					}
				}
			}
		}
	
	}

	XCloseDisplay(dpl);

	return 0;
}
