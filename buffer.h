#ifndef BUFFER_H
#define BUFFER_H

#define MAX_ROWS        1024
#define MAX_COLS        512
#define VISIBLE_ROWS    22
#define VISIBLE_COLS    80
#define LINE_NUM_WIDTH  5
#define STATUS_BAR_ROW  24
#include <windows.h>

typedef struct {
    char  data[MAX_ROWS][MAX_COLS];
    int   lineLen[MAX_ROWS];
    int   totalLines;
} Buffer;

typedef struct {
    int   curRow;
    int   curCol;
    int   viewRow;
    int   viewCol;
    
    int   modified;
    int   totalLines;
    char  filename[260];
    int   readOnly;
    
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO cbi;
    DWORD  oldConsoleMode;
} Editor;

extern Buffer buf;
extern Editor ed;

void initBuffer(void);

void insertCharAt(int row, int col, char c);

void deleteCharAt(int row, int col);

int insertNewLine(int row, int col);

int mergeLines(int row);

void validateCursor(void);

void scrollView(void);

#endif 
