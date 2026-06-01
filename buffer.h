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

Node* createNode(void);

void initBuffer(void);

void insertCharAt(char c);

void deleteCharAt(void);

int insertNewLine(void);

int mergeLines(void);

void validateCursor(void);

void scrollView(void);

void freeBuffer(void);

#endif
