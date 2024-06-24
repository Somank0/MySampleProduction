#ifndef ANALYZEHGCMuons_H
#define ANALYZEHGCMuons_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "HGCNtupleVariables.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TText.h"
#include "TH3F.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TFrame.h"
#include "TFile.h"
#include "TKey.h"
#include "TLorentzVector.h"
#include "TDirectory.h"
#include "TVirtualHistPainter.h"
#include "TPaveStats.h"
#include "TLatex.h"

void PaintOverflow(TH1 *h)
{
  // This function paint the histogram h with an extra bin for overflows

  const char *name = h->GetName();
  const char *title = h->GetTitle();
  Int_t nx = h->GetNbinsX() + 1;
  Double_t x1 = h->GetBinLowEdge(1);
  Double_t bw = h->GetBinWidth(nx);
  Double_t x2 = h->GetBinLowEdge(nx) + bw;

  // Book a temporary histogram having ab extra bin for overflows
  TH1F *htmp = new TH1F("rebinned", title, nx, x1, x2);

  // Fill the new hitogram including the extra bin for overflows
  for (Int_t i = 1; i <= nx; i++)
  {
    htmp->Fill(htmp->GetBinCenter(i), h->GetBinContent(i));
  }

  // Fill the underflows
  htmp->Fill(x1 - 1, h->GetBinContent(0));

  // Restore the number of entries
  htmp->SetEntries(h->GetEntries());

  // Draw the temporary histogram
  htmp->Draw();
  TText *t = new TText(x2 - bw / 2, h->GetBinContent(nx), "Overflow");
  t->SetTextAngle(90);
  t->SetTextAlign(12);
  t->SetTextSize(0.03);
  ;
  t->Draw();
}
class AnalyzeHGCMuons : public HGCNtupleVariables
{

public:
  AnalyzeHGCMuons(const TString &inputFileList = "foo.txt", const char *outFileName = "histo.root", const char *dataset = "data", const char *massP="0.1");
  ~AnalyzeHGCMuons();
  Bool_t FillChain(TChain *chain, TChain *chain2, const TString &inputFileList);
  void graphHist(TH2F *hist, char title[], char name[]);
  Long64_t LoadTree(Long64_t entry);
  void EventLoop(const char *);
  void BookHistogram(const char *);
  void graphSide(TH1F *hist1, TH1F *hist2, string name,string x_title, string y_title);
  void graphSide(TH2F *hist1, TH2F *hist2, string name, string x_title, string y_title);
  void graphOverlay(TH2F *hist1, TH2F *hist2, string name,string x_title,string y_title);
  void graphOverlay(TH1F *hist1, TH1F *hist2, string name,string x_title,string y_title);
  void graphOverlay(TH1F *hist1, TH1F *hist2, TH1F *hist4,string name,string x_title,string y_title);
  void graphOverlay(TH1F *hist1, TH1F *hist2,TH1F *hist4,TH1F *hist5, string name,string x_title,string y_title);
  void DrawHist(TH1F *hist1, string name, string x_title, string y_title);
  void DrawHist(TH2F *hist1, string name, string x_title, string y_title);
  void DrawHistTXT(TH2F *hits, string name, string x_title, string y_title);
  void DrawHistNoStat(TH2F *hist1, string name, string x_title, string y_title);
  int fillhist = 1;
  /*int ctr_twogen = 0;
  int ctr_mcut = 0;
  int ctr_tworeco = 0;
  int ctr_onereco = 0;
  int ctr_onedr = 0;
  int ctr_twodr = 0;*/
//  string mass = "1.8";
  string gamma = "";
  string mass = "1.8";

  TFile *oFile;
  TDirectory *d_Layer1;

  TTree *treeout;
  double M_m_gen;
  double M_m_reco;
  double M_p_gen;
  double M_pt_gen;
  double M_eta_gen;
  double M_phi_gen;
  vector<float> M_pt_reco;
  vector<float> M_eta_reco;
  vector<float> M_phi_reco;
  vector<float> M_E_reco;

  vector<float> *M_HitX1;
  bool M_EEFlag1;
  bool M_EEFlag2;
  vector<float> *M_HitY1;
  vector<float> *M_HitZ1;
  vector<float> *M_HitEta1;
  vector<float> *M_HitPhi1;
  vector<float> *M_HitiEta1;
  vector<float> *M_HitiPhi1;
  vector<float> *M_HitEn1;
  vector<float> *M_HitET1;
  vector<float> *M_HitEZ1;
  vector<float> *M_HitX2;
  vector<float> *M_HitY2;
  vector<float> *M_HitZ2;
  vector<float> *M_HitEta2;
  vector<float> *M_HitPhi2;
  vector<float> *M_HitiEta2;
  vector<float> *M_HitiPhi2;
  vector<float> *M_HitEn2;
  vector<float> *M_HitET2;
  vector<float> *M_HitEZ2;
  vector<float> M_SigIEIE1;
  vector<float> M_SigIEIE2;
  vector<float> M_SigIPhiIPhi1;
  vector<float> M_SigIPhiIPhi2;
  vector<float> M_R9_Pho1;
  vector<float> M_R9_Pho2;
  
  vector<float> *M_ES_HitX1;
  vector<float> *M_ES_HitY1;
  vector<float> *M_ES_HitZ1;
  vector<float> *M_ES_HitEta1;
  vector<float> *M_ES_HitPhi1;
  vector<float> *M_ES_HitEn1;
  vector<float> *M_ES_HitX2;
  vector<float> *M_ES_HitY2;
  vector<float> *M_ES_HitZ2;
  vector<float> *M_ES_HitEta2;
  vector<float> *M_ES_HitPhi2;
  vector<float> *M_ES_HitEn2;

  double M_EBM;
  double M_angle_gen;
  int M_event;
  int M_lumi;
  int M_run;
  //  float m_gen;
  //Declare Historgrams
  //1D histograms
  TH1F *a_gen_mass;
  TH1F *a_gen_pt;
  TH1F *a_gen_E;
  TH1F *a_gen_eta;
  TH1F *a_gen_phi;
  TH1F *a_gen_gamma;
  TH1F *E_sublead_by_E_lead;
  TH1F *pho1_EE_hit_eta;
  TH1F *pho2_EE_hit_eta;
  TH1F *pho1_hitX;
  TH1F *pho1_hitY;
  TH1F *pho1_hit_Z;
  TH1F *pho2_hitX;
  TH1F *pho2_hitY;
  TH1F *pho2_hit_Z;
  TH1F *pho1_ES_hitX;
  TH1F *pho1_ES_hitY;
  TH1F *pho1_ES_hit_Z;
  TH1F *pho2_ES_hitX;
  TH1F *pho2_ES_hitY;
  TH1F *pho2_ES_hit_Z;
  TH1F *angle_240_260;
  TH1F *angle_490_510;
  TH1F *angle_740_760;
  TH1F *angle_990_1010;
  TH1F *nGen;
  TH1F *nreco;
  TH1F *r9_eta_1;
  TH1F *r9_eta_2;
  TH1F *r9_eta_3;
  TH1F *ES_L1_hits;
  TH1F *ES_L2_hits;
  TH1F *ES_L1_L2_hits_En_weighed;
 // TH1F *ES_L2_hits_En_weighed;
  //2D histograms
  
  TH2F *a_gen_mass_vs_pt;
  TH2F *a_gen_eta_vs_phi;
  TH2F *angle_vs_gamma_Ma_240_260;
  TH2F *angle_vs_gamma_Ma_490_510;
  TH2F *angle_vs_gamma_Ma_740_760;
  TH2F *angle_vs_gamma_Ma_990_1010;
  TH2F *deta_dphi_gen;
  TH2F *EE_XY_occupancy;
  TH2F *EE_XY_occu_En_weighed;
  TH2F *Gen_pho_sep; 
  TH2F *Pho1_RechitE_vs_A_gen_E;
  TH2F *Pho1_UnclRechitE_vs_A_gen_E;
  TH2F *Pho1_ClusRechitE_vs_A_gen_E;
  TH2F *Pho2_RechitE_vs_A_gen_E;
  TH2F *Pho2_UnclRechitE_vs_A_gen_E;
  TH2F *Pho2_ClusRechitE_vs_A_gen_E;

};
#endif

#ifdef ANALYZEHGCMuons_cxx

void AnalyzeHGCMuons::BookHistogram(const char *outFileName)
{

  //  char hname[200], htit[200];
  //  double xlow = 0.0,  xhigh = 2000.0;
  //  int nbins = 2000;

  oFile = new TFile(outFileName, "recreate");
  oFile->cd();
  if (fillhist)
  { //Define histograms
    a_gen_mass = new TH1F("M_gen","Mass of gen A;M",100,0,2.5);
    a_gen_pt = new TH1F("A_gen_pT","A_gen_pT",100,0,120);
    a_gen_eta= new TH1F("A_gen_eta","A_gen_eta",100,-3.7,3.7);
    a_gen_phi = new TH1F("A_gen_phi","A_gen_phi",100,-4.5,4.5);
    a_gen_E = new TH1F( "A_gen_energy","A_gen_E",100,9,0);
    a_gen_gamma = new TH1F ("Lorentz boost of A","Lorentz boost of A",100,9,0);
    E_sublead_by_E_lead = new TH1F("Energy of sublead/Energy of lead","E_sublead/E_lead",100,0,2);
    pho1_EE_hit_eta =new TH1F("Photon1 EE rechit eta ","Pho1 EE hit eta",100,-3,3);
    pho2_EE_hit_eta = new TH1F("Photon2 EE rechit eta ","Pho2 EE hit eta",100,-3,3);
    pho1_hitX = new TH1F("Photon1 EE hits X","Phho1_hit_X",320,-160,1600);
    nGen = new TH1F("No. of gen photons","no. of gen photons",10,0,10);
    nreco = new TH1F("No. of reco photons","no. of reco photons",10,0,10);
    angle_240_260= new TH1F("240<=Ma<=260","240<=Ma<=260",100,9,0);
    angle_490_510= new TH1F("490<=Ma<=510","490<=Ma<=510",100,9,0);
    angle_740_760= new TH1F("740<=Ma<=760","740<=Ma<=760",100,9,0);
    angle_990_1010= new TH1F("990<=Ma<=1010","990<=Ma<=1010",100,9,0);
    r9_eta_1= new TH1F("R9 (1.44<= Eta <=1.57)","1.44<= Eta <=1.57",100,-0.5,1.5);
    r9_eta_2= new TH1F("R9 (1.57< Eta <2)","1.57< Eta <=2",100,-0.5,1.5);
    r9_eta_3=new TH1F("R9 2< Eta <=2.5","2< Eta <=2.5",100,-0.5,1.5);
    ES_L1_hits= new TH1F ("ES Layer 1 hits","ES_L1_hits",100,280,320);
    ES_L2_hits=new TH1F("ES Layer 2 hits","ES_L2_hits",100,280,320);
    ES_L1_L2_hits_En_weighed= new TH1F  ("ES Layers  hits weighed by rechit energy","ES_L1_L2_hits_en_weighed",100,280,320);
   // ES_L2_hits_En_weighed= new TH1F  ("ES Layer 2 hits weighed by rechit energy","ES_L2_hits_en_weighed",100,280,320);

    a_gen_mass_vs_pt = new TH2F ("A gen mass vs pt","Gen Mass vs pT",200,9,0,200,9,0);
    a_gen_eta_vs_phi = new TH2F ("A gen eta vs phi", "Eta vs Phi",100,9,0,100,9,0);
    angle_vs_gamma_Ma_240_260=new TH2F("Angle vs gamma (240<= Ma <=260)","240<= Ma <=260",100,9,0,100,9,0);
    angle_vs_gamma_Ma_490_510=new TH2F("Angle vs gamma (490<= Ma <=510)","490<= Ma <=510",100,9,0,100,9,0);
    angle_vs_gamma_Ma_740_760=new TH2F("Angle vs gamma (740<= Ma <=760)","740<= Ma <=760",100,9,0,100,9,0);
    angle_vs_gamma_Ma_990_1010=new TH2F("Angle vs gamma (990<= Ma <=1010)","990<= Ma <=1010",100,9,0,100,9,0);
    EE_XY_occupancy= new TH2F("EE_XY_occupancy","EE_XY_occupancy",126,-180,180,126,-180,180);
    EE_XY_occu_En_weighed=new TH2F("EE_XY_rechits_En_weighed","En_weighed_EE_rechits",126,-180,180,126,-180,180);
    Gen_pho_sep= new TH2F("Separation between gen photons","Separation between gen photons",9,0,9,9,0,9);
    Pho1_RechitE_vs_A_gen_E= new TH2F("Total rechit energy (photon1) vs Energy of A","Rechit_E_pho1 vs A_gen_E",100,9,0,100,9,0);
    Pho1_UnclRechitE_vs_A_gen_E= new TH2F("Total energy in unclustered rechits (photon1) vs energy of A","Unclustered_rechit_E_pho1 vs A_gen_E",100,0,1000,100,0,1000);
    Pho1_ClusRechitE_vs_A_gen_E=new TH2F("Total energy in clustered rechits (photon1) vs energy of A","Clustered_rechit_E_pho1 vs A_gen_E",100,0,1000,100,0,1000);
    Pho2_RechitE_vs_A_gen_E= new TH2F("Total rechit energy(photon2) vs Energy of A","Rechit_E_pho2 vs A_gen_E",100,0,1000,100,0,1000);
    Pho2_UnclRechitE_vs_A_gen_E= new TH2F("Total energy in unclustered rechits (photon2) vs energy of A","Unclustered_rechit_E_pho2 vs A_gen_E",100,0,1000,100,0,1000);
    Pho2_ClusRechitE_vs_A_gen_E=new TH2F("Total energy in clustered rechits (photon2) vs energy of A","Clustered_rechit_E_pho2 vs A_gen_E",100,0,1000,100,0,1000);

  }
  }

AnalyzeHGCMuons::AnalyzeHGCMuons(const TString &inputFileList, const char *outFileName, const char *dataset, const char *massP)
{
    TChain *tree = new TChain("nTuplelize/T");
  TChain *tree2;
  mass = string(massP);

  if (!FillChain(tree, tree2, inputFileList))
    {std::cerr << "Cannot get the tree " << std::endl;
  }
  else
  {
    std::cout << "Initiating analysis of dataset " << dataset << std::endl;
  }

  HGCNtupleVariables::Init(tree, tree2);

  BookHistogram(outFileName);
//cout<<massP<<endl;
  treeout = new TTree("fordrn", "ForDRN");
  treeout->Branch("Hit_X_Pho1", &M_HitX1);
  treeout->Branch("EEFlag1", &M_EEFlag1);
  treeout->Branch("EEFlag2", &M_EEFlag2);
  treeout->Branch("Hit_Y_Pho1", &M_HitY1);
  treeout->Branch("Hit_Z_Pho1", &M_HitZ1);
  treeout->Branch("Hit_Eta_Pho1", &M_HitEta1);
  treeout->Branch("Hit_Phi_Pho1", &M_HitPhi1);
  treeout->Branch("Hit_iEta_Pho1", &M_HitiEta1);
  treeout->Branch("Hit_iPhi_Pho1", &M_HitiPhi1);
  treeout->Branch("Hit_X_Pho2", &M_HitX2);
  treeout->Branch("Hit_Y_Pho2", &M_HitY2);
  treeout->Branch("Hit_Z_Pho2", &M_HitZ2);
  treeout->Branch("Hit_Eta_Pho2", &M_HitEta2);
  treeout->Branch("Hit_Phi_Pho2", &M_HitPhi2);
  treeout->Branch("Hit_iEta_Pho2", &M_HitiEta2);
  treeout->Branch("Hit_iPhi_Pho2", &M_HitiPhi2);
  treeout->Branch("RecHitEnPho1", &M_HitEn1);
  //treeout->Branch("RecHitETPho1", &M_HitET1);
  //treeout->Branch("RecHitEZPho1", &M_HitEZ1);
  treeout->Branch("RecHitEnPho2", &M_HitEn2);
  //treeout->Branch("RecHitETPho2", &M_HitET2);
  //treeout->Branch("RecHitEZPho2", &M_HitEZ2);
  treeout->Branch("A_Gen_mass", &M_m_gen);
  //treeout->Branch("p_gen", &M_p_gen);
  treeout->Branch("pt_gen", &M_pt_gen);
  treeout->Branch("A_Gen_pt", &M_eta_gen);
  treeout->Branch("A_Gen_phi", &M_phi_gen);
  treeout->Branch("Pho_SigIEIE",&M_SigIEIE1);
  //treeout->Branch("SigIEIEPho2",&M_SigIEIE2);
  treeout->Branch("R9_Pho1",&M_R9_Pho1);
  treeout->Branch("R9_Pho2",&M_R9_Pho2);
  treeout->Branch("Pho_SigIPhiIPhiPho",&M_SigIPhiIPhi1);
  //treeout->Branch("SigIPhiIPhiPho2",&M_SigIPhiIPhi2);

  treeout->Branch("Hit_ES_X_Pho1", &M_ES_HitX1);
  treeout->Branch("Hit_ES_Y_Pho1", &M_ES_HitY1);
  treeout->Branch("Hit_ES_Z_Pho1", &M_ES_HitZ1);
  treeout->Branch("Hit_ES_Eta_Pho1", &M_ES_HitEta1);
  treeout->Branch("Hit_ES_Phi_Pho1", &M_ES_HitPhi1);
  treeout->Branch("ES_RecHitEnPho1", &M_ES_HitEn1);
  treeout->Branch("Hit_ES_X_Pho2", &M_ES_HitX2);
  treeout->Branch("Hit_ES_Y_Pho2", &M_ES_HitY2);
  treeout->Branch("Hit_ES_Z_Pho2", &M_ES_HitZ2);
  treeout->Branch("Hit_ES_Eta_Pho2", &M_ES_HitEta2);
  treeout->Branch("Hit_ES_Phi_Pho2", &M_ES_HitPhi2);
  treeout->Branch("ES_RecHitEnPho2", &M_ES_HitEn2);
}

Bool_t AnalyzeHGCMuons::FillChain(TChain *chain, TChain *chain2, const TString &inputFileList)
{

  ifstream infile(inputFileList, ifstream::in);
  std::string buffer;

  if (!infile.is_open())
  {
    std::cerr << "** ERROR: Can't open '" << inputFileList << "' for input" << std::endl;
    return kFALSE;
  }

  std::cout << "TreeUtilities : FillChain " << std::endl;
  while (1)
  {
    infile >> buffer;
    if (!infile.good())
      break;
    // std::cout << "Adding tree from " << buffer.c_str() << std::endl;
    chain->Add(buffer.c_str());
    // chain2->Add(buffer.c_str());
  }
  std::cout << "No. of Entries in chain  : " << chain->GetEntries() << std::endl;
  // std::cout << "No. of Entries in chain2 : " << chain2->GetEntries() << std::endl;
  return kTRUE;
}

Long64_t AnalyzeHGCMuons::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain)
    return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0)
    return centry;
  if (!fChain->InheritsFrom(TChain::Class()))
    return centry;
  TChain *chain = (TChain *)fChain;
  if (chain->GetTreeNumber() != fCurrent)
  {
    fCurrent = chain->GetTreeNumber();
    //    Notify();
  }
  // Modified By Chirayu
  return centry;
  // End Modified

  if (!fChain2)
    return -5;
  Long64_t centry2 = fChain2->LoadTree(entry);
  if (centry2 < 0)
    return centry2;
  if (!fChain2->InheritsFrom(TChain::Class()))
    return centry2;
  TChain *chain2 = (TChain *)fChain2;
  if (chain2->GetTreeNumber() != fCurrent)
  {
    fCurrent = chain->GetTreeNumber();
    //    Notify();
  }

  if (centry == centry2)
    return centry;
  else
    return -1;
}
void AnalyzeHGCMuons::DrawHist(TH1F *hist1,string name, string x_title="", string y_title="")
{
string Name = name + ";" + x_title + ";" + y_title;
TCanvas *C= new TCanvas("C","C",1000,1000);
C->cd();
hist1->Draw("hist");
hist1->SetTitle(Name.c_str());
hist1->GetXaxis()->CenterTitle(true);
hist1->GetYaxis()->CenterTitle(true);
hist1->Write();
C->Update();
TPaveStats *st1 = (TPaveStats*)hist1->GetListOfFunctions()->FindObject("stats");	
st1->SetX1NDC(.77); st1->SetX2NDC(.9);st1->SetY1NDC(.9); st1->SetY2NDC(.77);
st1->Draw();
C->Modified();
C->Write();
C->SaveAs((name + string(".png")).c_str());
C->SaveAs((name + string(".pdf")).c_str());

}
void AnalyzeHGCMuons::DrawHistTXT(TH2F *hist1, string name, string x_title="", string y_title="")
{
string Name = name + ";" + x_title + ";" + y_title;
TCanvas *C1= new TCanvas (name.c_str(),"",1200,1000);
C1->SetRightMargin(0.15);
hist1->Draw("COLZ+TEXT");
hist1->SetTitle(Name.c_str());
hist1->GetXaxis()->CenterTitle(true);
hist1->GetYaxis()->CenterTitle(true);
C1->Update();
hist1->Write();
hist1->SetStats(0);
C1->Modified();
C1->Write();
C1->SaveAs((name + string(".png")).c_str());
C1->SaveAs((name + string(".pdf")).c_str());

}
void AnalyzeHGCMuons::DrawHist(TH2F *hist1, string name, string x_title="", string y_title="")
{
string Name = name + ";" + x_title + ";" + y_title;
TCanvas *C1= new TCanvas (name.c_str(),"",1200,1000);
C1->SetRightMargin(0.15);
hist1->Draw("COLZ");
hist1->SetTitle(Name.c_str());
hist1->GetXaxis()->CenterTitle(true);
hist1->GetYaxis()->CenterTitle(true);
hist1->Write();
C1->Modified();

C1->Update();
C1->Write();
C1->SaveAs((name + string(".png")).c_str());
C1->SaveAs((name + string(".pdf")).c_str());

}
void AnalyzeHGCMuons::DrawHistNoStat(TH2F *hist1, string name, string x_title="", string y_title="")
{
string Name = name + ";" + x_title + ";" + y_title;
TCanvas *C1= new TCanvas (name.c_str(),"",1200,1000);
C1->SetRightMargin(0.15);
hist1->Draw("COLZ");
hist1->SetTitle(Name.c_str());
hist1->GetXaxis()->CenterTitle(true);
hist1->GetYaxis()->CenterTitle(true);
C1->Update();
hist1->SetStats(0);
hist1->Write();
C1->Modified();

C1->Write();
C1->SaveAs((name + string(".png")).c_str());
C1->SaveAs((name + string(".pdf")).c_str());

}


void AnalyzeHGCMuons::graphSide(TH1F *hist1, TH1F *hist2, string name,string x_title="", string y_title="")
{
  TCanvas *c1 = new TCanvas(name.c_str(), "", 200, 10, 700, 500);
  c1->Divide(2, 1);
  c1->cd(1);
  hist1->Draw("colz");
  hist1->GetXaxis()->SetTitle(x_title.c_str());
  hist1->GetYaxis()->SetTitle(y_title.c_str());
  hist1->GetXaxis()->CenterTitle(true);
  hist1->GetYaxis()->CenterTitle(true);
  c1->cd(2);
  hist2->Draw("colz");
  hist2->GetXaxis()->SetTitle(x_title.c_str());
  hist2->GetYaxis()->SetTitle(y_title.c_str());
  hist2->GetXaxis()->CenterTitle(true);
  hist2->GetYaxis()->CenterTitle(true);
  c1->Update();
  c1->GetFrame()->SetBorderSize(12);
  c1->Modified();
  c1->Write();
  c1->SaveAs((name + string(".png")).c_str());
 c1->SaveAs((name + string(".pdf")).c_str());
}
void AnalyzeHGCMuons::graphSide(TH2F *hist1, TH2F *hist2, string name,string x_title, string y_title)
{
  TCanvas *c1 = new TCanvas(name.c_str(), "", 200, 10, 700, 500);
  c1->Divide(2, 1);
  c1->cd(1);
  hist1->Draw("colz");
  hist1->GetXaxis()->SetTitle(x_title.c_str());
  hist1->GetYaxis()->SetTitle(x_title.c_str());
  hist1->GetXaxis()->CenterTitle(true);
  hist1->GetYaxis()->CenterTitle(true);

  c1->cd(2);
  hist2->Draw("colz");
  hist1->GetXaxis()->SetTitle(x_title.c_str());
  hist1->GetYaxis()->SetTitle(x_title.c_str());
  hist1->GetXaxis()->CenterTitle(true);
  hist1->GetYaxis()->CenterTitle(true);

  c1->Update();
  c1->GetFrame()->SetBorderSize(12);
  c1->Modified();
  c1->Write();
  c1->SaveAs((name + string(".png")).c_str());
  c1->SaveAs((name + string(".png")).c_str());

}

void AnalyzeHGCMuons::graphOverlay(TH1F *hist1, TH1F *hist2, TH1F *hist4, TH1F *hist5, string name,string x_title="",string y_title="")
{ 
  string Name=name + ";"+ x_title + ";" + y_title;
  gStyle->SetOptStat(1111);
  THStack *hist3 = new THStack(name.c_str(), Name.c_str());
  hist1->SetLineColor(kRed);
  hist2->SetLineColor(kBlue);
  hist4->SetLineColor(kGreen);
  hist5->SetLineColor(kBlack);
  hist3->Add(hist1,"sames");
  hist3->Add(hist2,"sames");
  hist3->Add(hist4,"sames");
  hist3->Add(hist5,"sames");
  TCanvas *c3 = new TCanvas("c3", "c3", 1000, 1000);
  c3->cd();
  hist3->Draw("NOSTACK");
    hist3->Write();
  c3->Update();
  TPaveStats *st1 = (TPaveStats*)hist1->GetListOfFunctions()->FindObject("stats");	
  TPaveStats *st2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");	
  TPaveStats *st4 = (TPaveStats*)hist4->GetListOfFunctions()->FindObject("stats");	
  TPaveStats *st5 = (TPaveStats*)hist5->GetListOfFunctions()->FindObject("stats");	
st1->SetX1NDC(.7); st1->SetX2NDC(.9);st1->SetY1NDC(.7); st1->SetY2NDC(.6);
st2->SetX1NDC(.7); st2->SetX2NDC(.9);st2->SetY1NDC(.6); st2->SetY2NDC(.5);
st4->SetX1NDC(.7); st4->SetX2NDC(.9);st4->SetY1NDC(.5); st4->SetY2NDC(.4);
st5->SetX1NDC(.7); st5->SetX2NDC(.9);st5->SetY1NDC(.4); st5->SetY2NDC(.3);
st1->Draw();st2->Draw();
st4->Draw();st5->Draw();
  c3->Modified();
  c3->BuildLegend(0.7, 0.7, 0.9, 0.9, "");
  
  c3->Write();
 
  c3->SaveAs((name + string(".pdf")).c_str());
  c3->SaveAs((name + string(".png")).c_str());
}
void AnalyzeHGCMuons::graphOverlay(TH1F *hist1, TH1F *hist2, string name,string x_title ="",string y_title="")
{ 
  string Name =name + ";"+ x_title + ";" + y_title;
  gStyle->SetOptStat(1111);
  THStack *hist3 = new THStack(name.c_str(), name.c_str());
  hist1->SetLineColor(kRed);
  hist2->SetLineColor(kBlue);
  hist3->Add(hist1,"sames");
  hist3->Add(hist2,"sames");
   TCanvas *c3 = new TCanvas("c3", "c3", 1000, 1000);
 // c3->cd();
  hist3->Draw("NOSTACK");
  hist3->GetXaxis()->SetTitle(x_title.c_str());
  hist3->GetYaxis()->SetTitle(y_title.c_str());
   hist3->Write();
  c3->Update();
  TPaveStats *st1 = (TPaveStats*)hist1->GetListOfFunctions()->FindObject("stats");	
  TPaveStats *st2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");	
st1->SetX1NDC(.7); st1->SetX2NDC(.9);st1->SetY1NDC(.7); st1->SetY2NDC(.6);
st2->SetX1NDC(.7); st2->SetX2NDC(.9);st2->SetY1NDC(.6); st2->SetY2NDC(.5);
st1->Draw();st2->Draw();
  c3->Modified();
  c3->BuildLegend(0.7, 0.7, 0.9, 0.9, "");
 
  c3->Write();
 
  c3->SaveAs((name + string(".pdf")).c_str());
  c3->SaveAs((name + string(".png")).c_str());
}

void AnalyzeHGCMuons::graphOverlay(TH1F *hist1, TH1F *hist2, TH1F *hist4,  string name,string x_title="",string y_title="")
{
  string Name=name + ";"+ x_title + ";" + y_title;
   gStyle->SetOptStat(1111);
  //c3->cd();
  THStack *hist3 = new THStack(name.c_str(), Name.c_str());
  hist1->SetLineColor(kRed);
  hist2->SetLineColor(kBlue);
  hist4->SetLineColor(kGreen);
  
  hist3->Add(hist1,"sames");
  hist3->Add(hist2,"sames");
  hist3->Add(hist4,"sames");
  
  TCanvas *c3 = new TCanvas("c3", "c3", 1000, 1000);
  hist3->Draw("NOSTACK");
    hist3->Write();
  c3->Update();
  TPaveStats *st1 = (TPaveStats*)hist1->GetListOfFunctions()->FindObject("stats");	
  TPaveStats *st2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");	
  TPaveStats *st4 = (TPaveStats*)hist4->GetListOfFunctions()->FindObject("stats");	
  
st1->SetX1NDC(.7); st1->SetX2NDC(.9);st1->SetY1NDC(.7); st1->SetY2NDC(.6);
st2->SetX1NDC(.7); st2->SetX2NDC(.9);st2->SetY1NDC(.6); st1->SetY2NDC(.5);
st4->SetX1NDC(.7); st4->SetX2NDC(.9);st4->SetY1NDC(.5); st1->SetY2NDC(.4);

st1->Draw();st2->Draw();
st4->Draw();
  c3->Modified();
  c3->BuildLegend(0.7, 0.7, 0.9, 0.9, "");
  
  c3->Write();
 
  c3->SaveAs((name + string(".pdf")).c_str());
  c3->SaveAs((name + string(".png")).c_str());
}


void AnalyzeHGCMuons::graphHist(TH2F *hist, char title[], char name[])
{

  TCanvas *c1 = new TCanvas(name, title, 200, 10, 700, 500);
  TGraph *gr1 = new TGraph();
  for (int i = 0; i < hist->GetNbinsX(); i++)
  {
    for (int j = 0; j < hist->GetNbinsY(); j++)
    {
      double x = hist->GetXaxis()->GetBinCenter(i);
      double y = hist->GetYaxis()->GetBinCenter(j);
      gr1->SetPoint(gr1->GetN(), x, y);
    }
  }
  gr1->SetLineColor(2);
  gr1->SetLineWidth(4);
  gr1->SetMarkerStyle(0);
  gr1->SetTitle(title);
  gr1->GetXaxis()->SetTitle("Eta");
  gr1->GetYaxis()->SetTitle("Pt");
  gr1->Draw("ACP");
  gr1->Write(name);

  // TCanvas::Update() draws the frame, after which one can change it
  c1->Update();
  c1->GetFrame()->SetBorderSize(12);
  c1->Modified();
}
void DivideHistogramZValues(TH2F *hist, Double_t constant)
{
  Int_t nBinsX = hist->GetNbinsX();
  Int_t nBinsY = hist->GetNbinsY();

  // Iterate over each bin and divide the z-value by the constant
  for (Int_t i = 1; i <= nBinsX; i++)
  {
    for (Int_t j = 1; j <= nBinsY; j++)
    {
      Double_t binContent = hist->GetBinContent(i, j);
      Double_t newContent = binContent / constant;
      hist->SetBinContent(i, j, newContent);
    }
  }
}

AnalyzeHGCMuons::~AnalyzeHGCMuons()
{

  fillhist = 1;
  if (fillhist)
  {
/*
    TH1F *plotsToPrintTH1F[] = {
  a_gen_mass,
  a_gen_pt,
  a_gen_E,
  
  nGen,
  
  nreco,
   } ;
    TH1F *plotsToPrintTH1Flog[] = {};
    TH1F *plotsToPrintTH1Flog[] = {};

    TH1F *plotsSideBySideTH1F[][2] = {};
    TH1F *plotsOverlayTH1F[][2] = {};
    TH2F *plotsToPrintTH2F[] = {} ;
    TH2F *plotsSideBySideTH2F[][2] = {};
    TH2F *plotsOverlayTH2F[][2] = {};
    //DivideHistogramZValues(deta_dphi_gen, deta_dphi_gen->GetEntries());
    DivideHistogramZValues();
   
    TStyle *st1 = new TStyle("st1", "my style");
    st1->cd();
    st1->SetPaintTextFormat(".2f");
    st1->SetOptStat(111111);
    st1->SetFrameFillColor(10);
    st1->SetFillColor(10);
    st1->SetCanvasColor(10);

    for (auto i : plotsToPrintTH2F)
    {
      TCanvas *c3 = new TCanvas("c3", "c3", 1600, 1400);
      c3->SetLeftMargin(0.125);
      c3->cd();
      i->Draw("colz");
      i->Draw("colz");
      i->GetXaxis()->SetTitleSize(0.045);
      i->GetYaxis()->SetTitleSize(0.045);
      i->SetStats(0);
      c3->Update();
      c3->Modified();
      c3->Write(i->GetName());
      c3->SaveAs((string(i->GetName()) + string(".pdf")).c_str());
      c3->SaveAs((string(i->GetName()) + string(".png")).c_str());
    }
    for (auto i : plotsSideBySideTH2F)
    {
      auto p1 = i[0];
      auto p2 = i[1];
      string name = string(p1->GetName()) + "," + string(p2->GetName());
      graphSide(p1, p2, name);
    }
    for (auto i : plotsOverlayTH2F)
    {
      auto p1 = i[0];
      auto p2 = i[1];
      string name = string(p1->GetName()) + "+" + string(p2->GetName());
      graphOverlay(p1, p2, name);
    }
    for (auto i : plotsToPrintTH1F)
    {
      TCanvas *c3 = new TCanvas("c3", "c3", 1600, 1400);
      c3->cd();
  //c3->SetLogy();
      i->SetTitle((i->GetTitle()+string(" mass(MeV)=")+mass).c_str());
      cout<<i->GetTitle()<<endl;
      i->Draw("colz");
      c3->Update();
      c3->Modified();
      c3->Write(i->GetName());
      c3->SaveAs((string("0")+mass+string(i->GetName()) + string(".pdf")).c_str());
      c3->SaveAs((string("0")+mass+string(i->GetName()) + string(".png")).c_str());
    }
    for (auto i : plotsToPrintTH1Flog)
    {
      TCanvas *c3 = new TCanvas("c3", "c3", 1600, 1400);
      c3->cd();
  c3->SetLogy();
      i->SetTitle((i->GetTitle()+string(" mass(MeV)=")+mass).c_str());
      i->Draw("colz");
      c3->Update();
      c3->Modified();
      c3->Write(i->GetName());
      c3->SaveAs((string("0log")+mass+string(i->GetName()) + string(".pdf")).c_str());
      c3->SaveAs((string("0log")+mass+string(i->GetName()) + string(".png")).c_str());
    }
    for (auto i : plotsSideBySideTH1F)
    {
      auto p1 = i[0];
      auto p2 = i[1];
      string name = string(p1->GetName()) + "," + string(p2->GetName());
      graphSide(p1, p2, name);
    }
    for (auto i : plotsOverlayTH1F)
    {
      auto p1 = i[0];
      auto p2 = i[1];
      string name = string(p1->GetName()) + "+" + string(p2->GetName());
      graphOverlay(p1, p2, name);
    }
    */
  graphOverlay(angle_240_260,angle_490_510,angle_740_760,angle_990_1010,"Angle_between_gen_photons","Angle","");
  graphOverlay(ES_L1_hits,ES_L2_hits,"Number_of_ES_rechits","Absolute Z (in cm)","");
  //graphOverlay(ES_L1_hits_En_weighed,ES_L2_hits_En_weighed,"ES_hits_weighed_by_energy","Absolute Z coordinate (in cm)","");
  DrawHistNoStat(EE_XY_occupancy,"EE XY hits", "X in cm", "Y in cm");
  DrawHistNoStat(EE_XY_occu_En_weighed,"EE XY hits weighed by energy","X in cm","Y in cm");
  DrawHist(ES_L1_L2_hits_En_weighed,"ES_hits_weighed_by_energy","Absolute Z coordinate (in cm)","");
  DrawHistTXT(Gen_pho_sep,"Seperation between gen photons","#Delta #eta","#Delta #phi");
  DrawHist(Pho1_RechitE_vs_A_gen_E,"Photon1 total rechit energy vs energy of A","Energy of A","Total rechit energy");
  DrawHist(a_gen_mass,"Gen mass of A","Mass of A (in GeV)");
  DrawHist(a_gen_pt,"Gen pT of A","pT of A (in GeV)");
  DrawHist(a_gen_eta,"Gen eta of A","#eta");
  DrawHist(a_gen_phi,"Gen phi of A","#phi");
  DrawHist(a_gen_E,"Gen energy of A","A_gen_energy (in GeV)");
  DrawHist(a_gen_gamma,"Lorentz boost of A","Lorentz boost");
  DrawHistNoStat(a_gen_eta_vs_phi,"Gen #eta vs #phi of A","|#eta|","#phi");
  DrawHistNoStat(a_gen_mass_vs_pt,"Gen mass vs pT of A","Mass of A (in GeV)","pT of A (in GeV)");
 
 }


  // if (!fChain || !fChain2) return;
  if (!fChain)
    return;
  delete fChain->GetCurrentFile();
  // delete fChain2->GetCurrentFile();
  oFile->cd();
  oFile->Write();
  // fChain->CloneTree(-1,"");
  oFile->Close();
}

#endif
// TODO: Pt condition in dR matching (later), Plots vs mass using jupyter notebook, Publish , Write explainations( tomorrow)
