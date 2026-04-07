#include "editor.h"
#include "buffer.h"
#include "fileio.h"
#include "display.h"
#include <string.h>

Buffer buf;
Editor ed;

int main() {
	initBuffer();
	insertCharAt(0, 0, 'A');
    insertCharAt(0, 1, 'C');
    insertCharAt(0, 1, 'B'); // Sisipkan 'B' di antara A dan C -> "ABC"

    // 2. Buat baris baru di tengah
    insertNewLine(0, 2); // Pecah "ABC" di posisi 2 -> Baris 0: "AB", Baris 1: "C"

    // 3. Isi baris baru (Baris 1)
    insertCharAt(1, 1, 'D'); // Sisipkan 'D' setelah 'C' -> "CD"
    
    // 4. Hapus karakter di koordinat spesifik
    deleteCharAt(0, 0); // Hapus 'A' di Baris 0 -> Sisa "B"

    // --- CETAK HASIL ---
    for (int i = 0; i < buf.totalLines; i++) {
        printf("Baris %d: %s (Len: %d)\n", i, buf.data[i], buf.lineLen[i]);
    }
    return 0;
}