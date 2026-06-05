# Terminal-Based Text Editor (C)

Sebuah aplikasi *text editor* ringan berbasis terminal yang dikembangkan menggunakan bahasa C murni. Proyek ini mengimplementasikan struktur data *Doubly Linked List* untuk alokasi memori dinamis, memungkinkan manipulasi teks yang efisien tanpa batasan *array* statis.

Dikembangkan sebagai bagian dari pemenuhan tugas akademik di Program Studi D3 Teknik Informatika, Politeknik Negeri Bandung.

## ⚙️ Arsitektur Sistem & Fitur Utama

* **Dynamic Memory Management:** Menggunakan *Doubly Linked List* untuk setiap baris teks, memungkinkan penambahan baris (`insertNewLine`) dan penggabungan baris (`mergeLines`) secara dinamis tanpa *memory leak*.
* **Custom Terminal Rendering:** Menggunakan *ANSI Escape Codes* untuk memanipulasi kursor dan me-*render* tampilan *viewport* secara independen, mencegah *flickering* saat pengetikan.
* **Intelligent File I/O:** * Mendukung pembacaan aliran *binary* untuk menghindari korupsi teks tingkat sistem operasi.
  * Injeksi ekstensi `.txt` otomatis untuk setiap operasi penyimpanan, penamaan ulang, dan pembukaan file.
  * Proteksi memori dari modifikasi file yang bersifat *Read-Only*.
* **Data Loss Prevention:** Menahan interupsi pengguna jika terdapat modifikasi di RAM (`ed.modified`) yang belum diserialisasi ke dalam *hardisk*.

## ⌨️ Pintasan Keyboard (Keybindings)

| Perintah | Aksi | Deskripsi |
| :--- | :--- | :--- |
| `Ctrl + O` | Open File | Membuka file dari disk ke dalam memori. |
| `Ctrl + S` | Save / Save As | Menyimpan perubahan. Jika file baru/Read-Only, memicu *Save As*. |
| `Ctrl + R` | Rename | Mengubah nama file yang sedang aktif secara aman. |
| `Ctrl + Q` | Quit | Keluar dari program dengan pembersihan *buffer* RAM absolut. |
| `Panah` | Navigasi | Menggeser *viewport* dan kursor secara vertikal/horizontal. |

## 🚀 Instruksi Kompilasi

Kompilasi source code menggunakan GCC (GNU Compiler Collection). Pastikan semua modul `.c` ditautkan (*linked*) secara bersamaan untuk mencegah *Undefined Reference Error*.
"gcc main.c buffer.c display.c fileio.c -o text_editor.exe"

Pada git bash, Jalankan executable yang dihasilkan:
./text_editor.exe

👨‍💻 Tim Pengembang (NamaKelompok)
Daffa Rauf Alifandra (NIM: 251511006)
Kevin Akbar Darmawan (NIM: 251511014)
Raihan Elshirazy Sanjaya Putra (NIM: 251511026)