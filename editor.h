#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>

#define VISIBLE_ROWS    22
#define VISIBLE_COLS    80
#define LINE_NUM_WIDTH  5
#define STATUS_BAR_ROW  24

typedef struct LineText{
    char  *data;
    int   lineLen;
    int   memCap;
    struct LineText *prev;
    struct LineText *next;
} LineText;

typedef struct {
	LineText *head;
	LineText *tail;
	
	LineText *curNode;
	LineText *viewNode;
	
    int   curRow;
    int   curCol;
    int   viewRow;
    int   viewCol;
    
    int   modified;
    int   totalLines;
    char  filename[260];
    
} Editor;

extern LineText lt;
extern Editor ed;

#endif