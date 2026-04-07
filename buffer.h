#ifndef TEXTEDITOR_NAMAKELOMPOK_BUFFER_H
#define TEXTEDITOR_NAMAKELOMPOK_BUFFER_H

void initBuffer(void);

void insertCharAt(int row, int col, char c);

void deleteCharAt(int row, int col);

int insertNewLine(int row, int col);

int mergeLines(int row);

void syncCursor(void);

#endif //TEXTEDITOR_NAMAKELOMPOK_BUFFER_H
