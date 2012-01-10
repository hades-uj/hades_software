#include <TApplication.h>
#include <TGClient.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1F.h>
#include <TRandom.h>
#include <TGButton.h>
#include <TRootEmbeddedCanvas.h>
#include <fstream>
#include <string>

#include "data_show.h"

using namespace std;

//FUNCTIONS/////////////
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
///////////////////////////////////////////////////////////////



MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h)
{ 
        FILE *cfg_file = fopen ("param.txt","rt");
        char str_buf [25];
        int val;

        if (cfg_file == NULL) 
	{
            operation_mode_flag=0;//przy braku pliku konfiguracyjnego program będzie rysował wszystkie pliki z katalogu
	    printf ("No config file - default settings\r\n");
	 //sprawdzamy ilość plików 
	  //gApplication->Terminate(0);
             i_r1_min = 0;
             i_r1_max = 7;
             i_c1_min = 0;
             i_c1_max = 7;
             i_r2_min = 0;
             i_r2_max = 7;
             i_c2_min = 0;
             i_c2_max = 7;
        }
	else
	{//wpisujemy wartosci indeksow
        while (!feof(cfg_file)) {//////////////////////////////////////////wczytanie wartości z pliku konfiguracyjnego
	    operation_mode_flag=1;//program sam bedzie generował sobie nazwy plików do narysowania
            fscanf (cfg_file,"%s %d\n",str_buf,&val);
            if ( strcmp (str_buf,"ITER_r1_min") == 0 ) i_r1_min = val;
            if ( strcmp (str_buf,"ITER_r1_max") == 0 ) i_r1_max = val;
            if ( strcmp (str_buf,"ITER_c1_min") == 0 ) i_c1_min = val;
            if ( strcmp (str_buf,"ITER_c1_max") == 0 ) i_c1_max = val;
            if ( strcmp (str_buf,"ITER_r2_min") == 0 ) i_r2_min = val;
            if ( strcmp (str_buf,"ITER_r2_max") == 0 ) i_r2_max = val;
            if ( strcmp (str_buf,"ITER_c2_min") == 0 ) i_c2_min = val;
            if ( strcmp (str_buf,"ITER_c2_max") == 0 ) i_c2_max = val;
            if ( strcmp (str_buf,"#####################") == 0 ) break;
        }

        fclose (cfg_file);////////////////////////////////////////////////////////
	}

// Create a main frame
fMain = new TGMainFrame(p,w,h);
// Create canvas widget
fEcanvas = new TRootEmbeddedCanvas("Ecanvas",fMain,1400,800);
fMain->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX| kLHintsExpandY,
10,10,10,1));
TCanvas *tmp = fEcanvas->GetCanvas();
tmp->Divide(7,4,0.001,0.001);
// Create a horizontal frame widget with buttons
TGHorizontalFrame *hframe = new TGHorizontalFrame(fMain,1400,40);
TGTextButton *draw = new TGTextButton(hframe,"&Draw");
draw->Connect("Clicked()","MyMainFrame",this,"DoDraw()");
hframe->AddFrame(draw, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
TGTextButton *exit = new TGTextButton(hframe,"&Exit",
"gApplication->Terminate(0)");
hframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
fMain->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
// Set a name to the main frame
fMain->SetWindowName("Simple Example");
// Map all subwindows of main frame
fMain->MapSubwindows();
// Initialize the layout algorithm
fMain->Resize(fMain->GetDefaultSize());
// Map main frame
fMain->MapWindow();

  
}
MyMainFrame::~MyMainFrame()
{

  // Clean up used widgets: frames, buttons, layouthints
fMain->Cleanup();
delete fMain;

  
}
void MyMainFrame::DoDraw() 
{
string pliki[28];
int x,y;
//tworzenia nazw 28 plikow z danymi do histogramu
unsigned short index=0;
short unsigned  hr1= i_r1_min;
short unsigned  hc1= i_c1_min;
short unsigned  hr2= i_r2_min;
short unsigned  hc2= i_c2_min;

while (hr1<=i_r1_max)
{
  while (hc1<=i_c1_max)
  {
    while (hr2<=i_r2_max)
    {      
      while (hc2<=i_c2_max)
        {
	pliki[index]+= dec8_to_bin(hr1) + dec8_to_bin(hc1) + dec8_to_bin(hr2) + dec8_to_bin(hc2);
	index++;	
	hc2++;
	if(index==28){i_c2_min=hc2;	break;}
	}
    hc2=0;
    if(index==28){i_r2_min=hr2;  break;}
    hr2++;
    }
  hr2=0;
  if(index==28){i_c1_min=hc1;  break;}
  hc1++;
  }
hc1=0;
if(index==28){i_r1_min=hr1;  break;}
hr1++;
}
/////////////////////////////////////////////////////koniec tworzenia nazw plikow

//otwieramy kazdy plik wczytujemy jego dane do histogramu
TH1F *hist[28];
TCanvas *fCanvas = fEcanvas->GetCanvas();

FILE *data_file;


for(int k=0 ; k<28 ; k++)
   {
   if(pliki[k].length() == 0)
   break;	
   hist[k] = new TH1F(pliki[k].c_str(),pliki[k].c_str(),1800,200,2000);
   cout<<pliki[k]<<" <> ";

  // data_file = fopen (string("/home/PS/Programy/PicoScope/panda_fe_akwizycja/v3/output/"+pliki[k]).c_str(),"rt");
   data_file = fopen (string(pliki[k]).c_str(),"rt");

   if (data_file == NULL) 
      {
            cout<<" There is no file: "<<pliki[k]<<" filling empty histogram";
	    fCanvas->cd(k+1);
            hist[k]->Draw();
            continue;
      }

    while (!feof(data_file))//właściwe uzupełnianie histogramu 
	  { 
            fscanf (data_file,"%d %d\n",&x,&y);
	    hist[k]->Fill(x,y);
          }
          fclose (data_file);////////////////////////////////////////////////////////

    fCanvas->cd(k+1);
    hist[k]->Draw();
   }
cout<<"\n\n\n";

fCanvas->Update();//odswieżanie
}



void example()
{    // Popup the GUI...
new MyMainFrame(gClient->GetRoot(),500,500);
 }





int main(int argc, char **argv) {
TApplication theApp("App",&argc,argv);
example();
theApp.Run();
return 0;
}

