#include <TApplication.h>
#include <TGClient.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TRandom.h>
#include <TGButton.h>
#include <TRootEmbeddedCanvas.h>
#include <fstream>
#include <string>

#include "data_show.h"



MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h)
{ 
//wpisujemy wartosci indeksow
std::string buf;
  ifstream myfile ("param.txt");
  if (myfile.is_open())
     {
     if ( myfile.good() )
        {
        getline (myfile,buf);
        }
     myfile.close();
     }
     else {std::cout << "Unable to open file: 'param.txt'\n"; gApplication->Terminate(0);}
  
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
// Draws function graphics in randomly choosen interval
TH1F *hist[28];
for(int i =0 ; i<28 ; i++)
//	hist[i] = new TH1F("cofig","config",1000,0,1000);
i_r1++;



TF1 *f1 = new TF1("f1","sin(x)/x*x",0,gRandom->Rndm()*10);
f1->SetFillColor(19);
f1->SetFillStyle(1);
f1->SetLineWidth(3);

TCanvas *fCanvas = fEcanvas->GetCanvas();
//fCanvas->Divide(2,2);
fCanvas->cd(2);
f1->Draw();
fCanvas->Update();
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

