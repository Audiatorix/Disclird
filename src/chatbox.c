#include "disclird.h"
#include "chatbox.h"
#include "disclirdutil.h"

#include <ncurses.h>

#include <stdlib.h>


int cb_x = 0,	// Current relative x
    cb_y = 2,	// Current relative y
    cb_pos = 0,	// Current position along the text
    cb_top = 0,	// Index of the topmost line of text displayed
    cb_len = 0, // Text length
    cb_curline = 0;	// Current line along text
wchar_t *cb_text;
uint8_t *cb_line_lens; // The length of each line (to make display easier)


void cb_input(wchar_t ch)
{
	switch (ch)
	{
		case KEY_UP:
			if (cb_curline > 0)
			{
				cb_curline--;
				cb_pos -= cb_x + 1;
				uint8_t diff = cb_x - cb_line_lens[cb_curline] + 1;
				if (diff > 0)
				{
					cb_x -= diff;
					cb_pos -= 1;
				}
				else
				{
					cb_pos += diff - 2;
				}

				if (cb_curline < cb_top)
				{
					cb_top--;
				}
				else
				{
					cb_y++;
				}	
			}
			else // Send to beginning of line if on first line
			{
				cb_pos = 0;
				cb_x = 0;
			}
			return;
		case KEY_DOWN:
			if (cb_pos + cb_line_lens[cb_curline] < cb_len)
			{
				cb_curline++;
				cb_pos += cb_line_lens[cb_curline] - cb_x;
				uint8_t diff = cb_x - cb_line_lens[cb_curline] + 1;
				if (diff > 0)
				{
					cb_x -= diff;
					cb_pos += cb_line_lens[cb_curline];
				}
				else
				{
					cb_pos += cb_x + 1;
				}

				if (cb_curline > cb_top + 2)
				{
					cb_top++;
				}
				else
				{
					cb_y--;
				}
			}
			else // Send to end of line if on last line
			{
				cb_pos = cb_len - 1;
				cb_x = cb_line_lens[cb_curline] - 1;
			}
			return;
		case KEY_LEFT:
			if (cb_pos > 0)
			{
				cb_pos--;
				if (cb_x > 0)
				{
					cb_x--;
				}
				else
				{
					cb_curline--;
					cb_x = cb_line_lens[cb_curline] - 1;
					if (cb_curline < cb_top)
					{
						cb_top--;
					}
					else
					{
						cb_y++;
					}
				}
			}
			return;
		case KEY_RIGHT:
			if (cb_pos < cb_len - 1)
			{
				cb_pos++;
				if (cb_x < cb_line_lens[cb_curline])
				{
					cb_x++;
				}
				else
				{
					cb_curline++;
					cb_x = 0;
					if (cb_curline > cb_top + 2)
					{
						cb_top++;
					}
					else
					{
						cb_y--;
					}
				}
			}
			return;
	}
}

void cb_addtext(wchar_t *text, int len)
{
	// TODO implement
}

void cb_clear()
{
	// TODO implement
}

int cb_gettext(wchar_t *out)
{
	// TODO implement
}

void cb_draw()
{
	int pos = 0, i = 0;
	for (; i < cb_top; i++)
	{
		pos += cb_line_lens[i];
	}

	for (int j = 0; j < 3 && pos < cb_len; j++)
	{
		addnwstr(cb_text + pos, cb_line_lens[i]);
		pos += cb_line_lens[i];
		i++;
	}
}

void cb_draw_init()
{
	move(3, 0);
	for (int i = 0; i < dcli_maxx; i++)
	{
		addch((char) 219);
	}
}

void cb_init()
{
	cb_text = malloc(2001 * sizeof(wchar_t));
	cb_line_lens = malloc(2000);


	// temporary
	for (int i = 0; i < 20; i++)
	{
		cb_text[i] = 'a' + i;
		cb_text[i + 21] = 'a' + i;
	}
	cb_text[20] = '\n';
	cb_len = 42;
}

void cb_resize()
{
	// TODO implement
}


