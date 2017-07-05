#include "disclird.h"
#include "chatbox.h"
#include "disclirdutil.h"

#include <ncurses.h>

#include <stdlib.h>
#include <string.h>


int cb_x = 0,		// Current relative x
    cb_y = 2,		// Current relative y
    cb_pos = 0,		// Current position along the text
    cb_top = 0,		// Index of the topmost line of text displayed
    cb_lines = 0,	// Number of lines
    cb_len = 0, 	// Text length
    cb_curline = 0;	// Current line along text
wchar_t *cb_text;
uint16_t *cb_line_lens;	// The length of each line (to make display easier)


void cb_input(wchar_t ch)
{
	switch (ch)
	{
		case KEY_UP:
			if (cb_curline > 0)
			{
				cb_curline--;
				cb_pos -= cb_x + 1;
				int diff = cb_x - cb_line_lens[cb_curline] + 1;
				if (diff > 0)
				{
					cb_x -= diff;
				}
				else
				{
					cb_pos += diff;
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
			if (cb_curline + 1 < cb_lines)
			{
				cb_pos += cb_line_lens[cb_curline] - cb_x - 1;
				cb_curline++;
				int diff = cb_x - cb_line_lens[cb_curline] + 1;
				if (diff > 0)
				{
					cb_x -= diff;
					cb_pos += cb_line_lens[cb_curline];
					if (cb_curline + 1 == cb_lines)
					{
						cb_pos++;
						cb_x++;
					}
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
				cb_pos = cb_len;
				cb_x = cb_line_lens[cb_curline];
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
				if (cb_x < cb_line_lens[cb_curline] - 1)
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
			else if (cb_pos == cb_len - 1)
			{
				cb_pos++;
				if (cb_x == dcli_maxx)
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
				else
				{
					cb_x++;
				}
			}
			return;
	}
	
}

void cb_addtext(wchar_t *text, int len)
{
	// TODO implement (does this need to exist?)
}

void cb_clear()
{
	cb_x = 0;
	cb_y = 2;
	cb_pos = 0;
	cb_top = 0;
	cb_lines = 0;
	cb_len = 0;
	cb_curline = 0;
	memset(cb_line_lens, 0, 4000);
}

int cb_gettext(wchar_t *out)
{
	memcpy(out, cb_text, cb_len);
	*(out + cb_len) = 0;
	return cb_len;
}

void cb_draw()
{
	/*char buf[dcli_maxx];
	sprintf(buf, "x: %d, y: %d, top: %d, pos: %d, curline: %d      ", cb_x, cb_y, cb_top, cb_pos, cb_curline);
	move(dcli_maxy - 4, 0);
	addstr(buf);*/

	// skip undisplayed lines above top
	int pos = 0, i = 0;
	for (; i < cb_top; i++)
	{
		pos += cb_line_lens[i];
	}

	dcli_color_set(COLOR_WHITE, COLOR_BLACK);
	move(dcli_maxy - 3, 0);
	for (int j = 0; j < 3 && pos < cb_len; j++)
	{
		addnwstr(cb_text + pos, cb_line_lens[i]);
		pos += cb_line_lens[i];
		i++;
	}
	move(dcli_maxy - (cb_y + 1), cb_x);
}

void cb_draw_init()
{
	move(dcli_maxy - 4, 0);
	dcli_color_set(COLOR_BLACK, COLOR_WHITE);
	int i = 0;
	for (; i < dcli_maxx; i++)
	{
		addch(' ');
	}
	/*dcli_color_set(COLOR_BLACK, COLOR_BLACK);
	i = dcli_maxx * 3 - 3;
	for (int j = 0; j < i; j++)
	{
		addch(' ');
	}*/
}

void cb_init()
{
	cb_text = malloc(2000 * sizeof(wchar_t));
	cb_line_lens = malloc(4000);


	// temporary
	for (int i = 0; i < 5; i++)
	{
		cb_text[i] = 'a' + i;
	}
	cb_line_lens[0] = 6;
	for (int i = 0; i < 20; i++)
	{
		cb_text[6 + i] = 'a' + i;
	}
	cb_line_lens[1] = 20;
	cb_text[5] = '\n';
	cb_len = 26;
	cb_lines = 2;
}

void cb_resize()
{
	// TODO implement
}
