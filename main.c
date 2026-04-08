#include "editor.h"
#include "buffer.h"
#include "fileio.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//global file from editor.h
Buffer buf;
Editor ed;


int main(int argc, char *argv[]){ 
    memset(&ed, 0, sizeof(ed));
    ed.hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    SMALL_RECT windowSize = {0, 0, VISIBLE_COLS - 1, STATUS_BAR_ROW};
    SetConsoleWindowInfo(ed.hConsole, TRUE, &windowSize);

    ed.lastSave = time(NULL);
    initBuffer();

    if(argc > 1) {
        openFile(argv[1]);
    }
    
    setTerminalMode(1);
    clearTerminal();
    drawScreen(); //full render for the frsit time


    int running = 1;
    while (running){
        autoSave();
        
        int key = readKey();
        if (key == -1) continue;
        
        //saving old view before press any button
        int oldViewRow = ed.viewRow; 

        if (key >= 1000 && key <= 1009){ 
            handleNavigation(key); 
        }
        else if (key == 1010){
            if (ed.curCol < buf.lineLen[ed.curRow]){
                deleteCharAt(ed.curRow, ed.curCol);
            } else if (ed.curRow < buf.totalLines - 1){
                //UI doesnt give a reaction if buffer rejected merge
                mergeLines(ed.curRow); 
            }
            syncCursor(); 
        }
        else if (key == 17){
            running = 0; 
        }
        else if (key == 19){
            if (ed.filename[0] == '\0'){
                showPrompt(" Simpan sebagai: ", ed.filename, sizeof(ed.filename));
            }
            saveFile(ed.filename); 
        }
        else if (key == 18){
            if (ed.filename[0] == '\0'){
                showPrompt(" File belum disave. Simpan sebagai: ", ed.filename, sizeof(ed.filename));
                saveFile(ed.filename);
            }else{
                char newName[260];
                showPrompt(" Masukkan nama baru: ", newName, sizeof(newName));
                if (newName[0] != '\0'){
                    renameCurrentFile(newName);
                }
            }
            //
            drawScreen(); 
            oldViewRow = -1; //force to skip drawCurrentLine in end loop
        }
        else if (key == 13){
            if (insertNewLine(ed.curRow, ed.curCol)){
                ed.curRow++; 
                ed.curCol = 0; 
            }
            syncCursor(); 
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
            syncCursor(); 
        }
        else if (key >= 32 && key <= 126){
            int oldLen = buf.lineLen[ed.curRow];
            insertCharAt(ed.curRow, ed.curCol, (char)key);
            
            if (buf.lineLen[ed.curRow] > oldLen){
                ed.curCol++; 
            }
            syncCursor();
        }

        //management render
        if (ed.viewRow != oldViewRow){
            drawScreen(); //render all text only when scroll up and down
        }else{
            drawCurrentLine(); //not scroll up and down? render only 1 row 
        }
    }

    exitManager();

    return 0;
}
