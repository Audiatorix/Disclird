#ifndef DISCLIRD_H
#define DISCLIRD_H

#define DCLI_VERSION "Disclird 1.0.0"
#define DCLI_VERSION_LEN 14

#include <ncurses.h>


int dcli_maxx, dcli_maxy;
WINDOW *dcli_window; 

void dcli_color_set(uint8_t fg, uint8_t bg);


#endif
