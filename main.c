#include "buffer.h"
#include "display.h"
#include "fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Buffer buf;
//Editor ed;


int main(int argc, char *argv[]){ 
    initBuffer();
    drawScreen();

    int running = 1;
    while (running) {
	    int oldViewRow = ed.viewRow;
        int oldViewCol = ed.viewCol;
        int lineChanged = 0;
        int key = readKey();
        
    if (key == KEY_UP) { // Up
    	lineChanged = moveUp();
	}
	else if (key == KEY_DOWN) { // Down
		lineChanged = moveDown();	
    }
    else if (key == KEY_LEFT) { // Left
        lineChanged = moveLeft(); 
    }
	else if (key == KEY_RIGHT) { // Right
        lineChanged = moveRight();
    }
	else if (key == KEY_ENTER) { // Enter
        lineChanged = insertNewLine();
    }
	else if (key == KEY_BACKSPACE) { // Backspace
		if (!deleteCharAt()) {
		    lineChanged = mergeLines();
		}
    }
		    
	else if (key == KEY_CTRL_O) { // Ctrl + O
            char targetName[260];
            showPrompt(" Open file: ", targetName, sizeof(targetName));
            if (targetName[0] != '\0') {
                if (openFile(targetName)){
                    lineChanged = 1; 
                }
            }
        }

    else if (key == KEY_CTRL_R) { // Ctrl + R
            char newName[260];
            showPrompt(" Rename file to (janlup '.txt' nya~): ", newName, sizeof(newName));
            
            if (newName[0] != '\0') {
                int status = checkFileStatus(newName); 
                
                if (status == 1 || status == 2) {
                    char konfirmasi[10];
                    showPrompt(" Nama file sudah dipakai! Timpa? (y/n): ", konfirmasi, sizeof(konfirmasi));
                    
                    if (konfirmasi[0] == 'y' || konfirmasi[0] == 'Y') {
                        if (renameCurrentFile(newName)) structureChanged = 1;
                    } else {
                        showPrompt(" Rename dibatalkan. Tekan apa saja...", konfirmasi, 1);
                    }
                } else {
                    if (renameCurrentFile(newName)) structureChanged = 1;
                }
            }
        }
        
    else if (key == KEY_CTRL_Q) { //Ctrl + Q
       running = 0;
	}

	else if (key >= 32 && key <= 126) { //Normal Key
        insertCharAt((char)key);
	}
	
	validateCursor();
    scrollView();
	
	if (ed.viewRow != oldViewRow || ed.viewCol != oldViewCol || lineChanged) {
    	drawScreen();
    }else{
        drawCurrentLine(); 
    }
}

	exitManager();
    return 0;
}
