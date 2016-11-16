#include <stdio.h>
#include <X11/Xlib.h>

int main(int argc, char **argv)
{
    char *fontname = argc > 1 ? argv[1] : "9x15";
    Display *dpy = XOpenDisplay(NULL);
    int i, n;
    char **fonts = XListFonts(dpy, fontname, -1, &n);

    printf("%d fonts:\n", n);
    for (i=0; i<n; i++) {
        puts(fonts[i]);
    }

    XCloseDisplay(dpy);
    return 0;
}
