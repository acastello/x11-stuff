#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

int main(int argc, char **argv)
{
    Display *dpy = XOpenDisplay(NULL);
    char *fontname = argc > 1 ? argv[1] : "9x15";
    XftFont *font = XftFontOpenName(dpy, DefaultScreen(dpy), fontname);
    printf("%x\n", font);
    printf("%d %d %d %s\n", font->ascent, font->descent, font->max_advance_width, font->pattern);

    XCloseDisplay(dpy);
    return 0;
}
