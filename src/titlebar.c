#include "titlebar.h"
#include "disclird.h"
#include "disclirdutil.h"

#include <string.h>
#include <stdlib.h>

#include <ncurses.h>


char *server, *channel, *desc;

void tb_setserver(char *_server)
{
	str_realloc_copy(_server, &server);
}

void tb_setchannel(char *_channel, char *_desc)
{
	str_realloc_copy(_channel, &channel);
	str_realloc_copy(_desc, &desc);
}

void tb_draw()
{
	dcli_color_set(COLOR_BLACK, COLOR_WHITE);
	move(0, 1);
	printw(server);
	printw(" | ");
	printw(channel);
	printw(": ");
	int x, descmax; // replace this with a scrolling description?
	getyx(dcli_window, descmax, x);
	descmax = dcli_maxx - x - strlen(DCLI_VERSION) - 6;
	if (strlen(desc) > descmax)
	{
		char *cutdesc = malloc(descmax + 4);
		memcpy(cutdesc, desc, descmax);
		strcpy(cutdesc + descmax, "...");
		printw(cutdesc);
		free(cutdesc);
	}
	else
	{
		printw(desc);
	}
}

void tb_draw_init()
{
	dcli_color_set(COLOR_BLACK, COLOR_WHITE);
	int space = dcli_maxx - DCLI_VERSION_LEN - 1;
	for (int i = 0; i < space; i++)
	{
		addch(' ');
	}
	printw(DCLI_VERSION);
	addch(' ');
}
