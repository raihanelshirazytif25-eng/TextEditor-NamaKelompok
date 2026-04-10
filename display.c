#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "editor.h"
#include "display.h"
#include "buffer.h"

void moveCursorTo(int row, int col) {
    COORD c = {(SHORT)col, (SHORT)row};
    SetConsoleCursorPosition(ed.hConsole, c);
}

void setColor(int fg, int bg) {
    SetConsoleTextAttribute(ed.hConsole, (WORD)(bg << 4 | fg));
}

void resetColor(void) {
    SetConsoleTextAttribute(ed.hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void handleNavigation(int key) {
    int oldRow = ed.curRow;
    switch(key) {
        case 1000: ed.curRow--; break;
        case 1001: ed.curRow++; break;
        case 1002: if (ed.curCol > 0) ed.curCol--; else if (ed.curRow > 0) { ed.curRow--; ed.curCol = buf.lineLen[ed.curRow]; } break;
        case 1003: if (ed.curCol < buf.lineLen[ed.curRow]) ed.curCol++; else if (ed.curRow < buf.totalLines - 1) { ed.curRow++; ed.curCol = 0; } break;
        case 1004: ed.curCol = 0; break;
        case 1005: ed.curCol = buf.lineLen[ed.curRow]; break;
    }
    validateCursor();
    scrollView();
}

void drawRow(int screenRow, int bufRow) {
    moveCursorTo(screenRow, 0);

    if (bufRow >= buf.totalLines) {
        setColor(8, 0); printf("    ~ "); resetColor();
        COORD pos = {LINE_NUM_WIDTH, (SHORT)screenRow}; DWORD written;
        FillConsoleOutputCharacter(ed.hConsole, ' ', VISIBLE_COLS - LINE_NUM_WIDTH, pos, &written);
        return;
    }

    drawLineNumbers(screenRow, bufRow);
    moveCursorTo(screenRow, LINE_NUM_WIDTH);
    setColor(7, 0);

    for (int c = 0; c < VISIBLE_COLS - LINE_NUM_WIDTH; c++) {
        int idx = ed.viewCol + c;
        if (idx < buf.lineLen[bufRow]) {
            char ch = buf.data[bufRow][idx];
            putchar(ch >= 32 && ch < 127 ? ch : ' ');
        } else {
            putchar(' ');
        }
    }
    resetColor();
}

void drawScreen(void) {
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(ed.hConsole, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(ed.hConsole, &cci);

    for (int sr = 0; sr < VISIBLE_ROWS; sr++) {
        drawRow(sr, ed.viewRow + sr);
    }

    drawStatusBar();
    moveCursorTo(ed.curRow - ed.viewRow, LINE_NUM_WIDTH + (ed.curCol - ed.viewCol));
    cci.bVisible = TRUE;
    SetConsoleCursorInfo(ed.hConsole, &cci);
}

void drawLineNumbers(int screenRow, int bufRow) {
    moveCursorTo(screenRow, 0);
    if (bufRow == ed.curRow) setColor(15, 0);
    else setColor(8, 0);
    printf("%4d ", bufRow + 1);
    resetColor();
}

void drawCurrentLine(void) {
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(ed.hConsole, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(ed.hConsole, &cci);


    drawRow(ed.curRow - ed.viewRow, ed.curRow);
    drawStatusBar(); 

    moveCursorTo(ed.curRow - ed.viewRow, LINE_NUM_WIDTH + (ed.curCol - ed.viewCol));
    cci.bVisible = TRUE;
    SetConsoleCursorInfo(ed.hConsole, &cci);
}

void drawStatusBar(void) {
    moveCursorTo(VISIBLE_ROWS, 0);
    setColor(7, 0);
    char left[100], right[60], bar[VISIBLE_COLS + 1];
    long size = (ed.filename[0] != '\0') ? getFileSize(ed.filename) : 0;
    snprintf(left, 100, " %s%s%s | %ld bytes ", ed.filename[0] ? ed.filename : "[Untitled]", ed.modified ? " [*]" : "", ed.readOnly ? " [RO]" : "", size);
    snprintf(right, 60, " Ln %d, Col %d | ^S=Save ^R=Rename ^Q=Quit ", ed.curRow+1, ed.curCol+1);
    memset(bar, ' ', VISIBLE_COLS); bar[VISIBLE_COLS] = '\0';
    memcpy(bar, left, strlen(left));
    memcpy(bar + (VISIBLE_COLS - strlen(right)), right, strlen(right));
    printf("%.*s", VISIBLE_COLS, bar);
    resetColor();
}


int readKey(void) {
    int c = _getch();
    if (c == 0 || c == 224) {
        int c2 = _getch();
        switch (c2) {
            case 72: return 1000; case 80: return 1001; case 75: return 1002; case 77: return 1003;
            case 71: return 1004; case 79: return 1005; case 83: return 1010;
        }
    }
    return c;
}

void showPrompt(const char *msg, char *out, int maxLen) {
    moveCursorTo(VISIBLE_ROWS, 0);
    setColor(0, 11); printf("%-*s", VISIBLE_COLS, msg);
    moveCursorTo(VISIBLE_ROWS, (int)strlen(msg));
    setTerminalMode(0);
    if (fgets(out, maxLen, stdin)) {
        out[strcspn(out, "\n")] = 0;
    }
    setTerminalMode(1); resetColor();
}

void clearTerminal(void) {
    COORD coordScreen = {0, 0};
    DWORD charsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(ed.hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(ed.hConsole, ' ', dwConSize, coordScreen, &charsWritten);
    FillConsoleOutputAttribute(ed.hConsole, csbi.wAttributes, dwConSize, coordScreen, &charsWritten);
    SetConsoleCursorPosition(ed.hConsole, coordScreen);
}

void setTerminalMode(int raw) {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (raw) {
        GetConsoleMode(hIn, &ed.oldConsoleMode);
        SetConsoleMode(hIn, ed.oldConsoleMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT));
    } else {
        SetConsoleMode(hIn, ed.oldConsoleMode);
    }
}

