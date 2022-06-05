#ifndef ListPenyakit_H
#define ListPenyakit_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<conio.h>
#include "TIME.h"
#include "tampilan.h"
#define Nil  NULL
#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) ((L).First)


enum penyakit { //tipe data enum merupakan tipe data yang berisi sekumpulan konstanta 
    KULIT = 1,
    LUKA_RINGAN = 2,
    BERSIN = 3,
    CACINGAN = 4,
    DIARE = 5,
    LUKA_DALAM = 6,
    KERONGKONGAN = 7,
    KUNING = 8,
    VIRUS = 9,
};


typedef struct {
  enum penyakit namaPenyakit;
  char kategori; 
  int biaya;
  short jmlRingan;
  short jmlSedang;
  short jmlBerat;
}infoPenyakit;

typedef struct Elmtlist *addressPenyakit;
typedef struct  Elmtlist{
	infoPenyakit info;
	addressPenyakit next;
}ElmtList;

/* Definisi  List                   */
/* List Kosong  :  First(L) = Nil   */
/* Setiap elemen dengan address P dapat diacu Info(P),Next(P)       */
/* Elemen terakhir  List :jika addressnya Last, maka next(Last)=Nil */

typedef struct {
	addressPenyakit First;
}ListPenyakit;

/*----------------- Validator ----------------*/
bool IsListEmpty(ListPenyakit List);
/*
* Mengembalikan nilai true jika List kosong
*/

/*----------------- Creator ----------------*/
/* Pembuatan  List Kosong  */
void BuatListPenyakit(ListPenyakit *List);
/* I.S  :  Sembarang    		*/
/* F.S  :  Terbentuk  List kosong  	*/

/*----------------- Manajemen Memory ----------------*/			
addressPenyakit AlokasiPenyakit(infoPenyakit  Penyakit);
/* Mengirimkan  address  hasil alokasi    sebuah elemen */
/* Jika alokasi  berhasil, maka  address tidak nil, dan misalnya  */
/* menghasilkan   alamatPenyakit,  maka info(alamatPenyakit)=Penyakit,  Next(alamatPenyakit)=Nil;               */
/* Jika alokasi  gagal,  mengirimkan  Nil 			   */

void DealokasiPenyakit(addressPenyakit Node);
/* I.S  :   Node  terdefinisi         	*/
/* F.S  :   Node dikembalikan ke  sistem 	*/
/*   	    Melakukan  dealokasi, pengembalian address  Node */


/*----------------- Insert dan Delete ----------------*/	
void InsertPenyakit(ListPenyakit *List, infoPenyakit Penyakit);
/* I.S  : L mungkin kosong          */
/* F.S  : Melakukan alokasi sebuah elemen dan                */
/*        menambahkan elemen list di akhir; elemen terakhir  */
/*        yang baru bernilai X jika alokasi berhasil, 	     */	
/*	   	  Jika alokasi gagal: I.S = F.S			     */


void DealokasiList(ListPenyakit *List);
/*
* I.S : List Belum Terhapus
* F.S : List Penyakit sudah terhapus
*/

/*----------------- Lainnya ----------------*/	

void PrintPenyakit(ListPenyakit L);
/*
* I.S : L terdefinisi namun belum ditampilkan pada layar
* F.S : L ditampilkan pada layar
*/

int HitungElement(ListPenyakit L);
/* Mengirimkan banyaknya elemen list, mengirimkan Nol jika kosong */

char* convertEnum(addressPenyakit(alamatPenyakit));
/* Mengkonversi enum menjadi string */

bool periksaPenyakit(ListPenyakit sakit, int cari);
/* Memeriksa penyakit pada sebuah list agar tidak terjadi duplikasi */



#endif