#ifndef DISPLAY_H
#define DISPLAY_H

void drawScreen(void);
void drawCurrentLine(void); 
void drawLineNumbers(int screenRow, int bufRow);
void drawStatusBar(void);
void handleNavigation(int key);
void clearTerminal(void);
void setTerminalMode(int raw);
int  readKey(void);
void showPrompt(const char *msg, char *out, int maxLen);

#endif
