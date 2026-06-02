#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void pindahPosisiUI(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void hapusLayarCMD(void) {
    system("cls"); 
}

void drawLineNumbers(int screenRow, int bufRow) {
    moveCursorTo(screenRow, 0);	 
    if (bufRow == ed.curRow) printf("\033[1;36m%4d |\033[0m ", bufRow + 1); 
    else printf("%4d | ", bufRow + 1);
}


void perbaruiLayarUtuh(void) {
    hapusLayarCMD(); 
    
    BarisTeks *nodeRender = editor.nodeLayarAtas;
    int nomorBaris = editor.layarY + 1;
    

    for (int i = 0; i < 22; i++) {
        if (nodeRender != NULL) {
            printf("%4d | ", nomorBaris);

            for(int j = 0; j < 74; j++) { 
                int indexTeks = editor.layarX + j;
                if (indexTeks < nodeRender->panjangTeks) {
                    putchar(nodeRender->isiTeks[indexTeks]);
                } else {
                    break;
                }
            }
            printf("\n");
            
            nodeRender = nodeRender->bawah;
            nomorBaris++;
        } else {
            printf("   ~ |\n"); 
        }
    }
    
    gambarInfoBawah();
    pindahPosisiUI(editor.kursorX - editor.layarX + 7, editor.kursorY - editor.layarY); 
}

void drawStatusBar(void) {
void gambarInfoBawah(void) {
    pindahPosisiUI(0, 23); // Baris status bar di bawah
    printf("===============================================================================\n");
    printf(" File: %s %s | Baris: %d, Kolom: %d | ^S=Save ^Q=Quit", 
        editor.namaFile[0] == '\0' ? "[Tanpa Nama]" : editor.namaFile,
        editor.belumDisave ? "[*]" : "",
        editor.kursorY + 1, 
        editor.kursorX + 1);
}




int tangkapTombol(void) {
    int tombol = _getch();
    if (tombol == 0 || tombol == 224) {
        int arah = _getch();
        if (arah == 72) return 1000; // Atas
        if (arah == 80) return 1001; // Bawah
        if (arah == 75) return 1002; // Kiri
        if (arah == 77) return 1003; // Kanan
        if (arah == 83) return 1010; // Tombol Delete
    }
    return tombol;
}


void mintaInputUser(const char *pesan, char *output, int maksimal) {
    pindahPosisiUI(0, 24); 
    printf("%s", pesan);
    if (fgets(output, maksimal, stdin)) {
        output[strcspn(output, "\n")] = 0; 
    }
}



