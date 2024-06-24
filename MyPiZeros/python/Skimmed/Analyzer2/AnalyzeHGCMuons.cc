#define ANALYZEHGCMuons_cxx

#include "AnalyzeHGCMuons.h"
#include "TLorentzVector.h"
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
int ctr = 0;
float genMass;
float genAngle;
int main(int argc, char *argv[]) {

  if (argc < 2) {
    cerr << "Please give 3 arguments "
         << "runList "
         << " "
         << "outputFileName"
         << " "
         << "dataset" << endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName = argv[2];
  const char *data = argv[3];
  const char *massP = argv[4];

  cout<<massP<<endl;
  AnalyzeHGCMuons hgcmuons(inputFileList, outFileName, data,massP);
  // cout << "dataset " << data << " " << endl;

  hgcmuons.EventLoop(data);

  return 0;
}

double DeltaPhi(double phi1, double phi2) {
  double result = phi1 - phi2;
  while (result > M_PI)
    result -= 2 * M_PI;
  while (result <= -M_PI)
    result += 2 * M_PI;
  return result;
}
double DeltaEta(double eta1, double eta2){
double result= abs(eta1-eta2);
return result;
}
double DeltaR(double eta1, double phi1, double eta2, double phi2) {
  double deta = eta1 - eta2;
  double dphi = DeltaPhi(phi1, phi2);
  return std::sqrt(deta * deta + dphi * dphi);
}
void AnalyzeHGCMuons::EventLoop(const char *data) {
  if (fChain == 0)
    return;

  TLorentzVector p1gen, p2gen, pAgen;
  TLorentzVector p1reco, p2reco,pTreco;
  Long64_t nentries = fChain->GetEntriesFast();
 
  Long64_t nbytes = 0, nb = 0;
  Long64_t nbytes2 = 0, nb2 = 0;
  int decade = 0;

  for (Long64_t jentry = 0; jentry < nentries; jentry++) {

  
    // ==============print number of events done == == == == == == == =
    double progress = 10.0 * jentry / (1.0 * nentries);
    int k = int(progress);
    if (k > decade)
      // cout << 10 * k << " %" << endl;
      decade = k;

    // ===============read this entry == == == == == == == == == == ==
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;

    
    fillhist = 0;
    
	if(Pho_Gen_Pt->size() <2)
	  {
		continue;
	  }
        
        p1gen.SetPtEtaPhiE(Pho_Gen_Pt->at(0), Pho_Gen_Eta->at(0),Pho_Gen_Phi->at(0), Pho_Gen_E->at(0));
	p2gen.SetPtEtaPhiE(Pho_Gen_Pt->at(1), Pho_Gen_Eta->at(1),Pho_Gen_Phi->at(1), Pho_Gen_E->at(1));
        pAgen.SetPtEtaPhiM(A_Gen_pt->at(0), A_Gen_eta->at(0), A_Gen_phi->at(0), A_Gen_mass->at(0));
        //Defining gen quantities
        genMass = A_Gen_mass->at(0);
        genAngle = p1gen.Angle(p2gen.Vect());
        float genEnergy = pAgen.Energy();
        float AgenPt = A_Gen_pt->at(0);
        float AgenEta = A_Gen_eta->at(0);
        float AgenPhi = A_Gen_phi->at(0);
         float gamma= pAgen.Gamma();
	float deta=DeltaEta(Pho_Gen_Eta->at(1),Pho_Gen_Eta->at(0));
        float dphi= DeltaPhi(Pho_Gen_Phi->at(1),Pho_Gen_Phi->at(0));
        
	a_gen_gamma->Fill(gamma);
	nGen->Fill(Pho_Gen_Pt->size());
	nreco->Fill(pt->size());
        Gen_pho_sep->Fill(deta/0.05,dphi/0.05);
             
  double Ez = sqrt(pAgen.E()*pAgen.E() - pAgen.Et()*pAgen.Et());
  
 
  a_gen_mass->Fill(genMass);
  a_gen_pt->Fill(AgenPt);
  a_gen_eta->Fill(AgenEta);
  a_gen_phi->Fill(AgenPhi);
  a_gen_E->Fill(genEnergy);
  a_gen_mass_vs_pt->Fill(genMass,AgenPt);
  a_gen_eta_vs_phi->Fill(abs(AgenEta),AgenPhi);
  
  if(genMass>=0.24 && genMass<=0.26){
   angle_240_260->Fill(genAngle);
   angle_vs_gamma_Ma_240_260->Fill(gamma,genAngle);}
  if(genMass >=0.49 && genMass<=0.51){
   angle_490_510->Fill(genAngle);
   angle_vs_gamma_Ma_490_510->Fill(gamma,genAngle);}
  if (genMass>=0.74 && genMass<=0.76){
   angle_740_760->Fill(genAngle); 
   angle_vs_gamma_Ma_740_760->Fill(gamma,genAngle);}
  if(genMass>=0.99 && genMass<=1.01) {
   angle_990_1010->Fill(genAngle);
   angle_vs_gamma_Ma_990_1010->Fill(gamma,genAngle);}
  for (int i=0;i<eta->size();i++){
    if(1.44<=eta->at(i) && eta->at(i)<=1.57){r9_eta_1->Fill(Pho_R9->at(i));}
    if(1.57< eta->at(i) && eta->at(i)<=2){r9_eta_2->Fill(Pho_R9->at(i));}
    if(2< eta->at(i) && eta->at(i)<=2.5){r9_eta_3->Fill(Pho_R9->at(i));}
  }
float TotalRecE=0;
float TotalUncRecE=0;
float TotalCluRecE=0;

for(int i =0;i<Hit_X_Pho1->size();i++){
EE_XY_occupancy->Fill(Hit_X_Pho1->at(i),Hit_Y_Pho1->at(i));
EE_XY_occu_En_weighed->Fill(Hit_X_Pho1->at(i),Hit_Y_Pho1->at(i),RecHitEnPho1->at(i));
TotalRecE= TotalRecE +RecHitEnPho1->at(i);
if (RecHitFracPho1 <0){ TotalUncRecE = TotalUncRecE + RecHitEnPho1->at(i); }
else {TotalCluRecE= TotalCluRecE + RecHitEnPho1->at(i);} 
}
Pho1_RechitE_vs_A_gen_E->Fill(genEnergy,TotalRecE);
Pho1_UnclRechitE_vs_A_gen_E->Fill(genEnergy,TotalUncRecE);
Pho1_ClusRechitE_vs_A_gen_E->Fill(genEnergy,TotalCluRecE);

TotalRecE=0;
TotalUncRecE=0;
TotalCluRecE=0;

for(int i =0;i<Hit_X_Pho2->size();i++){
EE_XY_occupancy->Fill(Hit_X_Pho2->at(i),Hit_Y_Pho2->at(i));
EE_XY_occu_En_weighed->Fill(Hit_X_Pho2->at(i),Hit_Y_Pho2->at(i),RecHitEnPho2->at(i));
TotalRecE = TotalRecE + RecHitEnPho2->at(i);
if(RecHitFracPho2 <0){TotalUncRecE = TotalUncRecE + RecHitEnPho2->at(i) ;}
else {TotalCluRecE = TotalCluRecE + RecHitEnPho2->at(i);}
}
Pho2_RechitE_vs_A_gen_E->Fill(genEnergy,TotalRecE);
Pho2_UnclRechitE_vs_A_gen_E->Fill(genEnergy,TotalUncRecE);
Pho2_ClusRechitE_vs_A_gen_E->Fill(genEnergy,TotalCluRecE);

for(int i=0;i< Hit_ES_Z_Pho1->size();i++){
   ES_L1_L2_hits_En_weighed->Fill(abs(Hit_ES_Z_Pho1->at(i)),ES_RecHitEnPho1->at(i));
  if(308<=abs(Hit_ES_Z_Pho1->at(i))&& abs(Hit_ES_Z_Pho1->at(i))<=309){
    ES_L2_hits->Fill(abs(Hit_ES_Z_Pho1->at(i)));
   // ES_L2_hits_En_weighed->Fill(abs(Hit_ES_Z_Pho1->at(i)),ES_RecHitEnPho1->at(i));
  }
  if(303<=abs(Hit_ES_Z_Pho1->at(i)) && abs(Hit_ES_Z_Pho1->at(i)) <=304){
    ES_L1_hits->Fill(abs(Hit_ES_Z_Pho1->at(i)));
    // ES_L1_hits_En_weighed->Fill(abs(Hit_ES_Z_Pho1->at(i)),ES_RecHitEnPho1->at(i));
}
}
for(int j=0;j< Hit_ES_Z_Pho2->size();j++){
   ES_L1_L2_hits_En_weighed->Fill(abs(Hit_ES_Z_Pho2->at(j)),ES_RecHitEnPho2->at(j));
  if(308<=abs(Hit_ES_Z_Pho2->at(j)) && abs(Hit_ES_Z_Pho2->at(j))<=309){
    ES_L2_hits->Fill(Hit_ES_Z_Pho2->at(j));
   // ES_L2_hits_En_weighed->Fill(abs(Hit_ES_Z_Pho2->at(j)),ES_RecHitEnPho2->at(j));
  }
  if(303<=abs(Hit_ES_Z_Pho2->at(j)) && abs(Hit_ES_Z_Pho2->at(j)) <=304){
    ES_L1_hits->Fill(abs(Hit_ES_Z_Pho2->at(j)));
// ES_L1_hits_En_weighed->Fill(abs(Hit_ES_Z_Pho2->at(j)),ES_RecHitEnPho2->at(j));
}
}
 }
 
}
