#include "buffer.h"
#include <stdlib.h>
#include <string.h>

<<<<<<< Updated upstream
static Node* createNode(void) {
=======
Node* createNode(void) {
>>>>>>> Stashed changes
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) exit(1);
    newNode->capacity = 64; 
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
    
    ed.curCol = 0; ed.curRow = 0;
    ed.viewCol = 0; ed.viewRow = 0;
    ed.totalLines = 1;
    ed.modified = 0;
    ed.filename[0] = '\0';
}

void insertCharAt(char c){

}

void deleteCharAt(int row, int col){
//    if (row < 0 || row >= buf.totalLines) return;
//    if (col < 0 || col >= buf.lineLen[row]) return;
//    int len = buf.lineLen[row];
//    memmove(&buf.data[row][col], &buf.data[row][col + 1], len - col);
//    buf.lineLen[row]--;
//    buf.data[row][buf.lineLen[row]] = '\0';
//    ed.modified = 1;
}

int insertNewLine(int row, int col){
//    if (buf.totalLines >= MAX_ROWS || row < 0 || row >= buf.totalLines) return 0;
//    for (int i = buf.totalLines; i > row + 1; i--){
//        memcpy(buf.data[i], buf.data[i - 1], buf.lineLen[i - 1] + 1);
//        buf.lineLen[i] = buf.lineLen[i - 1];
//    }
//    int tailLen = buf.lineLen[row] - col;
//    memcpy(buf.data[row + 1], &buf.data[row][col], tailLen);
//    buf.data[row + 1][tailLen] = '\0';
//    buf.lineLen[row + 1] = tailLen;
//    buf.data[row][col] = '\0';
//    buf.lineLen[row] = col;
//    buf.totalLines++;
//    ed.modified = 1;
//    return 1;
}

int mergeLines(int row){
//    if (row < 0 || row >= buf.totalLines - 1) return 0;
//    int lenA = buf.lineLen[row];
//    int lenB = buf.lineLen[row + 1];
//    if (lenA + lenB >= MAX_COLS - 1) return 0;
//    memcpy(&buf.data[row][lenA], buf.data[row + 1], lenB);
//    buf.lineLen[row] = lenA + lenB;
//    buf.data[row][buf.lineLen[row]] = '\0';
//    for (int i = row + 1; i < buf.totalLines - 1; i++){
//        memcpy(buf.data[i], buf.data[i + 1], buf.lineLen[i + 1] + 1);
//        buf.lineLen[i] = buf.lineLen[i + 1];
//    }
//    buf.totalLines--;
//    ed.modified = 1;
//    return 1;
}

//memecah syncCursor menjadi dua for being modular able
void validateCursor(void){
//    if (ed.curRow < 0) ed.curRow = 0;
//    if (ed.curRow >= buf.totalLines) ed.curRow = buf.totalLines - 1;
//    
//    int maxCol = buf.lineLen[ed.curRow];
//    if (ed.curCol < 0) ed.curCol = 0;
//    if (ed.curCol > maxCol) ed.curCol = maxCol;
}

void scrollView(void){
//    //vertical scroll
//    if (ed.curRow < ed.viewRow) ed.viewRow = ed.curRow;
//    if (ed.curRow >= ed.viewRow + VISIBLE_ROWS) 
//        ed.viewRow = ed.curRow - VISIBLE_ROWS + 1;
//    
//    //horizontal scroll
//    if (ed.curCol < ed.viewCol) ed.viewCol = ed.curCol;
//    if (ed.curCol >= ed.viewCol + (VISIBLE_COLS - LINE_NUM_WIDTH))
//        ed.viewCol = ed.curCol - (VISIBLE_COLS - LINE_NUM_WIDTH) + 1;
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
