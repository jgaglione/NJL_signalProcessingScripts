/*
This macro performs the dielectron+jets selection for the LQ feasibility study and
it saves the histos relevant for doing further plots and estimating the significance

root -l lqAnalysis.C
*/

#include "TH1.h"
#include "TH2.h"
#include "TSystem.h"

#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "external/ExRootAnalysis/ExRootResult.h"
#endif

//User input
const float nAllEntries = -1; //-1 means all entries available in the current rootFile
const float luminosity = 300000; //in /pb (e.g. 300 /fb is 300*1000)
//Signal 
const string process = "outputName";
const string sample = "processFolder/runFolder";
const float xSec = xSecValue; //in pb
float numRuns = 1; //set it = to the runs used to produced a given sample:  = 1 for signal, n for background
const float sampleEventsTot = -1; //set -1 if the normalizations (weightEn,weightLumi) will be done on nAllEntries, or on the num you indicate (which should be tot num for all the runs of a sample)
//Background
//const string process = "ttbar";
//const string sample = "NJL_BG_tt123j_noMadspin_Events";
//const float xSec = 10.; //in pb
//float numRuns = 100; //set it = to the runs used to produced a given sample:  = 1 for signal, n for background
//const float sampleEventsTot = -1; //set -1 if the normalizations (weightEn,weightLumi) will be done on nAllEntries, or on the num you indicate (which should be tot num for all the runs of a sample)

//Standard input
const string inputFilePath = "/mnt/ceph/home/gaglijt1/";
const string rootFile = "/tag_1_delphes_events.root";
string run = "/Run_";

//Functions
class ExRootResult;
class ExRootTreeReader;
struct MyPlots{
 //event quantities
 TH1* hnEvtXSecLumiWeight;
 //genLQ
 TH1* hnGenLQ;
 //electrons
 TH1* hnEles;
 TH1* hEle0_pT;
 TH1* hEle0_pT_nGenLQ0;
 TH1* hEle0_pT_nGenLQ1;
 TH1* hEle0_pT_nGenLQ2;
 TH1* hEle1_pT;
 TH1* hEle1_pT_nGenLQ0;
 TH1* hEle1_pT_nGenLQ1;
 TH1* hEle1_pT_nGenLQ2;
 TH1* hEle0_eta;
 TH1* hEle0_eta_nGenLQ0;
 TH1* hEle0_eta_nGenLQ1;
 TH1* hEle0_eta_nGenLQ2;
 TH1* hEle1_eta;
 TH1* hEle1_eta_nGenLQ0;
 TH1* hEle1_eta_nGenLQ1;
 TH1* hEle1_eta_nGenLQ2;
 //jets
 TH1* hnJets;
 TH1* hnJets_nGenLQ0;
 TH1* hnJets_nGenLQ1;
 TH1* hnJets_nGenLQ2;
 TH1* hnBJets;
 TH1* hJet0_pT;
 TH1* hJet0_pT_nGenLQ0;
 TH1* hJet0_pT_nGenLQ1;
 TH1* hJet0_pT_nGenLQ2;
 TH1* hJet1_pT;
 TH1* hJet1_pT_nGenLQ0;
 TH1* hJet1_pT_nGenLQ1;
 TH1* hJet1_pT_nGenLQ2;
 TH1* hJet2_pT;
 TH1* hJet2_pT_nGenLQ0;
 TH1* hJet2_pT_nGenLQ1;
 TH1* hJet2_pT_nGenLQ2;
 TH1* hJet3_pT;
 TH1* hJet3_pT_nGenLQ0;
 TH1* hJet3_pT_nGenLQ1;
 TH1* hJet3_pT_nGenLQ2;
 TH1* hJet0_eta;
 TH1* hJet0_eta_nGenLQ0;
 TH1* hJet0_eta_nGenLQ1;
 TH1* hJet0_eta_nGenLQ2;
 TH1* hJet1_eta;
 TH1* hJet1_eta_nGenLQ0;
 TH1* hJet1_eta_nGenLQ1;
 TH1* hJet1_eta_nGenLQ2;
 TH1* hJet2_eta;
 TH1* hJet2_eta_nGenLQ0;
 TH1* hJet2_eta_nGenLQ1;
 TH1* hJet2_eta_nGenLQ2;
 TH1* hJet3_eta;
 TH1* hJet3_eta_nGenLQ0;
 TH1* hJet3_eta_nGenLQ1;
 TH1* hJet3_eta_nGenLQ2;
 //met
 TH1* hMet;
 //for selected events
 TH1* hCutFlow;
 TH1* hCutFlow_nGenLQ0;
 TH1* hCutFlow_nGenLQ1;
 TH1* hCutFlow_nGenLQ2;
 TH1* hChi;
 TH1* hChi_nGenLQ0;
 TH1* hChi_nGenLQ1;
 TH1* hChi_nGenLQ2;
 TH1* hChi0;
 TH1* hChi0_nGenLQ0;
 TH1* hChi0_nGenLQ1;
 TH1* hChi0_nGenLQ2;
 TH1* hChi1;
 TH1* hChi1_nGenLQ0;
 TH1* hChi1_nGenLQ1;
 TH1* hChi1_nGenLQ2;
 TH1* hChi2;
 TH1* hChi2_nGenLQ0;
 TH1* hChi2_nGenLQ1;
 TH1* hChi2_nGenLQ2;
 TH1* hChi3;
 TH1* hChi3_nGenLQ0;
 TH1* hChi3_nGenLQ1;
 TH1* hChi3_nGenLQ2;
 TH1* hMass;
 TH1* hMass_nGenLQ0;
 TH1* hMass_nGenLQ1;
 TH1* hMass_nGenLQ2;
 TH1* hMass0;
 TH1* hMass0_nGenLQ0;
 TH1* hMass0_nGenLQ1;
 TH1* hMass0_nGenLQ2;
 TH1* hMass1;
 TH1* hMass1_nGenLQ0;
 TH1* hMass1_nGenLQ1;
 TH1* hMass1_nGenLQ2;
 TH1* hMass2;
 TH1* hMass2_nGenLQ0;
 TH1* hMass2_nGenLQ1;
 TH1* hMass2_nGenLQ2;
 TH1* hMass3;
 TH1* hMass3_nGenLQ0;
 TH1* hMass3_nGenLQ1;
 TH1* hMass3_nGenLQ2;
 TH1* hSt;
 TH1* hSt_nGenLQ0;
 TH1* hSt_nGenLQ1;
 TH1* hSt_nGenLQ2;
 TH1* hSt0;
 TH1* hSt0_nGenLQ0;
 TH1* hSt0_nGenLQ1;
 TH1* hSt0_nGenLQ2;
 TH1* hSt1;
 TH1* hSt1_nGenLQ0;
 TH1* hSt1_nGenLQ1;
 TH1* hSt1_nGenLQ2;
 TH1* hSt2;
 TH1* hSt2_nGenLQ0;
 TH1* hSt2_nGenLQ1;
 TH1* hSt2_nGenLQ2;
 TH1* hSt3;
 TH1* hSt3_nGenLQ0;
 TH1* hSt3_nGenLQ1;
 TH1* hSt3_nGenLQ2;
 TH1* hSt_asymBins;
 TH1* hSt_asymBins_nGenLQ0;
 TH1* hSt_asymBins_nGenLQ1;
 TH1* hSt_asymBins_nGenLQ2;
 TH1* hSt0_asymBins;
 TH1* hSt0_asymBins_nGenLQ0;
 TH1* hSt0_asymBins_nGenLQ1;
 TH1* hSt0_asymBins_nGenLQ2;
 TH1* hSt1_asymBins;
 TH1* hSt1_asymBins_nGenLQ0;
 TH1* hSt1_asymBins_nGenLQ1;
 TH1* hSt1_asymBins_nGenLQ2;
 TH1* hSt2_asymBins;
 TH1* hSt2_asymBins_nGenLQ0;
 TH1* hSt2_asymBins_nGenLQ1;
 TH1* hSt2_asymBins_nGenLQ2;
 TH1* hSt3_asymBins;
 TH1* hSt3_asymBins_nGenLQ0;
 TH1* hSt3_asymBins_nGenLQ1;
 TH1* hSt3_asymBins_nGenLQ2;
 TH2* hChiSt; 
 TH2* hChiSt_nGenLQ0;
 TH2* hChiSt_nGenLQ1;
 TH2* hChiSt_nGenLQ2;
 TH2* hChiSt0;
 TH2* hChiSt0_nGenLQ0;
 TH2* hChiSt0_nGenLQ1;
 TH2* hChiSt0_nGenLQ2;
 TH2* hChiSt1;
 TH2* hChiSt1_nGenLQ0;
 TH2* hChiSt1_nGenLQ1;
 TH2* hChiSt1_nGenLQ2;
 TH2* hChiSt2;
 TH2* hChiSt2_nGenLQ0;
 TH2* hChiSt2_nGenLQ1;
 TH2* hChiSt2_nGenLQ2;
 TH2* hChiSt3;
 TH2* hChiSt3_nGenLQ0;
 TH2* hChiSt3_nGenLQ1;
 TH2* hChiSt3_nGenLQ2;
 //sensitivity
 TH1* hSt_jet0_chi0;
 TH1* hSt_jet0_chi0_nGenLQ0;
 TH1* hSt_jet0_chi0_nGenLQ1;
 TH1* hSt_jet0_chi0_nGenLQ2;
 TH1* hSt_jet0_chi1;
 TH1* hSt_jet0_chi1_nGenLQ0;
 TH1* hSt_jet0_chi1_nGenLQ1;
 TH1* hSt_jet0_chi1_nGenLQ2;
 TH1* hSt_jet0_chi2;
 TH1* hSt_jet0_chi2_nGenLQ0;
 TH1* hSt_jet0_chi2_nGenLQ1;
 TH1* hSt_jet0_chi2_nGenLQ2;
 TH1* hSt_jet1_chi0;
 TH1* hSt_jet1_chi0_nGenLQ0;
 TH1* hSt_jet1_chi0_nGenLQ1;
 TH1* hSt_jet1_chi0_nGenLQ2;
 TH1* hSt_jet1_chi1;
 TH1* hSt_jet1_chi1_nGenLQ0;
 TH1* hSt_jet1_chi1_nGenLQ1;
 TH1* hSt_jet1_chi1_nGenLQ2;
 TH1* hSt_jet1_chi2;
 TH1* hSt_jet1_chi2_nGenLQ0;
 TH1* hSt_jet1_chi2_nGenLQ1;
 TH1* hSt_jet1_chi2_nGenLQ2;
 TH1* hSt_jet2_chi0;
 TH1* hSt_jet2_chi0_nGenLQ0;
 TH1* hSt_jet2_chi0_nGenLQ1;
 TH1* hSt_jet2_chi0_nGenLQ2;
 TH1* hSt_jet2_chi1;
 TH1* hSt_jet2_chi1_nGenLQ0;
 TH1* hSt_jet2_chi1_nGenLQ1;
 TH1* hSt_jet2_chi1_nGenLQ2;
 TH1* hSt_jet2_chi2;
 TH1* hSt_jet2_chi2_nGenLQ0;
 TH1* hSt_jet2_chi2_nGenLQ1;
 TH1* hSt_jet2_chi2_nGenLQ2;
 TH1* hSt_jet3_chi0;
 TH1* hSt_jet3_chi0_nGenLQ0;
 TH1* hSt_jet3_chi0_nGenLQ1;
 TH1* hSt_jet3_chi0_nGenLQ2;
 TH1* hSt_jet3_chi1;
 TH1* hSt_jet3_chi1_nGenLQ0;
 TH1* hSt_jet3_chi1_nGenLQ1;
 TH1* hSt_jet3_chi1_nGenLQ2;
 TH1* hSt_jet3_chi2;
 TH1* hSt_jet3_chi2_nGenLQ0;
 TH1* hSt_jet3_chi2_nGenLQ1;
 TH1* hSt_jet3_chi2_nGenLQ2;
 TH1* hSt_jet0_chi0_asymBins;
 TH1* hSt_jet0_chi0_asymBins_nGenLQ0;
 TH1* hSt_jet0_chi0_asymBins_nGenLQ1;
 TH1* hSt_jet0_chi0_asymBins_nGenLQ2;
 TH1* hSt_jet0_chi1_asymBins;
 TH1* hSt_jet0_chi1_asymBins_nGenLQ0;
 TH1* hSt_jet0_chi1_asymBins_nGenLQ1;
 TH1* hSt_jet0_chi1_asymBins_nGenLQ2;
 TH1* hSt_jet0_chi2_asymBins;
 TH1* hSt_jet0_chi2_asymBins_nGenLQ0;
 TH1* hSt_jet0_chi2_asymBins_nGenLQ1;
 TH1* hSt_jet0_chi2_asymBins_nGenLQ2;
 TH1* hSt_jet1_chi0_asymBins;
 TH1* hSt_jet1_chi0_asymBins_nGenLQ0;
 TH1* hSt_jet1_chi0_asymBins_nGenLQ1;
 TH1* hSt_jet1_chi0_asymBins_nGenLQ2;
 TH1* hSt_jet1_chi1_asymBins;
 TH1* hSt_jet1_chi1_asymBins_nGenLQ0;
 TH1* hSt_jet1_chi1_asymBins_nGenLQ1;
 TH1* hSt_jet1_chi1_asymBins_nGenLQ2;
 TH1* hSt_jet1_chi2_asymBins;
 TH1* hSt_jet1_chi2_asymBins_nGenLQ0;
 TH1* hSt_jet1_chi2_asymBins_nGenLQ1;
 TH1* hSt_jet1_chi2_asymBins_nGenLQ2;
 TH1* hSt_jet2_chi0_asymBins;
 TH1* hSt_jet2_chi0_asymBins_nGenLQ0;
 TH1* hSt_jet2_chi0_asymBins_nGenLQ1;
 TH1* hSt_jet2_chi0_asymBins_nGenLQ2;
 TH1* hSt_jet2_chi1_asymBins;
 TH1* hSt_jet2_chi1_asymBins_nGenLQ0;
 TH1* hSt_jet2_chi1_asymBins_nGenLQ1;
 TH1* hSt_jet2_chi1_asymBins_nGenLQ2;
 TH1* hSt_jet2_chi2_asymBins;
 TH1* hSt_jet2_chi2_asymBins_nGenLQ0;
 TH1* hSt_jet2_chi2_asymBins_nGenLQ1;
 TH1* hSt_jet2_chi2_asymBins_nGenLQ2;
 TH1* hSt_jet3_chi0_asymBins;
 TH1* hSt_jet3_chi0_asymBins_nGenLQ0;
 TH1* hSt_jet3_chi0_asymBins_nGenLQ1;
 TH1* hSt_jet3_chi0_asymBins_nGenLQ2;
 TH1* hSt_jet3_chi1_asymBins;
 TH1* hSt_jet3_chi1_asymBins_nGenLQ0;
 TH1* hSt_jet3_chi1_asymBins_nGenLQ1;
 TH1* hSt_jet3_chi1_asymBins_nGenLQ2;
 TH1* hSt_jet3_chi2_asymBins;
 TH1* hSt_jet3_chi2_asymBins_nGenLQ0;
 TH1* hSt_jet3_chi2_asymBins_nGenLQ1;
 TH1* hSt_jet3_chi2_asymBins_nGenLQ2;
};
void BookHistograms(ExRootResult *result, MyPlots *plots);
void AnalyseEvents(ExRootTreeReader *treeReader, MyPlots *plots);
void PrintHistograms(ExRootResult *result, MyPlots *plots);
void valInBoundaries(float& val,float iniRange,float endRange);

//------------------------------------------------------------------------------
//histo bins and range
//event quantities
const int hnEvtXSecLumiWeight_binsX = 3;   const float hnEvtXSecLumiWeight_IniRangeX = 0.;    const float hnEvtXSecLumiWeight_EndRangeX = 3.;
//genLQ
const int hnGenLQ_binsX = 3;   const float hnGenLQ_IniRangeX = 0.;    const float hnGenLQ_EndRangeX = 3.;
const int hnJets_nGenLQ_binsX = 4;   const float hnJets_nGenLQ_IniRangeX = 0.;    const float hnJets_nGenLQ_EndRangeX = 4.;
//electrons
const int hnEles_binsX = 10;   const float hnEles_IniRangeX = 0.;    const float hnEles_EndRangeX = 10.;
const int hEle_pT_binsX = 100; const float hEle_pT_IniRangeX = 0.;   const float hEle_pT_EndRangeX = 1000.;
const int hEle_eta_binsX = 30; const float hEle_eta_IniRangeX = -5.; const float hEle_eta_EndRangeX = 5.;
//jets
const int hnJets_binsX = 10;   const float hnJets_IniRangeX = 0.;    const float hnJets_EndRangeX = 10.;
const int hJet_pT_binsX = 100; const float hJet_pT_IniRangeX = 0.;   const float hJet_pT_EndRangeX = 1000.;
const int hJet_eta_binsX = 30; const float hJet_eta_IniRangeX = -5.; const float hJet_eta_EndRangeX = 5.;
const int hnBJets_binsX = 10;  const float hnBJets_IniRangeX = 0.;   const float hnBJets_EndRangeX = 10.;
//met
const int hMet_binsX = 100;    const float hMet_IniRangeX = 0.;     const float hMet_EndRangeX = 1000.;
//selection
const int hCutFlow_binsX = 10;       const float hCutFlow_IniRangeX = 0.; const float hCutFlow_EndRangeX = 10.;
const int hChi_binsX = 100;          const float hChi_IniRangeX = 0.;     const float hChi_EndRangeX = 25.;
const int hMass_binsX = 100;         const float hMass_IniRangeX = 0.;    const float hMass_EndRangeX = 1000.;
const int hSt_binsX = 300;           const float hSt_IniRangeX = 0.;      const float hSt_EndRangeX = 3000.;
const int hChiSt_binsX = hSt_binsX;  const float hChiSt_IniRangeX = hSt_IniRangeX; const float hChiSt_EndRangeX = hSt_EndRangeX;
const int hChiSt_binsY = hChi_binsX; const float hChiSt_IniRangeY = hChi_IniRangeX; const float hChiSt_EndRangeY = hChi_EndRangeX;
//sensitivity
const int hSt_jet_chi_binx = 15; const float hSt_jet_chi_IniRangeX = 0.; const float hSt_jet_chi_EndRangeX = 3000.;
const float chi0bin = 2.5; 
const float chi1bin = 6; 
const Int_t asymBinsN = 12;
const Int_t asymBinsDim = asymBinsN+1;
const Float_t asymBins[asymBinsDim] = {0.,100.,200.,300.,400.,500.,600.,800.,1000.,1250.,1500.,2000.,3000.};
 
void scriptName(){//const char *inputFile)
 gSystem->Load("/home/romeof1/pheno/Delphes-3.5.0/libDelphes.so");
 // /afs/cern.ch/work/f/fromeo/pheno/Delphes-3.5.0/libDelphes.so");

 for(int nr=1; nr<=numRuns; nr++){
  //prepare names
  char int_str[20];
  sprintf(int_str,"%d",nr);
  string fileName = "";
  string inputFile = "";
  if(numRuns==1){
   fileName = process+".root";
   inputFile = inputFilePath+sample+rootFile; 
  }else{
   fileName = process+"_"+int_str+".root";
   inputFile = inputFilePath+sample+run+int_str+rootFile;
  }
  cout<<fileName<<endl; 
  cout<<inputFile<<endl;

  //call delphes root file
  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile.c_str());
   
  //analyze it
  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);
  ExRootResult *result = new ExRootResult();
  MyPlots *plots = new MyPlots;
  BookHistograms(result,plots);

  AnalyseEvents(treeReader,plots);

  //save results
  //PrintHistograms(result,plots);
  result->Write(fileName.c_str());
  
  string mvFile = "mv " + fileName + " /mnt/ceph/home/gaglijt1/NJL_rootFiles_ee1J_ap_ptjMin10_wCuts";
  const char *command = mvFile.c_str();
  system(command);

  cout<<"done"<<endl;
  cout<<endl;
 
  delete plots;
  delete result;
  delete treeReader;
  delete chain;
 }
}

void AnalyseEvents(ExRootTreeReader *treeReader, MyPlots *plots){
 //
 //Get branches of objects
 //
 TClonesArray *branchParticle = treeReader->UseBranch("Particle");
 TClonesArray *branchElectron = treeReader->UseBranch("Electron");
 TClonesArray *branchJet = treeReader->UseBranch("Jet");
 TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");
 //
 //Loop over events
 //
 Long64_t allEntries = nAllEntries;
 if(nAllEntries==-1) allEntries = treeReader->GetEntries();
 cout<<"Chain contains "<<treeReader->GetEntries()<<" events and we read "<<allEntries<<endl;
 float allEntriesTot = sampleEventsTot;
 if(sampleEventsTot==-1) allEntriesTot = allEntries;
 float weightEn = 1./float(allEntriesTot);
 float weightLumi = float(xSec)*float(luminosity)/float(allEntriesTot); 
 plots->hnEvtXSecLumiWeight->SetBinContent(1,float(xSec));
 plots->hnEvtXSecLumiWeight->SetBinContent(2,float(allEntriesTot));
 plots->hnEvtXSecLumiWeight->SetBinContent(3,weightLumi);
 for(Long64_t entry=0; entry<allEntries; entry++){
  //Load selected branches with data from specified event
  treeReader->ReadEntry(entry);
  //Save some info before selection
  //num of leptoquarks at generator level
  bool lqPart = false;
  bool lqAntiPart = false;
  float nGenLQ = 0;
  for(Int_t i=0; i < branchParticle->GetEntriesFast(); i++){
   GenParticle *gen = (GenParticle*) branchParticle->At(i);
   if(gen->PID==9000006 && !lqPart){
    nGenLQ = nGenLQ+1;
    lqPart = true;
   } 
   if(gen->PID==-9000006 && !lqAntiPart){
    nGenLQ = nGenLQ+1;
    lqAntiPart = true;
   } 
   //cout<<"N: "<<i<<", St: "<<gen->Status<<", PID: "<<gen->PID<<", E: "<<gen->E<<", Px: "<<gen->Px<<", Py: "<<gen->Py<<", Pz: "<<gen->Pz<<", M: "<<gen->Mass<<", T: "<<gen->T<<", X: "<<gen->X<<", Y: "<<gen->Y<<", Z: "<<gen->Z<<", M1: "<<gen->M1<<", M2: "<<gen->M2<<", D1: "<<gen->D1<<", D2: "<<gen->D2<<endl;
  }
  //cout<<"num lq is "<<nGenLQ<<endl;
  valInBoundaries(nGenLQ,hnGenLQ_IniRangeX,hnGenLQ_EndRangeX);
  plots->hnGenLQ->Fill(nGenLQ,weightEn);
  //electrons
  float nElectrons = branchElectron->GetEntries();
  //valInBoundaries(nElectrons,hnEles_IniRangeX,hnEles_EndRangeX);
  //plots->hnEles->Fill(nElectrons,weightEn);
  float anEles = 0;
  float aele0_pT = 0;
  float aele1_pT = 0;
  float aele0_eta = 0;
  float aele1_eta = 0;
  float aele0_charge = 0;
  float aele1_charge = 0;
  TLorentzVector aele0_momentum; aele0_momentum.SetPxPyPzE(0.0, 0.0, 0.0, 0.0);
  TLorentzVector aele1_momentum; aele1_momentum.SetPxPyPzE(0.0, 0.0, 0.0, 0.0);
  for(Int_t el=0; el<nElectrons; el++){
   Electron* ele = (Electron*) branchElectron->At(el);
   if(ele->PT>20 && fabs(ele->Eta)<2.5 && ele->IsolationVar<0.3){ // IsolationVar: 0.1 - Loose , 0.2 - Medium, 0.3 - Tight
    if(anEles==0){
     aele0_pT = ele->PT;
     aele0_eta = ele->Eta;
     aele0_charge = ele->Charge;
     aele0_momentum = ele->P4();
     float ele0PT = ele->PT; valInBoundaries(ele0PT,hEle_pT_IniRangeX,hEle_pT_EndRangeX);
     plots->hEle0_pT->Fill(ele0PT,weightEn);
     if(nGenLQ==0) plots->hEle0_pT_nGenLQ0->Fill(ele0PT,weightEn);
     if(nGenLQ==1) plots->hEle0_pT_nGenLQ1->Fill(ele0PT,weightEn);
     if(nGenLQ==2) plots->hEle0_pT_nGenLQ2->Fill(ele0PT,weightEn); 
     float ele0Eta = ele->Eta; valInBoundaries(ele0Eta,hEle_eta_IniRangeX,hEle_eta_EndRangeX);
     plots->hEle0_eta->Fill(ele0Eta,weightEn);
     if(nGenLQ==0) plots->hEle0_eta_nGenLQ0->Fill(ele0Eta,weightEn);
     if(nGenLQ==1) plots->hEle0_eta_nGenLQ1->Fill(ele0Eta,weightEn);
     if(nGenLQ==2) plots->hEle0_eta_nGenLQ2->Fill(ele0Eta,weightEn);
    }
    if(anEles==1){
     aele1_pT = ele->PT;
     aele1_eta = ele->Eta;
     aele1_charge = ele->Charge;
     aele1_momentum = ele->P4();
     float ele1PT = ele->PT; valInBoundaries(ele1PT,hEle_pT_IniRangeX,hEle_pT_EndRangeX);
     plots->hEle1_pT->Fill(ele1PT,weightEn);
     if(nGenLQ==0) plots->hEle1_pT_nGenLQ0->Fill(ele1PT,weightEn);
     if(nGenLQ==1) plots->hEle1_pT_nGenLQ1->Fill(ele1PT,weightEn);
     if(nGenLQ==2) plots->hEle1_pT_nGenLQ2->Fill(ele1PT,weightEn); 
     float ele1Eta = ele->Eta; valInBoundaries(ele1Eta,hEle_eta_IniRangeX,hEle_eta_EndRangeX);
     plots->hEle1_eta->Fill(ele1Eta,weightEn);
     if(nGenLQ==0) plots->hEle1_eta_nGenLQ0->Fill(ele1Eta,weightEn);
     if(nGenLQ==1) plots->hEle1_eta_nGenLQ1->Fill(ele1Eta,weightEn);
     if(nGenLQ==2) plots->hEle1_eta_nGenLQ2->Fill(ele1Eta,weightEn); 
    }
    anEles++;
   }
  }
  valInBoundaries(anEles,hnEles_IniRangeX,hnEles_EndRangeX);
  plots->hnEles->Fill(anEles,weightEn);
  //jets
  float nJets = branchJet->GetEntries();
  //valInBoundaries(nJets,hnJets_IniRangeX,hnJets_EndRangeX);
  //plots->hnJets->Fill(nJets,weightEn);
  float anJets = 0;
  float anBJets = 0;
  float ajet0_pT = 0;
  float ajet1_pT = 0;
  float ajet2_pT = 0;
  float ajet3_pT = 0;
  float ajet0_eta = 0;
  float ajet1_eta = 0;
  float ajet2_eta = 0;
  float ajet3_eta = 0;
  for(Int_t jt=0; jt<branchJet->GetEntries(); jt++){
   Jet* jet = (Jet*) branchJet->At(jt);
   if(jet->PT>20 && fabs(jet->Eta)<5){
    if(anEles==0 || (anEles>0 && aele0_momentum.DeltaR(jet->P4())>0.4)){ 
     if(anEles==0 || anEles==1 || (anEles>1 && aele1_momentum.DeltaR(jet->P4())>0.4)){
      if(anJets==0){
       ajet0_pT = jet->PT;
       ajet0_eta = jet->Eta;
       float jet0PT = jet->PT; valInBoundaries(jet0PT,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
       plots->hJet0_pT->Fill(jet0PT,weightEn);
       if(nGenLQ==0) plots->hJet0_pT_nGenLQ0->Fill(jet0PT,weightEn);
       if(nGenLQ==1) plots->hJet0_pT_nGenLQ1->Fill(jet0PT,weightEn);
       if(nGenLQ==2) plots->hJet0_pT_nGenLQ2->Fill(jet0PT,weightEn); 
       float jet0Eta = jet->Eta; valInBoundaries(jet0Eta,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
       plots->hJet0_eta->Fill(jet0Eta,weightEn);
       if(nGenLQ==0) plots->hJet0_eta_nGenLQ0->Fill(jet0Eta,weightEn);
       if(nGenLQ==1) plots->hJet0_eta_nGenLQ1->Fill(jet0Eta,weightEn);
       if(nGenLQ==2) plots->hJet0_eta_nGenLQ2->Fill(jet0Eta,weightEn); 
      }
      if(anJets==1){
       ajet1_pT = jet->PT;
       ajet1_eta = jet->Eta;
       float jet1PT = jet->PT; valInBoundaries(jet1PT,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
       plots->hJet1_pT->Fill(jet1PT,weightEn);
       if(nGenLQ==0) plots->hJet1_pT_nGenLQ0->Fill(jet1PT,weightEn);
       if(nGenLQ==1) plots->hJet1_pT_nGenLQ1->Fill(jet1PT,weightEn);
       if(nGenLQ==2) plots->hJet1_pT_nGenLQ2->Fill(jet1PT,weightEn); 
       float jet1Eta = jet->Eta; valInBoundaries(jet1Eta,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
       plots->hJet1_eta->Fill(jet1Eta,weightEn);
       if(nGenLQ==0) plots->hJet1_eta_nGenLQ0->Fill(jet1Eta,weightEn);
       if(nGenLQ==1) plots->hJet1_eta_nGenLQ1->Fill(jet1Eta,weightEn);
       if(nGenLQ==2) plots->hJet1_eta_nGenLQ2->Fill(jet1Eta,weightEn); 
      }
      if(anJets==2){
       ajet2_pT = jet->PT;
       ajet2_eta = jet->Eta;
       float jet2PT = jet->PT; valInBoundaries(jet2PT,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
       plots->hJet2_pT->Fill(jet2PT,weightEn);
       if(nGenLQ==0) plots->hJet2_pT_nGenLQ0->Fill(jet2PT,weightEn);
       if(nGenLQ==1) plots->hJet2_pT_nGenLQ1->Fill(jet2PT,weightEn);
       if(nGenLQ==2) plots->hJet2_pT_nGenLQ2->Fill(jet2PT,weightEn); 
       float jet2Eta = jet->Eta; valInBoundaries(jet2Eta,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
       plots->hJet2_eta->Fill(jet2Eta,weightEn);
       if(nGenLQ==0) plots->hJet2_eta_nGenLQ0->Fill(jet2Eta,weightEn);
       if(nGenLQ==1) plots->hJet2_eta_nGenLQ1->Fill(jet2Eta,weightEn);
       if(nGenLQ==2) plots->hJet2_eta_nGenLQ2->Fill(jet2Eta,weightEn); 
      }
      if(anJets==3){
       ajet3_pT = jet->PT;
       ajet3_eta = jet->Eta;
       float jet3PT = jet->PT; valInBoundaries(jet3PT,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
       plots->hJet3_pT->Fill(jet3PT,weightEn);
       if(nGenLQ==0) plots->hJet3_pT_nGenLQ0->Fill(jet3PT,weightEn);
       if(nGenLQ==1) plots->hJet3_pT_nGenLQ1->Fill(jet3PT,weightEn);
       if(nGenLQ==2) plots->hJet3_pT_nGenLQ2->Fill(jet3PT,weightEn); 
       float jet3Eta = jet->Eta; valInBoundaries(jet3Eta,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
       plots->hJet3_eta->Fill(jet3Eta,weightEn);
       if(nGenLQ==0) plots->hJet3_eta_nGenLQ0->Fill(jet3Eta,weightEn);
       if(nGenLQ==1) plots->hJet3_eta_nGenLQ1->Fill(jet3Eta,weightEn);
       if(nGenLQ==2) plots->hJet3_eta_nGenLQ2->Fill(jet3Eta,weightEn); 
      }
      anJets++;
      if(fabs(jet->Eta)<2.5 && jet->BTag) anBJets++;
     }
    } 
   }
  }
  float anJetMult = anJets;
  if(anJets>=3) anJetMult = 3;
  valInBoundaries(anJetMult,hnJets_nGenLQ_IniRangeX,hnJets_nGenLQ_EndRangeX);
  if(nGenLQ==0) plots->hnJets_nGenLQ0->Fill(anJetMult,weightEn);
  if(nGenLQ==1) plots->hnJets_nGenLQ1->Fill(anJetMult,weightEn);
  if(nGenLQ==2) plots->hnJets_nGenLQ2->Fill(anJetMult,weightEn);
  valInBoundaries(anJets,hnJets_IniRangeX,hnJets_EndRangeX);
  plots->hnJets->Fill(anJets,weightEn);
  valInBoundaries(anBJets,hnBJets_IniRangeX,hnBJets_EndRangeX);
  plots->hnBJets->Fill(anBJets,weightEn); 
  //met
  MissingET* met = (MissingET*) branchMissingET->At(0);
  float metEvt = met->MET; valInBoundaries(metEvt,hMet_IniRangeX,hMet_EndRangeX);
  plots->hMet->Fill(metEvt,weightEn);
  //Select events
  plots->hCutFlow->Fill(0.,weightEn);
  if(nGenLQ==0) plots->hCutFlow_nGenLQ0->Fill(0.,weightEn);
  if(nGenLQ==1) plots->hCutFlow_nGenLQ1->Fill(0.,weightEn);
  if(nGenLQ==2) plots->hCutFlow_nGenLQ2->Fill(0.,weightEn);
  if(anEles==2 && aele0_charge*aele1_charge==-1){
   plots->hCutFlow->Fill(1.,weightEn);
   if(nGenLQ==0) plots->hCutFlow_nGenLQ0->Fill(1.,weightEn);
   if(nGenLQ==1) plots->hCutFlow_nGenLQ1->Fill(1.,weightEn);
   if(nGenLQ==2) plots->hCutFlow_nGenLQ2->Fill(1.,weightEn);
   //mass
   float mass = (aele0_momentum+aele1_momentum).M(); valInBoundaries(mass,hMass_IniRangeX,hMass_EndRangeX);
   if(mass>120){
    plots->hCutFlow->Fill(2.,weightEn);
    if(nGenLQ==0) plots->hCutFlow_nGenLQ0->Fill(2.,weightEn);
    if(nGenLQ==1) plots->hCutFlow_nGenLQ1->Fill(2.,weightEn);
    if(nGenLQ==2) plots->hCutFlow_nGenLQ2->Fill(2.,weightEn);
    if(met->MET<50){
     plots->hCutFlow->Fill(3.,weightEn);
     if(nGenLQ==0) plots->hCutFlow_nGenLQ0->Fill(3.,weightEn);
     if(nGenLQ==1) plots->hCutFlow_nGenLQ1->Fill(3.,weightEn);
     if(nGenLQ==2) plots->hCutFlow_nGenLQ2->Fill(3.,weightEn);
     if(anBJets==0){
      plots->hCutFlow->Fill(4.,weightEn); 
      if(nGenLQ==0) plots->hCutFlow_nGenLQ0->Fill(4.,weightEn);
      if(nGenLQ==1) plots->hCutFlow_nGenLQ1->Fill(4.,weightEn);
      if(nGenLQ==2) plots->hCutFlow_nGenLQ2->Fill(4.,weightEn);
      //mass
      plots->hMass->Fill(mass,weightLumi);
      if(nGenLQ==0) plots->hMass_nGenLQ0->Fill(mass,weightLumi);
      if(nGenLQ==1) plots->hMass_nGenLQ1->Fill(mass,weightLumi);
      if(nGenLQ==2) plots->hMass_nGenLQ2->Fill(mass,weightLumi);
      //chi
      float chi = exp(fabs(aele0_eta-aele1_eta)); valInBoundaries(chi,hChi_IniRangeX,hChi_EndRangeX);
      plots->hChi->Fill(chi,weightLumi);
      if(nGenLQ==0) plots->hChi_nGenLQ0->Fill(chi,weightLumi);
      if(nGenLQ==1) plots->hChi_nGenLQ1->Fill(chi,weightLumi);
      if(nGenLQ==2) plots->hChi_nGenLQ2->Fill(chi,weightLumi);
      //st
      float st = 0;
      st = aele0_pT+aele1_pT;
      //For different categories based on # of jets
      if(anJets==0){
       plots->hCutFlow->Fill(6.,weightEn);
       if(nGenLQ==0) plots->hCutFlow_nGenLQ0->Fill(6.,weightEn);
       if(nGenLQ==1) plots->hCutFlow_nGenLQ1->Fill(6.,weightEn);
       if(nGenLQ==2) plots->hCutFlow_nGenLQ2->Fill(6.,weightEn);
       plots->hMass0->Fill(mass,weightLumi);
       if(nGenLQ==0) plots->hMass0_nGenLQ0->Fill(mass,weightLumi);
       if(nGenLQ==1) plots->hMass0_nGenLQ1->Fill(mass,weightLumi);
       if(nGenLQ==2) plots->hMass0_nGenLQ2->Fill(mass,weightLumi);
       plots->hChi0->Fill(chi,weightLumi);
       if(nGenLQ==0) plots->hChi0_nGenLQ0->Fill(chi,weightLumi);
       if(nGenLQ==1) plots->hChi0_nGenLQ1->Fill(chi,weightLumi);
       if(nGenLQ==2) plots->hChi0_nGenLQ2->Fill(chi,weightLumi);
       st = st; valInBoundaries(st,hSt_IniRangeX,hSt_EndRangeX); 
       plots->hSt0->Fill(st,weightLumi); 
       if(nGenLQ==0) plots->hSt0_nGenLQ0->Fill(st,weightLumi);
       if(nGenLQ==1) plots->hSt0_nGenLQ1->Fill(st,weightLumi);
       if(nGenLQ==2) plots->hSt0_nGenLQ2->Fill(st,weightLumi);
       plots->hSt0_asymBins->Fill(st,weightLumi); 
       if(nGenLQ==0) plots->hSt0_asymBins_nGenLQ0->Fill(st,weightLumi);
       if(nGenLQ==1) plots->hSt0_asymBins_nGenLQ1->Fill(st,weightLumi);
       if(nGenLQ==2) plots->hSt0_asymBins_nGenLQ2->Fill(st,weightLumi);
       plots->hChiSt0->Fill(st,chi,weightLumi);
       if(nGenLQ==0) plots->hChiSt0_nGenLQ0->Fill(st,chi,weightLumi);
       if(nGenLQ==1) plots->hChiSt0_nGenLQ1->Fill(st,chi,weightLumi);
       if(nGenLQ==2) plots->hChiSt0_nGenLQ2->Fill(st,chi,weightLumi);
            if(chi<chi0bin)                {
					     plots->hSt_jet0_chi0->Fill(st,weightLumi); 
       					     if(nGenLQ==0) plots->hSt_jet0_chi0_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet0_chi0_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet0_chi0_nGenLQ2->Fill(st,weightLumi);
				 	     plots->hSt_jet0_chi0_asymBins->Fill(st,weightLumi);
       					     if(nGenLQ==0) plots->hSt_jet0_chi0_asymBins_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet0_chi0_asymBins_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet0_chi0_asymBins_nGenLQ2->Fill(st,weightLumi);
                                           }
       else if(chi0bin<=chi && chi<chi1bin){
					     plots->hSt_jet0_chi1->Fill(st,weightLumi); 
       					     if(nGenLQ==0) plots->hSt_jet0_chi1_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet0_chi1_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet0_chi1_nGenLQ2->Fill(st,weightLumi);
				 	     plots->hSt_jet0_chi1_asymBins->Fill(st,weightLumi);
       					     if(nGenLQ==0) plots->hSt_jet0_chi1_asymBins_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet0_chi1_asymBins_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet0_chi1_asymBins_nGenLQ2->Fill(st,weightLumi);
 					   }
       else                                {
					     plots->hSt_jet0_chi2->Fill(st,weightLumi); 
       					     if(nGenLQ==0) plots->hSt_jet0_chi2_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet0_chi2_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet0_chi2_nGenLQ2->Fill(st,weightLumi);
				 	     plots->hSt_jet0_chi2_asymBins->Fill(st,weightLumi);
       					     if(nGenLQ==0) plots->hSt_jet0_chi2_asymBins_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet0_chi2_asymBins_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet0_chi2_asymBins_nGenLQ2->Fill(st,weightLumi);
					   } 
      }
      if(anJets==1){
       plots->hCutFlow->Fill(7.,weightEn);
       if(nGenLQ==0) plots->hCutFlow_nGenLQ0->Fill(7.,weightEn);
       if(nGenLQ==1) plots->hCutFlow_nGenLQ1->Fill(7.,weightEn);
       if(nGenLQ==2) plots->hCutFlow_nGenLQ2->Fill(7.,weightEn);
       plots->hMass1->Fill(mass,weightLumi);
       if(nGenLQ==0) plots->hMass1_nGenLQ0->Fill(mass,weightLumi);
       if(nGenLQ==1) plots->hMass1_nGenLQ1->Fill(mass,weightLumi);
       if(nGenLQ==2) plots->hMass1_nGenLQ2->Fill(mass,weightLumi);
       plots->hChi1->Fill(chi,weightLumi);
       if(nGenLQ==0) plots->hChi1_nGenLQ0->Fill(chi,weightLumi);
       if(nGenLQ==1) plots->hChi1_nGenLQ1->Fill(chi,weightLumi);
       if(nGenLQ==2) plots->hChi1_nGenLQ2->Fill(chi,weightLumi);
       st = st+ajet0_pT; valInBoundaries(st,hSt_IniRangeX,hSt_EndRangeX); 
       plots->hSt1->Fill(st,weightLumi); 
       if(nGenLQ==0) plots->hSt1_nGenLQ0->Fill(st,weightLumi);
       if(nGenLQ==1) plots->hSt1_nGenLQ1->Fill(st,weightLumi);
       if(nGenLQ==2) plots->hSt1_nGenLQ2->Fill(st,weightLumi);
       plots->hSt1_asymBins->Fill(st,weightLumi); 
       if(nGenLQ==0) plots->hSt1_asymBins_nGenLQ0->Fill(st,weightLumi);
       if(nGenLQ==1) plots->hSt1_asymBins_nGenLQ1->Fill(st,weightLumi);
       if(nGenLQ==2) plots->hSt1_asymBins_nGenLQ2->Fill(st,weightLumi);
       plots->hChiSt1->Fill(st,chi,weightLumi);
       if(nGenLQ==0) plots->hChiSt1_nGenLQ0->Fill(st,chi,weightLumi);
       if(nGenLQ==1) plots->hChiSt1_nGenLQ1->Fill(st,chi,weightLumi);
       if(nGenLQ==2) plots->hChiSt1_nGenLQ2->Fill(st,chi,weightLumi);
            if(chi<chi0bin)                {
					     plots->hSt_jet1_chi0->Fill(st,weightLumi); 
       					     if(nGenLQ==0) plots->hSt_jet1_chi0_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet1_chi0_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet1_chi0_nGenLQ2->Fill(st,weightLumi);
				 	     plots->hSt_jet1_chi0_asymBins->Fill(st,weightLumi);
       					     if(nGenLQ==0) plots->hSt_jet1_chi0_asymBins_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet1_chi0_asymBins_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet1_chi0_asymBins_nGenLQ2->Fill(st,weightLumi);
                                           }
       else if(chi0bin<=chi && chi<chi1bin){
					     plots->hSt_jet1_chi1->Fill(st,weightLumi); 
       					     if(nGenLQ==0) plots->hSt_jet1_chi1_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet1_chi1_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet1_chi1_nGenLQ2->Fill(st,weightLumi);
				 	     plots->hSt_jet1_chi1_asymBins->Fill(st,weightLumi);
       					     if(nGenLQ==0) plots->hSt_jet1_chi1_asymBins_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet1_chi1_asymBins_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet1_chi1_asymBins_nGenLQ2->Fill(st,weightLumi);
 					   }
       else                                {
					     plots->hSt_jet1_chi2->Fill(st,weightLumi); 
       					     if(nGenLQ==0) plots->hSt_jet1_chi2_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet1_chi2_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet1_chi2_nGenLQ2->Fill(st,weightLumi);
				 	     plots->hSt_jet1_chi2_asymBins->Fill(st,weightLumi);
       					     if(nGenLQ==0) plots->hSt_jet1_chi2_asymBins_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet1_chi2_asymBins_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet1_chi2_asymBins_nGenLQ2->Fill(st,weightLumi);
					   } 
      }
      if(anJets==2){
       plots->hCutFlow->Fill(8.,weightEn);
       if(nGenLQ==0) plots->hCutFlow_nGenLQ0->Fill(8.,weightEn);
       if(nGenLQ==1) plots->hCutFlow_nGenLQ1->Fill(8.,weightEn);
       if(nGenLQ==2) plots->hCutFlow_nGenLQ2->Fill(8.,weightEn);
       plots->hMass2->Fill(mass,weightLumi);
       if(nGenLQ==0) plots->hMass2_nGenLQ0->Fill(mass,weightLumi);
       if(nGenLQ==1) plots->hMass2_nGenLQ1->Fill(mass,weightLumi);
       if(nGenLQ==2) plots->hMass2_nGenLQ2->Fill(mass,weightLumi);
       plots->hChi2->Fill(chi,weightLumi);
       if(nGenLQ==0) plots->hChi2_nGenLQ0->Fill(chi,weightLumi);
       if(nGenLQ==1) plots->hChi2_nGenLQ1->Fill(chi,weightLumi);
       if(nGenLQ==2) plots->hChi2_nGenLQ2->Fill(chi,weightLumi);
       st = st+ajet0_pT+ajet1_pT; valInBoundaries(st,hSt_IniRangeX,hSt_EndRangeX); 
       plots->hSt2->Fill(st,weightLumi); 
       if(nGenLQ==0) plots->hSt2_nGenLQ0->Fill(st,weightLumi);
       if(nGenLQ==1) plots->hSt2_nGenLQ1->Fill(st,weightLumi);
       if(nGenLQ==2) plots->hSt2_nGenLQ2->Fill(st,weightLumi);
       plots->hSt2_asymBins->Fill(st,weightLumi); 
       if(nGenLQ==0) plots->hSt2_asymBins_nGenLQ0->Fill(st,weightLumi);
       if(nGenLQ==1) plots->hSt2_asymBins_nGenLQ1->Fill(st,weightLumi);
       if(nGenLQ==2) plots->hSt2_asymBins_nGenLQ2->Fill(st,weightLumi);
       plots->hChiSt2->Fill(st,chi,weightLumi);
       if(nGenLQ==0) plots->hChiSt2_nGenLQ0->Fill(st,chi,weightLumi);
       if(nGenLQ==1) plots->hChiSt2_nGenLQ1->Fill(st,chi,weightLumi);
       if(nGenLQ==2) plots->hChiSt2_nGenLQ2->Fill(st,chi,weightLumi);
            if(chi<chi0bin)                {
					     plots->hSt_jet2_chi0->Fill(st,weightLumi); 
       					     if(nGenLQ==0) plots->hSt_jet2_chi0_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet2_chi0_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet2_chi0_nGenLQ2->Fill(st,weightLumi);
				 	     plots->hSt_jet2_chi0_asymBins->Fill(st,weightLumi);
       					     if(nGenLQ==0) plots->hSt_jet2_chi0_asymBins_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet2_chi0_asymBins_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet2_chi0_asymBins_nGenLQ2->Fill(st,weightLumi);
                                           }
       else if(chi0bin<=chi && chi<chi1bin){
					     plots->hSt_jet2_chi1->Fill(st,weightLumi); 
       					     if(nGenLQ==0) plots->hSt_jet2_chi1_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet2_chi1_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet2_chi1_nGenLQ2->Fill(st,weightLumi);
				 	     plots->hSt_jet2_chi1_asymBins->Fill(st,weightLumi);
       					     if(nGenLQ==0) plots->hSt_jet2_chi1_asymBins_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet2_chi1_asymBins_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet2_chi1_asymBins_nGenLQ2->Fill(st,weightLumi);
 					   }
       else                                {
					     plots->hSt_jet2_chi2->Fill(st,weightLumi); 
       					     if(nGenLQ==0) plots->hSt_jet2_chi2_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet2_chi2_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet2_chi2_nGenLQ2->Fill(st,weightLumi);
				 	     plots->hSt_jet2_chi2_asymBins->Fill(st,weightLumi);
       					     if(nGenLQ==0) plots->hSt_jet2_chi2_asymBins_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet2_chi2_asymBins_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet2_chi2_asymBins_nGenLQ2->Fill(st,weightLumi);
					   } 
      }
      if(anJets>=3){
       plots->hCutFlow->Fill(9.,weightEn);
       if(nGenLQ==0) plots->hCutFlow_nGenLQ0->Fill(9.,weightEn);
       if(nGenLQ==1) plots->hCutFlow_nGenLQ1->Fill(9.,weightEn);
       if(nGenLQ==2) plots->hCutFlow_nGenLQ2->Fill(9.,weightEn);
       plots->hMass3->Fill(mass,weightLumi);
       if(nGenLQ==0) plots->hMass3_nGenLQ0->Fill(mass,weightLumi);
       if(nGenLQ==1) plots->hMass3_nGenLQ1->Fill(mass,weightLumi);
       if(nGenLQ==2) plots->hMass3_nGenLQ2->Fill(mass,weightLumi);
       plots->hChi3->Fill(chi,weightLumi);
       if(nGenLQ==0) plots->hChi3_nGenLQ0->Fill(chi,weightLumi);
       if(nGenLQ==1) plots->hChi3_nGenLQ1->Fill(chi,weightLumi);
       if(nGenLQ==2) plots->hChi3_nGenLQ2->Fill(chi,weightLumi);
       st = st+ajet0_pT+ajet1_pT+ajet2_pT; valInBoundaries(st,hSt_IniRangeX,hSt_EndRangeX); 
       plots->hSt3->Fill(st,weightLumi); 
       if(nGenLQ==0) plots->hSt3_nGenLQ0->Fill(st,weightLumi);
       if(nGenLQ==1) plots->hSt3_nGenLQ1->Fill(st,weightLumi);
       if(nGenLQ==2) plots->hSt3_nGenLQ2->Fill(st,weightLumi);
       plots->hSt3_asymBins->Fill(st,weightLumi); 
       if(nGenLQ==0) plots->hSt3_asymBins_nGenLQ0->Fill(st,weightLumi);
       if(nGenLQ==1) plots->hSt3_asymBins_nGenLQ1->Fill(st,weightLumi);
       if(nGenLQ==2) plots->hSt3_asymBins_nGenLQ2->Fill(st,weightLumi);
       plots->hChiSt3->Fill(st,chi,weightLumi);
       if(nGenLQ==0) plots->hChiSt3_nGenLQ0->Fill(st,chi,weightLumi);
       if(nGenLQ==1) plots->hChiSt3_nGenLQ1->Fill(st,chi,weightLumi);
       if(nGenLQ==2) plots->hChiSt3_nGenLQ2->Fill(st,chi,weightLumi);
            if(chi<chi0bin)                {
					     plots->hSt_jet3_chi0->Fill(st,weightLumi); 
       					     if(nGenLQ==0) plots->hSt_jet3_chi0_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet3_chi0_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet3_chi0_nGenLQ2->Fill(st,weightLumi);
				 	     plots->hSt_jet3_chi0_asymBins->Fill(st,weightLumi);
       					     if(nGenLQ==0) plots->hSt_jet3_chi0_asymBins_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet3_chi0_asymBins_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet3_chi0_asymBins_nGenLQ2->Fill(st,weightLumi);
                                           }
       else if(chi0bin<=chi && chi<chi1bin){
					     plots->hSt_jet3_chi1->Fill(st,weightLumi); 
       					     if(nGenLQ==0) plots->hSt_jet3_chi1_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet3_chi1_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet3_chi1_nGenLQ2->Fill(st,weightLumi);
				 	     plots->hSt_jet3_chi1_asymBins->Fill(st,weightLumi);
       					     if(nGenLQ==0) plots->hSt_jet3_chi1_asymBins_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet3_chi1_asymBins_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet3_chi1_asymBins_nGenLQ2->Fill(st,weightLumi);
 					   }
       else                                {
					     plots->hSt_jet3_chi2->Fill(st,weightLumi); 
       					     if(nGenLQ==0) plots->hSt_jet3_chi2_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet3_chi2_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet3_chi2_nGenLQ2->Fill(st,weightLumi);
				 	     plots->hSt_jet3_chi2_asymBins->Fill(st,weightLumi);
       					     if(nGenLQ==0) plots->hSt_jet3_chi2_asymBins_nGenLQ0->Fill(st,weightLumi);
					     if(nGenLQ==1) plots->hSt_jet3_chi2_asymBins_nGenLQ1->Fill(st,weightLumi);
					     if(nGenLQ==2) plots->hSt_jet3_chi2_asymBins_nGenLQ2->Fill(st,weightLumi);
					   } 
      }
      plots->hSt->Fill(st,weightLumi);
      if(nGenLQ==0) plots->hSt_nGenLQ0->Fill(st,weightLumi);
      if(nGenLQ==1) plots->hSt_nGenLQ1->Fill(st,weightLumi);
      if(nGenLQ==2) plots->hSt_nGenLQ2->Fill(st,weightLumi);
      plots->hSt_asymBins->Fill(st,weightLumi);
      if(nGenLQ==0) plots->hSt_asymBins_nGenLQ0->Fill(st,weightLumi);
      if(nGenLQ==1) plots->hSt_asymBins_nGenLQ1->Fill(st,weightLumi);
      if(nGenLQ==2) plots->hSt_asymBins_nGenLQ2->Fill(st,weightLumi);
      plots->hChiSt->Fill(st,chi,weightLumi);
      if(nGenLQ==0) plots->hChiSt_nGenLQ0->Fill(st,chi,weightLumi);
      if(nGenLQ==1) plots->hChiSt_nGenLQ1->Fill(st,chi,weightLumi);
      if(nGenLQ==2) plots->hChiSt_nGenLQ2->Fill(st,chi,weightLumi);
     }
    }
   }
  } 
 }
}

void valInBoundaries(float& val,float iniRange,float endRange){
 if(val<=iniRange) val = iniRange*1.005;
 if(val>=endRange) val = endRange*0.995;
}

void BookHistograms(ExRootResult *result, MyPlots *plots){
 //comment
 TPaveText *comment; 
 comment = result->AddComment(0.64, 0.64, 0.64, 0.64);
 comment->AddText("");
 //AddHist1D("filename","title","x-axis","y-axis",num bint int, low x float, high x float)
 //event quantities
 plots->hnEvtXSecLumiWeight = result->AddHist1D("nEvtXSecLumiWeight","","nEvtXSecLumiWeight","nEvents",hnEvtXSecLumiWeight_binsX,hnEvtXSecLumiWeight_IniRangeX,hnEvtXSecLumiWeight_EndRangeX);
 result->Attach(plots->hnEvtXSecLumiWeight,comment);
 //genLQ
 plots->hnGenLQ = result->AddHist1D("nGenLQ","","nGenLQ","nEvents",hnGenLQ_binsX,hnGenLQ_IniRangeX,hnGenLQ_EndRangeX);
 result->Attach(plots->hnGenLQ,comment);
 //electrons
 plots->hnEles = result->AddHist1D("nEles","","nEles","nEvents",hnEles_binsX,hnEles_IniRangeX,hnEles_EndRangeX);
 result->Attach(plots->hnEles,comment);
 plots->hEle0_pT = result->AddHist1D("Ele0_pT","","Ele0_pT","nEvents",hEle_pT_binsX,hEle_pT_IniRangeX,hEle_pT_EndRangeX);
 plots->hEle0_pT_nGenLQ0 = result->AddHist1D("Ele0_pT_nGenLQ0","","Ele0_pT_nGenLQ0","nEvents",hEle_pT_binsX,hEle_pT_IniRangeX,hEle_pT_EndRangeX);
 plots->hEle0_pT_nGenLQ1 = result->AddHist1D("Ele0_pT_nGenLQ1","","Ele0_pT_nGenLQ1","nEvents",hEle_pT_binsX,hEle_pT_IniRangeX,hEle_pT_EndRangeX);
 plots->hEle0_pT_nGenLQ2 = result->AddHist1D("Ele0_pT_nGenLQ2","","Ele0_pT_nGenLQ2","nEvents",hEle_pT_binsX,hEle_pT_IniRangeX,hEle_pT_EndRangeX);
 result->Attach(plots->hEle0_pT,comment);
 result->Attach(plots->hEle0_pT_nGenLQ0,comment);
 result->Attach(plots->hEle0_pT_nGenLQ1,comment);
 result->Attach(plots->hEle0_pT_nGenLQ2,comment);
 plots->hEle0_eta = result->AddHist1D("Ele0_eta","","Ele0_eta","nEvents",hEle_eta_binsX,hEle_eta_IniRangeX,hEle_eta_EndRangeX);
 plots->hEle0_eta_nGenLQ0 = result->AddHist1D("Ele0_eta_nGenLQ0","","Ele0_eta_nGenLQ0","nEvents",hEle_eta_binsX,hEle_eta_IniRangeX,hEle_eta_EndRangeX);
 plots->hEle0_eta_nGenLQ1 = result->AddHist1D("Ele0_eta_nGenLQ1","","Ele0_eta_nGenLQ1","nEvents",hEle_eta_binsX,hEle_eta_IniRangeX,hEle_eta_EndRangeX);
 plots->hEle0_eta_nGenLQ2 = result->AddHist1D("Ele0_eta_nGenLQ2","","Ele0_eta_nGenLQ2","nEvents",hEle_eta_binsX,hEle_eta_IniRangeX,hEle_eta_EndRangeX);
 result->Attach(plots->hEle0_eta,comment);
 result->Attach(plots->hEle0_eta_nGenLQ0,comment);
 result->Attach(plots->hEle0_eta_nGenLQ1,comment);
 result->Attach(plots->hEle0_eta_nGenLQ2,comment);
 plots->hEle1_pT = result->AddHist1D("Ele1_pT","","Ele1_pT","nEvents",hEle_pT_binsX,hEle_pT_IniRangeX,hEle_pT_EndRangeX);
 plots->hEle1_pT_nGenLQ0 = result->AddHist1D("Ele1_pT_nGenLQ0","","Ele1_pT_nGenLQ0","nEvents",hEle_pT_binsX,hEle_pT_IniRangeX,hEle_pT_EndRangeX);
 plots->hEle1_pT_nGenLQ1 = result->AddHist1D("Ele1_pT_nGenLQ1","","Ele1_pT_nGenLQ1","nEvents",hEle_pT_binsX,hEle_pT_IniRangeX,hEle_pT_EndRangeX);
 plots->hEle1_pT_nGenLQ2 = result->AddHist1D("Ele1_pT_nGenLQ2","","Ele1_pT_nGenLQ2","nEvents",hEle_pT_binsX,hEle_pT_IniRangeX,hEle_pT_EndRangeX);
 result->Attach(plots->hEle1_pT,comment);
 result->Attach(plots->hEle1_pT_nGenLQ0,comment);
 result->Attach(plots->hEle1_pT_nGenLQ1,comment);
 result->Attach(plots->hEle1_pT_nGenLQ2,comment);
 plots->hEle1_eta = result->AddHist1D("Ele1_eta","","Ele1_eta","nEvents",hEle_eta_binsX,hEle_eta_IniRangeX,hEle_eta_EndRangeX);
 plots->hEle1_eta_nGenLQ0 = result->AddHist1D("Ele1_eta_nGenLQ0","","Ele1_eta_nGenLQ0","nEvents",hEle_eta_binsX,hEle_eta_IniRangeX,hEle_eta_EndRangeX);
 plots->hEle1_eta_nGenLQ1 = result->AddHist1D("Ele1_eta_nGenLQ1","","Ele1_eta_nGenLQ1","nEvents",hEle_eta_binsX,hEle_eta_IniRangeX,hEle_eta_EndRangeX);
 plots->hEle1_eta_nGenLQ2 = result->AddHist1D("Ele1_eta_nGenLQ2","","Ele1_eta_nGenLQ2","nEvents",hEle_eta_binsX,hEle_eta_IniRangeX,hEle_eta_EndRangeX);
 result->Attach(plots->hEle1_eta,comment);
 result->Attach(plots->hEle1_eta_nGenLQ0,comment);
 result->Attach(plots->hEle1_eta_nGenLQ1,comment);
 result->Attach(plots->hEle1_eta_nGenLQ2,comment);
 //jets
 plots->hnJets = result->AddHist1D("nJets","","nJets","nEvents",hnJets_binsX,hnJets_IniRangeX,hnJets_EndRangeX);
 result->Attach(plots->hnJets,comment);
 plots->hnJets_nGenLQ0 = result->AddHist1D("nJets_nGenLQ0","","nJets_nGenLQ0","nEvents",hnJets_nGenLQ_binsX,hnJets_nGenLQ_IniRangeX,hnJets_nGenLQ_EndRangeX);
 result->Attach(plots->hnJets_nGenLQ0,comment);
 plots->hnJets_nGenLQ1 = result->AddHist1D("nJets_nGenLQ1","","nJets_nGenLQ1","nEvents",hnJets_nGenLQ_binsX,hnJets_nGenLQ_IniRangeX,hnJets_nGenLQ_EndRangeX);
 result->Attach(plots->hnJets_nGenLQ1,comment);
 plots->hnJets_nGenLQ2 = result->AddHist1D("nJets_nGenLQ2","","nJets_nGenLQ2","nEvents",hnJets_nGenLQ_binsX,hnJets_nGenLQ_IniRangeX,hnJets_nGenLQ_EndRangeX);
 result->Attach(plots->hnJets_nGenLQ2,comment);
 plots->hnBJets = result->AddHist1D("nBJets","","nBJets","nEvents",hnBJets_binsX,hnBJets_IniRangeX,hnBJets_EndRangeX);
 result->Attach(plots->hnBJets,comment);
 plots->hJet0_pT = result->AddHist1D("Jet0_pT","","Jet0_pT","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 plots->hJet0_pT_nGenLQ0 = result->AddHist1D("Jet0_pT_nGenLQ0","","Jet0_pT_nGenLQ0","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 plots->hJet0_pT_nGenLQ1 = result->AddHist1D("Jet0_pT_nGenLQ1","","Jet0_pT_nGenLQ1","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 plots->hJet0_pT_nGenLQ2 = result->AddHist1D("Jet0_pT_nGenLQ2","","Jet0_pT_nGenLQ2","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 result->Attach(plots->hJet0_pT,comment);
 result->Attach(plots->hJet0_pT_nGenLQ0,comment);
 result->Attach(plots->hJet0_pT_nGenLQ1,comment);
 result->Attach(plots->hJet0_pT_nGenLQ2,comment);
 plots->hJet0_eta = result->AddHist1D("Jet0_eta","","Jet0_eta","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 plots->hJet0_eta_nGenLQ0 = result->AddHist1D("Jet0_eta_nGenLQ0","","Jet0_eta_nGenLQ0","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 plots->hJet0_eta_nGenLQ1 = result->AddHist1D("Jet0_eta_nGenLQ1","","Jet0_eta_nGenLQ1","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 plots->hJet0_eta_nGenLQ2 = result->AddHist1D("Jet0_eta_nGenLQ2","","Jet0_eta_nGenLQ2","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 result->Attach(plots->hJet0_eta,comment);
 result->Attach(plots->hJet0_eta_nGenLQ0,comment);
 result->Attach(plots->hJet0_eta_nGenLQ1,comment);
 result->Attach(plots->hJet0_eta_nGenLQ2,comment);
 plots->hJet1_pT = result->AddHist1D("Jet1_pT","","Jet1_pT","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 plots->hJet1_pT_nGenLQ0 = result->AddHist1D("Jet1_pT_nGenLQ0","","Jet1_pT_nGenLQ0","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 plots->hJet1_pT_nGenLQ1 = result->AddHist1D("Jet1_pT_nGenLQ1","","Jet1_pT_nGenLQ1","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 plots->hJet1_pT_nGenLQ2 = result->AddHist1D("Jet1_pT_nGenLQ2","","Jet1_pT_nGenLQ2","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 result->Attach(plots->hJet1_pT,comment);
 result->Attach(plots->hJet1_pT_nGenLQ0,comment);
 result->Attach(plots->hJet1_pT_nGenLQ1,comment);
 result->Attach(plots->hJet1_pT_nGenLQ2,comment);
 plots->hJet1_eta = result->AddHist1D("Jet1_eta","","Jet1_eta","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 plots->hJet1_eta_nGenLQ0 = result->AddHist1D("Jet1_eta_nGenLQ0","","Jet1_eta_nGenLQ0","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 plots->hJet1_eta_nGenLQ1 = result->AddHist1D("Jet1_eta_nGenLQ1","","Jet1_eta_nGenLQ1","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 plots->hJet1_eta_nGenLQ2 = result->AddHist1D("Jet1_eta_nGenLQ2","","Jet1_eta_nGenLQ2","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 result->Attach(plots->hJet1_eta,comment);
 result->Attach(plots->hJet1_eta_nGenLQ0,comment);
 result->Attach(plots->hJet1_eta_nGenLQ1,comment);
 result->Attach(plots->hJet1_eta_nGenLQ2,comment);
 plots->hJet2_pT = result->AddHist1D("Jet2_pT","","Jet2_pT","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 plots->hJet2_pT_nGenLQ0 = result->AddHist1D("Jet2_pT_nGenLQ0","","Jet2_pT_nGenLQ0","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 plots->hJet2_pT_nGenLQ1 = result->AddHist1D("Jet2_pT_nGenLQ1","","Jet2_pT_nGenLQ1","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 plots->hJet2_pT_nGenLQ2 = result->AddHist1D("Jet2_pT_nGenLQ2","","Jet2_pT_nGenLQ2","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 result->Attach(plots->hJet2_pT,comment);
 result->Attach(plots->hJet2_pT_nGenLQ0,comment);
 result->Attach(plots->hJet2_pT_nGenLQ1,comment);
 result->Attach(plots->hJet2_pT_nGenLQ2,comment);
 plots->hJet2_eta = result->AddHist1D("Jet2_eta","","Jet2_eta","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 plots->hJet2_eta_nGenLQ0 = result->AddHist1D("Jet2_eta_nGenLQ0","","Jet2_eta_nGenLQ0","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 plots->hJet2_eta_nGenLQ1 = result->AddHist1D("Jet2_eta_nGenLQ1","","Jet2_eta_nGenLQ1","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 plots->hJet2_eta_nGenLQ2 = result->AddHist1D("Jet2_eta_nGenLQ2","","Jet2_eta_nGenLQ2","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 result->Attach(plots->hJet2_eta,comment);
 result->Attach(plots->hJet2_eta_nGenLQ0,comment);
 result->Attach(plots->hJet2_eta_nGenLQ1,comment);
 result->Attach(plots->hJet2_eta_nGenLQ2,comment);
 plots->hJet3_pT = result->AddHist1D("Jet3_pT","","Jet3_pT","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 plots->hJet3_pT_nGenLQ0 = result->AddHist1D("Jet3_pT_nGenLQ0","","Jet3_pT_nGenLQ0","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 plots->hJet3_pT_nGenLQ1 = result->AddHist1D("Jet3_pT_nGenLQ1","","Jet3_pT_nGenLQ1","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 plots->hJet3_pT_nGenLQ2 = result->AddHist1D("Jet3_pT_nGenLQ2","","Jet3_pT_nGenLQ2","nEvents",hJet_pT_binsX,hJet_pT_IniRangeX,hJet_pT_EndRangeX);
 result->Attach(plots->hJet3_pT,comment);
 result->Attach(plots->hJet3_pT_nGenLQ0,comment);
 result->Attach(plots->hJet3_pT_nGenLQ1,comment);
 result->Attach(plots->hJet3_pT_nGenLQ2,comment);
 plots->hJet3_eta = result->AddHist1D("Jet3_eta","","Jet3_eta","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 plots->hJet3_eta_nGenLQ0 = result->AddHist1D("Jet3_eta_nGenLQ0","","Jet3_eta_nGenLQ0","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 plots->hJet3_eta_nGenLQ1 = result->AddHist1D("Jet3_eta_nGenLQ1","","Jet3_eta_nGenLQ1","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 plots->hJet3_eta_nGenLQ2 = result->AddHist1D("Jet3_eta_nGenLQ2","","Jet3_eta_nGenLQ2","nEvents",hJet_eta_binsX,hJet_eta_IniRangeX,hJet_eta_EndRangeX);
 result->Attach(plots->hJet3_eta,comment);
 result->Attach(plots->hJet3_eta_nGenLQ0,comment);
 result->Attach(plots->hJet3_eta_nGenLQ1,comment);
 result->Attach(plots->hJet3_eta_nGenLQ2,comment);
 //met
 plots->hMet = result->AddHist1D("Met","","Met","nEvents",hMet_binsX,hMet_IniRangeX,hMet_EndRangeX);
 result->Attach(plots->hMet,comment);
 //for selected events
 plots->hCutFlow = result->AddHist1D("CutFlow","","CutFlow","nEvents normalized to 1",hCutFlow_binsX,hCutFlow_IniRangeX,hCutFlow_EndRangeX);
 plots->hCutFlow->GetXaxis()->SetBinLabel(1,"no selection");
 plots->hCutFlow->GetXaxis()->SetBinLabel(2,"# electrons = 2");
 plots->hCutFlow->GetXaxis()->SetBinLabel(3,"M(e1,e2) > 120 GeV");
 plots->hCutFlow->GetXaxis()->SetBinLabel(4,"MET < 50 GeV");
 plots->hCutFlow->GetXaxis()->SetBinLabel(5,"# b-jets = 0");
 plots->hCutFlow->GetXaxis()->SetBinLabel(6,"");
 plots->hCutFlow->GetXaxis()->SetBinLabel(7,"# jets == 0");
 plots->hCutFlow->GetXaxis()->SetBinLabel(8,"# jets == 1");
 plots->hCutFlow->GetXaxis()->SetBinLabel(9,"# jets == 2");
 plots->hCutFlow->GetXaxis()->SetBinLabel(10,"# jets >= 3");
 result->Attach(plots->hCutFlow,comment);
 plots->hCutFlow_nGenLQ0 = result->AddHist1D("CutFlow_nGenLQ0","","CutFlow_nGenLQ0","nEvents normalized to 1",hCutFlow_binsX,hCutFlow_IniRangeX,hCutFlow_EndRangeX);
 plots->hCutFlow_nGenLQ0->GetXaxis()->SetBinLabel(1,"no selection");
 plots->hCutFlow_nGenLQ0->GetXaxis()->SetBinLabel(2,"# electrons = 2");
 plots->hCutFlow_nGenLQ0->GetXaxis()->SetBinLabel(3,"M(e1,e2) > 120 GeV");
 plots->hCutFlow_nGenLQ0->GetXaxis()->SetBinLabel(4,"MET < 50 GeV");
 plots->hCutFlow_nGenLQ0->GetXaxis()->SetBinLabel(5,"# b-jets = 0");
 plots->hCutFlow_nGenLQ0->GetXaxis()->SetBinLabel(6,"");
 plots->hCutFlow_nGenLQ0->GetXaxis()->SetBinLabel(7,"# jets == 0");
 plots->hCutFlow_nGenLQ0->GetXaxis()->SetBinLabel(8,"# jets == 1");
 plots->hCutFlow_nGenLQ0->GetXaxis()->SetBinLabel(9,"# jets == 2");
 plots->hCutFlow_nGenLQ0->GetXaxis()->SetBinLabel(10,"# jets >= 3");
 result->Attach(plots->hCutFlow_nGenLQ0,comment);
 plots->hCutFlow_nGenLQ1 = result->AddHist1D("CutFlow_nGenLQ1","","CutFlow_nGenLQ1","nEvents normalized to 1",hCutFlow_binsX,hCutFlow_IniRangeX,hCutFlow_EndRangeX);
 plots->hCutFlow_nGenLQ1->GetXaxis()->SetBinLabel(1,"no selection");
 plots->hCutFlow_nGenLQ1->GetXaxis()->SetBinLabel(2,"# electrons = 2");
 plots->hCutFlow_nGenLQ1->GetXaxis()->SetBinLabel(3,"M(e1,e2) > 120 GeV");
 plots->hCutFlow_nGenLQ1->GetXaxis()->SetBinLabel(4,"MET < 50 GeV");
 plots->hCutFlow_nGenLQ1->GetXaxis()->SetBinLabel(5,"# b-jets = 0");
 plots->hCutFlow_nGenLQ1->GetXaxis()->SetBinLabel(6,"");
 plots->hCutFlow_nGenLQ1->GetXaxis()->SetBinLabel(7,"# jets == 0");
 plots->hCutFlow_nGenLQ1->GetXaxis()->SetBinLabel(8,"# jets == 1");
 plots->hCutFlow_nGenLQ1->GetXaxis()->SetBinLabel(9,"# jets == 2");
 plots->hCutFlow_nGenLQ1->GetXaxis()->SetBinLabel(10,"# jets >= 3");
 result->Attach(plots->hCutFlow_nGenLQ1,comment);
 plots->hCutFlow_nGenLQ2 = result->AddHist1D("CutFlow_nGenLQ2","","CutFlow_nGenLQ2","nEvents normalized to 1",hCutFlow_binsX,hCutFlow_IniRangeX,hCutFlow_EndRangeX);
 plots->hCutFlow_nGenLQ2->GetXaxis()->SetBinLabel(1,"no selection");
 plots->hCutFlow_nGenLQ2->GetXaxis()->SetBinLabel(2,"# electrons = 2");
 plots->hCutFlow_nGenLQ2->GetXaxis()->SetBinLabel(3,"M(e1,e2) > 120 GeV");
 plots->hCutFlow_nGenLQ2->GetXaxis()->SetBinLabel(4,"MET < 50 GeV");
 plots->hCutFlow_nGenLQ2->GetXaxis()->SetBinLabel(5,"# b-jets = 0");
 plots->hCutFlow_nGenLQ2->GetXaxis()->SetBinLabel(6,"");
 plots->hCutFlow_nGenLQ2->GetXaxis()->SetBinLabel(7,"# jets == 0");
 plots->hCutFlow_nGenLQ2->GetXaxis()->SetBinLabel(8,"# jets == 1");
 plots->hCutFlow_nGenLQ2->GetXaxis()->SetBinLabel(9,"# jets == 2");
 plots->hCutFlow_nGenLQ2->GetXaxis()->SetBinLabel(10,"# jets >= 3");
 result->Attach(plots->hCutFlow_nGenLQ2,comment);

 plots->hChi = result->AddHist1D("Chi","","Chi","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi,comment);
 plots->hChi0 = result->AddHist1D("Chi0","","Chi0","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi0,comment);
 plots->hChi1 = result->AddHist1D("Chi1","","Chi1","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi1,comment);
 plots->hChi2 = result->AddHist1D("Chi2","","Chi2","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi2,comment);
 plots->hChi3 = result->AddHist1D("Chi3","","Chi3","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi3,comment);
 
 plots->hChi_nGenLQ0 = result->AddHist1D("Chi_nGenLQ0","","Chi_nGenLQ0","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi_nGenLQ0,comment);
 plots->hChi0_nGenLQ0 = result->AddHist1D("Chi0_nGenLQ0","","Chi0_nGenLQ0","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi0_nGenLQ0,comment);
 plots->hChi1_nGenLQ0 = result->AddHist1D("Chi1_nGenLQ0","","Chi1_nGenLQ0","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi1_nGenLQ0,comment);
 plots->hChi2_nGenLQ0 = result->AddHist1D("Chi2_nGenLQ0","","Chi2_nGenLQ0","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi2,comment);
 plots->hChi3_nGenLQ0 = result->AddHist1D("Chi3_nGenLQ0","","Chi3_nGenLQ0","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi3_nGenLQ0,comment);
 plots->hChi_nGenLQ1 = result->AddHist1D("Chi_nGenLQ1","","Chi_nGenLQ1","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi_nGenLQ1,comment);
 plots->hChi0_nGenLQ1 = result->AddHist1D("Chi0_nGenLQ1","","Chi0_nGenLQ1","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi0_nGenLQ1,comment);
 plots->hChi1_nGenLQ1 = result->AddHist1D("Chi1_nGenLQ1","","Chi1_nGenLQ1","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi1_nGenLQ1,comment);
 plots->hChi2_nGenLQ1 = result->AddHist1D("Chi2_nGenLQ1","","Chi2_nGenLQ1","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi2,comment);
 plots->hChi3_nGenLQ1 = result->AddHist1D("Chi3_nGenLQ1","","Chi3_nGenLQ1","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi3_nGenLQ1,comment);
 plots->hChi_nGenLQ2 = result->AddHist1D("Chi_nGenLQ2","","Chi_nGenLQ2","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi_nGenLQ2,comment);
 plots->hChi0_nGenLQ2 = result->AddHist1D("Chi0_nGenLQ2","","Chi0_nGenLQ2","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi0_nGenLQ2,comment);
 plots->hChi1_nGenLQ2 = result->AddHist1D("Chi1_nGenLQ2","","Chi1_nGenLQ2","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi1_nGenLQ2,comment);
 plots->hChi2_nGenLQ2 = result->AddHist1D("Chi2_nGenLQ2","","Chi2_nGenLQ2","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi2,comment);
 plots->hChi3_nGenLQ2 = result->AddHist1D("Chi3_nGenLQ2","","Chi3_nGenLQ2","nEvents",hChi_binsX,hChi_IniRangeX,hChi_EndRangeX);
 result->Attach(plots->hChi3_nGenLQ2,comment);
 
 plots->hMass = result->AddHist1D("Mass","","Mass","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass,comment);
 plots->hMass0 = result->AddHist1D("Mass0","","Mass0","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass0,comment);
 plots->hMass1 = result->AddHist1D("Mass1","","Mass1","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass1,comment);
 plots->hMass2 = result->AddHist1D("Mass2","","Mass2","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass2,comment);
 plots->hMass3 = result->AddHist1D("Mass3","","Mass3","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass3,comment);
 
 plots->hMass_nGenLQ0 = result->AddHist1D("Mass_nGenLQ0","","Mass_nGenLQ0","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass_nGenLQ0,comment);
 plots->hMass0_nGenLQ0 = result->AddHist1D("Mass0_nGenLQ0","","Mass0_nGenLQ0","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass0_nGenLQ0,comment);
 plots->hMass1_nGenLQ0 = result->AddHist1D("Mass1_nGenLQ0","","Mass1_nGenLQ0","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass1_nGenLQ0,comment);
 plots->hMass2_nGenLQ0 = result->AddHist1D("Mass2_nGenLQ0","","Mass2_nGenLQ0","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass2,comment);
 plots->hMass3_nGenLQ0 = result->AddHist1D("Mass3_nGenLQ0","","Mass3_nGenLQ0","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass3_nGenLQ0,comment);
 plots->hMass_nGenLQ1 = result->AddHist1D("Mass_nGenLQ1","","Mass_nGenLQ1","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass_nGenLQ1,comment);
 plots->hMass0_nGenLQ1 = result->AddHist1D("Mass0_nGenLQ1","","Mass0_nGenLQ1","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass0_nGenLQ1,comment);
 plots->hMass1_nGenLQ1 = result->AddHist1D("Mass1_nGenLQ1","","Mass1_nGenLQ1","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass1_nGenLQ1,comment);
 plots->hMass2_nGenLQ1 = result->AddHist1D("Mass2_nGenLQ1","","Mass2_nGenLQ1","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass2,comment);
 plots->hMass3_nGenLQ1 = result->AddHist1D("Mass3_nGenLQ1","","Mass3_nGenLQ1","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass3_nGenLQ1,comment);
 plots->hMass_nGenLQ2 = result->AddHist1D("Mass_nGenLQ2","","Mass_nGenLQ2","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass_nGenLQ2,comment);
 plots->hMass0_nGenLQ2 = result->AddHist1D("Mass0_nGenLQ2","","Mass0_nGenLQ2","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass0_nGenLQ2,comment);
 plots->hMass1_nGenLQ2 = result->AddHist1D("Mass1_nGenLQ2","","Mass1_nGenLQ2","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass1_nGenLQ2,comment);
 plots->hMass2_nGenLQ2 = result->AddHist1D("Mass2_nGenLQ2","","Mass2_nGenLQ2","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass2,comment);
 plots->hMass3_nGenLQ2 = result->AddHist1D("Mass3_nGenLQ2","","Mass3_nGenLQ2","nEvents",hMass_binsX,hMass_IniRangeX,hMass_EndRangeX);
 result->Attach(plots->hMass3_nGenLQ2,comment);
 
 plots->hSt = result->AddHist1D("St","","St","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt,comment);
 plots->hSt0 = result->AddHist1D("St0","","St0","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt0,comment);
 plots->hSt1 = result->AddHist1D("St1","","St1","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt1,comment);
 plots->hSt2 = result->AddHist1D("St2","","St2","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt2,comment);
 plots->hSt3 = result->AddHist1D("St3","","St3","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt3,comment);
 
 plots->hSt_nGenLQ0 = result->AddHist1D("St_nGenLQ0","","St_nGenLQ0","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt_nGenLQ0,comment);
 plots->hSt0_nGenLQ0 = result->AddHist1D("St0_nGenLQ0","","St0_nGenLQ0","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt0_nGenLQ0,comment);
 plots->hSt1_nGenLQ0 = result->AddHist1D("St1_nGenLQ0","","St1_nGenLQ0","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt1_nGenLQ0,comment);
 plots->hSt2_nGenLQ0 = result->AddHist1D("St2_nGenLQ0","","St2_nGenLQ0","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt2,comment);
 plots->hSt3_nGenLQ0 = result->AddHist1D("St3_nGenLQ0","","St3_nGenLQ0","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt3_nGenLQ0,comment);
 plots->hSt_nGenLQ1 = result->AddHist1D("St_nGenLQ1","","St_nGenLQ1","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt_nGenLQ1,comment);
 plots->hSt0_nGenLQ1 = result->AddHist1D("St0_nGenLQ1","","St0_nGenLQ1","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt0_nGenLQ1,comment);
 plots->hSt1_nGenLQ1 = result->AddHist1D("St1_nGenLQ1","","St1_nGenLQ1","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt1_nGenLQ1,comment);
 plots->hSt2_nGenLQ1 = result->AddHist1D("St2_nGenLQ1","","St2_nGenLQ1","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt2,comment);
 plots->hSt3_nGenLQ1 = result->AddHist1D("St3_nGenLQ1","","St3_nGenLQ1","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt3_nGenLQ1,comment);
 plots->hSt_nGenLQ2 = result->AddHist1D("St_nGenLQ2","","St_nGenLQ2","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt_nGenLQ2,comment);
 plots->hSt0_nGenLQ2 = result->AddHist1D("St0_nGenLQ2","","St0_nGenLQ2","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt0_nGenLQ2,comment);
 plots->hSt1_nGenLQ2 = result->AddHist1D("St1_nGenLQ2","","St1_nGenLQ2","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt1_nGenLQ2,comment);
 plots->hSt2_nGenLQ2 = result->AddHist1D("St2_nGenLQ2","","St2_nGenLQ2","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt2,comment);
 plots->hSt3_nGenLQ2 = result->AddHist1D("St3_nGenLQ2","","St3_nGenLQ2","nEvents",hSt_binsX,hSt_IniRangeX,hSt_EndRangeX);
 result->Attach(plots->hSt3_nGenLQ2,comment);
 
 plots->hSt_asymBins = result->AddHist1D("St_asymBins","","St_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_asymBins,comment);
 plots->hSt_asymBins_nGenLQ0 = result->AddHist1D("St_asymBins_nGenLQ0","","St_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_asymBins_nGenLQ0,comment);
 plots->hSt_asymBins_nGenLQ1 = result->AddHist1D("St_asymBins_nGenLQ1","","St_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_asymBins_nGenLQ1,comment);
 plots->hSt_asymBins_nGenLQ2 = result->AddHist1D("St_asymBins_nGenLQ2","","St_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_asymBins_nGenLQ2,comment);
 plots->hSt0_asymBins = result->AddHist1D("St0_asymBins","","St0_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt0_asymBins,comment);
 plots->hSt0_asymBins_nGenLQ0 = result->AddHist1D("St0_asymBins_nGenLQ0","","St0_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt0_asymBins_nGenLQ0,comment);
 plots->hSt0_asymBins_nGenLQ1 = result->AddHist1D("St0_asymBins_nGenLQ1","","St0_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt0_asymBins_nGenLQ1,comment);
 plots->hSt0_asymBins_nGenLQ2 = result->AddHist1D("St0_asymBins_nGenLQ2","","St0_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt0_asymBins_nGenLQ2,comment);
 plots->hSt1_asymBins = result->AddHist1D("St1_asymBins","","St1_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt1_asymBins,comment);
 plots->hSt1_asymBins_nGenLQ0 = result->AddHist1D("St1_asymBins_nGenLQ0","","St1_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt1_asymBins_nGenLQ0,comment);
 plots->hSt1_asymBins_nGenLQ1 = result->AddHist1D("St1_asymBins_nGenLQ1","","St1_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt1_asymBins_nGenLQ1,comment);
 plots->hSt1_asymBins_nGenLQ2 = result->AddHist1D("St1_asymBins_nGenLQ2","","St1_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt1_asymBins_nGenLQ2,comment);
 plots->hSt2_asymBins = result->AddHist1D("St2_asymBins","","St2_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt2_asymBins,comment);
 plots->hSt2_asymBins_nGenLQ0 = result->AddHist1D("St2_asymBins_nGenLQ0","","St2_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt2_asymBins_nGenLQ0,comment);
 plots->hSt2_asymBins_nGenLQ1 = result->AddHist1D("St2_asymBins_nGenLQ1","","St2_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt2_asymBins_nGenLQ1,comment);
 plots->hSt2_asymBins_nGenLQ2 = result->AddHist1D("St2_asymBins_nGenLQ2","","St2_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt2_asymBins_nGenLQ2,comment);
 plots->hSt3_asymBins = result->AddHist1D("St3_asymBins","","St3_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt3_asymBins,comment);
 plots->hSt3_asymBins_nGenLQ0 = result->AddHist1D("St3_asymBins_nGenLQ0","","St3_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt3_asymBins_nGenLQ0,comment);
 plots->hSt3_asymBins_nGenLQ1 = result->AddHist1D("St3_asymBins_nGenLQ1","","St3_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt3_asymBins_nGenLQ1,comment);
 plots->hSt3_asymBins_nGenLQ2 = result->AddHist1D("St3_asymBins_nGenLQ2","","St3_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt3_asymBins_nGenLQ2,comment);
 plots->hChiSt = result->AddHist2D("ChiSt","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt,comment);
 plots->hChiSt_nGenLQ0 = result->AddHist2D("ChiSt_nGenLQ0","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt_nGenLQ0,comment);
 plots->hChiSt_nGenLQ1 = result->AddHist2D("ChiSt_nGenLQ1","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt_nGenLQ1,comment);
 plots->hChiSt_nGenLQ2 = result->AddHist2D("ChiSt_nGenLQ2","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt_nGenLQ2,comment);
 plots->hChiSt0 = result->AddHist2D("ChiSt0","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt0,comment);
 plots->hChiSt0_nGenLQ0 = result->AddHist2D("ChiSt0_nGenLQ0","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt0_nGenLQ0,comment);
 plots->hChiSt0_nGenLQ1 = result->AddHist2D("ChiSt0_nGenLQ1","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt0_nGenLQ1,comment);
 plots->hChiSt0_nGenLQ2 = result->AddHist2D("ChiSt0_nGenLQ2","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt0_nGenLQ2,comment);
 plots->hChiSt1 = result->AddHist2D("ChiSt1","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt1,comment);
 plots->hChiSt1_nGenLQ0 = result->AddHist2D("ChiSt1_nGenLQ0","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt1_nGenLQ0,comment);
 plots->hChiSt1_nGenLQ1 = result->AddHist2D("ChiSt1_nGenLQ1","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt1_nGenLQ1,comment);
 plots->hChiSt1_nGenLQ2 = result->AddHist2D("ChiSt1_nGenLQ2","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt1_nGenLQ2,comment);
 plots->hChiSt2 = result->AddHist2D("ChiSt2","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt2,comment);
 plots->hChiSt2_nGenLQ0 = result->AddHist2D("ChiSt2_nGenLQ0","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt2_nGenLQ0,comment);
 plots->hChiSt2_nGenLQ1 = result->AddHist2D("ChiSt2_nGenLQ1","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt2_nGenLQ1,comment);
 plots->hChiSt2_nGenLQ2 = result->AddHist2D("ChiSt2_nGenLQ2","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt2_nGenLQ2,comment);
 plots->hChiSt3 = result->AddHist2D("ChiSt3","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt3,comment);
 plots->hChiSt3_nGenLQ0 = result->AddHist2D("ChiSt3_nGenLQ0","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt3_nGenLQ0,comment);
 plots->hChiSt3_nGenLQ1 = result->AddHist2D("ChiSt3_nGenLQ1","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt3_nGenLQ1,comment);
 plots->hChiSt3_nGenLQ2 = result->AddHist2D("ChiSt3_nGenLQ2","","St","Chi",hChiSt_binsX,hChiSt_IniRangeX,hChiSt_EndRangeX,hChiSt_binsY,hChiSt_IniRangeY,hChiSt_EndRangeY);
 result->Attach(plots->hChiSt3_nGenLQ2,comment);

 plots->hSt_jet0_chi0 = result->AddHist1D("St_jet0_chi0","","St_jet0_chi0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet0_chi0,comment);
 plots->hSt_jet0_chi0_nGenLQ0 = result->AddHist1D("St_jet0_chi0_nGenLQ0","","St_jet0_chi0_nGenLQ0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet0_chi0_nGenLQ0,comment);
 plots->hSt_jet0_chi0_nGenLQ1 = result->AddHist1D("St_jet0_chi0_nGenLQ1","","St_jet0_chi0_nGenLQ1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet0_chi0_nGenLQ1,comment);
 plots->hSt_jet0_chi0_nGenLQ2 = result->AddHist1D("St_jet0_chi0_nGenLQ2","","St_jet0_chi0_nGenLQ2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet0_chi0_nGenLQ2,comment);
 plots->hSt_jet0_chi1 = result->AddHist1D("St_jet0_chi1","","St_jet0_chi1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet0_chi1,comment);
 plots->hSt_jet0_chi1_nGenLQ0 = result->AddHist1D("St_jet0_chi1_nGenLQ0","","St_jet0_chi1_nGenLQ0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet0_chi1_nGenLQ0,comment);
 plots->hSt_jet0_chi1_nGenLQ1 = result->AddHist1D("St_jet0_chi1_nGenLQ1","","St_jet0_chi1_nGenLQ1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet0_chi1_nGenLQ1,comment);
 plots->hSt_jet0_chi1_nGenLQ2 = result->AddHist1D("St_jet0_chi1_nGenLQ2","","St_jet0_chi1_nGenLQ2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet0_chi1_nGenLQ2,comment);
 plots->hSt_jet0_chi2 = result->AddHist1D("St_jet0_chi2","","St_jet0_chi2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet0_chi2,comment);
 plots->hSt_jet0_chi2_nGenLQ0 = result->AddHist1D("St_jet0_chi2_nGenLQ0","","St_jet0_chi2_nGenLQ0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet0_chi2_nGenLQ0,comment);
 plots->hSt_jet0_chi2_nGenLQ1 = result->AddHist1D("St_jet0_chi2_nGenLQ1","","St_jet0_chi2_nGenLQ1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet0_chi2_nGenLQ1,comment);
 plots->hSt_jet0_chi2_nGenLQ2 = result->AddHist1D("St_jet0_chi2_nGenLQ2","","St_jet0_chi2_nGenLQ2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet0_chi2_nGenLQ2,comment);

 plots->hSt_jet1_chi0 = result->AddHist1D("St_jet1_chi0","","St_jet1_chi0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet1_chi0,comment);
 plots->hSt_jet1_chi0_nGenLQ0 = result->AddHist1D("St_jet1_chi0_nGenLQ0","","St_jet1_chi0_nGenLQ0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet1_chi0_nGenLQ0,comment);
 plots->hSt_jet1_chi0_nGenLQ1 = result->AddHist1D("St_jet1_chi0_nGenLQ1","","St_jet1_chi0_nGenLQ1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet1_chi0_nGenLQ1,comment);
 plots->hSt_jet1_chi0_nGenLQ2 = result->AddHist1D("St_jet1_chi0_nGenLQ2","","St_jet1_chi0_nGenLQ2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet1_chi0_nGenLQ2,comment);
 plots->hSt_jet1_chi1 = result->AddHist1D("St_jet1_chi1","","St_jet1_chi1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet1_chi1,comment);
 plots->hSt_jet1_chi1_nGenLQ0 = result->AddHist1D("St_jet1_chi1_nGenLQ0","","St_jet1_chi1_nGenLQ0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet1_chi1_nGenLQ0,comment);
 plots->hSt_jet1_chi1_nGenLQ1 = result->AddHist1D("St_jet1_chi1_nGenLQ1","","St_jet1_chi1_nGenLQ1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet1_chi1_nGenLQ1,comment);
 plots->hSt_jet1_chi1_nGenLQ2 = result->AddHist1D("St_jet1_chi1_nGenLQ2","","St_jet1_chi1_nGenLQ2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet1_chi1_nGenLQ2,comment);
 plots->hSt_jet1_chi2 = result->AddHist1D("St_jet1_chi2","","St_jet1_chi2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet1_chi2,comment);
 plots->hSt_jet1_chi2_nGenLQ0 = result->AddHist1D("St_jet1_chi2_nGenLQ0","","St_jet1_chi2_nGenLQ0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet1_chi2_nGenLQ0,comment);
 plots->hSt_jet1_chi2_nGenLQ1 = result->AddHist1D("St_jet1_chi2_nGenLQ1","","St_jet1_chi2_nGenLQ1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet1_chi2_nGenLQ1,comment);
 plots->hSt_jet1_chi2_nGenLQ2 = result->AddHist1D("St_jet1_chi2_nGenLQ2","","St_jet1_chi2_nGenLQ2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet1_chi2_nGenLQ2,comment);

 plots->hSt_jet2_chi0 = result->AddHist1D("St_jet2_chi0","","St_jet2_chi0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet2_chi0,comment);
 plots->hSt_jet2_chi0_nGenLQ0 = result->AddHist1D("St_jet2_chi0_nGenLQ0","","St_jet2_chi0_nGenLQ0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet2_chi0_nGenLQ0,comment);
 plots->hSt_jet2_chi0_nGenLQ1 = result->AddHist1D("St_jet2_chi0_nGenLQ1","","St_jet2_chi0_nGenLQ1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet2_chi0_nGenLQ1,comment);
 plots->hSt_jet2_chi0_nGenLQ2 = result->AddHist1D("St_jet2_chi0_nGenLQ2","","St_jet2_chi0_nGenLQ2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet2_chi0_nGenLQ2,comment);
 plots->hSt_jet2_chi1 = result->AddHist1D("St_jet2_chi1","","St_jet2_chi1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet2_chi1,comment);
 plots->hSt_jet2_chi1_nGenLQ0 = result->AddHist1D("St_jet2_chi1_nGenLQ0","","St_jet2_chi1_nGenLQ0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet2_chi1_nGenLQ0,comment);
 plots->hSt_jet2_chi1_nGenLQ1 = result->AddHist1D("St_jet2_chi1_nGenLQ1","","St_jet2_chi1_nGenLQ1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet2_chi1_nGenLQ1,comment);
 plots->hSt_jet2_chi1_nGenLQ2 = result->AddHist1D("St_jet2_chi1_nGenLQ2","","St_jet2_chi1_nGenLQ2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet2_chi1_nGenLQ2,comment);
 plots->hSt_jet2_chi2 = result->AddHist1D("St_jet2_chi2","","St_jet2_chi2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet2_chi2,comment);
 plots->hSt_jet2_chi2_nGenLQ0 = result->AddHist1D("St_jet2_chi2_nGenLQ0","","St_jet2_chi2_nGenLQ0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet2_chi2_nGenLQ0,comment);
 plots->hSt_jet2_chi2_nGenLQ1 = result->AddHist1D("St_jet2_chi2_nGenLQ1","","St_jet2_chi2_nGenLQ1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet2_chi2_nGenLQ1,comment);
 plots->hSt_jet2_chi2_nGenLQ2 = result->AddHist1D("St_jet2_chi2_nGenLQ2","","St_jet2_chi2_nGenLQ2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet2_chi2_nGenLQ2,comment);

 plots->hSt_jet3_chi0 = result->AddHist1D("St_jet3_chi0","","St_jet3_chi0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet3_chi0,comment);
 plots->hSt_jet3_chi0_nGenLQ0 = result->AddHist1D("St_jet3_chi0_nGenLQ0","","St_jet3_chi0_nGenLQ0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet3_chi0_nGenLQ0,comment);
 plots->hSt_jet3_chi0_nGenLQ1 = result->AddHist1D("St_jet3_chi0_nGenLQ1","","St_jet3_chi0_nGenLQ1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet3_chi0_nGenLQ1,comment);
 plots->hSt_jet3_chi0_nGenLQ2 = result->AddHist1D("St_jet3_chi0_nGenLQ2","","St_jet3_chi0_nGenLQ2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet3_chi0_nGenLQ2,comment);
 plots->hSt_jet3_chi1 = result->AddHist1D("St_jet3_chi1","","St_jet3_chi1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet3_chi1,comment);
 plots->hSt_jet3_chi1_nGenLQ0 = result->AddHist1D("St_jet3_chi1_nGenLQ0","","St_jet3_chi1_nGenLQ0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet3_chi1_nGenLQ0,comment);
 plots->hSt_jet3_chi1_nGenLQ1 = result->AddHist1D("St_jet3_chi1_nGenLQ1","","St_jet3_chi1_nGenLQ1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet3_chi1_nGenLQ1,comment);
 plots->hSt_jet3_chi1_nGenLQ2 = result->AddHist1D("St_jet3_chi1_nGenLQ2","","St_jet3_chi1_nGenLQ2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet3_chi1_nGenLQ2,comment);
 plots->hSt_jet3_chi2 = result->AddHist1D("St_jet3_chi2","","St_jet3_chi2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet3_chi2,comment);
 plots->hSt_jet3_chi2_nGenLQ0 = result->AddHist1D("St_jet3_chi2_nGenLQ0","","St_jet3_chi2_nGenLQ0","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet3_chi2_nGenLQ0,comment);
 plots->hSt_jet3_chi2_nGenLQ1 = result->AddHist1D("St_jet3_chi2_nGenLQ1","","St_jet3_chi2_nGenLQ1","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet3_chi2_nGenLQ1,comment);
 plots->hSt_jet3_chi2_nGenLQ2 = result->AddHist1D("St_jet3_chi2_nGenLQ2","","St_jet3_chi2_nGenLQ2","nEvents",hSt_jet_chi_binx,hSt_jet_chi_IniRangeX,hSt_jet_chi_EndRangeX);
 result->Attach(plots->hSt_jet3_chi2_nGenLQ2,comment);

 plots->hSt_jet0_chi0_asymBins = result->AddHist1D("St_jet0_chi0_asymBins","","St_jet0_chi0_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet0_chi0_asymBins,comment);
 plots->hSt_jet0_chi0_asymBins_nGenLQ0 = result->AddHist1D("St_jet0_chi0_asymBins_nGenLQ0","","St_jet0_chi0_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet0_chi0_asymBins_nGenLQ0,comment);
 plots->hSt_jet0_chi0_asymBins_nGenLQ1 = result->AddHist1D("St_jet0_chi0_asymBins_nGenLQ1","","St_jet0_chi0_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet0_chi0_asymBins_nGenLQ1,comment);
 plots->hSt_jet0_chi0_asymBins_nGenLQ2 = result->AddHist1D("St_jet0_chi0_asymBins_nGenLQ2","","St_jet0_chi0_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet0_chi0_asymBins_nGenLQ2,comment);
 plots->hSt_jet0_chi1_asymBins = result->AddHist1D("St_jet0_chi1_asymBins","","St_jet0_chi1_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet0_chi1_asymBins,comment);
 plots->hSt_jet0_chi1_asymBins_nGenLQ0 = result->AddHist1D("St_jet0_chi1_asymBins_nGenLQ0","","St_jet0_chi1_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet0_chi1_asymBins_nGenLQ0,comment);
 plots->hSt_jet0_chi1_asymBins_nGenLQ1 = result->AddHist1D("St_jet0_chi1_asymBins_nGenLQ1","","St_jet0_chi1_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet0_chi1_asymBins_nGenLQ1,comment);
 plots->hSt_jet0_chi1_asymBins_nGenLQ2 = result->AddHist1D("St_jet0_chi1_asymBins_nGenLQ2","","St_jet0_chi1_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet0_chi1_asymBins_nGenLQ2,comment);
 plots->hSt_jet0_chi2_asymBins = result->AddHist1D("St_jet0_chi2_asymBins","","St_jet0_chi2_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet0_chi2_asymBins,comment);
 plots->hSt_jet0_chi2_asymBins_nGenLQ0 = result->AddHist1D("St_jet0_chi2_asymBins_nGenLQ0","","St_jet0_chi2_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet0_chi2_asymBins_nGenLQ0,comment);
 plots->hSt_jet0_chi2_asymBins_nGenLQ1 = result->AddHist1D("St_jet0_chi2_asymBins_nGenLQ1","","St_jet0_chi2_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet0_chi2_asymBins_nGenLQ1,comment);
 plots->hSt_jet0_chi2_asymBins_nGenLQ2 = result->AddHist1D("St_jet0_chi2_asymBins_nGenLQ2","","St_jet0_chi2_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet0_chi2_asymBins_nGenLQ2,comment);

 plots->hSt_jet1_chi0_asymBins = result->AddHist1D("St_jet1_chi0_asymBins","","St_jet1_chi0_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet1_chi0_asymBins,comment);
 plots->hSt_jet1_chi0_asymBins_nGenLQ0 = result->AddHist1D("St_jet1_chi0_asymBins_nGenLQ0","","St_jet1_chi0_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet1_chi0_asymBins_nGenLQ0,comment);
 plots->hSt_jet1_chi0_asymBins_nGenLQ1 = result->AddHist1D("St_jet1_chi0_asymBins_nGenLQ1","","St_jet1_chi0_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet1_chi0_asymBins_nGenLQ1,comment);
 plots->hSt_jet1_chi0_asymBins_nGenLQ2 = result->AddHist1D("St_jet1_chi0_asymBins_nGenLQ2","","St_jet1_chi0_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet1_chi0_asymBins_nGenLQ2,comment);
 plots->hSt_jet1_chi1_asymBins = result->AddHist1D("St_jet1_chi1_asymBins","","St_jet1_chi1_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet1_chi1_asymBins,comment);
 plots->hSt_jet1_chi1_asymBins_nGenLQ0 = result->AddHist1D("St_jet1_chi1_asymBins_nGenLQ0","","St_jet1_chi1_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet1_chi1_asymBins_nGenLQ0,comment);
 plots->hSt_jet1_chi1_asymBins_nGenLQ1 = result->AddHist1D("St_jet1_chi1_asymBins_nGenLQ1","","St_jet1_chi1_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet1_chi1_asymBins_nGenLQ1,comment);
 plots->hSt_jet1_chi1_asymBins_nGenLQ2 = result->AddHist1D("St_jet1_chi1_asymBins_nGenLQ2","","St_jet1_chi1_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet1_chi1_asymBins_nGenLQ2,comment);
 plots->hSt_jet1_chi2_asymBins = result->AddHist1D("St_jet1_chi2_asymBins","","St_jet1_chi2_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet1_chi2_asymBins,comment);
 plots->hSt_jet1_chi2_asymBins_nGenLQ0 = result->AddHist1D("St_jet1_chi2_asymBins_nGenLQ0","","St_jet1_chi2_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet1_chi2_asymBins_nGenLQ0,comment);
 plots->hSt_jet1_chi2_asymBins_nGenLQ1 = result->AddHist1D("St_jet1_chi2_asymBins_nGenLQ1","","St_jet1_chi2_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet1_chi2_asymBins_nGenLQ1,comment);
 plots->hSt_jet1_chi2_asymBins_nGenLQ2 = result->AddHist1D("St_jet1_chi2_asymBins_nGenLQ2","","St_jet1_chi2_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet1_chi2_asymBins_nGenLQ2,comment);

 plots->hSt_jet2_chi0_asymBins = result->AddHist1D("St_jet2_chi0_asymBins","","St_jet2_chi0_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet2_chi0_asymBins,comment);
 plots->hSt_jet2_chi0_asymBins_nGenLQ0 = result->AddHist1D("St_jet2_chi0_asymBins_nGenLQ0","","St_jet2_chi0_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet2_chi0_asymBins_nGenLQ0,comment);
 plots->hSt_jet2_chi0_asymBins_nGenLQ1 = result->AddHist1D("St_jet2_chi0_asymBins_nGenLQ1","","St_jet2_chi0_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet2_chi0_asymBins_nGenLQ1,comment);
 plots->hSt_jet2_chi0_asymBins_nGenLQ2 = result->AddHist1D("St_jet2_chi0_asymBins_nGenLQ2","","St_jet2_chi0_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet2_chi0_asymBins_nGenLQ2,comment);
 plots->hSt_jet2_chi1_asymBins = result->AddHist1D("St_jet2_chi1_asymBins","","St_jet2_chi1_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet2_chi1_asymBins,comment);
 plots->hSt_jet2_chi1_asymBins_nGenLQ0 = result->AddHist1D("St_jet2_chi1_asymBins_nGenLQ0","","St_jet2_chi1_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet2_chi1_asymBins_nGenLQ0,comment);
 plots->hSt_jet2_chi1_asymBins_nGenLQ1 = result->AddHist1D("St_jet2_chi1_asymBins_nGenLQ1","","St_jet2_chi1_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet2_chi1_asymBins_nGenLQ1,comment);
 plots->hSt_jet2_chi1_asymBins_nGenLQ2 = result->AddHist1D("St_jet2_chi1_asymBins_nGenLQ2","","St_jet2_chi1_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet2_chi1_asymBins_nGenLQ2,comment);
 plots->hSt_jet2_chi2_asymBins = result->AddHist1D("St_jet2_chi2_asymBins","","St_jet2_chi2_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet2_chi2_asymBins,comment);
 plots->hSt_jet2_chi2_asymBins_nGenLQ0 = result->AddHist1D("St_jet2_chi2_asymBins_nGenLQ0","","St_jet2_chi2_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet2_chi2_asymBins_nGenLQ0,comment);
 plots->hSt_jet2_chi2_asymBins_nGenLQ1 = result->AddHist1D("St_jet2_chi2_asymBins_nGenLQ1","","St_jet2_chi2_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet2_chi2_asymBins_nGenLQ1,comment);
 plots->hSt_jet2_chi2_asymBins_nGenLQ2 = result->AddHist1D("St_jet2_chi2_asymBins_nGenLQ2","","St_jet2_chi2_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet2_chi2_asymBins_nGenLQ2,comment);

 plots->hSt_jet3_chi0_asymBins = result->AddHist1D("St_jet3_chi0_asymBins","","St_jet3_chi0_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet3_chi0_asymBins,comment);
 plots->hSt_jet3_chi0_asymBins_nGenLQ0 = result->AddHist1D("St_jet3_chi0_asymBins_nGenLQ0","","St_jet3_chi0_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet3_chi0_asymBins_nGenLQ0,comment);
 plots->hSt_jet3_chi0_asymBins_nGenLQ1 = result->AddHist1D("St_jet3_chi0_asymBins_nGenLQ1","","St_jet3_chi0_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet3_chi0_asymBins_nGenLQ1,comment);
 plots->hSt_jet3_chi0_asymBins_nGenLQ2 = result->AddHist1D("St_jet3_chi0_asymBins_nGenLQ2","","St_jet3_chi0_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet3_chi0_asymBins_nGenLQ2,comment);
 plots->hSt_jet3_chi1_asymBins = result->AddHist1D("St_jet3_chi1_asymBins","","St_jet3_chi1_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet3_chi1_asymBins,comment);
 plots->hSt_jet3_chi1_asymBins_nGenLQ0 = result->AddHist1D("St_jet3_chi1_asymBins_nGenLQ0","","St_jet3_chi1_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet3_chi1_asymBins_nGenLQ0,comment);
 plots->hSt_jet3_chi1_asymBins_nGenLQ1 = result->AddHist1D("St_jet3_chi1_asymBins_nGenLQ1","","St_jet3_chi1_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet3_chi1_asymBins_nGenLQ1,comment);
 plots->hSt_jet3_chi1_asymBins_nGenLQ2 = result->AddHist1D("St_jet3_chi1_asymBins_nGenLQ2","","St_jet3_chi1_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet3_chi1_asymBins_nGenLQ2,comment);
 plots->hSt_jet3_chi2_asymBins = result->AddHist1D("St_jet3_chi2_asymBins","","St_jet3_chi2_asymBins","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet3_chi2_asymBins,comment);
 plots->hSt_jet3_chi2_asymBins_nGenLQ0 = result->AddHist1D("St_jet3_chi2_asymBins_nGenLQ0","","St_jet3_chi2_asymBins_nGenLQ0","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet3_chi2_asymBins_nGenLQ0,comment);
 plots->hSt_jet3_chi2_asymBins_nGenLQ1 = result->AddHist1D("St_jet3_chi2_asymBins_nGenLQ1","","St_jet3_chi2_asymBins_nGenLQ1","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet3_chi2_asymBins_nGenLQ1,comment);
 plots->hSt_jet3_chi2_asymBins_nGenLQ2 = result->AddHist1D("St_jet3_chi2_asymBins_nGenLQ2","","St_jet3_chi2_asymBins_nGenLQ2","nEvents",asymBinsN,asymBins);
 result->Attach(plots->hSt_jet3_chi2_asymBins_nGenLQ2,comment);
}

void PrintHistograms(ExRootResult *result, MyPlots *plots){
 result->Print("png");
}
