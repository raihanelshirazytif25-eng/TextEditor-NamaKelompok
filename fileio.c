#include "editor.h"
#include "fileio.h"
#include "buffer.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkFileStatus(const char *path) {
    
}

int openFile(const char *path) {
    
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

void exitManager(void) {
    setTerminalMode(0);
    clearTerminal();
    printf("Editor ditutup.\n");
}

long getFileSize(const char *path) {
    if (!path || path[0] == '\0') return 0;
    FILE *fp = fopen(path, "rb");
    if (!fp) return 0;
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return (size < 0) ? 0 : size;
}

int saveAsFile(const char *newPath) {
    if (!newPath || newPath[0] == '\0') return 0;
    FILE *fp = fopen(newPath, "wb");
    if (!fp) return 0;
    fclose(fp); 
    strncpy(ed.filename, newPath, sizeof(ed.filename) - 1);
    ed.filename[sizeof(ed.filename) - 1] = '\0';
    ed.readOnly = 0; 
    return saveFile(ed.filename);
}

int renameCurrentFile(const char *newPath) {
    if (ed.filename[0] == '\0' || !newPath || newPath[0] == '\0') return 0;
    if (ed.modified) {
        if (!saveFile(ed.filename)) return 0;
    }
    if (rename(ed.filename, newPath) == 0) {
        strncpy(ed.filename, newPath, sizeof(ed.filename) - 1);
        ed.filename[sizeof(ed.filename) - 1] = '\0';
        return 1;
    }
    return 0; 
}
