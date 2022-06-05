
#include "TIME.h"
#include "tampilan.h"


/* Prototype ADT Time */
/** Konstruktor membentuk ADT TIME **/
void CreateTIME (TIME *J, int HH, int MM)
{
/* Membentuk sebuah TIME dari komponen-komponennya yang valid 
     Pre condition : HH,MM,SS valid untuk membentuk TIME
     I.S : J tidak terdefinisi, tidak diketahui nilainya
     F.S : membentuk sebuah TIME dari komponen-komponennya dengan J diinisialisasi nilainya dengan 
	   Hour = HH, Minute = MM, Second = SS 
*/
    (*J).Hour = HH;
    (*J).Minute = MM;
}

/*****************************************************************/
/** { Operasi terhadap komponen : selektor Get dan Set } **/
/* GETTER TIME **/
int GetHour(TIME J)
{
// Mengirimkan komponen Hour dari J
    return J.Hour;
}
int GetMinute(TIME J)
{
// Mengirimkan komponen Minute dari J
    return J.Minute;
}

/* Set nilai komponen */
void SetHour(TIME *J, int newHour)
{
// Mengubah komponen Hour dari J
    (*J).Hour = newHour;
}

void SetMinute(TIME *J, int newMinute)
{
// Mengubah komponen Minute dari J
    (*J).Minute = newMinute;
}



/*****************************************************************/
/** {Kelompok Baca/Tulis} **/
void ReadTIME (TIME *J)
{
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan TIME yang valid */
/* Proses : mengulangi membaca komponen H,M,S sehingga membentuk J yang valid.*/
/* Tidak mungkin menghasilkan J yang tidak valid */
    TIME new;
    do
    {
    	gotoxy(26,3);printf("                 ");
    	gotoxy(26,3);scanf("%d %d", &new.Hour, &new.Minute);
    	fflush(stdin);
    } while (!IsJValid(new.Hour, new.Minute));

    *J = new;
}

void PrintTIME (TIME J)
{
/* I.S. : J sembarang */
/* F.S. : Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar */ 
    printf("%02d:%02d", J.Hour, J.Minute);
}

/*****************************************************************/
/** { kelompok Validasi Type } **/
bool IsJValid (int H, int M)
{
/* Mengirim true jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah TIME */
/* Konstruktor: Membentuk sebuah TIME dari komponen-komponennya */
    return (((H >= 0) && (H <= 23)) && ((M >= 0) && (M <= 59)));
}

/** {Operator Relasional} **/
bool JEQ(TIME J1, TIME J2)
{
/* Mengirimkan true jika Jl=J2, false jika tidak */
    return (J1.Hour == J2.Hour) && (J1.Minute == J2.Minute);
}

bool JNEQ(TIME J1, TIME J2)
{
/* Mengirimkan true jika Jl tidak sama dengan J2 */
    return !JEQ(J1, J2);
}

bool JLT(TIME J1, TIME J2)
{
/* Mengirimkan true jika J1<J2 , false jika tidak */
    if (JNEQ(J1, J2))
    {
        if (J1.Hour > J2.Hour)
            return false;
        else if (J1.Hour < J2.Hour)
            return true;
        else
        {
            if (J1.Minute > J2.Minute)
                return false;
            else if (J1.Minute < J2.Minute)
                return true;
  		}
  	}
    else
        return false;
}

bool JGT(TIME J1, TIME J2)
{
/* Mengirimkan true jika Jl>J2, false jika tidak*/
    return JNEQ(J1, J2) && !JLT(J1, J2);
}
/*****************************************************************/
/** { operator aritmatika } **/
TIME JPlus(TIME J1, TIME J2)
{
/* Menghasilkan Jl+J2, clalam bentuk TIME */
    TIME J;
    J.Minute = J1.Minute + J2.Minute;
    J.Hour = J1.Hour + J2.Hour;

    while (J.Minute >= 60)
    {
        J.Hour++;
        J.Minute -= 60;
    }

    while (J.Hour >= 24)
        J.Hour = 0;

    return J;
}

TIME JMinus(TIME J1, TIME J2)
{
/* Menghasilkan Jl?J2, dalam bentuk TIME */
/* Precond : Jl<:J2 */
    TIME J;
    J.Minute = J1.Minute - J2.Minute;
    J.Hour = J1.Hour - J2.Hour;
    if (J.Minute < 0)
    {
        J.Hour--;
        J.Minute += 60;
    }

    if (J.Hour < 0)
        J.Hour += 24;

    return J;
}


long int Durasi (TIME Jaw , TIME JAkh)
{
/* Mengirim JAkh ?JAw dlm Detik, dengen kalkulasi */
/* Hasilnya negatif jika Jaw > JAkhir */
    return TimeToDetik(JAkh) - TimeToDetik(Jaw);
}

/*****************************************************************/
/** {Kelompok Konversi Terhadap Type} **/
long int TimeToDetik (TIME J)
{
/* Diberikan sebuah TIME, mengkonversi menjadi Detik */
/* Rumus : detik = 3600*hour+menit*60 + detik */
/* nilai maksimum = 3600*23+59*60+59*60 */
/* hati-hati dengan representasi integer pada bahasa implementasi */
/* kebanyakan sistem mengimplementasi integer, */
/* bernilai maksimum kurang dari nilai maksimum hasil konversi */
    return 3600 * J.Hour + 60 * J.Minute;
}

void DetikToTIME (long int N)
{
/* Mengirim konversi detik ke TIME. Pada beberapa bahasa, representasi integer tidak cukup untuk menampung N */
    TIME J;
	
    J.Hour = N/3600;
    printf("%d:",J.Hour);
    N %= 3600;
	
    J.Minute = N/60;
    printf("%d:",J.Minute);
    N %= 60;

}