


#define Myanalysisclass_cxx
#include "Myanalysisclass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <string>
#include<TGraph.h>
void Myanalysisclass::Loop(const char *outFileName = "outputplot.root")
{
//   In a ROOT session, you can do:
//      root> .L Myanalysisclass.C
//      root> Myanalysisclass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

TFile *fout = new TFile(outFileName,"RECREATE");
   //A_gen quantities
   TH1D *M_Gen_A = new TH1D("Gen Mass of A (in GeV)", "Gen Mass of A (in GeV)", 200, 2, 0);
   TH1D *Eta_A_Gen = new TH1D("A_Gen_Eta", "A_Gen_Eta", 100, -3.5, 3.5);
   TH1D *Pt_A_Gen = new TH1D("A_Gen_pt (GeV)", "A_Gen_pt (GeV)", 100, 10, 5);
   TH1D *Energy_A_Gen = new TH1D("A_Gen_Energy (GeV)", "A_Gen_Energy (GeV)", 200,9, 0);
   
   //Photon energies
   TH2D *E_pho1_vs_E_pho2 = new TH2D("E_pho1_vs_E_pho2 (GeV)","E_pho1_vs_E_pho2 (GeV)", 100,9, 0,100,9,0);
   TH1D *E_pho1_by_E_pho2 = new TH1D("E_pho2_by_E_pho1(GeV)","E_pho2_by_E_pho1(GeV)", 100,9,0);
   TH1D *E_pho_reco_ratio = new TH1D("E_g_sublead_reco/E_g_lead_reco","E_g_sublead_reco/E_g_lead_reco",100,9,0);
   //Angle between two gen photons
   TH1F *Angle_vs_Ma_200 = new TH1F("Angle between two photons(200<M_a < 210MeV) and gamma <=10 ","Angle between two photons",100,9,0);
   TH2F *Angle_vs_gamma_Ma_200_210 = new TH2F("Angle between photons vs gamma (200<M_a<210)","Angle between photons vs gamma",100,9,0,100,9,0);
   TH1F *Angle_vs_Ma_400 = new TH1F("Angle between two photons(400<M_a<410MeV)","Angle between two photons",100,9,0);
   TH2F *Angle_vs_gamma_Ma_400_410 = new TH2F("Angle between photons vs gamma(400<M_a<410)","Angle between photons vs gamma",100,9,0,100,9,0);
   //1D Preshower hits
   TH1D *Pho1_ES_hitx = new TH1D("Pho1_ES_Hits_X","Pho1_ES_Hits_X", 100, 9,0);
   TH1D *Pho2_ES_hitx = new TH1D("Pho2_ES_Hits_X","Pho2_ES_Hits_X", 100, 9,0); 
   TH1D *Pho2_ES_hits_y= new TH1D("Pho2_ES_Hits_Y", "Pho2_ES_Hits_Y",100, 9,0);
   TH1D *Pho1_ES_hits_y= new TH1D("Pho1_ES_Hits_Y", "Pho1_ES_Hits_Y",100, 9,0);
   TH1D *Pho1_ES_hits_z=new TH1D("Pho1_ES_Hits_Z","Pho1_ES_Hits_Z",100,-315,315);
   TH1D *Pho2_ES_hits_z=new TH1D("Pho2_ES_Hits_Z","Pho2_ES_Hits_Z",100,-315,315);
   //1D Preshower hits with some threshold   
   TH1D *Pho1_ES_hitx_200 = new TH1D("Pho1_ES_Hits_X (E_rc > 200 MeV)","Rechit energy > 200 MeV", 100, 9,0);
   TH1D *Pho1_ES_hitx_400 = new TH1D("Pho1_ES_Hits_X (E_rc > 400 MeV)","Rechit energy > 400 MeV", 100, 9,0);
   TH1D *Pho1_ES_hit_y_200 = new TH1D("Pho1_ES_Hits_Y (E_rc > 200 MeV)","Rechit energy > 200 MeV", 100, 9,0);
   TH1D *Pho1_ES_hit_y_400 = new TH1D("Pho1_ES_Hits_Y (E_rc > 400 MeV)","Rechit energy > 400 MeV", 100, 9,0);
   TH1D *Pho2_ES_hitx_200 = new TH1D("Pho2_ES_Hits_X(E_rc > 200 MeV)","Rechit energy >200 MeV", 100, 9,0);
   TH1D *Pho2_ES_hitx_400 = new TH1D("Pho2_ES_Hits_X(E_rc > 400 MeV)","Rechit energy >400 MeV", 100, 9,0);
   //2D ES Rechit plots
   TH2F *Pho1_XY_ES_hits = new TH2F("Photon1 ES XY rechits", "Photon1 ES XY rechits", 1500,-150,150,1500,-150,150);
   TH2F *pho1_X_EE_hits_vs_R9 = new TH2F("Photon1 EE X rechits vs R9","Photon1 EE X rechits vs R9", 112, -160, 160, 100, 9,0);
   TH2F *pho1_Y_EE_hits_vs_R9 = new TH2F("Photon1 EE Y rechits vs R9","Photon1 EE Y rechits vs R9", 112, -160, 160, 100, 9,0);
   TH2F *pho1_X_ES_hits_vs_R9 = new TH2F("Photon1 ES X rechits vs R9","Photon1 ES X rechits vs R9", 1500, -150, 150, 100, 9,0);
   TH2F *pho1_Y_ES_hits_vs_R9 = new TH2F("Photon1 ES Y rechits vs R9","Photon1 ES Y rechits vs R9", 1500, -150, 150, 100, 9,0);
   TH2F *ES_XY_occupancy = new TH2F ("All X-Y rechits in ES", "All X-Y rechits in ES",400,-160,160,400,-160,160);
    //graphs
    auto *Pho1_ES_XYhit = new TGraph();
    auto *Pho1_XY_ES_hits_zoomed = new TGraph(0);
    auto *Pho1_XY_EE_hits_zoomed_1 = new TGraph();

   //1D EE Rechits plots
   TH1D *RechitE_Pho1_200 = new TH1D("Rechit energy with threshold 200MeV","Rechit energy with threshold 200MeV",200,9,0);
   TH1D *RechitE_Pho1_400 = new TH1D("Rechit energy with threshold 400MeV","Rechit energy with threshold 400MeV",200,9,0);
   TH1F *EE_X_hit_pho1 = new TH1F("Photon1 EE X hits with energy>200MeV","Photon1 EE X hits with energy>200MeV",200,9,0);
   TH1D *Pho1_EE_hits_eta = new TH1D("Photon1_EE_hits_eta","Photon1_EE_hits_eta", 100,-3,3);
   //2D EE Rechits plots
   TH2F *Pho1_XY_EE_hits = new TH2F ("photon1 EE XY rechits","photon1 EE XY rechits", 112,-160,160,112,-160,160);
   TH2F *Pho1_XY_EE_hits_zoomed = new TH2F("Photon 1 endcap XY rechits(50<x<60,50<y<60)","Photon 1 endcap XY rechits 17<x<60,17<y<60", 15, 17,60, 15,17,60);
   TH2F *Pho1_XY_EEhits = new TH2F ("Photon1 EE XY rechits","Photon1 EE XY rechits", 1600,-160,160,1600,-160,160);
   TH2F *pho1_EE_rechit_En_vs_eta = new TH2F("Photon1 EE rechit energy vs eta","Photon1 EE rechit energy vs eta",100,-3,3,100,0,9);
   TH2F *pho1_EE_hit_x_vs_eta = new TH2F("Photon1 EE hit x vs eta", "photon1 EE hit X vs eta", 200, -3,3,200,-160,160);
   TH2F *pho1_EE_radial_vs_eta = new TH2F("Photon1 EE radial hits vs eta","Photon1 EE radial hits vs eta",100,-3,3,100,0,180);
   TH2F *Endcap_XY_occupancy = new TH2F("X-Y rechits from all photons in EE", "All X-Y rechits in EE", 120,-160,160,120,-160,160);

   TH2F *nphotons_vs_eta = new TH2F("Number of reconstructed photons vs eta","No. photons vs eta", 100,-3,3,10,-1,10);

//################################################################################
   //rest of the code  
   Long64_t nentries = fChain->GetEntriesFast();
   int plus=0;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
     
      if(A_Gen_eta->at(0)>0){plus =plus+1;}
      else {plus = plus-1;}
      if(A_Gen_mass->size()>0){
      TLorentzVector V_A(0,0,0,0);
      V_A.SetPtEtaPhiM(A_Gen_pt->at(0),A_Gen_eta->at(0),A_Gen_phi->at(0),A_Gen_mass->at(0));
      M_Gen_A->Fill(A_Gen_mass->at(0));
      Pt_A_Gen->Fill(A_Gen_pt->at(0));
      Eta_A_Gen->Fill(A_Gen_eta->at(0));
      Energy_A_Gen->Fill(V_A.Energy());             
      
      float gamma = V_A.Energy()/A_Gen_mass->at(0);
      
      if (Pho_Gen_Eta->size()==2 && Pho_Gen_Phi->size()==2){
      TLorentzVector V_Gen_Pho1;
      TLorentzVector V_Gen_Pho2;
      V_Gen_Pho1.SetPtEtaPhiE(Pho_Gen_Pt->at(0),Pho_Gen_Eta->at(0),Pho_Gen_Phi->at(0),Pho_Gen_E->at(0));
      V_Gen_Pho2.SetPtEtaPhiE(Pho_Gen_Pt->at(1),Pho_Gen_Eta->at(1),Pho_Gen_Phi->at(1),Pho_Gen_E->at(1)); 
      
      float angle = V_Gen_Pho1.Angle(V_Gen_Pho2.Vect());
      
      if(A_Gen_mass->at(0)>=0.2 && A_Gen_mass->at(0)<=0.210){
	      Angle_vs_Ma_200->Fill(angle);
              Angle_vs_gamma_Ma_200_210->Fill(gamma,angle);}
      if(A_Gen_mass->at(0)>=0.4 && A_Gen_mass->at(0)<=0.410){
	      Angle_vs_Ma_400->Fill(angle);
              Angle_vs_gamma_Ma_400_410->Fill(gamma,angle);}

      double epho1_by_epho2;
      
      E_pho1_vs_E_pho2->Fill(Pho_Gen_E->at(0),Pho_Gen_E->at(1));
      if(Pho_Gen_E->at(1)<Pho_Gen_E->at(0)){    
       epho1_by_epho2 = Pho_Gen_E->at(1)/Pho_Gen_E->at(0);
      }
      else {
      epho1_by_epho2 = Pho_Gen_E->at(0)/Pho_Gen_E->at(1);
      }
       E_pho1_by_E_pho2->Fill(epho1_by_epho2);
      }
      else if( Pho_Gen_Eta->size()>0){
      TLorentzVector V_Gen_Pho1;
      V_Gen_Pho1.SetPtEtaPhiE(Pho_Gen_Pt->at(0),Pho_Gen_Eta->at(0),Pho_Gen_Phi->at(0),Pho_Gen_E->at(0));
      }
      if(energy->size()==2){ 
      double E_reco_pho_ratio;
      if(energy->at(0)<energy->at(1)){
       E_reco_pho_ratio = energy->at(0)/energy->at(1) ; }
      else if (energy->size()>0){
      E_reco_pho_ratio = energy->at(1)/energy->at(0) ;
      } 
      E_pho_reco_ratio->Fill(E_reco_pho_ratio);  
      }
     }
// ###### Rechit plots #################################################
    
     if (Hit_ES_X_Pho2->size()>0){
     int n = Hit_ES_X_Pho2->size();
     for (int i=0; i<n; i++){
     ES_XY_occupancy->Fill(Hit_ES_X_Pho2->at(i),Hit_ES_Y_Pho2->at(i));
     Pho2_ES_hitx->Fill(Hit_ES_X_Pho2->at(i));
     if(ES_RecHitEnPho2->at(i) >0.2){Pho2_ES_hitx_200->Fill(Hit_ES_X_Pho2->at(i));}
     if(ES_RecHitEnPho2->at(i) >0.4){Pho2_ES_hitx_400->Fill(Hit_ES_X_Pho2->at(i));}
     }
     }
     if (Hit_ES_X_Pho1->size()>0){
      int n = Hit_ES_X_Pho1->size();
     for (int i=0; i<n; i++){
      ES_XY_occupancy->Fill(Hit_ES_X_Pho1->at(i),Hit_ES_Y_Pho1->at(i));
     Pho1_ES_hitx->Fill(Hit_ES_X_Pho1->at(i));
     if(ES_RecHitEnPho1->at(i) >0.2){Pho1_ES_hitx_200->Fill(Hit_ES_X_Pho1->at(i));}
     if(ES_RecHitEnPho1->at(i) >0.4){Pho1_ES_hitx_400->Fill(Hit_ES_X_Pho1->at(i));}  
     }  
     }
     if (Hit_ES_Y_Pho2->size()>0){
     int n = Hit_ES_Y_Pho2->size();
     for (int i=0; i<n; i++){
     Pho2_ES_hits_y->Fill(Hit_ES_Y_Pho2->at(i));}
     }
     if (Hit_ES_Y_Pho1->size()>0){
     int n = Hit_ES_Y_Pho1->size();
     for (int i=0; i<n; i++){
     if(ES_RecHitEnPho1->at(i) >0.2){Pho1_ES_hit_y_200->Fill(Hit_ES_X_Pho1->at(i));}
     if(ES_RecHitEnPho1->at(i) >0.4){Pho1_ES_hit_y_400->Fill(Hit_ES_X_Pho1->at(i));} 
     Pho1_ES_hits_y->Fill(Hit_ES_Y_Pho1->at(i));}
     }
     if (Hit_ES_Z_Pho1->size()>0){
     int n = Hit_ES_Z_Pho1->size();
     for (int i=0; i<n; i++){
     Pho1_ES_hits_z->Fill(Hit_ES_Z_Pho1->at(i));}
     }
     if (Hit_ES_Z_Pho2->size()>0){
     int n = Hit_ES_Z_Pho2->size();
     for (int i=0; i<n; i++){
     Pho1_ES_hits_z->Fill(Hit_ES_Z_Pho2->at(i));}
     }
     if(RecHitEnPho1->size()>0){
	     for(int i=0; i<RecHitEnPho1->size();i++){if(RecHitEnPho1->at(i)>0.4){RechitE_Pho1_400->Fill(RecHitEnPho1->at(i));}
	    if(RecHitEnPho1->at(i)>0.2){RechitE_Pho1_200->Fill(RecHitEnPho1->at(i));}
	     }
     }
if(Hit_X_Pho1->size()>0){
for (int i =0; i< Hit_X_Pho1->size();i++){
Endcap_XY_occupancy->Fill(Hit_X_Pho1->at(i),Hit_Y_Pho1->at(i));
if(RecHitEnPho1->at(i)>0.2){
EE_X_hit_pho1->Fill(Hit_X_Pho1->at(i));
Pho1_EE_hits_eta->Fill(Hit_Eta_Pho1->at(i));
}
pho1_EE_rechit_En_vs_eta->Fill(Hit_Eta_Pho1->at(i),RecHitEnPho1->at(i));
float Radial = sqrt(Hit_Eta_Pho1->at(i)*Hit_Eta_Pho1->at(i) + Hit_Y_Pho1->at(i)*Hit_Y_Pho1->at(i));
pho1_EE_radial_vs_eta->Fill(Hit_Eta_Pho1->at(i),Radial);
pho1_EE_hit_x_vs_eta->Fill(Hit_Eta_Pho1->at(i), Hit_X_Pho1->at(i));
if(Pho_R9->size()>0){
      //Pho1_XY_EE_vs_R9->Fill(Hit_X_Pho1->at(i),Hit_Y_Pho1->at(i),Pho_R9->at(0));
        pho1_X_EE_hits_vs_R9->Fill(Pho_R9->at(0),Hit_X_Pho1->at(i));
        pho1_Y_EE_hits_vs_R9->Fill(Pho_R9->at(0),Hit_Y_Pho1->at(i));}
        if(Hit_X_Pho1->at(i)<=60 && Hit_X_Pho1->at(i)>=17 && Hit_Y_Pho1->at(i)<=60 && Hit_Y_Pho1->at(i)>=17){
        Pho1_XY_EE_hits_zoomed->Fill(Hit_X_Pho1->at(i),Hit_Y_Pho1->at(i));
        Pho1_XY_EE_hits_zoomed_1->AddPoint(Hit_X_Pho1->at(i),Hit_Y_Pho1->at(i));
        }                            
        }
}
if(Hit_X_Pho2->size()>0){for(int i =0; i<Hit_X_Pho2->size(); i++){
   Endcap_XY_occupancy->Fill(Hit_X_Pho2->at(i),Hit_Y_Pho2->at(i));
}}
 if(Hit_ES_X_Pho1->size()>0){
        for(int i =0; i<Hit_ES_X_Pho1->size(); i++){
        if(Hit_ES_X_Pho1->at(i)<=60 && Hit_ES_X_Pho1->at(i)>=17 && Hit_ES_Y_Pho1->at(i)<=60 && Hit_ES_Y_Pho1->at(i)>=17){
        Pho1_XY_ES_hits_zoomed->AddPoint(Hit_ES_X_Pho1->at(i),Hit_ES_Y_Pho1->at(i));
                }
        if(Pho_R9->size()>0){
      pho1_X_ES_hits_vs_R9->Fill(Pho_R9->at(0),Hit_ES_X_Pho1->at(i));
      pho1_Y_ES_hits_vs_R9->Fill(Pho_R9->at(0),Hit_ES_Y_Pho1->at(i));
      }
      Pho1_XY_ES_hits->Fill(Hit_ES_X_Pho1->at(i),Hit_ES_Y_Pho1->at(i));
      Pho1_ES_XYhit->AddPoint(Hit_ES_X_Pho1->at(i),Hit_ES_Y_Pho1->at(i));
             }
      }
      //nphotons_vs_eta->Fill(energy->size(),eta->at(0));
//Event displays

}

cout<<plus<<endl; 
/*###################################### Drawing and writing histograms ###############################################################*/

   TCanvas *c1 = new TCanvas("c1","c1", 600,500);
   M_Gen_A->SetLineColor(kBlue);
   M_Gen_A->GetXaxis()->SetTitle("mass of a (GeV)");
   M_Gen_A->GetXaxis()->CenterTitle(true);
   M_Gen_A->Draw();
  M_Gen_A->Write(); 
  // M_Gen_A_from_PP_hist->SetLineColor(kRed);
  //M_Gen_A_from_PP_hist->Draw("sames");
   
   /* TCanvas *c2 = new TCanvas ("C2","C2", 500, 500);
   M_A_reco_pho->SetTitle("mass of a from single reco photon");
   M_A_reco_pho->GetXaxis()->SetTitle("mass of a (GeV)");
   M_A_reco_pho->GetXaxis()->CenterTitle(true);
   M_A_reco_pho->Draw();
   */
   TCanvas *c3 = new TCanvas ("C3","C3",500, 500);
   E_pho_reco_ratio->SetTitle("E_g_reco_sublead by E_g_reco_lead");
   //E_pho_reco_ratio->GetXaxis()->SetTitle("mass of a (GeV)");
   //E_pho_reco_ratio->GetXaxis()->CenterTitle(true);
   E_pho_reco_ratio->Draw();
   E_pho_reco_ratio->Write();
   
   TCanvas *c4 = new TCanvas("C4","C4", 600, 500);
   Eta_A_Gen->SetTitle("A_Gen_Eta");
   Eta_A_Gen->GetXaxis()->SetTitle("Eta");
   Eta_A_Gen->GetXaxis()->CenterTitle(true);
   Eta_A_Gen->Draw();
   Eta_A_Gen->Write();
   TCanvas *c5 = new TCanvas("C5","C5", 600, 500);
   Pt_A_Gen->SetTitle("A_Gen_pt");
   Pt_A_Gen->GetXaxis()->SetTitle("pT (GeV)");
   Pt_A_Gen->GetXaxis()->CenterTitle(true);
   Pt_A_Gen ->Draw();
   Pt_A_Gen ->Write();
   
   TCanvas *c6 = new TCanvas("C6", "C6", 600, 500);
   Energy_A_Gen->SetTitle("A_Gen_energy");
   Energy_A_Gen->GetXaxis()->SetTitle("Energy (GeV)");
   Energy_A_Gen->GetXaxis()->CenterTitle(true);
   Energy_A_Gen->Draw();
   Energy_A_Gen->Write();

   TCanvas *c7 = new TCanvas("C7", "C7", 600, 500);
    E_pho1_vs_E_pho2->SetTitle("E_Pho_1 vs E_Pho_2");
   E_pho1_vs_E_pho2->GetXaxis()->SetTitle("Energy of photon 1 (GeV)");
   E_pho1_vs_E_pho2->GetXaxis()->CenterTitle(true);
    E_pho1_vs_E_pho2->GetYaxis()->SetTitle("Energy of photon 2 (GeV)");
   E_pho1_vs_E_pho2->GetYaxis()->CenterTitle(true);
   E_pho1_vs_E_pho2->Draw("colz");
   E_pho1_vs_E_pho2->Write();
 
   TCanvas *c8 = new TCanvas("C8", "C8", 600, 500);
   E_pho1_by_E_pho2->SetTitle("E_Pho_2/E_Pho_1");
   E_pho1_by_E_pho2->GetXaxis()->SetTitle("Energy ratio photon 2 to photon 1");
   E_pho1_by_E_pho2->GetXaxis()->CenterTitle(true);
   E_pho1_by_E_pho2->Draw();
   E_pho1_by_E_pho2->Write();
   
   TCanvas *c9 = new TCanvas("C9", "C9", 600, 500);
   
   Pho1_ES_hitx->Draw();
   Pho2_ES_hitx->SetLineColor(kRed);
   Pho2_ES_hitx->Draw("sames");
   Pho2_ES_hitx->Write();

   TCanvas *c10 = new TCanvas("Pho_ES_hits_Y", "Pho_ES_hits_Y", 600, 500);
   
   Pho1_ES_hits_y->Draw();
   Pho2_ES_hits_y->SetLineColor(kRed);
   Pho2_ES_hits_y->Draw("sames");
   Pho2_ES_hits_y->Write();
  
   TCanvas *c11 = new TCanvas ("Pho_ES_hits_Z","Pho_ES_Hits_Z", 600, 500);
   Pho1_ES_hits_z->SetTitle("Pho_ES_Hits_z");
   Pho1_ES_hits_z->GetXaxis()->SetTitle("z coordinate");
   Pho1_ES_hits_z->GetXaxis()->CenterTitle(true);
   Pho1_ES_hits_z->Draw();
   Pho1_ES_hits_z->Write();
   Pho2_ES_hits_z->SetLineColor(kRed);
   Pho2_ES_hits_z->Draw("sames");
   Pho2_ES_hits_z->Write();

TCanvas *c12 = new TCanvas("C1","C1", 900,900);
gStyle->SetGridStyle(1);
Pho1_XY_EE_hits->GetXaxis()->SetNdivisions(-105);
Pho1_XY_EE_hits->GetYaxis()->SetNdivisions(-105);
Pho1_XY_EE_hits->Draw("colz");
Pho1_ES_XYhit->SetMarkerStyle(1);
Pho1_ES_XYhit->Draw("Psame");
Pho1_ES_XYhit->Write();

TCanvas *c13= new TCanvas("photon1 ES rechits","photon1 ES rechits", 900, 900);
Pho1_XY_ES_hits->GetXaxis()->SetTitle("X (in cm)");
Pho1_XY_ES_hits->GetYaxis()->SetTitle("Y (in cm)");
Pho1_XY_ES_hits->Draw("colz");
Pho1_XY_ES_hits->Write();
TCanvas *c2 = new TCanvas("photon1 EE XY rechits zoomed","photon1 EE XY rechits zoomed", 900,900);
gStyle->SetGridStyle(1);
Pho1_XY_EE_hits_zoomed->GetXaxis()->SetNdivisions(-15);
Pho1_XY_EE_hits_zoomed->GetYaxis()->SetNdivisions(-15);
Pho1_XY_EE_hits_zoomed->GetXaxis()->SetTitle("X (in cm)");
Pho1_XY_EE_hits_zoomed->GetYaxis()->SetTitle("Y (in cm)");
Pho1_XY_EE_hits_zoomed->GetXaxis()->SetMaxDigits(3);
Pho1_XY_EE_hits_zoomed->GetYaxis()->SetMaxDigits(3);
Pho1_XY_EE_hits_zoomed->Draw("colz");
Pho1_XY_EE_hits_zoomed->Write();
Pho1_XY_ES_hits_zoomed->SetMarkerStyle(33);
Pho1_XY_ES_hits_zoomed->SetMarkerColorAlpha(kGreen, 0.35);
Pho1_XY_ES_hits_zoomed->Draw("Psame");
c2->SetGrid();
Pho1_XY_ES_hits_zoomed->Write();

TCanvas *c14 = new TCanvas("c3","c3", 900,900);

Pho1_XY_EE_hits_zoomed_1->Draw("AP");
Pho1_XY_EE_hits_zoomed_1->Write();
Pho1_XY_EE_hits_zoomed_1->GetXaxis()->SetTitle("X (in cm)");
Pho1_XY_EE_hits_zoomed_1->GetYaxis()->SetTitle("Y (in cm)");
Pho1_XY_ES_hits_zoomed->SetMarkerStyle(33);
Pho1_XY_ES_hits_zoomed->SetTitle("Photon1 ES XY rechits zoomed");
Pho1_XY_ES_hits_zoomed->SetMarkerColorAlpha(kGreen, 0.35);
Pho1_XY_ES_hits_zoomed->Draw("Psame");
Pho1_XY_ES_hits_zoomed->Write();
c3->SetGrid();
c3->BuildLegend();

TCanvas *c15 = new TCanvas ("c5","c5",900,900);
Pho1_XY_EEhits->Draw("colz");
Pho1_XY_EEhits->GetXaxis()->SetTitle("X (in cm)");
Pho1_XY_EEhits->GetYaxis()->SetTitle("Y (in cm)");
Pho1_XY_ES_hits->Draw("colzsame");


TCanvas *c16 = new TCanvas("c6","c6",900,900);
pho1_X_EE_hits_vs_R9->GetXaxis()->SetTitle("R9");
pho1_X_EE_hits_vs_R9->GetYaxis()->SetTitle("X (in cm)");
pho1_X_EE_hits_vs_R9->Draw("colz");
pho1_X_EE_hits_vs_R9->Write();

TCanvas *c17 = new TCanvas("c7","c7",900,900);
pho1_Y_EE_hits_vs_R9->GetXaxis()->SetTitle("R9");
pho1_Y_EE_hits_vs_R9->GetYaxis()->SetTitle("Y (in cm)");
pho1_Y_EE_hits_vs_R9->Draw("colz");

//#############################################################################################################
Angle_vs_gamma_Ma_200_210->GetXaxis()->SetTitle("Lorrentz boost");
Angle_vs_gamma_Ma_200_210->GetYaxis()->SetTitle("Angle between photons");

pho1_EE_hit_x_vs_eta->GetYaxis()->SetTitle("X (in cm)");
pho1_EE_hit_x_vs_eta->GetXaxis()->SetTitle("Eta");
Pho1_XY_EE_hits_zoomed_1->SetMarkerStyle(8);
Pho1_XY_EE_hits_zoomed_1->SetTitle("Photon1 EE XY rechits zoomed");
Pho1_XY_EE_hits_zoomed_1->GetXaxis()->SetNdivisions(-4);
Pho1_XY_EE_hits_zoomed_1->GetYaxis()->SetNdivisions(-4);

Endcap_XY_occupancy->GetYaxis()->SetTitle("Y (in cm)");
Endcap_XY_occupancy->GetXaxis()->SetTitle("X (in cm)");
ES_XY_occupancy->GetYaxis()->SetTitle("Y (in cm)");
ES_XY_occupancy->GetXaxis()->SetTitle("X (in cm)");

Pho1_ES_hit_y_200->GetXaxis()->SetTitle("Y (in cm)");
Pho1_ES_hit_y_400->GetXaxis()->SetTitle("Y (in cm)");

RechitE_Pho1_400->GetXaxis()->SetTitle("Rechit energy(in GeV)");
RechitE_Pho1_200->GetXaxis()->SetTitle("Rechit energy(in GeV)");

Pho1_ES_hitx_200->GetXaxis()->SetTitle("X (in cm)");
Pho1_ES_hitx_400->GetXaxis()->SetTitle("X (in cm)");
Pho2_ES_hitx_200->GetXaxis()->SetTitle("X (in cm)");
Pho2_ES_hitx_400->GetXaxis()->SetTitle("X (in cm)");

pho1_Y_ES_hits_vs_R9->GetYaxis()->SetTitle("Y (in cm)");
pho1_Y_ES_hits_vs_R9->GetXaxis()->SetTitle("R9");
pho1_X_ES_hits_vs_R9->GetXaxis()->SetTitle("R9");
pho1_X_ES_hits_vs_R9->GetYaxis()->SetTitle("X (in cm)");

Pho1_ES_hits_y->SetTitle("Pho_ES_Hits_Y");
Pho1_ES_hits_y->GetXaxis()->SetTitle("Y coordinate");
Pho1_ES_hits_y->GetXaxis()->CenterTitle(true);
Pho1_ES_hitx->SetTitle("Pho_ES_Hits_X");
Pho1_ES_hitx->GetXaxis()->SetTitle("X coordinate");
Pho1_ES_hitx->GetXaxis()->CenterTitle(true);

pho1_EE_rechit_En_vs_eta->GetXaxis()->SetTitle("Eta");
pho1_EE_rechit_En_vs_eta->GetYaxis()->SetTitle("Rechit energy");

nphotons_vs_eta->GetXaxis()->SetTitle("Eta");
nphotons_vs_eta->GetYaxis()->SetTitle("Number of reconstructed photons");
//#############################################################################################################################
EE_X_hit_pho1->Write();
RechitE_Pho1_200->Write();
RechitE_Pho1_400->Write();

pho1_EE_rechit_En_vs_eta->Write();
Pho1_EE_hits_eta->Write();
pho1_EE_hit_x_vs_eta->Write();
pho1_EE_radial_vs_eta->Write();


Endcap_XY_occupancy->Rebin2D();
Endcap_XY_occupancy->Write();
ES_XY_occupancy->Rebin2D();
ES_XY_occupancy->Write();

pho1_Y_ES_hits_vs_R9->Write();
pho1_X_ES_hits_vs_R9->Write();

Pho1_ES_hitx_200->Write();
Pho1_ES_hitx_400->Write();
Pho2_ES_hitx_200->Write();
Pho2_ES_hitx_400->Write();
Pho1_ES_hit_y_200->Write();
Pho1_ES_hit_y_400->Write();
Pho1_XY_ES_hits->Write();

Angle_vs_Ma_200->Write();
Angle_vs_Ma_400->Write();
Angle_vs_gamma_Ma_200_210->Write();


pho1_Y_EE_hits_vs_R9->Write();

nphotons_vs_eta->Write();

//######################################################################################
TCanvas *c19 = new TCanvas("c9","c9",900,900);
pho1_Y_ES_hits_vs_R9->Draw("colz");
c19->SaveAs("Pho1_ES_Y_hits_vs_R9.png");

TCanvas *c20 = new TCanvas("c20","c20",900,900);
ES_XY_occupancy->Draw("colz");
c20->SaveAs("ES_XY_occupancy.png");

TCanvas *c18 = new TCanvas("c8","c8",900,900);
pho1_X_ES_hits_vs_R9->Draw("colz");
c18->SaveAs("Pho1_ES_X_hits_vs_R9.png");

fout->Write();
fout->Close();
}

