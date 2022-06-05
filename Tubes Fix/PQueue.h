#ifndef PQueue_H
#define PQueue_H
#include <stdio.h>

#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "ListPenyakit.h"
#include "tampilan.h"
//#include "TIME.h"

//pendefinisian pointer
#define Nil NULL
#define Info(P) (P)->info
#define Next(P) (P)->next
#define Prioritas(P) (P)->prioritas
#define Front(P) (P).Front
#define Rear(P) (P).Rear
#define Wringan 15
#define Wsedang 30
#define Wberat 45



typedef struct InfoHewan{
    char nama[20]; // Nama Kucing Pelanggan 
    TIME waktuDatang; // Waktu Kedatangan Pelanggan dalam satuan menit
    TIME waktuTunggu; // Waktu Menunggu jika ada pelanggan lain yang belum dilayani
    TIME waktuMulai; // Waktu ini tergantung dari penyakit yang diderita kucing
    TIME waktuPelayanan; // Waktu ini tergantung penyakit yang dimasukkan pengunjung
    TIME waktuSelesai; // Estimasi waktu selesai 
    int bayar;
    ListPenyakit disease; // List Penyakit yang diderita hewan 
} InfoHewan;

typedef struct ElmQueue* addressQueue;
typedef struct ElmQueue{
	InfoHewan info;	// Bagian yang menampung info dari suatu node
	int prioritas; // Bagian yang menanmpung nilai prioritas suatu node
	addressQueue next; // Bagian yang menghubungkan node satu dengan node selanjutnya
} ElmQueue; 

typedef struct{
	addressQueue Front; // Pointer yang menunjuk bagian depan node yang menjadi penunjuk node yang akan keluar
	addressQueue Rear;  // Pointer yang menunjuk bagian belakang node yang menjadi penunjuk node yang akan masuk
} PriorityQueue;

/*----------------- Validator ----------------*/
bool IsQueueEmpty(PriorityQueue Q);
/* Memasukkan info baru ke dalam Queue dengan aturan FIFO */
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */ 
/* F.S. info baru (data) menjadi Rear yang baru dengan node Rear yang lama mengaitkan pointernya ke node yang baru */ 

/*----------------- Creator ----------------*/
void BuatAntrian(PriorityQueue *Q);
/* Membuat sebuah Queue kosong dengan Front(Q) = Nil dan Rear (Q) = Nil */
/* I.S. Belum terbentuk Queue */
/* F.S. Sudah terbentuk Queue */

/*----------------- Manajemen Memory ----------------*/			
addressQueue AlokasiPasien(InfoHewan Data);
/* Mengirimkan  address  hasil alokasi    sebuah elemen */
/* Jika alokasi  berhasil, maka  address tidak nil, dan misalnya  */
/* menghasilkan   alamatPenyakit,  maka info(alamatPenyakit)=Penyakit,  Next(alamatPenyakit)=Nil;      /
/* Jika alokasi  gagal,  mengirimkan  Nil */

void DealokasiPasien(addressQueue node);
/* Tujuan : Untuk membebaskan node dari memori */ 
/* I.S    : node terdefinisi */
/* F.S    : node dibebaskan dan dikembalikan ke sistem */

/*----------------- Insert dan Delete ----------------*/	
void InsertPasien(PriorityQueue *Q, InfoHewan data);
/* 
/* Tujuan : Memasukkan node baru pada antrian */
/* I.S    : Node baru belum masuk pada antrian */
/* F.S    : Node baru sudah masuk dalam antrian */

void Enqueue(PriorityQueue *Q, addressQueue PasienBaru); 
/* Tujuan : Memasukkan node baru pada antrian */
/* I.S    : Node baru belum masuk pada antrian */
/* F.S    : Node baru sudah masuk dalam antrian pada akhir antrian */  

void EnqueuePrioritas(PriorityQueue *Q, addressQueue PasienBaru);
/* Tujuan : Memasukkan node baru pada antrian sesuai dengan prioritas */
/* I.S    : Node baru belum masuk pada antrian */
/* F.S    : Node baru sudah masuk dalam antrian sesuai dengan prioritasnya */  

void deQueue(PriorityQueue *Q);
/* Tujuan : Menghapus Node pasien dengan urutan yang pertama setela diurutkan berdasarkan prioritas*/
/* I.S    : Q mungkin kosong */
/* F.S    : Q->Front menunjuk ke antrian selanjutnya atau menjadi NILL, Q->Front sebelumya di Dealokasi*/


/*----------------- Lainnya ----------------*/
 void TampilAntrian(PriorityQueue Q);
/* Tujuan : Mencetak data data di dalam antrian ke layar */
/* I.S    : Data atrian yang sudah diurutkan belum ditampilkan pada layar */
/* F.S    : Data atrian yang sudah diurutkan belum ditampilkan pada layar */

bool CariElemenQueue(PriorityQueue Q, char* nama);
/* Deskripsi : Mencari data dalam antrian berdasarkan nama pasien */
/* Mengembalikan lokasi yang dicari dalam antrian beserta informasi */
/* waktu dan biaya yang bertipe address_queue */

int getPrioritas(InfoHewan data);
/* Deskripsi : Menghitung nilai prioritas pada setiap pengunjung dengan */
/*             mempertimbangkan penyakit yang diderita hewan            */
/*             dan mengembalikan nilai integer yang merupakan hasil prioritas */

TIME HitungWaktuTunggu(PriorityQueue Q, addressQueue data);
/* Menghitung Estimasi waktu tunggu pada antrian pelanggan */


TIME HitungLamaPenyakit(InfoHewan data);
/* Menghitung lama pelayanan seorang pengunjung */


TIME HitungWaktuMulai (PriorityQueue Q, addressQueue data);
/* Menghitung waktu Mulai dilayani seorang pengunjung */

TIME HitungWaktuSelesai(addressQueue data);
/* Menghitung waktu kucing selesai dilayani */

int hitungBiaya(InfoHewan data);
/* Menghitung biaya yang harus dikeluarkan setiap penunjung */

void InputData(PriorityQueue *Q);
/* Memasukkan data yang dibutuhkan untuk menjadi suatu node antrian */
/* I.S. : Data pengunjung belum masuk pada node */
/* F.S. : Data pengunjung sudah masuk pada node */

void InputPenyakit(	ListPenyakit *daftarPenyakit, int total);
/* Menginputkan Penyakit yang diderita oleh hewan */
/* I.S.: Daftar penyakit belum masuk kedalam sebuah node antrian */
/* F.S.: Daftar penyakit sudah masuk kedalam sebuah node antrian */

void call(PriorityQueue Q);
/* Memanggil antrian selanjutnya */
/* I.S.: Antrian selanjutnya belum terpanggil */
/* F.S. : Antrian selanjutnya sudah terpanggil */

void ProsesPelanggan(PriorityQueue *Q);
/* Memproses antrian */
/* I.S : Pelanggan belum memilih dirinya sudah diproses atau belum */
/* F.S : Pelanggan sudah memilih dirinya sudah diproses atau belum */

int pilihanMenuUtama(PriorityQueue Antrian);
/* Memilih menu menggunakan kursor dan mengarahkannya ke menu yang sesuai */


void pilihanMenuPelayanan(PriorityQueue Antrian);
/* Memilih menu menggunakan kursor dan mengarahkannya ke menu yang sesuai */
/* I.S. : Menu pelayanan belum terpilih */
/* F.S. : Menu pelayanan sudah terpilih */

TIME getWaktuDatang(PriorityQueue Q);
/* Menginputkan waktu datang setiap pengunjung dengan valid */

void tulisFile(addressQueue data);
/* Memasukkan setiap data pengunjung yang sudah dilayani ke dalam file */
/* I.S : data pengunjung belum masuk dalam  file */
/* F.S : data pengunjung sudah masuk dalam file */

void bacaFile();
/* Membaca dan menampilkan data yang ada dalam file txt */
/* I.S : File belum terbaca sehingga belum ditampilkan */
/* F.S : File sudah terbaca sehingga sudah bisa menampilkan data */

void GabungKategori(char jenis[], ListPenyakit sakit);
/*  Menggabungkan kategori dari setiap penyakit yang bertipe char menjadi array of char */
/* I.S : kategori dari setiap penyakit belum digabungkan */
/* F.S :  kategori dari setiap penyakit sudah digabungkan */



#endif