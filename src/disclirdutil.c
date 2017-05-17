#include "disclirdutil.h"

#include <ncurses.h>

#include <string.h>
#include <stdlib.h>


void str_realloc_copy(char *src, char **dest)
{
	free(*dest);
	int len = strlen(src);
	*dest = malloc(len);
	memcpy(*dest, src, len);
}

void draw_ascii_box(int startx, int starty, int endx, int endy)
{
	move(starty, startx);
	draw();
}

int wstrlen(wchar_t *str)
{
	int len = 0;
	while (str[len] != 0)
	{
		len++;
	}
	return len;
}
