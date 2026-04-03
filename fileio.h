#ifndef TEXTEDITOR_NAMAKELOMPOK_FILEIO_H
#define TEXTEDITOR_NAMAKELOMPOK_FILEIO_H

#include <stdio.h>

#ifndef MAX_COLS
#define MAX_COLS 1024
#endif

extern char **buffer2D;
extern int max_lines;
extern int num_lines;
extern int cx;
extern int cy;
extern int row_offset;
extern char current_filename[256];

void saveFile(void);
void saveAsFile(void);
void openFile(void);
void exitManager(void);

#endif //TEXTEDITOR_NAMAKELOMPOK_FILEIO_H
