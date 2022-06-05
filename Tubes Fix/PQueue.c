#include "PQueue.h"


/*----------------- Validator ----------------*/
bool IsQueueEmpty(PriorityQueue Q){
	return Front(Q) == Nil && Rear(Q) == Nil;
	/* Mengirim true jika Queue kosong dan false jika tidak kosong */
}

/*----------------- Creator ----------------*/
void BuatAntrian(PriorityQueue *Q){
/* Pembuatan antrian kosong dimana Front dan Rear sama-sama menunjuk NULL */
	Front(*Q) = Nil; 
	Rear(*Q) = Nil;
}

/*----------------- Manajemen Memory ----------------*/			
addressQueue AlokasiPasien(InfoHewan Data){
	addressQueue Pasien;
	Pasien = (addressQueue)malloc(sizeof(ElmQueue)); // Pengalokasian pada memori
	/* Jika alokasi memori berhasil */
	if(Pasien != Nil){
		Info(Pasien) = Data;
		Prioritas(Pasien) = 0; 
		return Pasien; // Mengembalikan alamat yang telah terisi data 
	}else {
		return Nil;
	}
}

void DealokasiPasien(addressQueue node){
	DealokasiList(&(Info(node).disease)); // Penghapusan list penyakit dari pasien
	Info(node).disease.First = Nil; // Mengisikan First pada list penyakit dengan NULL
	free(node); // Membebaskan memori alamat node
}

/*----------------- Insert dan Delete ----------------*/	
void InsertPasien(PriorityQueue *Q, InfoHewan data){
/* Pengisian data penting yang tidak diinputkan dan memilih jenis Enqueue */
addressQueue PasienBaru = AlokasiPasien(data); 
Prioritas(PasienBaru) = getPrioritas(data); 
Info(PasienBaru).waktuMulai = HitungWaktuMulai(*Q,PasienBaru);
Info(PasienBaru).waktuSelesai=HitungWaktuSelesai(PasienBaru);                  
Info(PasienBaru).waktuTunggu = HitungWaktuTunggu(*Q,PasienBaru);

/* Jika alokasi gagal */
if(PasienBaru == Nil){
	printf("Alokasi Gagal");
    return;
}

/* Jika Queue masih kosong sehingga front dan rear menunjuk ke alamat tersebut */
if(IsQueueEmpty(*Q)){
	
	Front(*Q) = PasienBaru;
    Rear(*Q) = PasienBaru;
   	Next(Rear(*Q)) = Nil;
    return; // keluar dari fungsi
}

/* Jika tidak memenuhi kondisi untuk di insert dengan EnqueuePrioritas */
if(Prioritas(PasienBaru) <= Prioritas(Rear(*Q))|| (Front(*Q) == Rear(*Q)) || JGT(Info(PasienBaru).waktuDatang,Info(Rear(*Q)).waktuMulai)){
    Enqueue(&(*Q), PasienBaru);
}else{
	/* Memasukkan data tidak di ujung, tetapi sesuai dengan aturan prioritas program */
    EnqueuePrioritas(&(*Q), PasienBaru);
}
}


void Enqueue(PriorityQueue *Q, addressQueue PasienBaru){
	/* Pemasukkan data pada ujung antrian sesuai aturan queue pada umumnya */
	Info(PasienBaru).waktuTunggu = HitungWaktuTunggu(*Q, PasienBaru);
	Next(Rear(*Q))= PasienBaru;
	Rear(*Q) = PasienBaru;
	Next(Rear(*Q)) = Nil;
}

void EnqueuePrioritas(PriorityQueue *Q, addressQueue PasienBaru){
addressQueue current = Q->Front->next; // diisi dengan node kedua (setalah node yang ditunjuk front)
addressQueue prev = Q->Front; // diisi dengan node yang ditunjuk front
/* Perulangan untuk menemukan node yang harus dimundurkan antriannya */
while(current != Nil ){ // dijalankan selama node tidak NULL
    if(Prioritas(current) >= Prioritas(PasienBaru) || JLT(Info(current).waktuMulai,Info(PasienBaru).waktuDatang)){ // Pengkondisian yang tidak sesuai syarat pendahuluan prioritas
            prev = current;
            current = Next(current);
            continue;                   // jika tidak memenuhi syarat pendahuluan maka akan tidak akan terjadi pertukaran
        }
      	Next(PasienBaru) = Next(prev); // pointer next node baru menunjuk current 
        Info(PasienBaru).waktuMulai = Info(prev).waktuSelesai;
        Info(PasienBaru).waktuSelesai = HitungWaktuSelesai(PasienBaru);
        Info(PasienBaru).waktuTunggu = HitungWaktuTunggu(*Q,PasienBaru);
        Next(prev) = PasienBaru;

        addressQueue currentEdit = Next(PasienBaru); // currentEdit diisi dengan alamat dari current
        addressQueue prevEdit = PasienBaru; // prevEdit diisi dengan alamat node yang baru masuk
        
		/* Perulangan untuk merubah data waktu dari node yang ditukar dengan posisi node baru */
        while(currentEdit != Nil) {
        	Info(currentEdit).waktuMulai = Info(prevEdit).waktuSelesai ;      
        	Info(currentEdit).waktuSelesai = HitungWaktuSelesai(currentEdit);
        	Info(currentEdit).waktuTunggu = HitungWaktuTunggu(*Q, currentEdit);

            prevEdit = currentEdit;
            currentEdit = Next(currentEdit);
        }

        break;
        
    }
}

void deQueue(PriorityQueue *Q){
addressQueue P;
P = malloc(sizeof(ElmQueue));
P = Front(*Q);
	if(!IsQueueEmpty(*Q)){
		/* Jika hanya ada satu node */
		if(Next(Front(*Q)) == Nil){
			Front(*Q)= Nil;
			Rear(*Q)= Nil;
		}else{
			/* Jika tidak hanya satu node */
			Front(*Q) = Next(P);
			Next(P)= Nil;
			DealokasiPasien(P);
		}
	}else{
	printf("Antrian Sudah Kosong\n");
	}	
}

/*----------------- Lainnya ----------------*/

void TampilAntrian(PriorityQueue Q){
addressQueue current = Front(Q);
int i = 0;
system("cls");



printf("==========================================================================================================================================================\n");
printf("| No. | %-20s | Kategori   | prioritas | waktu kedatangan | estimasi mulai | waktu pelayanan | waktu selesai | waktu Tunggu | Total Biaya |\n", "Nama");
    while(current != NULL) {
    	char Kategori[10] = {'\0'};
    	GabungKategori(Kategori, current->info.disease);
        printf("| %3d | %-20s | %-10s | %-9d |       %02d:%02d      |      %02d:%02d     |      %02d:%02d      |     %02d:%02d     |     %02d:%02d    | %-11d |\n", ++i, Info(current).nama, Kategori, Prioritas(current), Info(current).waktuDatang.Hour, Info(current).waktuDatang.Minute , 
		Info(current).waktuMulai.Hour, Info(current).waktuMulai.Minute, Info(current).waktuPelayanan.Hour, Info(current).waktuPelayanan.Minute, Info(current).waktuSelesai.Hour, Info(current).waktuSelesai.Minute, Info(current).waktuTunggu.Hour, Info(current).waktuTunggu.Minute , Info(current).bayar);
        current = current->next;
    }
printf("==========================================================================================================================================================\n");
printf("Tekan Enter Untuk Kembali");
getchar();
}

bool CariElemenQueue(PriorityQueue Q, char* nama){
addressQueue P;
int cari;
P = Front(Q);
while(P != Nil){
	cari = strcmp(strupr(Info(P).nama),nama);
	/* Jika data ketemu dalam antrian */
	if(cari == 0){
		return true;
	}
		P = Next(P);
}
return false;
}

int getPrioritas(InfoHewan data){
	addressPenyakit List;
	int prioritas;
	prioritas =1; // default prioritas setiap antrian
	List = data.disease.First;
	/* Perulangan untuk menunjuk pada akhir list penyakit */
	while(Next(List) != Nil){
		List = Next(List);
	}
	/* Kondisi untuk menentukan prioritas */
	if(List->info.jmlRingan >= 3){
		prioritas += 2;
	}if(List->info.jmlSedang >= 2){
		prioritas += 3; 
	}if(List->info.jmlBerat >= 1){
		prioritas += 4;
	}
	return prioritas;
}

TIME HitungWaktuSelesai(addressQueue data){                                      
TIME t;
/* Perhitungan waktu selesai = waktu mulai + waktu pelayanan */
t = JPlus(Info(data).waktuMulai, Info(data).waktuPelayanan);
CreateTIME(&t,t.Hour,t.Minute);
return t;
}

TIME HitungWaktuMulai (PriorityQueue Q, addressQueue data){
TIME start;
/* Jika antrian kosong waktu mulai = waktu datang */
if(IsQueueEmpty(Q)){
	start = Info(data).waktuDatang;
	return start;
}else{ 
	bool uji = JLT(Info(data).waktuDatang,Info(Rear(Q)).waktuSelesai);
	if (uji == true){
		/* waktu datang < waktu selesai node sebelumnya, waktu mulai = waktu selesai node sebelumnya */
		start = Info(Rear(Q)).waktuSelesai;
	}else{
		/* waktu datang > waktu selesai node sebelumnya, waktu mulai = waktu datang */
		start = Info(data).waktuDatang;
	}
}
return start;
}

TIME HitungWaktuTunggu(PriorityQueue Q, addressQueue data){
TIME jeda;

/* Merupakan node pertama atau waktu datang > waktu mulai */
if(IsQueueEmpty(Q) || JGT(Info(data).waktuDatang,Info(data).waktuMulai)){
  	CreateTIME(&jeda,0,0);
  	return jeda;
}

/* waktu datang < waktu mulai */
if(JLT(Info(data).waktuDatang, Info(data).waktuMulai)){
	jeda = JMinus(Info(data).waktuMulai ,Info(data).waktuDatang);
	CreateTIME(&jeda, jeda.Hour, jeda.Minute--);
	return jeda;
}
}


TIME HitungLamaPenyakit(InfoHewan data){
TIME lama, waktu;
waktu.Hour = 0;
addressPenyakit List;
CreateTIME(&lama, 0, 0);
List = data.disease.First;
while(List != Nil){
	if(Next(List) == Nil){
		waktu.Minute = List->info.jmlRingan * 15;
		lama = JPlus(lama,waktu);
		waktu.Minute =  List->info.jmlSedang * 30;
		lama = JPlus(lama,waktu);
		waktu.Minute = List->info.jmlBerat * 45;
		lama = JPlus(lama,waktu);
	}
	List = Next(List);	
}
return lama;
}

int hitungBiaya(InfoHewan data){
	addressPenyakit List;
	int biaya = 0;
	List = data.disease.First;
	while(List != Nil){
		biaya = biaya + List->info.biaya;
		List = Next(List);	
	}
	return biaya;
}

void GabungKategori(char jenis[], ListPenyakit sakit){
	addressPenyakit s = sakit.First;
	int sama;
	int i ;
	for (i = 0; i < 9 ; i++){
		jenis[i] =' ';
	}
	i = 0;
	while (s != Nil){
		if (s->info.kategori == 'R' ){
			jenis[i] = 'R';
		}else if (s->info.kategori == 'S' ){
			jenis[i] = 'S';
		}else if (s->info.kategori == 'B' ){
			jenis[i] = 'B';
		}
		i++;
		s = s->next;
	}

}

void InputData(PriorityQueue *Q){
	system("cls");
	InfoHewan data;
	data.bayar = 0;
	CreateTIME(&data.waktuDatang, 0, 0);
	CreateTIME(&data.waktuMulai, 0, 0);
	CreateTIME(&data.waktuPelayanan, 0, 0);
	CreateTIME(&data.waktuSelesai, 0, 0);
	CreateTIME(&data.waktuTunggu, 0, 0);
	int i=0,total, waktu;
	
	FormatInput();
	data.waktuDatang = getWaktuDatang(*Q);
	fflush(stdin);
	
	/* Jika antrian tidak kosong maka waktu datang harus lebih besar dari waktu datang antrian sebelumnya */
	if(!IsQueueEmpty(*Q)){
		while(JLT(data.waktuDatang,Info(Rear(*Q)).waktuDatang)){
			data.waktuDatang = getWaktuDatang(*Q);
			fflush(stdin);
		}
	}
	
	gotoxy(26,4);scanf("%[^\n]s",data.nama);fflush(stdin);
	gotoxy(26,5);scanf("%d", &total);fflush(stdin);	
	InputPenyakit(&data.disease, total);
	data.bayar =hitungBiaya(data);
	data.waktuPelayanan = HitungLamaPenyakit(data);
	InsertPasien(&(*Q), data);
}

void InputPenyakit(ListPenyakit *daftarPenyakit, int total){
	infoPenyakit disease;
	int pilihan,i = 0;
	disease.jmlBerat =0;
	disease.jmlRingan = 0;
	disease.jmlSedang =0;
	BuatListPenyakit(&(*daftarPenyakit));
	do{
		tampilPenyakit();
		
		do{
			gotoxy(1,15); scanf("%d", &pilihan);fflush(stdin);
			gotoxy(1,15); printf("   ");
			
			/* Agar tidak ada duplikat penyakit */
			if (periksaPenyakit(*daftarPenyakit, pilihan)){
				gotoxy(1,17);printf(" Penyakit Tersebut telah Ada!!! ");
				Sleep(2000);
				gotoxy(1,17);printf("                                     ");
			}
			/* Jika memasukkan input yang tidak valid */
			if (pilihan < 1 || pilihan > 9 ){
				gotoxy(1,17);printf(" Masukkan Nomor Penyakit antara 1 - 9 !!! ");
				Sleep(2000);
				gotoxy(1,17);printf("                                            ");
			}
		}while(periksaPenyakit(*daftarPenyakit, pilihan) == true || pilihan < 1 || pilihan > 9);
		switch(pilihan){
		case 1 :
		case 2 :
		case 3 :
			disease.kategori = 'R';
			disease.biaya = 30000;
			disease.jmlRingan++;
			break;
		case 4 :
		case 5 :
		case 6 :
			disease.kategori = 'S';
			disease.biaya = 45000;
			disease.jmlSedang++;
			break;
		case 7 :
		case 8 :
		case 9 :
			disease.kategori = 'B';
			disease.biaya = 60000;
			disease.jmlBerat++;
			break;
		}
				disease.namaPenyakit = pilihan;
		i++;	
		InsertPenyakit(&(*daftarPenyakit),disease);
	}while(i != total);
	fflush(stdin);
	printf("Jika Selesi Tekan Enter   !                                 \n"); 
	getch();
}

void ProsesPelanggan(PriorityQueue *Q){
    addressQueue p;
    p = Front(*Q);
    char pilihan;

    system("cls");
    system("color 0E"); 
	judul();
    gotoxy(8,12);printf("[======================================================================================]\n");
	gotoxy(8,13);printf("[--------------------              Proses Antrian          ----------------------------]\n");
	gotoxy(8,14);printf("[======================================================================================]\n\n");
	/* Jika tidak ada antrian */
	if(p == Nil){ 
		gotoxy(36,16);printf(" !!! Tidak ada Pelanggan yang harus di Proses !!!\n");
		gotoxy(8,18);printf("Tekan Enter Untuk Kembali");
		getchar();
	}else {
		int jumlahPenyakit = HitungElement(Info(p).disease);
		gotoxy(25,16);printf("[*] Nama                  : %s\n", p->info.nama);
		gotoxy(25,17);printf("[*] Jam Kedatangan        : %02d:%02d\n", p->info.waktuDatang.Hour, p->info.waktuDatang.Minute);
		gotoxy(25,18);printf("[*] Estimasi Tunggu       : %d jam %d menit\n", p->info.waktuTunggu.Hour, p->info.waktuTunggu.Minute);
		gotoxy(25,19);printf("[*] Estimasi Selesai      : %02d:%02d\n", p->info.waktuSelesai.Hour, p->info.waktuSelesai.Minute);
		gotoxy(25,20);printf("[*] Estimasi Pelayanan    : %d jam %d menit\n", p->info.waktuPelayanan.Hour, p->info.waktuPelayanan.Minute);
		gotoxy(25,21);printf("[*] Penyakit              : "); PrintPenyakit(Info(p).disease);
		gotoxy(36,23 + jumlahPenyakit);printf("Apakah anda telah diobati ? [Y/N] "); scanf(" %c", &pilihan); fflush(stdin);
		/* Jika input y maka data dimasukkan file lalu dihapus */
		if (pilihan == 'Y' || pilihan == 'y'){
			tulisFile(p);
			deQueue(Q);
			KataSelesai();
			Sleep(3000);
			call(*Q);
		}
		else if(pilihan == 'N' || pilihan == 'n'){
			KataMenunggu();
			    getchar();
		}
	}

}

void call(PriorityQueue Q){
	addressQueue antrian,next;
	system("cls");
	
	antrian = Front(Q);
	system("color 0B"); 
			printf("======================= PARADISE PET CLINIC =======================\n");
			printf("||              [Panggil Kucing Selanjutnya]                     ||\n");
    	if(antrian != NULL){
			printf("|| Antrian Berikutnya                                            ||\n");
    		printf("|| Nama                 : %-15s                        ||\n", Info(antrian).nama);
			printf("|| Waktu Mulai          : %02d:%02d                                  ||\n", Info(antrian).waktuMulai.Hour, Info(antrian).waktuMulai.Minute);
    		printf("||                                                               ||\n");
			printf("|| Tekan Enter Untuk Kembali ke Menu Pelayanan                   ||\n");  
			printf("===================================================================\n");
		}else{
			system("cls");
			printf("Belum Ada Antrian Selanjutnya\n");
			printf("Tekan Enter Untuk Kembali");
			//getchar();
		}
		getchar();
}

int pilihanMenuUtama(PriorityQueue Antrian)
{
	int end, menu;		
	menu = MenuUtama();
	switch(menu)
	{
		case 1:
			pilihanMenuPelayanan(Antrian);
			break;
		case 2:
			lihatTabelPenyakit();
			pilihanMenuUtama(Antrian);
			break;
		case 3:
			bacaFile();
			break;
		case 4:
			end=1;					//end bernilai 1 setelah memilih exit
			break;
	}
	return end;
}

void pilihanMenuPelayanan(PriorityQueue Antrian)
{
system("Color F0");
bool end = true;
int menu;
char Nama[30];
while (end){
	menu = MenuPelayanan();
	switch(menu)
	{
		case 1:
			InputData(&Antrian);
			break;
		case 2:
			if(!IsQueueEmpty(Antrian)){
				TampilAntrian(Antrian);
			}else{
				system("cls");
				printf("Belum Ada Antrian\n\n");
				printf("============    Tekan Enter untuk kembali    ==========");
				getchar();
			}
			break;
		case 3:
			ProsesPelanggan(&Antrian);
			break;
		case 4:
			system("cls");
		   	printf("Masukkan Nama Kucing yang dicari \n");
		   	printf("Nama  :");
		   	scanf("%[^\n]s", Nama);
		   	fflush(stdin);
		   	if(CariElemenQueue(Antrian, strupr(Nama)) == true){
		   		printf("Kucing dengan Nama %s Terdapat dalam Antrian\n", Nama);
			}else{
				printf("Tidak ada kucing dengan Nama tersebut\n");
			}
			printf("Tekan Enter untuk kembali ke menu");
			getchar();
			break;
		case 5:
			tutup(&end);
			if (end== false){
				while(!IsQueueEmpty(Antrian)){
					deQueue(&Antrian);
				}
				
			}
		break;
	}
}
}
 

TIME getWaktuDatang(PriorityQueue Q){
	TIME waktu;
	gotoxy(26,3); printf("       "); 
	gotoxy(1,8); printf("Format Entry waktu");
	gotoxy(1,9); printf("jam <spasi> menit");
	ReadTIME(&waktu); 
	return waktu;
}

void tulisFile(addressQueue data){
    FILE *fptr;
    char Jamdatang[10], Menitdatang[10], biaya[10],selesai[10],jumlah[10],namaSakit[34], nomor[10], kategoriSakit[10];

    int banyak,i, no;
    no = 0;

    addressPenyakit penyakit;
    // membuka file
    fptr = fopen("History.txt","a+");

    // mengubah integer menjadi char agar dapat masuk dalam file
	  itoa(data->info.waktuDatang.Hour,Jamdatang,10);
	  itoa(data->info.waktuDatang.Minute,Menitdatang,10);

    banyak = HitungElement(data->info.disease);
    itoa(banyak,jumlah,10);
    itoa(no,nomor,10);
    itoa(data->info.bayar, biaya, 10);
    

    penyakit = data->info.disease.First;

    // menulis ke text ke file
    fputs("[=] Nama                  : ", fptr); fputs(data->info.nama, fptr);
	fputs("\n[=] Jam Kedatangan        : ", fptr); fputs(Jamdatang, fptr);
	fputs(" : ", fptr); fputs(Menitdatang, fptr);
    fputs("\n[=] Jumlah Penyakit       : ", fptr); fputs(jumlah, fptr);
    fputs("\n[=] Penyakit              : ", fptr);
    while (penyakit != NULL ){
    	strcpy(namaSakit, convertEnum(penyakit));
        if(penyakit->info.kategori == 'R'){
        	strcpy(kategoriSakit, "Ringan");
		}else if(penyakit->info.kategori == 'S'){
			strcpy(kategoriSakit, "Sedang");
		}else if(penyakit->info.kategori == 'B'){
			strcpy(kategoriSakit, "Berat");
		}
        fputs(namaSakit, fptr); fputs(" ( ", fptr); fputs(kategoriSakit, fptr); fputs(" ), ", fptr);
        penyakit = penyakit->next;
    }
   fputs("\n[=] Total Biaya           : Rp. ", fptr); fputs(biaya, fptr);
  	fputs("\n====================================================================================== ", fptr);
    fputs("\n\n", fptr);

    // tutup file
    fclose(fptr);
}

void bacaFile(){
    system("cls");
    system("color a");
	judul();
    gotoxy(8,12);printf("[======================================================================================]\n");
	gotoxy(8,13);printf("[--------------------            HISTORY PET CLINIC        ----------------------------]\n");
	gotoxy(8,14);printf("[======================================================================================]\n\n");


    FILE *fp;
    char str[87];

    int j=1;
    /* membuka file */
    fp = fopen("History.txt" , "r");
    if(fp == NULL) {
        perror("Error opening file");
        return;
    }
    while(fgets (str, 87, fp)!=NULL ) {
        gotoxy(10,13+(j+1)); puts(str);
        j++;
    }
    fclose(fp);
	gotoxy(30, 9+(j+5)); printf("Tekan Apapun Untuk Kembali !!!");
    getch();
}

