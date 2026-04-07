#include "editor.h"
#include "buffer.h"
#include <string.h>

void initBuffer(void){
	memset(&buf, 0, sizeof(buf));
    buf.totalLines  = 1;
    buf.lineLen[0]  = 0;
    buf.data[0][0]  = '\0';	
}

void insertCharAt(int row, int col, char c) {
    if (row < 0 || row >= buf.totalLines) return;
    if (col < 0 || col > buf.lineLen[row]) return;
    if (buf.lineLen[row] >= MAX_COLS - 1) {
        resizeBuffer();
        return;
    }
    int len = buf.lineLen[row];
    memmove(&buf.data[row][col + 1], &buf.data[row][col], len - col);
    buf.data[row][col] = c;
    buf.lineLen[row]++;
    buf.data[row][buf.lineLen[row]] = '\0';
    ed.modified = 1;
}

void deleteCharAt(int row, int col) {
    if (row < 0 || row >= buf.totalLines) return;
    if (col < 0 || col >= buf.lineLen[row]) return;
    int len = buf.lineLen[row];
    memmove(&buf.data[row][col], &buf.data[row][col + 1], len - col);
    buf.lineLen[row]--;
    buf.data[row][buf.lineLen[row]] = '\0';
    ed.modified = 1;
}

void insertNewLine(int row, int col) {
    if (buf.totalLines >= MAX_ROWS || row < 0 || row >= buf.totalLines) return;
    for (int i = buf.totalLines; i > row + 1; i--) {
        memcpy(buf.data[i], buf.data[i - 1], buf.lineLen[i - 1] + 1);
        buf.lineLen[i] = buf.lineLen[i - 1];
    }
    int tailLen = buf.lineLen[row] - col;
    memcpy(buf.data[row + 1], &buf.data[row][col], tailLen);
    buf.data[row + 1][tailLen] = '\0';
    buf.lineLen[row + 1] = tailLen;
    buf.data[row][col] = '\0';
    buf.lineLen[row] = col;
    buf.totalLines++;
    ed.modified = 1;
}

void resizeBuffer(void){
	
}

void mergeLines(int row){
	if (row < 0 || row >= buf.totalLines - 1) return;
    int lenA = buf.lineLen[row];
    int lenB = buf.lineLen[row + 1];
    if (lenA + lenB >= MAX_COLS) return;
    memcpy(&buf.data[row][lenA], buf.data[row + 1], lenB);
    buf.lineLen[row] = lenA + lenB;
    buf.data[row][buf.lineLen[row]] = '\0';
    for (int i = row + 1; i < buf.totalLines - 1; i++) {
        memcpy(buf.data[i], buf.data[i + 1], buf.lineLen[i + 1] + 1);
        buf.lineLen[i] = buf.lineLen[i + 1];
    }
    buf.totalLines--;
    ed.modified = 1;
}

void syncCursor(void){
    if (ed.curRow < 0) ed.curRow = 0;
    if (ed.curRow >= buf.totalLines) ed.curRow = buf.totalLines - 1;
    int maxCol = buf.lineLen[ed.curRow];
    if (ed.curCol < 0) ed.curCol = 0;
    if (ed.curCol > maxCol) ed.curCol = maxCol;

    if (ed.curRow < ed.viewRow) ed.viewRow = ed.curRow;
    if (ed.curRow >= ed.viewRow + VISIBLE_ROWS) ed.viewRow = ed.curRow - VISIBLE_ROWS + 1;
    
    if (ed.curCol < ed.viewCol) ed.viewCol = ed.curCol;
    if (ed.curCol >= ed.viewCol + (VISIBLE_COLS - LINE_NUM_WIDTH))
        ed.viewCol = ed.curCol - (VISIBLE_COLS - LINE_NUM_WIDTH) + 1;
}
