#ifndef Tampilan_H
#define Tampilah_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>


// Menampilkan Judul Permainan 
void judul();

// Menampilkan bingkai 
void bingkai();

// Prosedur dari referensi internet untuk menentukan posisi 
void gotoxy(int x, int y);

// Fungsi dari referensi untuk menggerakkan kursor
int cursor(int option,int x,int y);

// Prosedur untuk melihat daftar tabel penyakit
void lihatTabelPenyakit();

// Prosedur untuk menampilkan kalimat jika pelayanan sudah selesai
void KataSelesai();

// Prosedur untuk menampilkan kalimat jika pelayanan masih harus menunggu
void KataMenunggu();

// Fungsi untuk menampilkan tampilan menu utama
int MenuUtama();

// Fungsi untuk menampilkan tampilan menu halaman
int MenuPelayanan();

/* 
Menampilkan tampilan ketika user menutup pet paradise
I.S : Tampilan tutup belum ditampilkan dan data antrian belum terhapus
F.S :  Tampilan tutup sudah ditampilkan dan data antrian sudah terhapus
*/
void tutup(bool *end);

/* 
Menampilkan loading sebagai tanda keluar dari program
I.S : Tampilan loading belum ditampilkan
F.S :Tampilan loading sudah ditampilkan
*/
void keluar();

/*
Menampilkan daftar penyakit yang bisa dipilih oleh user
I.S : Tampilan daftar penyakit belum tampil
F.S : Tampilan daftar penyakit sudah tampil
*/
void tampilPenyakit();

/*
Menampilkan format input yang harus diisi user
I.S : Tampilan format belum ditampilkan
F.S : Tampilan format sudah ditampilkan
*/
void FormatInput();



#endif