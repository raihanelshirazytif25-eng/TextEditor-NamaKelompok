#ifndef FILEIO_H
#define FILEIO_H

int  checkFileStatus(const char *path);
int  openFile(const char *path);
int  saveFile(const char *path);
void autoSave(void);
void exitManager(void);
long getFileSize(const char *path); //nunjukin ukuran file
int saveAsFile(const char *newPath); //simpen buffer saat ini di file baru
int renameCurrentFile(const char *newPath); //ganti nama file

#endif //TEXTEDITOR_NAMAKELOMPOK_FILEIO_H
