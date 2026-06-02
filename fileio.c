#include "fileio.h"
#include "buffer.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkFileStatus(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) return -1; 
    fclose(fp);
    fp = fopen(path, "r+");
    if (!fp) return 2; 
    fclose(fp);
    return 1;
}

int openFile(const char *path) {
    if (!path || path[0] == '\0') return 0;
    
    int status = checkFileStatus(path);
    if (status == -1) {
        freeBuffer();
        initBuffer();
        strncpy(ed.filename, path, 259);
        ed.filename[259] = '\0';
        ed.modified = 0; ed.readOnly = 0;
        return 1;
    }
    
    ed.readOnly = (status == 2) ? 1 : 0;
    FILE *fp = fopen(path, "rb");
    if (!fp) return 0;

    freeBuffer(); 
    initBuffer();
    strncpy(ed.filename, path, 259);
    ed.filename[259] = '\0';
    
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\r') continue;
        if (ch == '\n') insertNewLine(); 
        else insertCharAt((char)ch);
    }
    fclose(fp);
    
    ed.curNode = ed.head;
    ed.viewTop = ed.head;
    ed.curRow = 0; ed.curCol = 0; 
    ed.viewRow = 0; ed.viewCol = 0;
    ed.modified = 0;
    return 1;
}

int saveFile(const char *path) {
//    if (!path || path[0] == '\0' || ed.readOnly) return 0;
//    FILE *fp = fopen(path, "wb");
//    if (!fp) return 0;
//    for (int i = 0; i < buf.totalLines; i++) {
//        if (buf.lineLen[i] > 0) {
//            if (fwrite(buf.data[i], 1, buf.lineLen[i], fp) != (size_t)buf.lineLen[i]) {
//                fclose(fp);
//                return 0; 
//            }
//        }
//        if (i < buf.totalLines - 1) { 
//            if (fputs("\r\n", fp) == EOF) {
//                fclose(fp);
//                return 0;
//            }
//        }
//    }
//    fclose(fp);
//    ed.modified = 0;
//    return 1;
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
    return saveFile(newPath);
}

int renameCurrentFile(const char *newPath) {
//    if (ed.filename[0] == '\0' || !newPath || newPath[0] == '\0') return 0;
//    if (ed.modified) {
//        if (!saveFile(ed.filename)) return 0;
//    }
//    remove(newPath);
//    if (rename(ed.filename, newPath) == 0) {
//        strncpy(ed.filename, newPath, sizeof(ed.filename) - 1);
//        ed.filename[sizeof(ed.filename) - 1] = '\0';
//        return 1;
//    }
//    return 0; 
}

void exitManager(void) {
    clearTerminal();
    freeBuffer(); 
    printf("Selesai mengedit, dealokasi memori\n");
    exit(0);
}