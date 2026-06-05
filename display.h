#ifndef DISPLAY_H
#define DISPLAY_H
#define KEY_ENTER     13
#define KEY_BACKSPACE  8
#define KEY_UP       1000
#define KEY_DOWN     1001
#define KEY_LEFT     1002
#define KEY_RIGHT    1003
#define KEY_CTRL_O   15
#define KEY_CTRL_S   19
#define KEY_CTRL_Q   17
#define KEY_CTRL_R   18
#define IS_PRINTABLE(c) ((c) >= 32 && (c) <= 126)
#include "buffer.h"

void drawScreen(void);
void drawCurrentLine(void); 
void drawLineNumbers(int screenRow, int bufRow);
void drawStatusBar(void);
void moveCursorTo(int row, int col);
void clearTerminal(void);
void setTerminalMode(int raw); 
int  readKey(void);
void showPrompt(const char *msg, char *out, int maxLen);

#endif
