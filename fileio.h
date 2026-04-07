#ifndef FILEIO_H
#define FILEIO_H

int  checkFileStatus(const char *path);
int  flattenBuffer(char **out, int *outLen);
void parseToBuffer(const char *raw, int rawLen);
void openFile(void);
void saveFile(void);
void autoSave(void);
void exitManager(void);

#endif //TEXTEDITOR_NAMAKELOMPOK_FILEIO_H
