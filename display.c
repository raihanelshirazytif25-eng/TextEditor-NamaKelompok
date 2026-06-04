#include "display.h"
#include "fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void moveCursorTo(int row, int col) {
    printf("\033[%d;%dH", row + 1, col + 1); //Mindahin Kursor Terminal ini
}

void clearTerminal(void) {
	printf("\033[2J"); // clear screen
	printf("\033[3J"); // clear scrollback buffer
	printf("\033[H");  // cursor ke home
}

void drawLineNumbers(int screenRow, int bufRow) {
    moveCursorTo(screenRow, 0);
    if (bufRow == ed.curRow) printf("\033[1;36m%4d |\033[0m ", bufRow + 1); 
    else printf("%4d | ", bufRow + 1);
}

void drawScreen(void) {
    printf("\033[?25l"); 
    clearTerminal();
    
    Node *renderNode = ed.viewTop;
    int bufRow = ed.viewRow;
    
    for (int sr = 0; sr < 22; sr++) {
        if (renderNode) {
            drawLineNumbers(sr, bufRow);
            for(int j = 0; j < 74; j++) {
                int idx = ed.viewCol + j;
                if (idx < renderNode->len) putchar(renderNode->text[idx]);
                else putchar(' '); 
            }
            printf("\n");
            renderNode = renderNode->next;
            bufRow++;
        } else {

            printf("   ~ |                                                                          \n");
        }
    }
    drawStatusBar();
    moveCursorTo(ed.curRow - ed.viewRow, ed.curCol - ed.viewCol + 7);
    printf("\033[?25h"); 
    fflush(stdout);     
}

void drawCurrentLine(void) {
    int screenRow = ed.curRow - ed.viewRow;
    if (screenRow < 0 || screenRow >= 22) return; 

    printf("\033[?25l"); 
    drawLineNumbers(screenRow, ed.curRow);
    moveCursorTo(screenRow, 7); 
    
    for(int j = 0; j < 74; j++) {
        int idx = ed.viewCol + j;
        if (idx < ed.curNode->len) putchar(ed.curNode->text[idx]);
        else putchar(' ');
    }
    
    drawStatusBar();
    moveCursorTo(screenRow, ed.curCol - ed.viewCol + 7);
    printf("\033[?25h"); 
    fflush(stdout);
}

void drawStatusBar(void) {
    moveCursorTo(23, 0);
    long size;
    if (ed.filename[0] != '\0') {
        size = getFileSize(ed.filename);
    } else {
        size = 0;
    }
    
    //Tinggal penampilan teks
    printf(" File: %s %s %s | Size: %ld bytes | Ln %d, Col %d | ^O=Open ^S=Save ^R=Rename ^Q=Quit ", 
    ed.filename[0] == '\0' ? "[Untitled]" : ed.filename,
    ed.modified ? "[*]" : "",
    ed.readOnly ? "[RO]" : "",
    size,
    ed.curRow + 1, 
    ed.curCol + 1);
        
    for(int i = 0; i < 15; i++) printf(" "); 
}




int readKey(void) {
    int Key = _getch();
    if (Key == 0 || Key == 224) { // Cek apakah karakter special atau tidak
        int SpecialKeys = _getch();
        switch (SpecialKeys) {
            case 72: return KEY_UP; //224 72 v 0 72
            case 80: return KEY_DOWN;
            case 75: return KEY_LEFT;
            case 77: return KEY_RIGHT;
            case 71: return KEY_HOME;
            case 79: return KEY_END;
            case 73: return KEY_PGUP;
            case 81: return KEY_PGDN;
            case 83: return KEY_DEL;
            default: return -1;
    	}
	}
    return c;
}


void showPrompt(const char *msg, char *out, int maxLen) {
    moveCursorTo(24, 0);
    printf("%s", msg);
    if (fgets(out, maxLen, stdin)) {
        out[strcspn(out, "\n")] = 0;
    }
}



/* void setTerminalMode(int raw) {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (raw) {
        GetConsoleMode(hIn, &ed.oldConsoleMode);
        SetConsoleMode(hIn, ed.oldConsoleMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT));
    } else {
        SetConsoleMode(hIn, ed.oldConsoleMode);
    }
} */

