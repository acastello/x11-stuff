#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>
#include <X11/extensions/Xrender.h>

#define PADSTR "_"
#define BORDERW 2
#define DEFAULT_PATTERN "Fucking niggers. (%s)"

Display *dpy;
Window root;
XftColor col;

int width(XftFont *font, char *str)
{
    XGlyphInfo gi;
    XftTextExtents8(dpy, font, (FcChar8 *) str, strlen(str), &gi);
    return gi.width;
}

int parse_args(int argc, char **argv, char **pattern_ret, char **fontnames_ret)
{
    int i, n = 0;
    
    for (i=1; i<argc; i++) {
        if ( !strcmp(argv[i], "-d") ) {
            *pattern_ret = argv[++i];
        }
        else 
            fontnames_ret[n++] = argv[i];
    }

    if (n == 0) {
        fontnames_ret[n++] = "9x15";
    }

    return n;
}

int main(int argc, char **argv)
{
    char *fontname, *pattern = DEFAULT_PATTERN, *fontnames[argc], str[4096];
    int i, n = parse_args(argc, argv, &pattern, fontnames);

    dpy = XOpenDisplay(NULL);
    root = DefaultRootWindow(dpy);

    int x, y;
    Window window_ret;
    int int_ret;
    XQueryPointer(dpy, root, &window_ret, &window_ret, &x, &y, &int_ret, &int_ret, &int_ret);

    for (i=0, fontname=fontnames[i]; i<n; i++, fontname=fontnames[i]) {
        sprintf(str, pattern, fontname, fontname, fontname, fontname);
        
        XftFont *font = XftFontOpenName(dpy, DefaultScreen(dpy), fontname);
        int asc = font->ascent,
            desc = font->descent,
            hpad = width(font, PADSTR),
            vpad = 0.2*font->height,
            wid = 2*hpad + width(font, str),
            height = 2*vpad + asc+desc;

        XSetWindowAttributes attr = {
            .override_redirect = 1,
            .background_pixel = 0x222222,
            .border_pixel = 0xbabdb6,
        };

        col = (XftColor) {0xbabdb6, { 0xba00, 0xbd00, 0xb600, 0xffff} };

        Window window = XCreateWindow(dpy, root, x-BORDERW-hpad,
                y-BORDERW-2, wid, height, BORDERW, CopyFromParent, InputOutput, DefaultVisual(dpy, DefaultScreen(dpy)), 
                CWBorderPixel | CWBackPixel | CWOverrideRedirect, &attr);
        y+=12+height;
        XSelectInput(dpy, window, KeyPressMask | ButtonPressMask);

        XftDraw *draw = XftDrawCreate(dpy, window, DefaultVisual(dpy, DefaultScreen(dpy)), 
                DefaultColormap(dpy, DefaultScreen(dpy)));

        XMapWindow(dpy, window);
        XftDrawString8(draw, &col, font, hpad, asc+vpad, str, strlen(str));
    }
    XFlush(dpy);

    XEvent ev;
    XNextEvent(dpy, &ev);


    XCloseDisplay(dpy);
    return 0;
}
