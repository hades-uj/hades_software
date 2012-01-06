//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jan 04 11:11:52 2012 by ROOT version 5.28/00b
// from TTree T/An example of a ROOT tree
// found on file: ../../te11337190736.hld.root
//////////////////////////////////////////////////////////

#ifndef T_h
#define T_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

   const Int_t kMaxHits = 11;

class T : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
 //Event           *event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          EvtHdr_fUniqueID;
   UInt_t          EvtHdr_fBits;
   Int_t           EvtHdr_size;
   Int_t           EvtHdr_decoding;
   Int_t           EvtHdr_id;
   Int_t           EvtHdr_seqNr;
   Int_t           EvtHdr_date;
   Int_t           EvtHdr_time;
   Int_t           EvtHdr_year;
   Int_t           EvtHdr_month;
   Int_t           EvtHdr_day;
   Int_t           EvtHdr_hour;
   Int_t           EvtHdr_minute;
   Int_t           EvtHdr_second;
   Int_t           EvtHdr_pad;
   Int_t           EvtHdr_dataSize;
   Int_t           EvtHdr_paddedSize;
   Int_t           kMaxMult;
   Int_t           kMaxChannelNr;
   UInt_t          subEvtId;
   Int_t           errors_per_event;
   Int_t           referenceChannel;
   Int_t           referenceTime;
   Int_t           totalNHits;
   Int_t           Hits_;
   UInt_t          Hits_fUniqueID[kMaxHits];   //[Hits_]
   UInt_t          Hits_fBits[kMaxHits];   //[Hits_]
   Int_t           Hits_channel[kMaxHits];   //[Hits_]
   Int_t           Hits_TDC[kMaxHits];   //[Hits_]
   Int_t           Hits_nHits[kMaxHits];   //[Hits_]
   Int_t           Hits_width_wk[kMaxHits];   //[Hits_]
   Int_t           Hits_leadTime1[kMaxHits];   //[Hits_]
   Int_t           Hits_trailTime1[kMaxHits];   //[Hits_]
   Int_t           Hits_leadTime2[kMaxHits];   //[Hits_]
   Int_t           Hits_trailTime2[kMaxHits];   //[Hits_]
   Int_t           Hits_leadTime3[kMaxHits];   //[Hits_]
   Int_t           Hits_trailTime3[kMaxHits];   //[Hits_]
   Int_t           Hits_leadTime4[kMaxHits];   //[Hits_]
   Int_t           Hits_trailTime4[kMaxHits];   //[Hits_]

   // List of branches
   TBranch        *b_event_fUniqueID;   //!
   TBranch        *b_event_fBits;   //!
   TBranch        *b_event_EvtHdr_fUniqueID;   //!
   TBranch        *b_event_EvtHdr_fBits;   //!
   TBranch        *b_event_EvtHdr_size;   //!
   TBranch        *b_event_EvtHdr_decoding;   //!
   TBranch        *b_event_EvtHdr_id;   //!
   TBranch        *b_event_EvtHdr_seqNr;   //!
   TBranch        *b_event_EvtHdr_date;   //!
   TBranch        *b_event_EvtHdr_time;   //!
   TBranch        *b_event_EvtHdr_year;   //!
   TBranch        *b_event_EvtHdr_month;   //!
   TBranch        *b_event_EvtHdr_day;   //!
   TBranch        *b_event_EvtHdr_hour;   //!
   TBranch        *b_event_EvtHdr_minute;   //!
   TBranch        *b_event_EvtHdr_second;   //!
   TBranch        *b_event_EvtHdr_pad;   //!
   TBranch        *b_event_EvtHdr_dataSize;   //!
   TBranch        *b_event_EvtHdr_paddedSize;   //!
   TBranch        *b_event_kMaxMult;   //!
   TBranch        *b_event_kMaxChannelNr;   //!
   TBranch        *b_event_subEvtId;   //!
   TBranch        *b_event_errors_per_event;   //!
   TBranch        *b_event_referenceChannel;   //!
   TBranch        *b_event_referenceTime;   //!
   TBranch        *b_event_totalNHits;   //!
   TBranch        *b_event_Hits_;   //!
   TBranch        *b_Hits_fUniqueID;   //!
   TBranch        *b_Hits_fBits;   //!
   TBranch        *b_Hits_channel;   //!
   TBranch        *b_Hits_TDC;   //!
   TBranch        *b_Hits_nHits;   //!
   TBranch        *b_Hits_width_wk;   //!
   TBranch        *b_Hits_leadTime1;   //!
   TBranch        *b_Hits_trailTime1;   //!
   TBranch        *b_Hits_leadTime2;   //!
   TBranch        *b_Hits_trailTime2;   //!
   TBranch        *b_Hits_leadTime3;   //!
   TBranch        *b_Hits_trailTime3;   //!
   TBranch        *b_Hits_leadTime4;   //!
   TBranch        *b_Hits_trailTime4;   //!

   T(TTree * /*tree*/ =0) { }
   virtual ~T() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(T,0);
};

#endif

#ifdef T_cxx
void T::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_event_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_event_fBits);
   fChain->SetBranchAddress("EvtHdr.fUniqueID", &EvtHdr_fUniqueID, &b_event_EvtHdr_fUniqueID);
   fChain->SetBranchAddress("EvtHdr.fBits", &EvtHdr_fBits, &b_event_EvtHdr_fBits);
   fChain->SetBranchAddress("EvtHdr.size", &EvtHdr_size, &b_event_EvtHdr_size);
   fChain->SetBranchAddress("EvtHdr.decoding", &EvtHdr_decoding, &b_event_EvtHdr_decoding);
   fChain->SetBranchAddress("EvtHdr.id", &EvtHdr_id, &b_event_EvtHdr_id);
   fChain->SetBranchAddress("EvtHdr.seqNr", &EvtHdr_seqNr, &b_event_EvtHdr_seqNr);
   fChain->SetBranchAddress("EvtHdr.date", &EvtHdr_date, &b_event_EvtHdr_date);
   fChain->SetBranchAddress("EvtHdr.time", &EvtHdr_time, &b_event_EvtHdr_time);
   fChain->SetBranchAddress("EvtHdr.year", &EvtHdr_year, &b_event_EvtHdr_year);
   fChain->SetBranchAddress("EvtHdr.month", &EvtHdr_month, &b_event_EvtHdr_month);
   fChain->SetBranchAddress("EvtHdr.day", &EvtHdr_day, &b_event_EvtHdr_day);
   fChain->SetBranchAddress("EvtHdr.hour", &EvtHdr_hour, &b_event_EvtHdr_hour);
   fChain->SetBranchAddress("EvtHdr.minute", &EvtHdr_minute, &b_event_EvtHdr_minute);
   fChain->SetBranchAddress("EvtHdr.second", &EvtHdr_second, &b_event_EvtHdr_second);
   fChain->SetBranchAddress("EvtHdr.pad", &EvtHdr_pad, &b_event_EvtHdr_pad);
   fChain->SetBranchAddress("EvtHdr.dataSize", &EvtHdr_dataSize, &b_event_EvtHdr_dataSize);
   fChain->SetBranchAddress("EvtHdr.paddedSize", &EvtHdr_paddedSize, &b_event_EvtHdr_paddedSize);
   fChain->SetBranchAddress("kMaxMult", &kMaxMult, &b_event_kMaxMult);
   fChain->SetBranchAddress("kMaxChannelNr", &kMaxChannelNr, &b_event_kMaxChannelNr);
   fChain->SetBranchAddress("subEvtId", &subEvtId, &b_event_subEvtId);
   fChain->SetBranchAddress("errors_per_event", &errors_per_event, &b_event_errors_per_event);
   fChain->SetBranchAddress("referenceChannel", &referenceChannel, &b_event_referenceChannel);
   fChain->SetBranchAddress("referenceTime", &referenceTime, &b_event_referenceTime);
   fChain->SetBranchAddress("totalNHits", &totalNHits, &b_event_totalNHits);
   fChain->SetBranchAddress("Hits", &Hits_, &b_event_Hits_);
   fChain->SetBranchAddress("Hits.fUniqueID", Hits_fUniqueID, &b_Hits_fUniqueID);
   fChain->SetBranchAddress("Hits.fBits", Hits_fBits, &b_Hits_fBits);
   fChain->SetBranchAddress("Hits.channel", Hits_channel, &b_Hits_channel);
   fChain->SetBranchAddress("Hits.TDC", Hits_TDC, &b_Hits_TDC);
   fChain->SetBranchAddress("Hits.nHits", Hits_nHits, &b_Hits_nHits);
   fChain->SetBranchAddress("Hits.width_wk", Hits_width_wk, &b_Hits_width_wk);
   fChain->SetBranchAddress("Hits.leadTime1", Hits_leadTime1, &b_Hits_leadTime1);
   fChain->SetBranchAddress("Hits.trailTime1", Hits_trailTime1, &b_Hits_trailTime1);
   fChain->SetBranchAddress("Hits.leadTime2", Hits_leadTime2, &b_Hits_leadTime2);
   fChain->SetBranchAddress("Hits.trailTime2", Hits_trailTime2, &b_Hits_trailTime2);
   fChain->SetBranchAddress("Hits.leadTime3", Hits_leadTime3, &b_Hits_leadTime3);
   fChain->SetBranchAddress("Hits.trailTime3", Hits_trailTime3, &b_Hits_trailTime3);
   fChain->SetBranchAddress("Hits.leadTime4", Hits_leadTime4, &b_Hits_leadTime4);
   fChain->SetBranchAddress("Hits.trailTime4", Hits_trailTime4, &b_Hits_trailTime4);
}

Bool_t T::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef T_cxx
