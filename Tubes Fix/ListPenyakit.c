#include "ListPenyakit.h"

/*----------------- Validator ----------------*/
bool IsListEmpty(ListPenyakit List){
	return First(List) == Nil;
}

/*----------------- Creator ----------------*/
void BuatListPenyakit(ListPenyakit *List){
	First(*List) = Nil;
}

/*----------------- Manajemen Memory ----------------*/			
addressPenyakit AlokasiPenyakit(infoPenyakit  Penyakit){
addressPenyakit alamatPenyakit;
alamatPenyakit = (addressPenyakit)malloc(sizeof(ElmtList));
    if(alamatPenyakit != Nil){
        Info(alamatPenyakit) = Penyakit;
        Next(alamatPenyakit) = Nil;
    }
    return alamatPenyakit;
}

void DealokasiPenyakit(addressPenyakit Node){
	
	free(Node);
}

/*----------------- Insert dan Delete ----------------*/	
void InsertPenyakit(ListPenyakit *List, infoPenyakit Penyakit){
addressPenyakit alamatPenyakit = AlokasiPenyakit(Penyakit);
    if(alamatPenyakit == Nil){
        return;
    }
    if(First(*List) == Nil){
		First(*List) = alamatPenyakit;
        return;
    }
    addressPenyakit last = First(*List);
    while(Next(last) != Nil){
        last = Next(last);
    }
    Next(last) = alamatPenyakit;
    Next(Next(last)) = Nil;
}

void DealokasiList(ListPenyakit *List){
   addressPenyakit current = First(*List);
   addressPenyakit next;
 
   while (current != NULL)
   {
       next = Next(current);
       DealokasiPenyakit(current);
       current = next;
   }
   First(*List) = Nil;

}
/*----------------- Lainnya ----------------*/	

void PrintPenyakit(ListPenyakit List){
int i = 0;	
char sakit[35];
int x, y;
x = 53;
y = 20;
addressPenyakit alamatPenyakit=First(List);
while(alamatPenyakit!=Nil){
	strcpy(sakit,convertEnum(alamatPenyakit));
	gotoxy(x, ++y); printf("- %s [%c](%d)\n",sakit, alamatPenyakit->info.kategori, Info(alamatPenyakit).biaya);
	alamatPenyakit= Next(alamatPenyakit);
	}  
}

int HitungElement(ListPenyakit L){
    addressPenyakit P;
    int jumlah = 0;
    if(First(L) == Nil){
        return 0;
    }else{
        P = First(L);
        do{
            jumlah++;
            P = Next(P);
        }while(P != Nil);
    }
    return jumlah;
} /* Mengirimkan banyaknya elemen list, mengirimkan Nol jika kosong */

char* convertEnum(addressPenyakit(alamatPenyakit)){
/* Mengubah tipe enum menjadi string */
char* ubah;
ubah = malloc(1);
	switch (Info(alamatPenyakit).namaPenyakit){
		case 1:
			strcpy(ubah, "Penyakit Kulit");
			break;
		case 2:
			strcpy(ubah, "Luka Ringan");
			break;
		case 3:
			strcpy(ubah, "Bersin");
			break;
		case 4 :
			strcpy(ubah, "Cacingan");
			break;
		case 5 :
			strcpy(ubah, "Diare");
			break;
		case 6 :
			strcpy(ubah, "Luka Dalam");
			break;
		case 7 :
			strcpy(ubah, "Gangguan Kerongkongan");
			break;
		case 8:
			strcpy(ubah, "Kuning");
			break;
		case 9:
			strcpy(ubah, "Virus");
			break;
	}
	return ubah;
			
}

bool periksaPenyakit(ListPenyakit sakit, int cari){
	addressPenyakit alamatSakit = First(sakit);
	bool sama = false;
	while(alamatSakit != Nil){
		if (Info(alamatSakit).namaPenyakit == cari ){
			sama = true;
			break;
		}
		alamatSakit = Next(alamatSakit);
	}
	return sama;
} 



