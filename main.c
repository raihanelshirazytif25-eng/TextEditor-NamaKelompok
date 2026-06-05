#include "buffer.h"
#include "display.h"
#include "fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    	moveUp();
	}
	else if (key == KEY_DOWN) { // Down
		moveDown();	
    }
    else if (key == KEY_LEFT) { // Left
        moveLeft(); 
    }
	else if (key == KEY_RIGHT) { // Right
        moveRight();
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
        int proceed = 1;
        if (ed.modified) {
            char konfirmasi[10];
            showPrompt(" Pekerjaan belum disave! Buang perubahan? (y/n): ", konfirmasi, sizeof(konfirmasi));
            if (konfirmasi[0] != 'y' && konfirmasi[0] != 'Y') proceed = 0;
            lineChanged = 1; 
        }
        
        if (proceed) {
            char targetName[260];
            showPrompt(" Open file: ", targetName, sizeof(targetName));
            ensureTxtExtension(targetName, sizeof(targetName));
            if (targetName[0] != '\0') {
                if (openFile(targetName)) lineChanged = 1; 
            }
        }
    }

    else if (key == KEY_CTRL_R) { // Ctrl + R
            char newName[260];
            showPrompt(" Rename file to: ", newName, sizeof(newName));
            ensureTxtExtension(newName, sizeof(newName));
            
            if (newName[0] != '\0') {
                int status = checkFileStatus(newName); 
                
                if (status == 1 || status == 2) {
                    char konfirmasi[10];
                    showPrompt(" Nama file sudah dipakai! Timpa? (y/n): ", konfirmasi, sizeof(konfirmasi));
                    
                    if (konfirmasi[0] == 'y' || konfirmasi[0] == 'Y') {
                        renameCurrentFile(newName);
                    } else {
                        showPrompt(" Rename dibatalkan. Tekan apa saja...", konfirmasi, 1);
                    }
                } else {
                    renameCurrentFile(newName);
                }
            }
            lineChanged = 1;
        }
       
	       else if (key == KEY_CTRL_S) { // Ctrl + S
            char tempName[260]; 
            if (ed.filename[0] == '\0' || ed.readOnly) {
                if (ed.readOnly) {
                    showPrompt(" File Read-Only! Simpan file baru sebagai: ", tempName, sizeof(tempName));
                } else {
                    showPrompt(" Simpan sebagai: ", tempName, sizeof(tempName));
                }
                
                ensureTxtExtension(tempName, sizeof(tempName)); 
                
                if (tempName[0] != '\0') {
                    int status = checkFileStatus(tempName); 
                    
                    if (status == 1 || status == 2) { 
                        char konfirmasi[10];
                        showPrompt(" File sudah ada! Timpa? (y/n): ", konfirmasi, sizeof(konfirmasi));
                        
                        if (konfirmasi[0] == 'y' || konfirmasi[0] == 'Y') {
                            int oldRO = ed.readOnly;
                            ed.readOnly = 0; 
                            if (!saveFile(tempName)) ed.readOnly = oldRO; 
                        } else {
                            showPrompt(" Simpan dibatalkan. Tekan apa saja...", konfirmasi, 1);
                        }
                    } else {
                        int oldRO = ed.readOnly;
                        ed.readOnly = 0;
                        if (!saveFile(tempName)) ed.readOnly = oldRO;
                    }
                }
            } else {
                saveFile(ed.filename);
            }
            lineChanged = 1;
        }
	    
    else if (key == KEY_CTRL_Q) { //Ctrl + Q
       if (ed.modified) {
            char konfirmasi[10];
            showPrompt(" Pekerjaan belum disave! Yakin keluar? (y/n): ", konfirmasi, sizeof(konfirmasi));
            if (konfirmasi[0] == 'y' || konfirmasi[0] == 'Y') running = 0;
            lineChanged = 1; 
        } else {
            running = 0;
        }
	}

	else if (IS_PRINTABLE(key)) { //Normal Key
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
}
