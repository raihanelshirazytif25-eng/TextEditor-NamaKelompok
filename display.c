#include "editor.h"
#include "display.h"
#include "buffer.h"
#include <stdio.h>
#include <conio.h>

/* Helper Internal */
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
    syncCursor();
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
