#include "editor.h"
#include "fileio.h"
#include "buffer.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkFileStatus(const char *path) {
    DWORD attr = GetFileAttributesA(path);
    if (attr == INVALID_FILE_ATTRIBUTES) return -1;
    if (attr & FILE_ATTRIBUTE_READONLY) return 2;
    return 1;
}

int flattenBuffer(char **out, int *outLen) {
    int total = 0;
    for (int i = 0; i < buf.totalLines; i++) total += buf.lineLen[i] + 2;
    char *flat = (char *)malloc(total + 1);
    if (!flat) return 0;
    int pos = 0;
    for (int i = 0; i < buf.totalLines; i++) {
        memcpy(flat + pos, buf.data[i], buf.lineLen[i]);
        pos += buf.lineLen[i];
        if (i < buf.totalLines - 1) { flat[pos++] = '\r'; flat[pos++] = '\n'; }
    }
    flat[pos] = '\0'; *out = flat; *outLen = pos;
    return 1;
}

void parseToBuffer(const char *raw, int rawLen) {
    initBuffer();
    int row = 0, col = 0;
    for (int i = 0; i < rawLen && row < MAX_ROWS; i++) {
        if (raw[i] == '\r') continue;
        if (raw[i] == '\n') {
            buf.lineLen[row] = col; buf.data[row][col] = '\0';
            row++; col = 0;
        } else if (col < MAX_COLS - 1) {
            buf.data[row][col++] = raw[i];
        }
    }
    buf.lineLen[row] = col; buf.data[row][col] = '\0';
    buf.totalLines = (row == 0 && col == 0) ? 1 : row + 1;
}

int openFile(const char *path) {
    if (!path || path[0] == '\0') return 0;
    int status = checkFileStatus(path);
    if (status == -1) {
        initBuffer();
        strncpy(ed.filename, path, sizeof(ed.filename) - 1);
        ed.modified = 0; ed.readOnly = 0;
        return 1;
    }
    ed.readOnly = (status == 2) ? 1 : 0;
    FILE *fp = fopen(path, "rb");
    if (!fp) return 0;
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    if (size <= 0) {
        fclose(fp); initBuffer();
        strncpy(ed.filename, path, sizeof(ed.filename) - 1);
        ed.modified = 0; return 1;
    }
}
