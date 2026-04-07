#ifndef FILEIO_H
#define FILEIO_H

void openFile(void);
void saveFile(void);
void parseToBuffer(const char *raw, int rawLen);
int  checkFileStatus(const char *path);
int  flattenBuffer(char **out, int *outLen);

#endif //TEXTEDITOR_NAMAKELOMPOK_FILEIO_H
