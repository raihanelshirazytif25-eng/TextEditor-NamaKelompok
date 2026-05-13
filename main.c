#include "buffer.h"
#include "fileio.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Buffer buf;
Editor ed;


int main(int argc, char *argv[]){ 
    memset(&ed, 0, sizeof(ed));
    ed.hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    SMALL_RECT windowSize = {0, 0, VISIBLE_COLS - 1, STATUS_BAR_ROW};
    SetConsoleWindowInfo(ed.hConsole, TRUE, &windowSize);
	HWND hwnd = GetConsoleWindow();
	DWORD style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_SIZEBOX;      
    style &= ~WS_MAXIMIZEBOX;  
    SetWindowLong(hwnd, GWL_STYLE, style);
    initBuffer();

    if(argc > 1) {
        openFile(argv[1]);
    }
    
    setTerminalMode(1);
    clearTerminal();
    drawScreen(); 


    int running = 1;
    while (running){
        
        int key = readKey();
        if (key == -1) continue;
        
        int oldViewRow = ed.viewRow; 

        if (key >= 1000 && key <= 1009){ 
            handleNavigation(key); 
        }
        else if (key == 1010){
            if (ed.curCol < buf.lineLen[ed.curRow]){
                deleteCharAt(ed.curRow, ed.curCol);
            } else if (ed.curRow < buf.totalLines - 1){
                mergeLines(ed.curRow); 
            }
            validateCursor();
            scrollView();
        }
        else if (key == 17){
            running = 0; 
        }
        else if (key == 15) { 
            char targetName[260];
            showPrompt(" Buka file: ", targetName, sizeof(targetName));
            if (targetName[0] != '\0') {
                openFile(targetName);
                oldViewRow = -1; 
            }
        }
        else if (key == 19){
            char tempName[260];
            if (ed.filename[0] == '\0'){
                showPrompt(" Simpan sebagai: ", tempName, sizeof(tempName));
                if (tempName[0] != '\0') {
                    int status = checkFileStatus(tempName);
                    if (status == 1 || status == 2) {
                        char konfirmasi[10];
                        showPrompt(" File sudah ada! Timpa? (y/n): ", konfirmasi, sizeof(konfirmasi));
                        if (konfirmasi[0] == 'y' || konfirmasi[0] == 'Y') {
                            saveFile(tempName);
                            oldViewRow = -1; 
                        } else {
                            showPrompt(" Simpan dibatalkan.", konfirmasi, 1);
                        }
                    } else {
                        saveFile(tempName);
                        oldViewRow = -1;
                    }
                }
            } else {
                saveFile(ed.filename); 
                oldViewRow = -1;
            }
        }
        else if (key == 18){
            if (ed.filename[0] == '\0'){
                char tempName[260];
                showPrompt(" File belum disave. Simpan sebagai: ", tempName, sizeof(tempName));
                if (tempName[0] != '\0') {
                    int status = checkFileStatus(tempName);
                    if (status == 1 || status == 2) {
                        char konfirmasi[10];
                        showPrompt(" File sudah ada! Timpa? (y/n): ", konfirmasi, sizeof(konfirmasi));
                        if (konfirmasi[0] == 'y' || konfirmasi[0] == 'Y') saveFile(tempName);
                    } else {
                        saveFile(tempName);
                    }
                }
            } else {
                char newName[260];
                showPrompt(" Masukkan nama baru: ", newName, sizeof(newName));
                if (newName[0] != '\0'){
                    int status = checkFileStatus(newName);
                    if (status == 1 || status == 2) {
                        char konfirmasi[10];
                        showPrompt(" Nama file sudah dipakai! Timpa? (y/n): ", konfirmasi, sizeof(konfirmasi));
                        if (konfirmasi[0] == 'y' || konfirmasi[0] == 'Y') {
                            renameCurrentFile(newName);
                        } else {
                            showPrompt(" Rename dibatalkan.", konfirmasi, 1);
                        }
                    } else {
                        renameCurrentFile(newName);
                    }
                }
            }
            oldViewRow = -1; 
        }
        else if (key == 13){
            if (insertNewLine(ed.curRow, ed.curCol)){
                ed.curRow++; 
                ed.curCol = 0; 
            }
            validateCursor();
            scrollView();
        }
        else if (key == 8){
            if (ed.curCol > 0){ 
                ed.curCol--; 
                deleteCharAt(ed.curRow, ed.curCol); 
            } else if (ed.curRow > 0){ 
                int prevLen = buf.lineLen[ed.curRow-1]; 

                if (mergeLines(ed.curRow-1)){
                    ed.curRow--; 
                    ed.curCol = prevLen; 
                }
            }
            validateCursor();
            scrollView();
        }
        else if (key >= 32 && key <= 126){
            int oldLen = buf.lineLen[ed.curRow];
            insertCharAt(ed.curRow, ed.curCol, (char)key);
            
            if (buf.lineLen[ed.curRow] > oldLen){
                ed.curCol++; 
            }
            validateCursor();
            scrollView();
        }
       
        int structureChanged = (key == 13 || key == 8 || key == 1010);
        
        if (ed.viewRow != oldViewRow || structureChanged){
            drawScreen(); 
        }else{
            drawCurrentLine(); 
        }
    }

    exitManager();

    return 0;
}
