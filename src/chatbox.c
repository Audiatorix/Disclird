#include "chatbox.h"
#include "disclirdutil.h"

#include <ncurses.h>


int cb_x = 0,	// Current relative x
    cb_y = 2,	// Current relative y
    cb_pos = 0,	// Current position along the text
    cb_top = 0,	// Index of the topmost line of text displayed
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
			int len = wstrlen(text);
			if (cb_pos + cb_line_lens[cb_curline] < len)
			{
				cb_curline++;
				cb_pos += cb_line_lens[cb_curline] - cb_x;
				uint8_t diff = cb_x - cb_line_lens[cb_curline] + 1;
				if (diff > 0)
				{
					cb_x -= diff;
					cb_pos += cb_lines_lens[cb_curline];
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
				cb_pos = len - 1;
				cb_x = cb_line_lens[cb_curline] - 1;
			}
			return;
		case KEY_LEFT:
			if (cb_pos == 0)
			{
				
	}
}

void cb_draw()
{
	int toppos = 0, i = 0;
	for (; i < cb_top; i++)
	{
		toppos += cb_line_lens[i];
	}

	int len = wstrlen(text);

	for (i = 0; i < 3 && cb_pos < len; i++)
	{

		addwstr(
}

void cb_draw_init()
{
	move(3, 0);
	for (int i = 0; i < dcli_maxx; i++)
	{
		draw((char) 219);
	}
}

void cb_init()
{
	text = malloc(2001 * sizeof(wchar_t));
	line_lens = malloc(2000);


	// temporary
	for (int i = 0; i < 20; i++)
	{
		text[i] = 'a' + i;
		text[i + 21] = 'a' + i;
	}
	text[20] = '\n';
}
