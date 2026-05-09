#ifndef BUFFER_H
#define BUFFER_H

#define VISIBLE_ROWS    22
#define VISIBLE_COLS    80
#define LINE_NUM_WIDTH  5
#define STATUS_BAR_ROW  24

typedef struct Node{
    char  *text;
    int   len;
    int   capacity;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
	Node *head;
	Node *tail;
	
	Node *curNode;
	Node *viewNode;
	
    int   curRow;
    int   curCol;
    int   viewRow;
    int   viewCol;
    
    int   modified;
    int   totalLines;
    char  filename[260];
    
} Editor;

extern Editor ed;

void initBuffer(void);

void insertCharAt(char c);

void deleteCharAt(void);

int insertNewLine(void);

int mergeLines(void);

void validateCursor(void);

void scrollView(void);

void freeBuffer(void);

#endif 
