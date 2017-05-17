#include "disclird.h"
#include "titlebar.h"

#include <ncurses.h>

#include <signal.h>
#include <unistd.h>


void color_init();
void test_tb();

int main()
{
	dcli_window = initscr();
	cbreak();
	noecho();
	getmaxyx(dcli_window, dcli_maxy, dcli_maxx);

	color_init();
	test_tb();
	while (1)
	{
		addch(getch());
	}

	endwin();

	return 0;
}

void test_tb()
{
	tb_setserver("Test Server");
	tb_setchannel("Test Channel", "spicy memes and spicy memes and spicy memesspicy memes and spicy memes and spicy memesspicy memes and spicy memes and spicy memesspicy memes and spicy memes and spicy memesspicy memes and spicy memes and spicy memesspicy memes and spicy memes and spicy memes");
	tb_draw_init();
	tb_draw();
	refresh();
	getch();
}

void color_init()
{
	start_color();
	for (uint8_t fg = 0; fg < 8; fg++)
	{
		for (uint8_t bg = 0; bg < 8; bg++)
		{
			init_pair((fg << 4) | bg, fg, bg);
		}
	}
}

void dcli_color_set(uint8_t fg, uint8_t bg)
{
	attron(COLOR_PAIR((fg << 4) | bg));
}
