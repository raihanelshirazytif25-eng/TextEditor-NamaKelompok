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
	
}

void syncCursor(void){
	
}