#ifndef BUFFER_H
#define BUFFER_H

typedef struct Node {
    char *text;
    int len;
    int capacity;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    
    Node *curNode;      
    Node *viewTop;      

    int curCol;
    int curRow;
    int viewCol;
    int viewRow;
    
    int totalLines;
    int modified;
    int readOnly;
    char filename[260];
} Editor;

extern Editor ed;

void initBuffer(void);

void insertCharAt(int row, int col, char c);

void deleteCharAt(int row, int col);

int insertNewLine(int row, int col);

int mergeLines(int row);

void validateCursor(void);

void scrollView(void);

#endif
