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

int openFile(const char *path) {
    if (!path || path[0] == '\0') return 0;
    int status = checkFileStatus(path);
    if (status == -1) {
        initBuffer();
        strncpy(ed.filename, path, sizeof(ed.filename) - 1);
		ed.filename[sizeof(ed.filename) - 1] = '\0';
        ed.modified = 0; ed.readOnly = 0;
        return 1;
    }
    ed.readOnly = (status == 2) ? 1 : 0;
    FILE *fp = fopen(path, "rb");
    if (!fp) return 0;
    initBuffer();
    int row = 0, col = 0;
    int ch;
    while ((ch = fgetc(fp)) != EOF && row < MAX_ROWS) {
        if (ch == '\r') continue;
        if (ch == '\n') {
            buf.lineLen[row] = col; 
            buf.data[row][col] = '\0';
            row++; 
            col = 0;
        } else if (col < MAX_COLS - 1) {
            buf.data[row][col++] = (char)ch;
        }
    }
    if (row < MAX_ROWS) {
        buf.lineLen[row] = col; 
        buf.data[row][col] = '\0';
        buf.totalLines = (row == 0 && col == 0) ? 1 : row + 1;
    } else {
        buf.totalLines = MAX_ROWS;
    }
    fclose(fp);
    strncpy(ed.filename, path, sizeof(ed.filename) - 1);
	ed.filename[sizeof(ed.filename) - 1] = '\0';
    ed.modified = 0; ed.curRow = 0; ed.curCol = 0; ed.viewRow = 0; ed.viewCol = 0;
    return 1;
}

int saveFile(const char *path) {
    if (!path || path[0] == '\0' || ed.readOnly) return 0;
    FILE *fp = fopen(path, "wb");
    if (!fp) return 0;
    for (int i = 0; i < buf.totalLines; i++) {
        if (buf.lineLen[i] > 0) {
            if (fwrite(buf.data[i], 1, buf.lineLen[i], fp) != (size_t)buf.lineLen[i]) {
                fclose(fp);
                return 0; 
            }
        }
        if (i < buf.totalLines - 1) { 
            if (fputs("\r\n", fp) == EOF) {
                fclose(fp);
                return 0;
            }
        }
    }
    fclose(fp);
    ed.modified = 0; 
    ed.lastSave = time(NULL);
    return 1;
}

void autoSave(void) {
    if (!ed.modified || ed.filename[0] == '\0' || ed.readOnly) return;
    if (difftime(time(NULL), ed.lastSave) >= AUTOSAVE_SEC) saveFile(ed.filename);
}

void exitManager(void) {
    setTerminalMode(0);
    clearTerminal();
    printf("Editor ditutup.\n");
}
