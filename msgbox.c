#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

int main(void)
{
    Display *dpy;
    Window root, win;
    XSetWindowAttributes swa;
    GC gc;
    XftFont *fn;
    XftDraw *draw;
    XftColor *col;

    dpy = XOpenDisplay(NULL);
    root = DefaultRootWindow(dpy);
    printf("%p\n", fn);
    swa.background_pixel = 0x353535;
    swa.border_pixel = 0x0a0a0a;
    swa.override_redirect = 1;

    win = XCreateWindow(dpy, root, 10, 10, 100, 100, 0,
                        DefaultDepth(dpy,0), CopyFromParent, 
                        DefaultVisual(dpy,0),
                        CWBackPixel | CWBorderPixel | CWOverrideRedirect, &swa);

    gc = XCreateGC(dpy, win, 0, 0);
    XSetForeground(dpy, gc, 0x992233);

    fn = XftFontOpenName(dpy, 0, "xft: Inconsolata: pixelsize=14px");

    XMapRaised(dpy, win);
    XFillRectangle(dpy, win, gc, 10, 10, 80, 80);
    XftDrawStringUtf8(draw, col, fn, 0, 0, "asd", 3);
    XFlush(dpy);

    getchar();
    XCloseDisplay(dpy);
    return 0;
}
