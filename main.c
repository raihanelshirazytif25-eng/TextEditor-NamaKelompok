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
    	lineChanged = 1;
	}
	
	else if (key == KEY_DOWN) { // Down
		lineChanged = 1;	
        }

    else if (key == KEY_LEFT) { // Left
        lineChanged = 1;
        
    }
   
	else if (key == KEY_RIGHT) { // Right
        lineChanged = 1;
    }
	
	else if (key == KEY_ENTER) { // Enter
        insertNewLine();
        lineChanged = 1;
    }
	
	else if (key == KEY_BACKSPACE) { // Backspace
		lineChanged = 1;
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

    else if (key == KEY_CTRL_Q) { //Ctrl + Q
       running = 0;
	}

	else if (key >= 32 && key <= 126) { //Normal Key
        insertCharAt((char)key);
	}
	
	if (ed.viewRow != oldViewRow || ed.viewCol != oldViewCol || structureChanged) {
    	drawScreen();
    } 
	else {
        drawCurrentLine(); 
    }
}
    return 0;
}
