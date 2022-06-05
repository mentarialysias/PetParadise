#include "PQueue.h"

int main(){
PriorityQueue Antrian;
int end;
system("Color F0");
//loading();
BuatAntrian(&Antrian);
	while(end!=1)				//game akan terus berlanjut selama end tidak sama dengan 1
	{
		end=pilihanMenuUtama(Antrian);
	}
	gotoxy(1,30);printf("Program Akan Diberhentikan");
	Sleep(1000);
	keluar();
	printf("\n\n");
	
	return 0;
}
