#include "tampilan.h"

void judul(){
int i;
system("cls");
i=1;
gotoxy(43,2);printf("W E L C O M E      T O ");
while (i<=10){
	gotoxy(i,5);     printf(" *#####*      *##*       *#####*      *##*     *#####*     ####  *#####+    #######    \n");
	gotoxy(19-i,6);  printf(" ##    ##    *#   #*     ##    ##    *#   #*    ##    #*     ##   ##    ##   ##         \n");
	gotoxy(i-1,7);   printf(" ##    ##   *#     #*    ##    ##   *#     #*   ##     #*    ##   ##         ##         \n");
	gotoxy(19-i,8);  printf(" **####*   *# ===== #*   *#####*   *# ===== #*  ##      #*   ##    *####*    *######    \n");
	gotoxy(i-1,9);   printf(" ##        ##       ##   ##  ##    ##       ##  ##     *#    ##         ##   ##         \n");
	gotoxy(19-i,10); printf(" ##        ##       ##   ##   ##   ##       ##  ##    *#     ##   ##    ##   ##         \n");
	gotoxy(i-1,11);  printf(" ##        ##       ##   ##    ##  ##       ##  *####*#     ####  +#####*    #######    \n");
		Sleep(300);
		i++;
	}
gotoxy(43,13);printf("P E T    C L I N I C ");
}


void bingkai(){
int i;
for (i = 19; i <= 81; i++){
		gotoxy(i,14);
		printf("=");
		gotoxy(i,26);
		printf("=");
		Sleep(10);
	}
	//bingkai samping
	for (i = 15; i <= 25; i++){
		gotoxy(19,i);
		printf("||");
		gotoxy(80,i);
		printf("||");
		Sleep(10);
	}	
}

void gotoxy(int x, int y){
	HANDLE hConsoleOutput;  
	COORD dwCursorPosition;  
	dwCursorPosition.X = x;  
	dwCursorPosition.Y = y;  
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);   
}


int cursor(int option,int x,int y)											
{
int select=1;
	int input;
	gotoxy(x,y);printf("%c",16);
	do
	{
		input=getch();															
		if(input==80)														
		{
			gotoxy(x,y);printf(" ");
			y++;select++;
			if(select>option)
			{
				y=y-option;
				select=1;
			}
			gotoxy(x,y);printf("%c",16);
		}
		if(input==72)											
		{
			gotoxy(x,y);printf(" ");
			y--;select--;
			if(select<1)
			{
				y=y+option;
				select=option;
			}
			gotoxy(x,y);printf("%c",16);			
		}
		if(input==8) //backspace
		{
			select=8;
		}
	}
	while(input!=13 && input!=8);														//berakhir saat input berisi enter
	return select;																
}


void lihatTabelPenyakit(/*int posisi*/){
    system("cls");
    int posisi = 24;
    judul();
    for (int i = 16; i <38 ; ++i) {
        gotoxy(8,i);printf("||                                                                                   ||\n");
    }
    gotoxy(8,18);printf("=======================================================================================\n");
    gotoxy(posisi,20);printf("||=======================================================||\n");
    gotoxy(posisi,21);printf("||--------------------  Tabel  Penyakit  ----------------||\n");
	gotoxy(posisi,22);printf("||=======================================================||\n");
  	gotoxy(posisi,23);printf("|| Kategori ||        Nama            || Biaya Pelayanan ||\n");
  	gotoxy(posisi,24);printf("||  Ringan  || Penyakit Kulit         ||    Rp. 30.000   ||\n");
    gotoxy(posisi,25);printf("||  Ringan  || Luka Ringan            ||    Rp. 30.000   ||\n");
	gotoxy(posisi,26);printf("||  Ringan  || Bersin                 ||    Rp. 30.000   ||\n");
    gotoxy(posisi,27);printf("||  Sedang  || Cacingan               ||    Rp. 45.000   ||\n");
    gotoxy(posisi,28);printf("||  Sedang  || Diare                  ||    Rp. 45.000   ||\n");
    gotoxy(posisi,29);printf("||  Sedang  || Luka Dalam             ||    Rp. 45.000   ||\n");
    gotoxy(posisi,30);printf("||  Berat   || Gangguan Kerongkongan  ||    Rp. 60.000   ||\n");
    gotoxy(posisi,31);printf("||  Berat   || Kuning                 ||    Rp. 60.000   ||\n");
    gotoxy(posisi,32);printf("||  Berat   || Virus                  ||    Rp. 60.000   ||\n");
  	gotoxy(posisi,33);printf("||=======================================================||\n");
  	gotoxy(posisi-5,36);printf("Tekan Enter Untuk Kembali ke Menu");
  	gotoxy(8,37);printf("=======================================================================================\n");
  	getchar();
}

void KataSelesai(){
system("cls");
judul();
bingkai();
gotoxy(23,18);printf("  *** ^_^  Selamat kucing anda sudah Terobati  ^_^ ***\n");
gotoxy(28,19);printf("[ Data Anda sudah dimasukkan dalam file kami ]");
gotoxy(30,22);printf("^_^ Semoga Kucing Anda Cepat Sembuh  ^_^\n");
}

void KataMenunggu(){
system("cls");
judul();
bingkai();
gotoxy(24,18);printf(" *** Kucing anda sedang dalam proses pengobatan ***\n");
gotoxy(40,19);printf("Harap bersabar ^_^\n");
gotoxy(24,20);printf("---- Tekan tombol enter untuk kembali ke menu ^_^ ----\n");
}



int MenuUtama(){
	judul();
	bingkai();
	system("Color F0");
	int i = 43;
	gotoxy(i, 16); printf("    Menu Utama \n\n");
	gotoxy(i, 18);printf("    Pelayanan                    \n");
	gotoxy(i, 19);printf(" Daftar Penyakit              \n");
	gotoxy(i, 20);	printf(" History Antrian              \n");
	gotoxy(i, 21);	printf("      Exit              \n");
	gotoxy(i, 24); printf(" CHOOSE THE MENU              \n");
	return cursor(4,41,18);	
}




int MenuPelayanan(){
	judul();
	bingkai();
	system("Color F0");
	int i = 40;
	gotoxy(i, 15); printf("     Menu Pelayanan               ");
	gotoxy(i, 17);printf("    Registrasi Baru              ");
	gotoxy(i, 18);printf("     Lihat Antrian                ");
	gotoxy(i, 19);	printf("    Proses Antrian             ");
	gotoxy(i, 20);	printf("     Cari Antrian                 ");
	gotoxy(i, 21);	printf("        Tutup                     ");
	gotoxy(i, 24); printf("   CHOOSE THE MENU                ");
	return cursor(5,39,17);	
	
}

void tutup(bool *end){
	system("cls");
	system("Color 07");
	judul();
	char pemilik = 'n';
	char tutup;
	char sandi[6] ={"TUBES"};
	char password[6];
	gotoxy(9, 15);printf("=============================================================================================\n");
	gotoxy(30, 16);printf("Apakan Anda Pemilik Pet Paradise ? [Y/N]  ");
	scanf("%c", &pemilik);
	fflush(stdin);
	if(pemilik == 'Y' || pemilik == 'y'){
		gotoxy(30,17);printf("Masukkan Kode Pet Paradise : ");
		scanf("%s", password);
		fflush(stdin);
		if(strcmp(password, sandi)==0){
			system("cls");
			system("Color 07");
			judul();
			bingkai();
			gotoxy(36,16);printf("Pet Paradise Telah Ditutup");
			gotoxy(26,18);printf("Data Pasien yang telah terobati disimpan dalam file");
			gotoxy(30,19);printf("Data Pasien yang belum terobati akan dihapus");
			gotoxy(22,20);printf("Data Pasien yang belum terobati tidak disimpan dalam file");
			gotoxy(35,23);printf("Selamat bekerja lagi esok hari ^_^ ");
			gotoxy(38,24);printf("Tekan Enter Untuk Kembali");
			getchar();
			(*end) = false;
		}else{
			gotoxy(30,26);printf("Anda bukan Pemilik Pet Paradise !!!");
			Sleep(3000);
		}	
	}else{
		gotoxy(30,18);printf("Anda Tidak bisa menutup Pet Paradise !!!");
		Sleep(3000);
	}
	
}

// Prosedur dari referensi internet untuk menampilkan loading
void keluar(){

system("cls");

	int i;
		for(i = 50; i<=90; i++){
		gotoxy(i,18);
		printf("-");
		gotoxy(i,20);
		printf("-");
		system("color 0F");
		Sleep(20);
	}
	
	for(i = 1; i <= 100; i++){
		gotoxy(63,19);
		printf("L O A D I N G ");
		printf("%d %%", i);
		Sleep(100);
	}
}

void tampilPenyakit()
{
	system("cls");
		system("color F0"); 
		printf("====================== PARADISE PET CLINIC ======================\n");
		printf("||                     [TYPE OF DISEASES]                      ||\n");
    	printf("|| Pilih Penyakit !!!                                          ||\n");
    	printf("|| 1. Penyakit Kulit        (R)                                ||\n");
    	printf("|| 2. Luka Ringan           (R)                                ||\n");
    	printf("|| 3. Bersin                (R)                                ||\n");
    	printf("|| 4. Cacingan              (S)                                ||\n");
		printf("|| 5. Diare                 (S)                                ||\n");
    	printf("|| 6. Luka Dalam            (S)                                ||\n");
		printf("|| 7. Gangguan Keronkongan  (B)                                ||\n");
    	printf("|| 8. Kuning                (B)                                ||\n"); 
    	printf("|| 9. Virus                 (B)                                ||\n");
		printf("||                                                             ||\n");
		printf("|| Masukkan Data Penyakit:                                     ||\n");  
		printf("=================================================================\n");
		
}

void FormatInput(){
	printf("===================== PARADISE  PET  CLINIC =====================\n");
    printf("||                     [REGISTRASI BARU]                       ||\n");
    printf("|| Silahkan Isi Formulir!                                      ||\n");
    printf("|| * Waktu Datang       :                                      ||\n");
    printf("|| * Nama               :                                      ||\n");
    printf("|| * Total Penyakit 	:                                      ||\n");
    printf("||                                                             ||\n");
	printf("=================================================================\n");
	fflush(stdin);
}
