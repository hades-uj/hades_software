/*********************************************
 *Program do analizy impulsów zebranych podczas testów 
 *detektora słomkowego. Otwiera po kolei pliki z zapisanymi
 *przebiegami. Szuka maksimum i minimum. Okresla baseline 
 *licząc wartość średnią z piewszych 100 pomiarów (baseline 
 *powinnien być równy zero ale z powodów szumów nie jest)
 *Nazwy plików zawierające przebiegi, które spełniają okreslone
 *założenia (odpowiednie czasy opadania i wznoszenia,
 *wzmocnienie). 
 *
 *Paweł Strzempek
 *pawel.strzempek@uj.edu.pl
 *
**********************************************/





#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cmath>

#define SCIEZKA "/home/ps/Programy/PicoScope/panda_fe_akwizycja/v3/output/"//sciezka do katalogu z danymi
#define CZAS 150

using namespace std;

//***************FUNKCJE*********************************
string dec8_to_bin (int input)
{
string output;
switch (input)
        {
        case 0: {output = "000";}; break;
        case 1: {output = "001";}; break;
        case 2: {output = "010";}; break;
        case 3: {output = "011";}; break;
        case 4: {output = "100";}; break;
        case 5: {output = "101";}; break;
        case 6: {output = "110";}; break;
        case 7: {output = "111";}; break;
        default: {output = "000";}; break;
        }
return output;
}
////////////////////
inline double wartosc_srednia(int tab[2000][2], double iter)
{
double wynik=0;
	for (int k = 0; k< iter ; k++)
	{
	wynik+=tab[k][1];
	}
wynik = wynik/iter;
//cout<<wynik<<endl;
return wynik;
}
////////////////////
inline double wartosc_srednia_kwadrat(int tab[2000][2], double iter)
{
double wynik=0;
        for (int k = 0; k< iter ; k++)
        {
        wynik+=(tab[k][1]*tab[k][1]);
        }
wynik = wynik/iter;
//cout<<"kw "<<wynik<<endl;
return wynik;
}
////////////////////
double odchylenie(int tab[2000][2], double iter)
{
double wynik=0;
double srednia = wartosc_srednia( tab, iter);
double srednia_kwadratow = wartosc_srednia_kwadrat( tab, iter);

wynik = srednia_kwadratow;
wynik -= (srednia*srednia);
wynik *=iter;
wynik /= (iter-1);
return sqrt(wynik);
}
                                 
//******************************************************


struct punkt
{
int x;
int y;
};





int main()
{
struct punkt minimum = {0,0};
struct punkt maximum = {0,0};

struct punkt P = {0,0};
struct punkt K = {0,0};


int data[2000][2];//tablica do przechowywania danych z pliku
string cmd = "";//
string buf = "";
int g=0;//licznik
int tmp_MAX, tmp_MIN, tmp_time_MAX;
FILE *fp = fopen("output_file4", "w");//plik z wynikami

//typy danych zapisywane do pliku:

 fprintf (fp,"PLIK - nazwa pliku z impulsem\nAMPL_MIN - amplituda przerzutu\nAMPL_MAX - amplituda impulsu\nCZAS_NAR - czas narastania czyli czas od momentu gdy impuls przekroczy wartość = baseline+3*odchylenia_standardowe do maksimum\nCZAS_OPA - czas opadania, jak wyżej tylko od maksimum do baseline+3*sigma\n  POCZ_IMP - początek impulsu czyli punkt przekroczenia baseline+3*sigma\nKONI_IMP - koniec impulsu czyli punkt powrotu do baseline+3*sigma (ale przed przerzutem)\nBP - brak przerzutu\n##########################################################################################################\n ");
 fprintf (fp,"PLIK\tAMPL_MIN\tAMPL_MAX\tCZAS_NAR\tCZAS_OPA\tPOCZ_IMP\tKONI_IMP\n");

int iter_max=7;
 for (int hr1= 0; hr1<=iter_max; hr1++)//cztery pętle każda odpowiada za iteracji po jednym z parametrów
 {
   for (int hc1= 0; hc1<=iter_max; hc1++)
   {
     for (int hr2= 0; hr2<=iter_max; hr2++)
     {
       for (int hc2= 0; hc2<=iter_max; hc2++)
         {
	 g =0;
	 tmp_MAX = 0;
	 tmp_MIN = 0;
	 tmp_time_MAX = 0;
	 maximum.x=0;
	 maximum.y =0;
	 minimum.x=0;
	 minimum.y =0;
	 for(int t=0 ; t<2000 ; t++){ data[t][0] =0 ; data[t][1]=0; }//czyscimy tablice
         cmd="";


	 //na podstawie aktualnych iteratorów generuje się nazwę pliku
         cmd += dec8_to_bin(hr1) + dec8_to_bin(hc1) + dec8_to_bin(hr2) + dec8_to_bin(hc2);
	 printf("Processing file: %s\r",cmd.c_str());
	 fstream data_file;
	 data_file.open(string(SCIEZKA+cmd).c_str(), ios::in);
        
	 if(!data_file.is_open())
          {//sprawdzamy czy uda się otworzyć plik jeślni nie to idziemy do następnego
           printf("Fail to open file %s\n",cmd.c_str());
	   fprintf (fp,"%s\t--err--\t--err--\n",cmd.c_str());
           continue; 
	  }
         while (getline(data_file,buf))//wczytujemy dane z pliku i zapisujemy je w tab 2D przy okazji szukamy punktu max i min
                {
                    sscanf(buf.c_str(),"%d %d",&data[g][0],&data[g][1]);//&x,&y);//wczytujemy dane
                    if(data[g][1]>maximum.y){ maximum.y = data[g][1]; maximum.x = data[g][0];}//szukamy wartosci max
		    if(data[g][1]<minimum.y){ minimum.y = data[g][1]; minimum.x = data[g][0];}//szukamy wartości min
	            g++;
		}
          data_file.close();


	//ustalamy base line jako wartosc srednia ze 100 pierwszy pomiarow. Za początek impulsu uznajemy punkt 
	//ale którego jego wartość przekaracza wartość średnia powiększoną o 3 odchyl standardowe
	double wartosc_kontrolna_max = wartosc_srednia(data,100.) + 3*odchylenie(data,100.);
	double wartosc_kontrolna_min = wartosc_srednia(data,100.) - 3*odchylenie(data,100.);


	/*Wyszukanie punktu w ktorym zaczyna sie impuls*/
	g=maximum.x;
        while(g>0)
		{
		if(data[g][1]<wartosc_kontrolna_max )
		  {
			P.x = data[g-1][0];
			P.y = data[g-1][1];
			break;
		  } 
		g--;
		}


	/*Wyszukanie punktu w ktorym konczy sie impuls*/
	g=maximum.x;
	while(g<2000)
		{
		if(data[g][1]<wartosc_kontrolna_max && data[g][0] > maximum.x )//jestesmy 'za' maksimum czyli na zboczu opadajacym 
		  {
	                K.x = data[g][0];
                        K.y = data[g][1];
		  	break;
		  }
		g++;
		}
        /******************************************/

	/*w tym miejscu mamy już tablicę dwu wymiarową z wszystkimi danymi oraz wybraną wartość max i min z tej tablicy*/
	/*teraz sprawdzimy czy konfiguracja będzie spełnie nasze założenia*/
	/*w tym celu szukamy miejsca w którym sygnał spada do pewnej wrtości procentowej maksymalnej amplitudy*/	  

	/*poprawiamy amplitudę uwzgledniając poziom baseline*/
	maximum.y -= wartosc_srednia(data,100.);
	minimum.y -= wartosc_srednia(data,100.); 
	/****************************************************/

	if(minimum.y>=wartosc_kontrolna_min)
	{//przebiegi bez przerzutu
	 fprintf (fp,"%s\t%d\t%d\t%d\t%d\t%d\t%d\tBP\n",cmd.c_str(),maximum.y,minimum.y,maximum.x-P.x,K.x-maximum.x,P.x,K.x );	
	}
	else
	{//przebiegi z przerzutem
	 if((minimum.x > maximum.x) && (data[maximum.x+CZAS][0]>minimum.x) &&(data[maximum.x+CZAS][1]>(wartosc_srednia(data,100.)-odchylenie(data,100.))) )
	 fprintf (fp,"%s\t%d\t%d\t%d\t%d\t%d\t%d\n",cmd.c_str(),maximum.y,minimum.y,maximum.x-P.x,K.x-maximum.x,P.x,K.x );	
	}
	  
     }
   }
 }
}   
fclose(fp);
printf("\n");
return 0;
}
