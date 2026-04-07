#ifndef FILEIO_H
#define FILEIO_H

int  checkFileStatus(const char *path);
int  openFile(const char *path);
int  saveFile(const char *path);
void autoSave(void);
void exitManager(void);

#endif //TEXTEDITOR_NAMAKELOMPOK_FILEIO_H
