#ifndef CHATBOX_H
#define CHATBOX_H

#include <wchar.h>


void cb_input(wchar_t ch);
void cb_addtext(wchar_t *text, int len);
int cb_gettext(wchar_t *out);
void cb_clear();


#endif
