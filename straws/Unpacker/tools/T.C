#define T_cxx
// The class definition in T.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("T.C")
// Root > T->Process("T.C","some options")
// Root > T->Process("T.C+")
//

#include "T.h"
#include <TH2.h>
#include <TStyle.h>


int channelA = 4;
int channelB = 8;
int channelC = 0;
int channelD = 24;
int timeA = -1000000;
int timeB = -1000000;
int timeC = -1000000;
int timeD = -1000000;
int trailTimeA = -1000000;
int trailTimeB = -1000000;
int trailTimeC = -1000000;
int trailTimeD = -1000000;


TH1 *diff4and8;
TH1 *diff24and0;
TH1 *countsAfterChA;
TH1 *countsAfterChC;
TH2 *totChAvsChB;
TH2 *totChCvsChD;
TH2 *totChAvsChD;
TH2 *totChCvsChB;
TH1 *totChA;
TH1 *totChB;
TH1 *totChC;
TH1 *totChD;
TH1 *driftChA;
TH1 *driftChB;
TH1 *driftChC;
TH1 *driftChD;
TH2 *driftChAvsChB;
TH2 *driftChAvsChD;
TH2 *driftChCvsChD;
TH2 *driftChCvsChB;
TH2 *driftChAvsTot;
TH2 *driftChBvsTot;
TH2 *driftChCvsTot;
TH2 *driftChDvsTot;

TCanvas *canvas;

TDatime *time;

void T::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void T::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   time = new TDatime();
   
   canvas = new TCanvas("Canvas", "Canvas", 0, 0, 500, 500);
   
   diff4and8  = new TH1F("ABDiff", "diff channel 4 and 8", 200, -100, 100);
   diff24and0 = new TH1F("CDDiff", "diff channel 24 and 0", 200, -100, 100);
   countsAfterChA = new TH1F("afterChA", "Channels hit after channel A", 31, 0, 31);
   countsAfterChC = new TH1F("afterChC", "Channels hit after channel C", 31, 0, 31);
   totChAvsChB = new TH2F("totChAvsChB", "TOT of channel A vs TOT of channel B", 2500, -1000, 1500, 2500, -1000, 1500);
   totChCvsChD = new TH2F("totChCvsChD", "TOT of channel C vs TOT of channel D", 2500, -1000, 1500, 2500, -1000, 1500);
   totChAvsChD = new TH2F("totChAvsChD", "TOT of channel A vs TOT of channel D", 2500, -1000, 1500, 2500, -1000, 1500);
   totChCvsChB = new TH2F("totChCvsChB", "TOT of channel C vs TOT of channel B", 2500, -1000, 1500, 2500, -1000, 1500);
   totChA = new TH1F("totChA", "TOT of channel A", 2500, -1000, 1500);
   totChB = new TH1F("totChB", "TOT of channel B", 2500, -1000, 1500);
   totChC = new TH1F("totChC", "TOT of channel C", 2500, -1000, 1500);
   totChD = new TH1F("totChD", "TOT of channel D", 2500, -1000, 1500);
   driftChA = new TH1F("driftChA", "Drift time on channel A", 2000, -1000, 1000);
   driftChB = new TH1F("driftChB", "Drift time on channel B", 2000, -1000, 1000);
   driftChC = new TH1F("driftChC", "Drift time on channel C", 2000, -1000, 1000);
   driftChD = new TH1F("driftChD", "Drift time on channel D", 2000, -1000, 1000);
   driftChAvsChB = new TH2F("driftChAvsChB", "Drift time on channel A vs drift time on channel B", 150, 300, 450, 150, 300, 450);
   driftChAvsChD = new TH2F("driftChAvsChD", "Drift time on channel A vs drift time on channel D", 150, 300, 450, 150, 300, 450);
   driftChCvsChD = new TH2F("driftChCvsChD", "Drift time on channel C vs drift time on channel D", 150, 300, 450, 150, 300, 450);
   driftChCvsChB = new TH2F("driftChCvsChB", "Drift time on channel C vs drift time on channel B", 150, 300, 450, 150, 300, 450);
   driftChAvsTot = new TH2F("driftChAvsTot", "Drift time vs TOT on channel A", 150, 300, 450, 1600, -600, 1000);
   driftChBvsTot = new TH2F("driftChBvsTot", "Drift time vs TOT on channel B", 150, 300, 450, 1600, -600, 1000);
   driftChCvsTot = new TH2F("driftChCvsTot", "Drift time vs TOT on channel C", 150, 300, 450, 1600, -600, 1000);
   driftChDvsTot = new TH2F("driftChDvsTot", "Drift time vs TOT on channel D", 150, 300, 450, 1600, -600, 1000);

}

Bool_t T::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either T::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
   
   b_event_totalNHits->GetEntry(entry);
   b_event_Hits_->GetEntry(entry);
   b_event_referenceTime->GetEntry(entry);
   
   bool foundA = false;
   bool foundB = false;
   bool foundC = false;
   bool foundD = false;
   
   // go to next event in case this ones reference time is corrupted
   if (referenceTime < 0) return kTRUE;

   
   for(int i = 0; i < totalNHits; i++) {
   	      
   	   // findtime difference between channels 4 and 8
   	   if(Hits_channel[i] == channelA && foundA == false && foundB == false) {
   	   	   timeA = Hits_leadTime1[i];
   	   	   trailTimeA = Hits_trailTime1[i];
   	   	   foundA = true;
   	   }
   	   else if(Hits_channel[i] == channelB && foundB == false && foundA == true) {
   	   	   timeB = Hits_leadTime1[i];
   	   	   trailTimeB = Hits_trailTime1[i];
   	   	   foundB = true;
   	   }
   	   
   	   // find time difference between channels 24 and 0
   	   if(Hits_channel[i] == channelC && foundC == false && foundD == false) {
   	   	   timeC = Hits_leadTime1[i];
   	   	   trailTimeC = Hits_trailTime1[i];
   	   	   foundC = true;
   	   }
   	   else if(Hits_channel[i] == channelD && foundD == false && foundC == true) {
   	   	   timeD = Hits_leadTime1[i];
   	   	   trailTimeD = Hits_trailTime1[i];
   	   	   foundD = true;
   	   }
   	   
   	   // channels hit after channel A
   	   if (foundA == true && (Hits_channel[i] == channelB || Hits_channel[i] == channelC || Hits_channel[i] == channelD)) {
   	   	   countsAfterChA->Fill(Hits_channel[i]);
   	   }
   	   
   	   // channels hit after channel C
   	   if (foundC == true && (Hits_channel[i] == channelA || Hits_channel[i] == channelB || Hits_channel[i] == channelD)) {
   	   	   countsAfterChC->Fill(Hits_channel[i]);
   	   }
   }
   
   if (foundA == true && foundB == true) {
   	   diff4and8->Fill(0.1 * (timeB - timeA));
   	   
   	   if (((referenceTime - timeA) > 3000 && (referenceTime - timeA) < 4500) && ((referenceTime - timeB) > 3000 && (referenceTime - timeB) < 4500)) {
   	   	   totChAvsChB->Fill(0.1 * (trailTimeA - timeA), 0.1 * (trailTimeB - timeB));
   	   	   driftChAvsChB->Fill(0.1 * (referenceTime - timeA), 0.1 * (referenceTime - timeB));
   	   }
   }
   
   if (foundC == true && foundD == true) {
   	   diff24and0->Fill(0.1 * (timeD - timeC));
   	   
   	   if (((referenceTime - timeC) > 3000 && (referenceTime - timeC) < 4500) && ((referenceTime - timeD) > 3000 && (referenceTime - timeD) < 4500)) {
   	   	   totChCvsChD->Fill(0.1 * (trailTimeC - timeC), 0.1 * (trailTimeD - timeD));
   	   	   driftChCvsChD->Fill(0.1 * (referenceTime - timeC), 0.1 * (referenceTime - timeD));
   	   }
   }
   
   if (foundC == true && foundB == true) {
   	   
   	   if (((referenceTime - timeC) > 3000 && (referenceTime - timeC) < 4500) && ((referenceTime - timeB) > 3000 && (referenceTime - timeB) < 4500)) {
   	   	   totChCvsChB->Fill(0.1 * (trailTimeC - timeC), 0.1 * (trailTimeB - timeB));
   	   	   driftChCvsChB->Fill(0.1 * (referenceTime - timeC), 0.1 * (referenceTime - timeB));	
   	   }   
   }
   
   if (foundA == true && foundD == true) {
   	   
   	   if (((referenceTime - timeA) > 3000 && (referenceTime - timeA) < 4500) && ((referenceTime - timeD) > 3000 && (referenceTime - timeD) < 4500)) {
   	   	   totChAvsChD->Fill(0.1 * (trailTimeA - timeA), 0.1 * (trailTimeD - timeD));
   	   	   driftChAvsChD->Fill(0.1 * (referenceTime - timeA), 0.1 * (referenceTime - timeD));
   	   }
   }
   
   if (foundA == true && ((referenceTime - timeA) > 3000 && (referenceTime - timeA) < 4500) && trailTimeA > 0) {
   	   
   	   totChA->Fill(0.1 * (trailTimeA - timeA));
	   driftChA->Fill(0.1 * (referenceTime - timeA));
	   driftChAvsTot->Fill(0.1 * (referenceTime - timeA), 0.1 * (trailTimeA - timeA)); 	   
   }
   
   if (foundB == true && ((referenceTime - timeB) > 3000 && (referenceTime - timeB) < 4500) && trailTimeB > 0) {
   	   totChB->Fill(0.1 * (trailTimeB - timeB));
   	   driftChB->Fill(0.1 * (referenceTime - timeB));
   	   driftChBvsTot->Fill(0.1 * (referenceTime - timeB), 0.1 * (trailTimeB - timeB));   	   
   }
   
   if (foundC == true && ((referenceTime - timeC) > 3000 && (referenceTime - timeC) < 4500) && trailTimeC > 0) {
   	   totChC->Fill(0.1 * (trailTimeC - timeC));
   	   driftChC->Fill(0.1 * (referenceTime - timeC));   	   
   	   driftChCvsTot->Fill(0.1 * (referenceTime - timeC), 0.1 * (trailTimeC - timeC));
   }
   
   if (foundD == true && ((referenceTime - timeD) > 3000 && (referenceTime - timeD) < 4500) && trailTimeD > 0) {
   	   totChD->Fill(0.1 * (trailTimeD - timeD));
   	   driftChD->Fill(0.1 * (referenceTime - timeD));   	   
   	   driftChDvsTot->Fill(0.1 * (referenceTime - timeD), 0.1 * (trailTimeD - timeD));
   }
   
   return kTRUE;
}

void T::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void T::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   
   
   
   diff4and8->Draw();
   canvas->Print("diff4and8.png", "png");
   diff24and0->Draw();
   canvas->Print("diff24and0.png", "png");
   afterChA->Draw();
   canvas->Print("afterChA.png", "png");
   afterChC->Draw();
   canvas->Print("afterChC.png", "png");
   totChAvsChB->Draw();
   canvas->Print("totChAvsChB.png", "png");
   totChCvsChD->Draw();
   canvas->Print("totChCvsChD.png", "png");
   totChAvsChD->Draw();
   canvas->Print("totChAvsChD.png", "png");
   totChCvsChB->Draw();
   canvas->Print("totChCvsChB.png", "png");
   totChA->Draw();
   canvas->Print("totChA.png", "png");
   totChB->Draw();
   canvas->Print("totChB.png", "png");
   totChC->Draw();
   canvas->Print("totChC.png", "png");
   totChD->Draw();
   canvas->Print("totChD.png", "png");
   driftChA->Draw();
   canvas->Print("driftChA.png", "png");
   driftChB->Draw();
   canvas->Print("driftChB.png", "png");
   driftChC->Draw();
   canvas->Print("driftChC.png", "png");
   driftChD->Draw();
   canvas->Print("driftChD.png", "png");
   driftChAvsChB->Draw();
   canvas->Print("driftChAvsChB.png", "png");
   driftChAvsChD->Draw();
   canvas->Print("driftChAvsChD.png", "png");
   driftChCvsChD->Draw();
   canvas->Print("driftChCvsChD.png", "png");
   driftChCvsChB->Draw();
   canvas->Print("driftChCvsChB.png", "png");
   driftChAvsTot->Draw();
   canvas->Print("driftChAvsTot.png", "png");
   driftChBvsTot->Draw();
   canvas->Print("driftChBvsTot.png", "png");
   driftChCvsTot->Draw();
   canvas->Print("driftChCvsTot.png", "png");
   driftChDvsTot->Draw();
   canvas->Print("driftChDvsTot.png", "png");
   
   cout<<"Generated histograms: \n - diff4and8 \n - diff24and0 \n - afterChA \n - afterChC \n - totChAvsChB \n - totChCvsChD \n - totChAvsChD \n - totChCvsChB \n - totChA \n - totChB \n - totChC \n - totChD \n - driftChA \n - driftChB \n - driftChC \n - driftChD \n - driftChAvsChB \n - driftChAvsChD \n - driftChCvsChB \n - driftChCvsChD \n - driftChAvsTot \n - driftChBvsTot \n - driftChCvsTot \n - driftChDvsTot \n";
}
