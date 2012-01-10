
#include <TH2.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TApplication.h>
#include <unistd.h>
#include <TSystem.h>
#include <TFile.h>
#include <TKey.h>


using namespace std;

int main(int argc, char **argv)
{
  TApplication theApp("App",&argc,argv);
  //Int_t ilosc_obiektow = 0;
  gStyle->SetPalette(1);
  
  //TFile f("/home/PS/Programy/ROOTprog/PPEpEm/wyniki/histogramy_PPEpEm.root");
  
  TCanvas *can1 = new TCanvas("can1","can1",800,800);
  TH1F *hist1 = new TH1F("h1","h1",100,0,100);
  hist1->Fill(12,22.4);
  hist1->Draw();

//gSystem->Sleep(20000); 
  //f.Close();  
  theApp.Run();
  return (0);
}


