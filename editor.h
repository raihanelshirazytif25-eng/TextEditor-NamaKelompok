#ifndef EDITOR_H
#define EDITOR_H

#include <windows.h>
#include <time.h>
#include <stdio.h>

#define MAX_ROWS        1024
#define MAX_COLS        512
#define VISIBLE_ROWS    22
#define VISIBLE_COLS    80
#define LINE_NUM_WIDTH  5
#define AUTOSAVE_SEC    30
#define STATUS_BAR_ROW  24

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
    char  filename[260];
    time_t lastSave;
    int   readOnly;
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO cbi;
    DWORD  oldConsoleMode;
} Editor;

extern Buffer buf;
extern Editor ed;

#endif