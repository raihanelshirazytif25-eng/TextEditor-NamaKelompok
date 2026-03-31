#ifndef TEXTEDITOR_NAMAKELOMPOK_BUFFER_H
#define TEXTEDITOR_NAMAKELOMPOK_BUFFER_H

void initBuffer(void);

void insertCharAt(int row, int col, char c);

void deleteCharAt(int row, int col);

void insertNewLine(int row, int col);

void mergeLines(int row);

void resizeBuffer(void);

void syncCursor(void);

#endif //TEXTEDITOR_NAMAKELOMPOK_BUFFER_H
