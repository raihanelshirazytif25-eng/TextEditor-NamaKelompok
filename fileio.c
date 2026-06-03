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
    if (!path || path[0] == '\0' || ed.readOnly) return 0;
    FILE *fp = fopen(path, "wb");
    if (!fp) return 0;

    Node *curr = ed.head;
    while (curr) {
        if (curr->len > 0) fwrite(curr->text, 1, curr->len, fp);
        if (curr->next) fputs("\r\n", fp);
        curr = curr->next;
    }
    
    fclose(fp);
    ed.modified = 0;
    
    if (strcmp(ed.filename, path) != 0) {
        strncpy(ed.filename, path, 259);
        ed.filename[259] = '\0';
    }
    return 1;
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
	if (!newPath || newPath[0] == '\0') return 0;
	
    if (ed.filename[0] == '\0') {
        return saveFile(newPath);
    }
    
    if (ed.modified) {
        if (!saveFile(ed.filename)) return 0;
    }
    
    remove(newPath);
    
    if (rename(ed.filename, newPath) == 0) {
        strncpy(ed.filename, newPath, 259);
        ed.filename[259] = '\0';
        return 1;
    }
    return 0; 
}

void exitManager(void) {
    clearTerminal();
    freeBuffer(); 
    printf("Selesai mengedit, dealokasi memori\n");
    exit(0);
}