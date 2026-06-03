#include "buffer.h"
#include <stdlib.h>
#include <string.h>

Editor ed;

Node* createNode(void) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) exit(1);
    newNode->capacity = MAX_CAPACITY; 
    newNode->text = (char*)malloc(newNode->capacity);
    newNode->text[0] = '\0';
    newNode->len = 0;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void initBuffer(void) {
    ed.head = createNode();
    ed.tail = ed.head;
    ed.curNode = ed.head;
    ed.viewTop = ed.head;
    
    ed.curCol = 0; 
	ed.curRow = 0;
    ed.viewCol = 0; 
	ed.viewRow = 0;
    ed.totalLines = 1;
    ed.modified = 0;
    ed.filename[0] = '\0';
}

void insertCharAt(char c){
    Node *curr = ed.curNode;
    if (curr->len + 1 >= curr->capacity) {
        curr->capacity *= 2;
        curr->text = (char*)realloc(curr->text, curr->capacity);
    }
    memmove(&curr->text[ed.curCol + 1], &curr->text[ed.curCol], curr->len - ed.curCol);
    curr->text[ed.curCol] = c;
    curr->len++;
    curr->text[curr->len] = '\0';
    ed.curCol++;
    ed.modified = 1;	
}

void deleteCharAt(void){
    Node *curr = ed.curNode;
    if (ed.curCol == 0) return;
    ed.curCol--;
    memmove(&curr->text[ed.curCol], &curr->text[ed.curCol + 1], curr->len - ed.curCol);
    curr->len--;
    curr->text[curr->len] = '\0';
    ed.modified = 1;
}

int insertNewLine(void){
    Node *curr = ed.curNode;
    Node *newNode = createNode();
    int tailLen = curr->len - ed.curCol;

    if (tailLen > 0) {
        if (tailLen + 1 > newNode->capacity) {
            newNode->capacity = tailLen + 1;
            newNode->text = (char*)realloc(newNode->text, newNode->capacity);
        }
        memcpy(newNode->text, &curr->text[ed.curCol], tailLen);
        newNode->len = tailLen;
        newNode->text[newNode->len] = '\0';
        curr->len = ed.curCol;
        curr->text[curr->len] = '\0';
    }

    newNode->prev = curr;
    newNode->next = curr->next;
    if (curr->next) curr->next->prev = newNode;
    else ed.tail = newNode;
    curr->next = newNode;

    ed.curNode = newNode;
    ed.curRow++;
    ed.curCol = 0;
    ed.totalLines++;
    ed.modified = 1;
    return 1;
}

int mergeLines(int row){
    Node *curr = ed.curNode;
    if (!curr->prev) return 0;
    
    Node *upNode = curr->prev;
    int oldCol = upNode->len;
    
    if (upNode->len + curr->len + 1 > upNode->capacity) {
        upNode->capacity = upNode->len + curr->len + 1;
        upNode->text = (char*)realloc(upNode->text, upNode->capacity);
    }
    
    memcpy(&upNode->text[upNode->len], curr->text, curr->len);
    upNode->len += curr->len;
    upNode->text[upNode->len] = '\0';
    
    upNode->next = curr->next;
    if (curr->next) curr->next->prev = upNode;
    else ed.tail = upNode;
    
    free(curr->text);
    free(curr);
    
    ed.curNode = upNode;
    ed.curRow--;
    ed.curCol = oldCol;
    ed.totalLines--;
    ed.modified = 1;
    return 1;
}

void validateCursor(void){
    if (ed.curCol < 0) ed.curCol = 0;
    if (ed.curCol > ed.curNode->len) ed.curCol = ed.curNode->len;
}

void scrollView(void){
	//vertikal
    while (ed.curRow < ed.viewRow) {
        if (ed.viewTop->prev){
	        ed.viewTop = ed.viewTop->prev;
	        ed.viewRow--;	
		}
    }
    while (ed.curRow >= ed.viewRow + VISIBLE_ROWS) { 
        if (ed.viewTop->next){
        	ed.viewTop = ed.viewTop->next;
        	ed.viewRow++;
		}
    }
    //hori...miya
    if (ed.curCol < ed.viewCol) ed.viewCol = ed.curCol;
    if (ed.curCol >= ed.viewCol + VISIBLE_COLS) ed.viewCol = ed.curCol - VISIBLE_COLS + 1;
}

void freeBuffer(void) {
    Node *curr = ed.head;
    while (curr) {
        Node *temp = curr;
        curr = curr->next;
        free(temp->text);
        free(temp);
    }
}
