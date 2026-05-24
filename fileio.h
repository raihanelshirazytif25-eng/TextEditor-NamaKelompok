#ifndef FILEIO_H
#define FILEIO_H

#include "buffer.h"

int  checkFileStatus(const char *path);
int  openFile(const char *path);
int  saveFile(const char *path);
void exitManager(void);
long getFileSize(const char *path); 
int saveAsFile(const char *newPath); 
int renameCurrentFile(const char *newPath); 

#endif 
