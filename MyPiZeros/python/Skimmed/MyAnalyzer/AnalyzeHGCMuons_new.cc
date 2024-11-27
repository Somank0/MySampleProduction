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
double DeltaX(double x1, double x2){
  double result = abs(x1 - x2);
  return result;
}
double DeltaL(double x1, double x2, double y1, double y2){
  double dx = x1-x2;
  double dy = y1-y2;
  double result = sqrt(dx*dx + dy*dy);
  return result;
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
       cout << 10 * k << " %" << endl;
      decade = k;

    // ===============read this entry == == == == == == == == == == ==
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;

    
    fillhist = 0;
        pAgen.SetPtEtaPhiM(A_Gen_pt->at(0), A_Gen_eta->at(0), A_Gen_phi->at(0), A_Gen_mass->at(0));

	if(Pho_Gen_Pt->size() <2)
	  {
		continue;
	  }
        
        p1gen.SetPtEtaPhiE(Pho_Gen_Pt->at(0), Pho_Gen_Eta->at(0),Pho_Gen_Phi->at(0), Pho_Gen_E->at(0));
	p2gen.SetPtEtaPhiE(Pho_Gen_Pt->at(1), Pho_Gen_Eta->at(1),Pho_Gen_Phi->at(1), Pho_Gen_E->at(1));
        //Defining gen quantities
        genMass = A_Gen_mass->at(0);
        genAngle = p1gen.Angle(p2gen.Vect());
        float genEnergy = pAgen.Energy();
        float AgenPt = A_Gen_pt->at(0);
        float AgenEta = A_Gen_eta->at(0);
        float AgenPhi = A_Gen_phi->at(0);
         float gamma= pAgen.Gamma();
         float eta1 = p1gen.Eta();
         float eta2 = p2gen.Eta();
         float phi1 = p1gen.Phi();
         float phi2 = p2gen.Phi();
         float pt1 = p1gen.Pt();
         float pt2 = p2gen.Pt();
         float Epho1 = p1gen.Energy();
         float Epho2 = p2gen.Energy();
	float deta=DeltaEta(Pho_Gen_Eta->at(1),Pho_Gen_Eta->at(0));
        float dphi= DeltaPhi(Pho_Gen_Phi->at(1),Pho_Gen_Phi->at(0));
        float dx = DeltaEta(p1gen.X(),p2gen.X());
        float dy = DeltaEta(p1gen.Y(),p2gen.Y());
        
	a_gen_gamma->Fill(gamma);
	nGen->Fill(Pho_Gen_Pt->size());
  pho1_gen_eta->Fill(eta1);
  pho1_gen_phi->Fill(phi1);
  pho1_gen_pt->Fill(pt1);
  pho2_gen_eta->Fill(eta2);
  pho2_gen_phi->Fill(phi2);
  pho2_gen_pt->Fill(pt2);
  pho1_gen_E->Fill(Epho1);
  pho2_gen_E->Fill(Epho2);
	nreco->Fill(pt->size());
        Gen_pho_sep->Fill(deta/0.05,dphi/0.05);
  E_pho1_vs_E_pho2->Fill(Epho1, Epho2);
if(pt1>=pt2){E_sublead_by_E_lead->Fill(Epho2/Epho1);}
else{E_sublead_by_E_lead->Fill(Epho1/Epho2);}
E_pho2_by_E_pho1->Fill(Epho2/Epho1);
             
  double Ez = sqrt(pAgen.E()*pAgen.E() - pAgen.Et()*pAgen.Et());
   
  gen_dR->Fill(deta/0.05, dphi/0.05);
  if(AgenPt >=20 && AgenPt<50){gen_dR_pt_20_50->Fill(deta/0.05,dphi/0.05);}
  if(AgenPt >=50 && AgenPt<80){gen_dR_pt_50_80->Fill(deta/0.05,dphi/0.05);}
  if(AgenPt >=80 && AgenPt<=100){gen_dR_pt_80_100->Fill(deta/0.05,dphi/0.05);}
  if(genMass>=0.08 && genMass<=0.12){gen_dR_ma_100->Fill(deta/0.05,dphi/0.05);}
  if (genMass>=0.18 && genMass<=0.22){gen_dR_ma_200->Fill(deta/0.05,dphi/0.05);}
  if (genMass>=0.38 && genMass<=0.42){gen_dR_ma_400->Fill(deta/0.05,dphi/0.05);}
  if (genMass>=0.58 && genMass<=0.62){gen_dR_ma_600->Fill(deta/0.05,dphi/0.05);}
  if (genMass>=0.78 && genMass<=0.82){gen_dR_ma_800->Fill(deta/0.05,dphi/0.05);}
  if (genMass>=0.98 && genMass<=1.02){gen_dR_ma_1000->Fill(deta/0.05,dphi/0.05);}
  if (genMass>=1.58 && genMass<=1.62){gen_dR_ma_1600->Fill(deta/0.05,dphi/0.05);}
  if (genMass>=1.78 && genMass<=1.82){gen_dR_ma_1800->Fill(deta/0.05,dphi/0.05);}

  dX->Fill(dx);
  dY->Fill(dy);
  d_Eta->Fill(deta);
  d_Phi->Fill(dphi);
  gen_dR_XY->Fill(dx/2.86,dy/2.86);
 
  a_gen_mass->Fill(genMass);
  a_gen_pt->Fill(AgenPt);
  a_gen_eta->Fill(AgenEta);
  a_gen_phi->Fill(AgenPhi);
  a_gen_E->Fill(genEnergy);
  a_gen_mass_vs_pt->Fill(genMass,AgenPt);
  a_gen_eta_vs_phi->Fill(abs(AgenEta),AgenPhi);
  gen_eta1_vs_eta2->Fill(eta1,eta2);
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


float P1TotalRecE=0;
float P1TotalUncRecE=0;
float P1TotalUncRecE0p2=0;
float P1TotUnc_E_noise_cut=0;
float P1TotalCluRecE=0;
float P2TotalRecE=0;
float P2TotalUncRecE=0;
float P2TotalUncRecE0p2=0;
float P2TotalCluRecE=0;
float P2TotUnc_E_noise_cut=0;

if(pt->size()>0){
reco_pho1_pt->Fill(pt->at(0)); reco_pho1_eta->Fill(eta->at(0));
if(pt->size()>1){ reco_pho2_pt->Fill(pt->at(1)); reco_pho2_eta->Fill(eta->at(1)); }
}
int clu_hit_pho1=0;
int unc_hit_pho1=0;
int clu_hit_pho2=0;
int unc_hit_pho2=0;

N_supcl_dr_hits->Fill(Hit_X_Pho1->size()+Hit_X_Pho2->size());
for(int i =0;i<Hit_X_Pho1->size();i++){
pho1_hitX->Fill(Hit_X_Pho1->at(i));
pho1_hitY->Fill(Hit_Y_Pho1->at(i));
pho1_hit_Z->Fill(abs(Hit_Z_Pho1->at(i)));
pho1_hit_E->Fill(RecHitEnPho1->at(i));
pho1_EE_hit_eta->Fill(Hit_Eta_Pho1->at(i));
pho1_EE_hit_phi->Fill(Hit_Phi_Pho1->at(i));

EE_eta_phi_occu->Fill(abs(Hit_Eta_Pho1->at(i)),Hit_Phi_Pho1->at(i));
EE_eta_phi_occu_En_weigh->Fill(abs(Hit_Eta_Pho1->at(i)),Hit_Phi_Pho1->at(i),RecHitEnPho1->at(i));

EE_XY_occupancy->Fill(Hit_X_Pho1->at(i),Hit_Y_Pho1->at(i));
EE_XY_occu_En_weighed->Fill(Hit_X_Pho1->at(i),Hit_Y_Pho1->at(i),RecHitEnPho1->at(i));
P1TotalRecE= P1TotalRecE +RecHitEnPho1->at(i);
if (RecHitFracPho1->at(i) <0 ){ P1TotalUncRecE = P1TotalUncRecE + RecHitEnPho1->at(i); unc_hit_pho1=unc_hit_pho1+1;
P1TotUnc_E_noise_cut=P1TotUnc_E_noise_cut + RecHitEnPho1->at(i) - HitNoisePho1->at(i);
if(genMass>0.08 && genMass<0.12){
Unc_rec_E_ma_100->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_100->Fill(HitNoisePho1->at(i));
Hit_noise_ma_100->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_100->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass>0.18 && genMass<0.22){
Unc_rec_E_ma_200->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_200->Fill(HitNoisePho1->at(i));
Hit_noise_ma_200->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_200->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass>0.28 && genMass<0.32){
Unc_rec_E_ma_300->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_300->Fill(HitNoisePho1->at(i));
Hit_noise_ma_300->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_300->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass>0.48 && genMass<0.52){
Unc_rec_E_ma_500->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_500->Fill(HitNoisePho1->at(i));
Hit_noise_ma_500->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_500->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}

if(genMass>0.38 && genMass<0.42){
Unc_rec_E_ma_400->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_400->Fill(HitNoisePho1->at(i));
Hit_noise_ma_400->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_400->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}
if(genMass>0.58 && genMass<0.62){
Unc_rec_E_ma_600->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_600->Fill(HitNoisePho1->at(i));
Hit_noise_ma_600->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_600->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}

if(genMass>0.68 && genMass<0.72){
Unc_rec_E_ma_700->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_700->Fill(HitNoisePho1->at(i));
Hit_noise_ma_700->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_700->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}

if(genMass>0.78 && genMass<0.82){
Unc_rec_E_ma_800->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_800->Fill(HitNoisePho1->at(i));
Hit_noise_ma_800->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_800->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}
if(genMass>0.88 && genMass<0.92){
Unc_rec_E_ma_900->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_900->Fill(HitNoisePho1->at(i));
Hit_noise_ma_900->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_900->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}

if(genMass>0.98 && genMass<1.02){
Unc_rec_E_ma_1000->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_1000->Fill(HitNoisePho1->at(i));
Hit_noise_ma_1000->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_1000->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}

if(genMass>1.08 && genMass<1.12){
Unc_rec_E_ma_1100->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_1100->Fill(HitNoisePho1->at(i));
Hit_noise_ma_1100->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_1100->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}
if(genMass>1.18 && genMass<1.22){
Unc_rec_E_ma_1200->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_1200->Fill(HitNoisePho1->at(i));
Hit_noise_ma_1200->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_1200->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}
if(genMass>1.28 && genMass<1.32){
Unc_rec_E_ma_1300->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_1300->Fill(HitNoisePho1->at(i));
Hit_noise_ma_1300->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_1300->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}
if(genMass>1.38 && genMass<1.42){
Unc_rec_E_ma_1400->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_1400->Fill(HitNoisePho1->at(i));
Hit_noise_ma_1400->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_1400->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}
if(genMass>1.48 && genMass<1.52){
Unc_rec_E_ma_1500->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_1500->Fill(HitNoisePho1->at(i));
Hit_noise_ma_1500->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_1500->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}
if(genMass>1.58 && genMass<1.62){
Unc_rec_E_ma_1600->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_1600->Fill(HitNoisePho1->at(i));
Hit_noise_ma_1600->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_1600->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}

if(genMass>1.68 && genMass<1.72){
Unc_rec_E_ma_1700->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_1700->Fill(HitNoisePho1->at(i));
Hit_noise_ma_1700->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_1700->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}

if(genMass>1.78 && genMass<1.82){
Unc_rec_E_ma_1800->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_1800->Fill(HitNoisePho1->at(i));
Hit_noise_ma_1800->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_1800->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}
if(genMass>1.88 && genMass<1.92){
Unc_rec_E_ma_1900->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_1900->Fill(HitNoisePho1->at(i));
Hit_noise_ma_1900->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_1900->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}
if(genMass>1.98 && genMass<2.02){
Unc_rec_E_ma_2000->Fill(RecHitEnPho1->at(i));
Unc_Hit_noise_ma_2000->Fill(HitNoisePho1->at(i));
Hit_noise_ma_2000->Fill(HitNoisePho1->at(i));
Hit_noise_vs_Eta_Ma_2000->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));

}
if(genMass<0.1) {
Unc_RH_E_vs_X_Ma_0_100->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_0_100->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_0_100->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_0_100->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
//cout<<"Filled"<<endl;
}
if(genMass < 0.2 && genMass>0.1){
Unc_RH_E_vs_X_Ma_100_200->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_100_200->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_100_200->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_100_200->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass < 0.3 && genMass>0.2){
Unc_RH_E_vs_X_Ma_200_300->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_200_300->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_200_300->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_200_300->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass < 0.4 && genMass>0.3){
Unc_RH_E_vs_X_Ma_300_400->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_300_400->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_300_400->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_300_400->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass < 0.5 && genMass>0.4){
Unc_RH_E_vs_X_Ma_400_500->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_400_500->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_400_500->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Unc_rec_E_ma_400_500->Fill(RecHitEnPho1->at(i));
Hit_noise_vs_Eta_Ma_400_500->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<0.6 && genMass>0.5){
Unc_RH_E_vs_X_Ma_500_600->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_500_600->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_500_600->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_500_600->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<0.7 && genMass>0.6){
Unc_RH_E_vs_X_Ma_600_700->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_600_700->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_600_700->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_600_700->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<0.8 && genMass>0.7){
Unc_RH_E_vs_X_Ma_700_800->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_700_800->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_700_800->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_700_800->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}

if(genMass<0.9 && genMass>0.8){
Unc_RH_E_vs_X_Ma_800_900->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_800_900->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_800_900->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_800_900->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<1.0 && genMass>0.9){
Unc_RH_E_vs_X_Ma_900_1000->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_900_1000->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_900_1000->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_900_1000->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<1.1 && genMass>1.0){
Unc_RH_E_vs_X_Ma_1000_1100->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_1000_1100->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_1000_1100->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_1000_1100->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<1.2 && genMass>1.1){
Unc_RH_E_vs_X_Ma_1100_1200->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_1100_1200->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_1100_1200->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_1100_1200->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<1.3 && genMass>1.2){
Unc_RH_E_vs_X_Ma_1200_1300->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_1200_1300->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_1200_1300->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_1200_1300->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<1.4 && genMass>1.3){
Unc_RH_E_vs_X_Ma_1300_1400->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_1300_1400->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_1300_1400->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_1300_1400->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<1.5 && genMass>1.4){
Unc_RH_E_vs_X_Ma_1400_1500->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_1400_1500->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_1400_1500->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_1400_1500->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<1.6 && genMass>1.5){
Unc_RH_E_vs_X_Ma_1500_1600->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_1500_1600->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_1500_1600->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_1500_1600->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<1.7 && genMass>1.6){
Unc_RH_E_vs_X_Ma_1600_1700->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_1600_1700->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_1600_1700->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_1600_1700->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<1.8 && genMass>1.7){
Unc_RH_E_vs_X_Ma_1700_1800->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_1700_1800->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_1700_1800->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Unc_rec_E_ma_1700_1800->Fill(RecHitEnPho1->at(i));
Hit_noise_vs_Eta_Ma_1700_1800->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<1.9 && genMass>1.8){
Unc_RH_E_vs_X_Ma_1800_1900->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_1800_1900->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_1800_1900->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_1800_1900->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}
if(genMass<2.0 && genMass>1.9){
Unc_RH_E_vs_X_Ma_1900_2000->Fill(RecHitEnPho1->at(i),Hit_X_Pho1->at(i));
Unc_RH_E_vs_Y_Ma_1900_2000->Fill(RecHitEnPho1->at(i),Hit_Y_Pho1->at(i));
Unc_RH_E_vs_eta_Ma_1900_2000->Fill(RecHitEnPho1->at(i),Hit_Eta_Pho1->at(i));
Hit_noise_vs_Eta_Ma_1900_2000->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
}


}
if(RecHitFracPho1->at(i) <0 && RecHitEnPho1->at(i) > 0.2){P1TotalUncRecE0p2 = P1TotalUncRecE0p2 + RecHitEnPho1->at(i); }
if(RecHitFracPho1->at(i)>=0) {P1TotalCluRecE= P1TotalCluRecE + RecHitEnPho1->at(i); clu_hit_pho1=clu_hit_pho1 + 1;
	if(genMass>0.08 && genMass<0.12){
	Clu_rec_E_ma_100->Fill(RecHitEnPho1->at(i)); 
	Clu_Hit_noise_ma_100->Fill(HitNoisePho1->at(i)); 
	Hit_noise_ma_100->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_100->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
					}
if(genMass>0.18 && genMass<0.22){
        Clu_rec_E_ma_200->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_200->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_200->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_200->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>0.28 && genMass<0.32){
        Clu_rec_E_ma_300->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_300->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_300->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_300->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>0.38 && genMass<0.42){
        Clu_rec_E_ma_400->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_400->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_400->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_400->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>0.48 && genMass<0.52){
        Clu_rec_E_ma_500->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_500->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_500->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_500->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>0.58 && genMass<0.62){
        Clu_rec_E_ma_600->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_600->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_600->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_600->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>0.68 && genMass<0.72){
        Clu_rec_E_ma_700->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_700->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_700->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_700->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>0.78 && genMass<0.82){
        Clu_rec_E_ma_800->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_800->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_800->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_800->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>0.88 && genMass<0.92){
        Clu_rec_E_ma_900->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_900->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_900->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_900->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>0.98 && genMass<1.02){
        Clu_rec_E_ma_1000->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_1000->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_1000->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_1000->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>1.08 && genMass<1.12){
        Clu_rec_E_ma_1100->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_1100->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_1100->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_1100->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>1.18 && genMass<1.22){
        Clu_rec_E_ma_1200->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_1200->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_1200->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_1200->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>1.28 && genMass<1.32){
        Clu_rec_E_ma_1300->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_1300->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_1300->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_1300->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>1.38 && genMass<1.42){
        Clu_rec_E_ma_1400->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_1400->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_1400->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_1400->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>1.48 && genMass<1.52){
        Clu_rec_E_ma_1500->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_1500->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_1500->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_1500->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>1.58 && genMass<1.62){
        Clu_rec_E_ma_1600->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_1600->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_1600->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_1600->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>1.68 && genMass<1.72){
        Clu_rec_E_ma_1700->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_1700->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_1700->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_1700->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>1.78 && genMass<1.82){
        Clu_rec_E_ma_1800->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_1800->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_1800->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_1800->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>1.88 && genMass<1.92){
        Clu_rec_E_ma_1900->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_1900->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_1900->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_1900->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
if(genMass>1.98 && genMass<2.02){
        Clu_rec_E_ma_2000->Fill(RecHitEnPho1->at(i));
	Clu_Hit_noise_ma_2000->Fill(HitNoisePho1->at(i)); 
        Hit_noise_ma_2000->Fill(HitNoisePho1->at(i));
        Hit_noise_vs_Eta_Ma_2000->Fill(abs(Hit_Eta_Pho1->at(i)),HitNoisePho1->at(i));
				}
	} 
}
Pho1_RechitE_vs_A_gen_E->Fill(genEnergy,P1TotalRecE);
Pho1_UnclRechitE_vs_A_gen_E->Fill(genEnergy,P1TotalUncRecE);
Pho1_ClusRechitE_vs_A_gen_E->Fill(genEnergy,P1TotalCluRecE);

for(int i =0;i<Hit_X_Pho2->size();i++){
pho2_hitX->Fill(Hit_X_Pho2->at(i));
pho2_hitY->Fill(Hit_Y_Pho2->at(i));
pho2_hit_Z->Fill(abs(Hit_Z_Pho2->at(i)));
pho2_hit_E->Fill(RecHitEnPho2->at(i));
pho2_EE_hit_eta->Fill(Hit_Eta_Pho2->at(i));
pho2_EE_hit_phi->Fill(Hit_Phi_Pho2->at(i));

EE_eta_phi_occu->Fill(abs(Hit_Eta_Pho2->at(i)),Hit_Phi_Pho2->at(i));
EE_eta_phi_occu_En_weigh->Fill(abs(Hit_Eta_Pho2->at(i)),Hit_Phi_Pho2->at(i),RecHitEnPho2->at(i));

EE_XY_occupancy->Fill(Hit_X_Pho2->at(i),Hit_Y_Pho2->at(i));
EE_XY_occu_En_weighed->Fill(Hit_X_Pho2->at(i),Hit_Y_Pho2->at(i),RecHitEnPho2->at(i));
P2TotalRecE = P2TotalRecE + RecHitEnPho2->at(i);
if(RecHitFracPho2->at(i) <0){P2TotalUncRecE = P2TotalUncRecE + RecHitEnPho2->at(i) ; unc_hit_pho2=unc_hit_pho2+1;
P2TotUnc_E_noise_cut= P2TotUnc_E_noise_cut + RecHitEnPho2->at(i) - HitNoisePho2->at(i);
if(genMass>0.08 && genMass<0.12){
Unc_rec_E_ma_100->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_100->Fill(HitNoisePho2->at(i));
Hit_noise_ma_100->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_100->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass>0.18 && genMass<0.22){
Unc_rec_E_ma_200->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_200->Fill(HitNoisePho2->at(i));
Hit_noise_ma_200->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_200->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass>0.28 && genMass<0.32){
Unc_rec_E_ma_300->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_300->Fill(HitNoisePho2->at(i));
Hit_noise_ma_300->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_300->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));

}
if(genMass>0.48 && genMass<0.52){
Unc_rec_E_ma_500->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_500->Fill(HitNoisePho2->at(i));
Hit_noise_ma_500->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_500->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));

}

if(genMass>0.38 && genMass<0.42){
Unc_rec_E_ma_400->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_400->Fill(HitNoisePho2->at(i));
Hit_noise_ma_400->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_400->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));

}
if(genMass>0.58 && genMass<0.62){
Unc_rec_E_ma_600->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_600->Fill(HitNoisePho2->at(i));
Hit_noise_ma_600->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_600->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));

}

if(genMass>0.68 && genMass<0.72){
Unc_rec_E_ma_700->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_700->Fill(HitNoisePho2->at(i));
Hit_noise_ma_700->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_700->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));

}

if(genMass>0.78 && genMass<0.82){
Unc_rec_E_ma_800->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_800->Fill(HitNoisePho2->at(i));
Hit_noise_ma_800->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_800->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));

}
if(genMass>0.88 && genMass<0.92){
Unc_rec_E_ma_900->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_900->Fill(HitNoisePho2->at(i));
Hit_noise_ma_900->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_900->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));

}

if(genMass>0.98 && genMass<1.02){
Unc_rec_E_ma_1000->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_1000->Fill(HitNoisePho2->at(i));
Hit_noise_ma_1000->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_1000->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));

}

if(genMass>1.08 && genMass<1.12){
Unc_rec_E_ma_1100->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_1100->Fill(HitNoisePho2->at(i));
Hit_noise_ma_1100->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_1100->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));

}
if(genMass>1.18 && genMass<1.22){
Unc_rec_E_ma_1200->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_1200->Fill(HitNoisePho2->at(i));
Hit_noise_ma_1200->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_1200->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));

}
if(genMass>1.28 && genMass<1.32){
Unc_rec_E_ma_1300->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_1300->Fill(HitNoisePho2->at(i));
Hit_noise_ma_1300->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_1300->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));

}
if(genMass>1.38 && genMass<1.42){
Unc_rec_E_ma_1400->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_1400->Fill(HitNoisePho2->at(i));
Hit_noise_ma_1400->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_1400->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));


}
if(genMass>1.48 && genMass<1.52){
Unc_rec_E_ma_1500->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_1500->Fill(HitNoisePho2->at(i));
Hit_noise_ma_1500->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_1500->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));


}
if(genMass>1.58 && genMass<1.62){
Unc_rec_E_ma_1600->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_1600->Fill(HitNoisePho2->at(i));
Hit_noise_ma_1600->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_1600->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));


}

if(genMass>1.68 && genMass<1.72){
Unc_rec_E_ma_1700->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_1700->Fill(HitNoisePho2->at(i));
Hit_noise_ma_1700->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_1700->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));


}

if(genMass>1.78 && genMass<1.82){
Unc_rec_E_ma_1800->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_1800->Fill(HitNoisePho2->at(i));
Hit_noise_ma_1800->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_1800->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));


}
if(genMass>1.88 && genMass<1.92){
Unc_rec_E_ma_1900->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_1900->Fill(HitNoisePho2->at(i));
Hit_noise_ma_1900->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_1900->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));


}
if(genMass>1.98 && genMass<2.02){
Unc_rec_E_ma_2000->Fill(RecHitEnPho2->at(i));
Unc_Hit_noise_ma_2000->Fill(HitNoisePho2->at(i));
Hit_noise_ma_2000->Fill(HitNoisePho2->at(i));
Hit_noise_vs_Eta_Ma_2000->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));

}


if(genMass<0.1) {
Unc_RH_E_vs_X_Ma_0_100->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_0_100->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_0_100->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
}
if(genMass < 0.2 && genMass>0.1){
Unc_RH_E_vs_X_Ma_100_200->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_100_200->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_100_200->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_0_100->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass < 0.3 && genMass>0.2){
Unc_RH_E_vs_X_Ma_200_300->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_200_300->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_200_300->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_200_300->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass < 0.4 && genMass>0.3){
Unc_RH_E_vs_X_Ma_300_400->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_300_400->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_300_400->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_300_400->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass < 0.5 && genMass>0.4){
Unc_RH_E_vs_X_Ma_400_500->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_400_500->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_400_500->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Unc_rec_E_ma_400_500->Fill(RecHitEnPho2->at(i));
Hit_noise_vs_Eta_Ma_400_500->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<0.6 && genMass>0.5){
Unc_RH_E_vs_X_Ma_500_600->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_500_600->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_500_600->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_500_600->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<0.7 && genMass>0.6){
Unc_RH_E_vs_X_Ma_600_700->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_600_700->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_600_700->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_600_700->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<0.8 && genMass>0.7){
Unc_RH_E_vs_X_Ma_700_800->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_700_800->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_700_800->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_700_800->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}

if(genMass<0.9 && genMass>0.8){
Unc_RH_E_vs_X_Ma_800_900->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_800_900->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_800_900->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_800_900->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<1.0 && genMass>0.9){
Unc_RH_E_vs_X_Ma_900_1000->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_900_1000->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_900_1000->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_900_1000->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<1.1 && genMass>1.0){
Unc_RH_E_vs_X_Ma_1000_1100->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_1000_1100->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_1000_1100->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_1000_1100->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<1.2 && genMass>1.1){
Unc_RH_E_vs_X_Ma_1100_1200->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_1100_1200->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_1100_1200->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_1100_1200->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<1.3 && genMass>1.2){
Unc_RH_E_vs_X_Ma_1200_1300->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_1200_1300->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_1200_1300->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_1200_1300->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<1.4 && genMass>1.3){
Unc_RH_E_vs_X_Ma_1300_1400->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_1300_1400->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_1300_1400->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_1300_1400->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<1.5 && genMass>1.4){
Unc_RH_E_vs_X_Ma_1400_1500->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_1400_1500->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_1400_1500->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_1400_1500->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<1.6 && genMass>1.5){
Unc_RH_E_vs_X_Ma_1500_1600->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_1500_1600->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_1500_1600->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_1500_1600->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<1.7 && genMass>1.6){
Unc_RH_E_vs_X_Ma_1600_1700->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_1600_1700->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_1600_1700->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_1600_1700->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<1.8 && genMass>1.7){
Unc_RH_E_vs_X_Ma_1700_1800->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_1700_1800->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_1700_1800->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Unc_rec_E_ma_1700_1800->Fill(RecHitEnPho2->at(i));
Hit_noise_vs_Eta_Ma_1700_1800->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<1.9 && genMass>1.8){
Unc_RH_E_vs_X_Ma_1800_1900->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_1800_1900->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_1800_1900->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_1800_1900->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
}
if(genMass<2.0 && genMass>1.9){
Unc_RH_E_vs_X_Ma_1900_2000->Fill(RecHitEnPho2->at(i),Hit_X_Pho2->at(i));
Unc_RH_E_vs_Y_Ma_1900_2000->Fill(RecHitEnPho2->at(i),Hit_Y_Pho2->at(i));
Unc_RH_E_vs_eta_Ma_1900_2000->Fill(RecHitEnPho2->at(i),Hit_Eta_Pho2->at(i));
Hit_noise_vs_Eta_Ma_1900_2000->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
//cout<< RecHitEnPho2->at(i)<<endl;
}

}
if(RecHitFracPho2->at(i)<0 && RecHitEnPho2->at(i)>0.2){P2TotalUncRecE0p2=P2TotalUncRecE0p2 + RecHitEnPho2->at(i);}
if(RecHitFracPho2->at(i) >=0) {P2TotalCluRecE = P2TotalCluRecE + RecHitEnPho2->at(i);clu_hit_pho2=clu_hit_pho2+1;
	if(genMass>0.08 && genMass<0.12){
	Clu_rec_E_ma_100->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_100->Fill(HitNoisePho2->at(i)); 
        Hit_noise_ma_100->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_100->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
					}
if(genMass>0.18 && genMass<0.22){
        Clu_rec_E_ma_200->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_200->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_200->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_200->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>0.28 && genMass<0.32){
        Clu_rec_E_ma_300->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_300->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_300->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_300->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>0.38 && genMass<0.42){
        Clu_rec_E_ma_400->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_400->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_400->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_400->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>0.48 && genMass<0.52){
        Clu_rec_E_ma_500->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_500->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_500->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_500->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>0.58 && genMass<0.62){
        Clu_rec_E_ma_600->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_600->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_600->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_600->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>0.68 && genMass<0.72){
        Clu_rec_E_ma_700->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_700->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_700->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_700->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>0.78 && genMass<0.82){
        Clu_rec_E_ma_800->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_800->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_800->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_800->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>0.88 && genMass<0.92){
        Clu_rec_E_ma_900->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_900->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_900->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_900->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>0.98 && genMass<1.02){
        Clu_rec_E_ma_1000->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_1000->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_1000->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_1000->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>1.08 && genMass<1.12){
        Clu_rec_E_ma_1100->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_1100->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_1100->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_1100->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>1.18 && genMass<1.22){
        Clu_rec_E_ma_1200->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_1200->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_1200->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_1200->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>1.28 && genMass<1.32){
        Clu_rec_E_ma_1300->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_1300->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_1300->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_1300->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>1.38 && genMass<1.42){
        Clu_rec_E_ma_1400->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_1400->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_1400->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_1400->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>1.48 && genMass<1.52){
        Clu_rec_E_ma_1500->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_1500->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_1500->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_1500->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>1.58 && genMass<1.62){
        Clu_rec_E_ma_1600->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_1600->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_1600->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_1600->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>1.68 && genMass<1.72){
        Clu_rec_E_ma_1700->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_1700->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_1700->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_1700->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>1.78 && genMass<1.82){
        Clu_rec_E_ma_1800->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_1800->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_1800->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_1800->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>1.88 && genMass<1.92){
        Clu_rec_E_ma_1900->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_1900->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_1900->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_1900->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}
if(genMass>1.98 && genMass<2.02){
        Clu_rec_E_ma_2000->Fill(RecHitEnPho2->at(i));
	Clu_Hit_noise_ma_2000->Fill(HitNoisePho2->at(i));
        Hit_noise_ma_2000->Fill(HitNoisePho2->at(i));
	Hit_noise_vs_Eta_Ma_2000->Fill(abs(Hit_Eta_Pho2->at(i)),HitNoisePho2->at(i));
				}

}
}
if(energy->size()==1){A_gen_E_vs_merged_pho_E->Fill(genEnergy,energy->at(0));
double rec_E =0;
double rec_E_100=0;
double rec_E_200 =0;
for(int x=0; x<RecHitEnPho1->size();x++){
rec_E = rec_E + RecHitEnPho1->at(x);
if(RecHitEnPho1->at(x)>0.1){rec_E_100 = rec_E_100+RecHitEnPho1->at(x);}
if(RecHitEnPho1->at(x)>0.2){rec_E_200 = rec_E_200+RecHitEnPho1->at(x);}
}
A_gen_E_vs_rechit_E->Fill(genEnergy,rec_E);
A_gen_E_vs_rechit_E_100->Fill(genEnergy,rec_E_100);
A_gen_E_vs_rechit_E_200->Fill(genEnergy,rec_E_200);
}


Pho2_RechitE_vs_A_gen_E->Fill(genEnergy,P2TotalRecE);
Pho2_UnclRechitE_vs_A_gen_E->Fill(genEnergy,P2TotalUncRecE);
Pho2_ClusRechitE_vs_A_gen_E->Fill(genEnergy,P2TotalCluRecE);

float TotRecE = P1TotalRecE + P2TotalRecE;
float TotUncRecE = P1TotalUncRecE + P2TotalUncRecE;
float TotCluRecE = P1TotalCluRecE + P2TotalCluRecE;
float TotUncRecE0p2 = P1TotalUncRecE0p2 + P2TotalUncRecE0p2;

int EE_hits = Hit_X_Pho1->size() + Hit_X_Pho2->size();
int ES_hits = Hit_ES_X_Pho1->size() + Hit_ES_X_Pho2->size();

float ES_pho1_en = 0;
float ES_pho2_en =0;

for(int i=0; i<Hit_ES_X_Pho1->size();i++){
pho1_ES_hit_eta->Fill(Hit_ES_Eta_Pho1->at(i));
pho1_ES_hit_phi->Fill(Hit_ES_Phi_Pho1->at(i));
pho1_ES_hitX->Fill(Hit_ES_X_Pho1->at(i));
pho1_ES_hitY->Fill(Hit_ES_Y_Pho1->at(i));
pho1_ES_hit_Z->Fill(abs(Hit_ES_Z_Pho1->at(i)));
pho1_ES_hit_E->Fill(ES_RecHitEnPho1->at(i));
  ES_pho1_en = ES_pho1_en +ES_RecHitEnPho1->at(i);
}
for(int i=0; i<Hit_ES_X_Pho2->size();i++){
pho2_ES_hit_eta->Fill(Hit_ES_Eta_Pho2->at(i));
pho2_ES_hit_phi->Fill(Hit_ES_Phi_Pho2->at(i));
pho2_ES_hitX->Fill(Hit_ES_X_Pho2->at(i));
pho2_ES_hitY->Fill(Hit_ES_Y_Pho2->at(i));
pho2_ES_hit_Z->Fill(abs(Hit_ES_Z_Pho2->at(i)));
pho2_ES_hit_E->Fill(ES_RecHitEnPho2->at(i));

  ES_pho2_en = ES_pho2_en +ES_RecHitEnPho2->at(i);
}
float Tot_ES_en = ES_pho1_en + ES_pho2_en;

if(genMass>=0.24 && genMass <=0.26){
Tot_rechit_E_Ma_250->Fill(TotRecE); Tot_unc_rechit_E_Ma_250 ->Fill(TotUncRecE); Tot_clu_rechit_E_Ma_250->Fill(TotCluRecE); nreco_Ma_250->Fill(eta->size());
n_EE_rechit_Ma_250->Fill(EE_hits);n_ES_rechit_ma_250->Fill(ES_hits);
}
if(genMass>=0.49 && genMass <=0.51){
  Tot_rechit_E_Ma_500->Fill(TotRecE);Tot_unc_rechit_E_Ma_500->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_500->Fill(TotCluRecE);nreco_Ma_500->Fill(eta->size());
  n_EE_rechit_Ma_500->Fill(EE_hits);n_ES_rechit_ma_500->Fill(ES_hits);
}
if(genMass>=0.74 && genMass<=0.76){
  Tot_rechit_E_Ma_750->Fill(TotRecE);Tot_unc_rechit_E_Ma_750->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_750->Fill(TotCluRecE);nreco_Ma_750->Fill(eta->size());
  n_EE_rechit_Ma_750->Fill(EE_hits);n_ES_rechit_ma_750->Fill(ES_hits);
}
if(genMass>=0.99 && genMass<=1.01){
  //1D histograms
  Tot_rechit_E_Ma_1000->Fill(TotRecE);Tot_unc_rechit_E_Ma_1000->Fill(TotUncRecE);Tot_clu_rechit_E_Ma_1000->Fill(TotCluRecE);nreco_Ma_1000->Fill(eta->size());
  n_EE_rechit_Ma_1000->Fill(EE_hits);n_ES_rechit_ma_1000->Fill(ES_hits);
  //2D histograms
}
if(genMass>0 && genMass<0.1){	Tot_unc_rechit_E_Ma_0_100->Fill(TotUncRecE); 
				Tot_unc_rechit_E_0p2_Ma_0_100->Fill(TotUncRecE0p2); 
				Tot_unc_rechit_E_noise_Ma_0_100->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_0_100->Fill(TotCluRecE);
				N_clu_hits_0_100->Fill(clu_hit_pho1 + clu_hit_pho2);
   				N_unc_hits_0_100->Fill(unc_hit_pho1+unc_hit_pho2);
				N_supclu_dr_hits_0_100->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);}

if(genMass>0.1 && genMass<0.2){	Tot_unc_rechit_E_Ma_100_200->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_100_200->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_100_200->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_100_200->Fill(TotCluRecE);
				N_clu_hits_100_200->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_100_200->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_100_200->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}

if(genMass>=0.2 && genMass<0.3){Tot_unc_rechit_E_Ma_200_300->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_200_300->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_200_300->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_200_300->Fill(TotCluRecE); 
				Tot_ES_RH_E_Ma_200_300->Fill(Tot_ES_en);
				N_clu_hits_200_300->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_200_300->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_200_300->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}
if(genMass>=0.3 && genMass<0.4){Tot_unc_rechit_E_Ma_300_400->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_300_400->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_300_400->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_300_400->Fill(TotCluRecE); 
				Tot_ES_RH_E_Ma_300_400->Fill(Tot_ES_en);
				N_clu_hits_300_400->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_300_400->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_300_400->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}
if(genMass>=0.4 && genMass<0.5){Tot_unc_rechit_E_Ma_400_500->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_400_500->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_400_500->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_400_500->Fill(TotCluRecE); 
				Tot_ES_RH_E_Ma_400_500->Fill(Tot_ES_en);
				N_clu_hits_400_500->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_400_500->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_400_500->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}
if(genMass>=0.5 && genMass<0.6){Tot_unc_rechit_E_Ma_500_600->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_500_600->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_500_600->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_500_600->Fill(TotCluRecE); 
				Tot_ES_RH_E_Ma_500_600->Fill(Tot_ES_en);
				N_clu_hits_500_600->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_500_600->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_500_600->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}
if(genMass>=0.6 && genMass<0.7){Tot_unc_rechit_E_Ma_600_700->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_600_700->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_600_700->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_600_700->Fill(TotCluRecE); 
				Tot_ES_RH_E_Ma_600_700->Fill(Tot_ES_en);
				N_clu_hits_600_700->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_600_700->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_600_700->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}
if(genMass>=0.7 && genMass<0.8){Tot_unc_rechit_E_Ma_700_800->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_700_800->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_700_800->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_700_800->Fill(TotCluRecE); 
				Tot_ES_RH_E_Ma_700_800->Fill(Tot_ES_en);
				N_clu_hits_700_800->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_700_800->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_700_800->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}
if(genMass>=0.8 && genMass<0.9){Tot_unc_rechit_E_Ma_800_900->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_800_900->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_800_900->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_800_900->Fill(TotCluRecE); 
				Tot_ES_RH_E_Ma_800_900->Fill(Tot_ES_en);
				N_clu_hits_800_900->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_800_900->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_800_900->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}
if(genMass>=0.9 && genMass<1.0){Tot_unc_rechit_E_Ma_900_1000->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_900_1000->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_900_1000->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_900_1000->Fill(TotCluRecE);
				Tot_ES_RH_E_Ma_900_1000->Fill(Tot_ES_en);
				N_clu_hits_900_1000->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_900_1000->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_900_1000->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}
if(genMass>=1.0 && genMass<1.1){Tot_unc_rechit_E_Ma_1000_1100->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_1000_1100->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_1000_1100->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_1000_1100->Fill(TotCluRecE);
				N_clu_hits_1000_1100->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_1000_1100->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_1000_1100->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}

if(genMass>=1.1 && genMass<1.2){Tot_unc_rechit_E_Ma_1100_1200->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_1100_1200->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_1100_1200->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_1100_1200->Fill(TotCluRecE);
				N_clu_hits_1100_1200->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_1100_1200->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_1100_1200->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}

if(genMass>=1.2 && genMass<1.3){Tot_unc_rechit_E_Ma_1200_1300->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_1200_1300->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_1200_1300->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_1200_1300->Fill(TotCluRecE);
				N_clu_hits_1200_1300->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_1200_1300->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_1200_1300->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}

if(genMass>=1.3 && genMass<1.4){Tot_unc_rechit_E_Ma_1300_1400->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_1300_1400->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_1300_1400->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_1300_1400->Fill(TotCluRecE);
				N_clu_hits_1300_1400->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_1300_1400->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_1300_1400->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}

if(genMass>=1.4 && genMass<1.5){Tot_unc_rechit_E_Ma_1400_1500->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_1400_1500->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_1400_1500->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_1400_1500->Fill(TotCluRecE);
				N_clu_hits_1400_1500->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_1400_1500->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_1400_1500->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}

if(genMass>=1.5 && genMass<1.6){Tot_unc_rechit_E_Ma_1500_1600->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_1500_1600->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_1500_1600->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_1500_1600->Fill(TotCluRecE);
				N_clu_hits_1500_1600->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_1500_1600->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_1500_1600->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}

if(genMass>=1.6 && genMass<1.7){Tot_unc_rechit_E_Ma_1600_1700->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_1600_1700->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_1600_1700->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_1600_1700->Fill(TotCluRecE);
				N_clu_hits_1600_1700->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_1600_1700->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_1600_1700->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}

if(genMass>=1.7 && genMass<1.8){Tot_unc_rechit_E_Ma_1700_1800->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_1700_1800->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_1700_1800->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_1700_1800->Fill(TotCluRecE);
				N_clu_hits_1700_1800->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_1700_1800->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_1700_1800->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}

if(genMass>=1.8 && genMass<1.9){Tot_unc_rechit_E_Ma_1800_1900->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_1800_1900->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_1800_1900->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_1800_1900->Fill(TotCluRecE);
				N_clu_hits_1800_1900->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_1800_1900->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_1800_1900->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}

if(genMass>=1.9 && genMass<=2.0){Tot_unc_rechit_E_Ma_1900_2000->Fill(TotUncRecE);
				Tot_unc_rechit_E_0p2_Ma_1900_2000->Fill(TotUncRecE0p2);
				Tot_unc_rechit_E_noise_Ma_1900_2000->Fill(P1TotUnc_E_noise_cut + P2TotUnc_E_noise_cut);
				Tot_clu_rechit_E_Ma_1900_2000->Fill(TotCluRecE);
				N_clu_hits_1900_2000->Fill(clu_hit_pho1 + clu_hit_pho2);
                                N_unc_hits_1900_2000->Fill(unc_hit_pho1+unc_hit_pho2);
                                N_supclu_dr_hits_1900_2000->Fill(clu_hit_pho1 + clu_hit_pho2+unc_hit_pho1+unc_hit_pho2);
}
if(genMass>0.08 && genMass<0.12){   Tot_unc_rechit_E_Ma_100->Fill(TotUncRecE); 
                                Tot_unc_rechit_E_0p2_Ma_100->Fill(TotUncRecE0p2);}
if(genMass>0.18 && genMass<0.22){   Tot_unc_rechit_E_Ma_200->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_200->Fill(TotUncRecE0p2);}
if(genMass>0.28 && genMass<0.32){   Tot_unc_rechit_E_Ma_300->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_300->Fill(TotUncRecE0p2);}
if(genMass>0.38 && genMass<0.42){   Tot_unc_rechit_E_Ma_400->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_400->Fill(TotUncRecE0p2);}
if(genMass>0.48 && genMass<0.52){   Tot_unc_rechit_E_Ma_500->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_500->Fill(TotUncRecE0p2);}
if(genMass>0.58 && genMass<0.62){   Tot_unc_rechit_E_Ma_600->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_600->Fill(TotUncRecE0p2);}
if(genMass>0.68 && genMass<0.72){   Tot_unc_rechit_E_Ma_700->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_700->Fill(TotUncRecE0p2);}
if(genMass>0.78 && genMass<0.82){   Tot_unc_rechit_E_Ma_800->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_800->Fill(TotUncRecE0p2);}
if(genMass>0.88 && genMass<0.92){   Tot_unc_rechit_E_Ma_900->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_900->Fill(TotUncRecE0p2);}
if(genMass>0.98 && genMass<1.02){   Tot_unc_rechit_E_Ma_1000->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_1000->Fill(TotUncRecE0p2);}
if(genMass>1.08 && genMass<1.12){   Tot_unc_rechit_E_Ma_1100->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_1100->Fill(TotUncRecE0p2);}
if(genMass>1.18 && genMass<1.22){   Tot_unc_rechit_E_Ma_1200->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_1200->Fill(TotUncRecE0p2);}
if(genMass>1.28 && genMass<1.32){   Tot_unc_rechit_E_Ma_1300->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_1300->Fill(TotUncRecE0p2);}
if(genMass>1.38 && genMass<1.42){   Tot_unc_rechit_E_Ma_1400->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_1400->Fill(TotUncRecE0p2);}
if(genMass>1.48 && genMass<1.52){   Tot_unc_rechit_E_Ma_1500->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_1500->Fill(TotUncRecE0p2);}
if(genMass>1.58 && genMass<1.62){   Tot_unc_rechit_E_Ma_1600->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_1600->Fill(TotUncRecE0p2);}
if(genMass>1.68 && genMass<1.72){   Tot_unc_rechit_E_Ma_1700->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_1700->Fill(TotUncRecE0p2);}
if(genMass>1.78 && genMass<1.82){   Tot_unc_rechit_E_Ma_1800->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_1800->Fill(TotUncRecE0p2);}
if(genMass>1.88 && genMass<1.92){   Tot_unc_rechit_E_Ma_1900->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_1900->Fill(TotUncRecE0p2);}
if(genMass>1.98 && genMass<2.02){   Tot_unc_rechit_E_Ma_2000->Fill(TotUncRecE);  
                                Tot_unc_rechit_E_0p2_Ma_2000->Fill(TotUncRecE0p2);}


int n_es_l1_hits =0;
int n_es_l2_hits =0;
float es_l1_e =0;
float es_l2_e =0;
if(Hit_ES_X_Pho1->size()>0){ 
  for(int i =0; i<Hit_ES_X_Pho1->size(); i++){
  if(abs(Hit_ES_Z_Pho1->at(i))>302 && abs(Hit_ES_Z_Pho1->at(i)<305)){n_es_l1_hits = n_es_l1_hits + 1; es_l1_e= es_l1_e + ES_RecHitEnPho1->at(i);}
  if(abs(Hit_ES_Z_Pho1->at(i))>=308 && abs(Hit_ES_Z_Pho1->at(i))<310){n_es_l2_hits = n_es_l2_hits + 1;es_l2_e = es_l2_e + ES_RecHitEnPho1->at(i);}
}
}
if(Hit_ES_X_Pho2->size()>0){ 
  for(int i =0; i<Hit_ES_X_Pho2->size(); i++){
  if(abs(Hit_ES_Z_Pho2->at(i))>303 && abs(Hit_ES_Z_Pho2->at(i)<305)){ n_es_l1_hits = n_es_l1_hits + 1; es_l1_e = es_l1_e + ES_RecHitEnPho2->at(i);}
  if(abs(Hit_ES_Z_Pho2->at(i))>=308 && abs(Hit_ES_Z_Pho2->at(i))<310){ n_es_l2_hits = n_es_l2_hits + 1;es_l2_e = es_l2_e + ES_RecHitEnPho2->at(i);}
}
}
ES_L1_hits->Fill(n_es_l1_hits);
ES_L2_hits->Fill(n_es_l2_hits);
ES_L1_hits_En_weighed->Fill(n_es_l1_hits,es_l1_e);
ES_L2_hits_En_weighed->Fill(n_es_l2_hits, es_l2_e);

for (int i=0; i<Pho_SigIEIE->size();i++){
float pho_sigiEiE = Pho_SigIEIE->at(i);
float pho_sigiPhiiPhi = Pho_SigIPhiIPhi->at(i);
Pho_sig_iEiE->Fill(pho_sigiEiE);
Pho_sig_iPhiiPhi->Fill(pho_sigiPhiiPhi);
	if(genMass >=0.2 && genMass <0.3){
Pho_sig_iEiE_Ma_200_300->Fill(pho_sigiEiE); Pho_sig_iPhiiPhi_Ma_200_300->Fill(pho_sigiPhiiPhi);}

if(genMass >=0.3 && genMass <0.4){
Pho_sig_iEiE_Ma_300_400->Fill(pho_sigiEiE); Pho_sig_iPhiiPhi_Ma_300_400->Fill(pho_sigiPhiiPhi);}

if(genMass >=0.4 && genMass <0.5){
Pho_sig_iEiE_Ma_400_500->Fill(pho_sigiEiE); Pho_sig_iPhiiPhi_Ma_400_500->Fill(pho_sigiPhiiPhi);}

if(genMass >=0.5 && genMass <0.6){
Pho_sig_iEiE_Ma_500_600->Fill(pho_sigiEiE); Pho_sig_iPhiiPhi_Ma_500_600->Fill(pho_sigiPhiiPhi);}

if(genMass >=0.6 && genMass <0.7){
Pho_sig_iEiE_Ma_600_700->Fill(pho_sigiEiE); Pho_sig_iPhiiPhi_Ma_600_700->Fill(pho_sigiPhiiPhi);}

if(genMass >=0.7 && genMass <0.8){
Pho_sig_iEiE_Ma_700_800->Fill(pho_sigiEiE); Pho_sig_iPhiiPhi_Ma_700_800->Fill(pho_sigiPhiiPhi);}

if(genMass >=0.8 && genMass <0.9){
Pho_sig_iEiE_Ma_800_900->Fill(pho_sigiEiE); Pho_sig_iPhiiPhi_Ma_800_900->Fill(pho_sigiPhiiPhi);}

if(genMass >=0.9 && genMass <1.0){
Pho_sig_iEiE_Ma_900_1000->Fill(pho_sigiEiE); Pho_sig_iPhiiPhi_Ma_900_1000->Fill(pho_sigiPhiiPhi);}

}
float tot_raw_e=0;
for(int k=0;k<RawRecHitEnPho1->size();k++){
tot_raw_e=tot_raw_e+RawRecHitEnPho1->at(k);
	for(float a=0;a<20;a++){
        if(genMass>a/10 && genMass<(a+1)/10){raw_E_dist[a]->Fill(RawRecHitEnPho1->at(k));}
				}
} 
for(int k=0;k<RawRecHitEnPho2->size();k++){
tot_raw_e=tot_raw_e+RawRecHitEnPho2->at(k);
for(float a=0;a<20;a++){
        if(genMass>a/10 && genMass<(a+1)/10){raw_E_dist[a]->Fill(RawRecHitEnPho2->at(k));}
                                }
}

for(float i=0;i<20;i++){
float m_min=i/10;
float m_max=(i+1)/10;
//cout <<m_min<<endl;
if(genMass > m_min && genMass< m_max){
N_hits_supcl[i]->Fill(Hit_X_Pho1->size() + Hit_X_Pho2->size() - dRHit_X_Pho1->size() - dRHit_X_Pho2->size());
N_hits_supcl_dr[i]->Fill(Hit_X_Pho1->size() + Hit_X_Pho2->size());
//cout<<Hit_X_Pho1->size() + Hit_X_Pho2->size() <<endl;
N_hits_raw[i]->Fill(RawRecHitEnPho1->size() + RawRecHitEnPho2->size());
Tot_raw_energy[i]->Fill(tot_raw_e);
//cout<<N_hits_supcl[i] <<endl;
					}
			}
 }

}
