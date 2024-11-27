//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug 16 18:22:34 2018 by ROOT version 6.06/01
// from TTree hits/HGC rechits
// found on file: muon_v10.root
//////////////////////////////////////////////////////////

#ifndef HGCNtupleVariables_h
#define HGCNtupleVariables_h

#include <TChain.h>
#include <TFile.h>
#include <TROOT.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

using namespace std;

class HGCNtupleVariables {
public:
  HGCNtupleVariables(TTree * /*tree*/ = 0) : fChain(0) {}
  ~HGCNtupleVariables() {}
  // void    Init(TTree *tree);
  void Init(TTree *tree, TTree *tree2);
  Bool_t Notify();
  Int_t GetEntry(Long64_t entry, Int_t getall = 0) {
    return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0;
  }

  TTree *fChain;   //! pointer to the analyzed TTree or TChain
  TTree *fChain2;  //! pointer to the analyzed TTree or TChain
  Int_t fCurrent;  //! current Tree number in a TChain
  Int_t fCurrent2; //! current Tree number in a TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types
  //
    vector<float>   *iEtaPho1;
   vector<float>   *iPhiPho1;
   vector<float>   *Hit_ES_Eta_Pho1;
   vector<float>   *Hit_ES_Phi_Pho1;
   vector<float>   *Hit_ES_X_Pho1;
   vector<float>   *Hit_ES_Y_Pho1;
   vector<float>   *Hit_ES_Z_Pho1;
   vector<float>   *ES_RecHitEnPho1;
   vector<float>   *Hit_Eta_Pho1;
   vector<float>   *Hit_Phi_Pho1;
   vector<float>   *Hit_X_Pho1;
   vector<float>   *Hit_Y_Pho1;
   vector<float>   *Hit_Z_Pho1;
   vector<float>   *RecHitEnPho1;
   vector<float>   *RecHitFracPho1;
   vector<int>     *RecHitGain1;
   vector<bool>    *RecHitQuality1;
   vector<float>   *HitNoisePho1;
   vector<float>   *dRHit_Eta_Pho1;
   vector<float>   *dRHit_Phi_Pho1;
   vector<float>   *RawHit_Eta_Pho1;
   vector<float>   *RawHit_Phi_Pho1;
   vector<float>   *RawRecHitEnPho1;
   vector<float>   *RawRecHit_X_Pho1;
   vector<float>   *RawRecHit_Y_Pho1;
   vector<float>   *RawRecHit_Z_Pho1;
   vector<float>   *RawHit_Eta_Pho2;
   vector<float>   *RawHit_Phi_Pho2;
   vector<float>   *RawRecHitEnPho2;
   vector<float>   *RawRecHit_X_Pho2;
   vector<float>   *RawRecHit_Y_Pho2;
   vector<float>   *RawRecHit_Z_Pho2;
   vector<float>   *dRHit_X_Pho1;
   vector<float>   *dRHit_Y_Pho1;
   vector<float>   *dRHit_Z_Pho1;
   vector<float>   *dRRecHitEnPho1;
   vector<float>   *dRRecHitFracPho1;
   vector<float>   *dRHit_Eta_Pho2;
   vector<float>   *dRHit_Phi_Pho2;
   vector<float>   *dRHit_X_Pho2;
   vector<float>   *dRHit_Y_Pho2;
   vector<float>   *dRHit_Z_Pho2;
   vector<float>   *dRRecHitEnPho2;
   vector<float>   *dRRecHitFracPho2;
   vector<bool>    *RecHitFlag_kGood_pho1;
   vector<bool>    *RecHitFlag_kPoorReco_pho1;
   vector<bool>    *RecHitFlag_kOutOfTime_pho1;
   vector<bool>    *RecHitFlag_kFaultyHardware_pho1;
   vector<bool>    *RecHitFlag_kNoisy_pho1;
   vector<bool>    *RecHitFlag_kPoorCalib_pho1;
   vector<bool>    *RecHitFlag_kSaturated_pho1;
   vector<bool>    *RecHitFlag_kLeadingEdgeRecovered_pho1;
   vector<bool>    *RecHitFlag_kNeighboursRecovered_pho1;
   vector<bool>    *RecHitFlag_kTowerRecovered_pho1;
   vector<bool>    *RecHitFlag_kDead_pho1;
   vector<bool>    *RecHitFlag_kKilled_pho1;
   vector<bool>    *RecHitFlag_kTPSaturated_pho1;
   vector<bool>    *RecHitFlag_kL1SpikeFlag_pho1;
   vector<bool>    *RecHitFlag_kWeird_pho1;
   vector<bool>    *RecHitFlag_kDiWeird_pho1;
   vector<bool>    *RecHitFlag_kHasSwitchToGain6_pho1;
   vector<bool>    *RecHitFlag_kHasSwitchToGain1_pho1;
   vector<bool>    *RecHitFlag_kESGood_pho1;
   vector<bool>    *RecHitFlag_kESDead_pho1;
   vector<bool>    *RecHitFlag_kESHot_pho1;
   vector<bool>    *RecHitFlag_kESPassBX_pho1;
   vector<bool>    *RecHitFlag_kESTwoGoodRatios_pho1;
   vector<bool>    *RecHitFlag_kESBadRatioFor12_pho1;
   vector<bool>    *RecHitFlag_kESBadRatioFor23Upper_pho1;
   vector<bool>    *RecHitFlag_kESBadRatioFor23Lower_pho1;
   vector<bool>    *RecHitFlag_kESTS1Largest_pho1;
   vector<bool>    *RecHitFlag_kESTS3Largest_pho1;
   vector<bool>    *RecHitFlag_kESTS3Negative_pho1;
   vector<bool>    *RecHitFlag_kESSaturated_pho1;
   vector<bool>    *RecHitFlag_kESTS2Saturated_pho1;
   vector<bool>    *RecHitFlag_kESTS3Saturated_pho1;
   vector<bool>    *RecHitFlag_kESTS13Sigmas_pho1;
   vector<bool>    *RecHitFlag_kESTS15Sigmas_pho1;
   vector<float>   *iEtaPho2;
   vector<float>   *iPhiPho2;
   vector<float>   *Hit_ES_Eta_Pho2;
   vector<float>   *Hit_ES_Phi_Pho2;
   vector<float>   *Hit_ES_X_Pho2;
   vector<float>   *Hit_ES_Y_Pho2;
   vector<float>   *Hit_ES_Z_Pho2;
   vector<float>   *ES_RecHitEnPho2;
   vector<float>   *Hit_Eta_Pho2;
   vector<float>   *Hit_Phi_Pho2;
   vector<float>   *Hit_X_Pho2;
   vector<float>   *Hit_Y_Pho2;
   vector<float>   *Hit_Z_Pho2;
   vector<float>   *RecHitEnPho2;
   vector<float>   *RecHitFracPho2;
   vector<int>     *RecHitGain2;
   vector<bool>    *RecHitQuality2;
   vector<float>   *HitNoisePho2;
   vector<bool>    *RecHitFlag_kGood_pho2;
   vector<bool>    *RecHitFlag_kPoorReco_pho2;
   vector<bool>    *RecHitFlag_kOutOfTime_pho2;
   vector<bool>    *RecHitFlag_kFaultyHardware_pho2;
   vector<bool>    *RecHitFlag_kNoisy_pho2;
   vector<bool>    *RecHitFlag_kPoorCalib_pho2;
   vector<bool>    *RecHitFlag_kSaturated_pho2;
   vector<bool>    *RecHitFlag_kLeadingEdgeRecovered_pho2;
   vector<bool>    *RecHitFlag_kNeighboursRecovered_pho2;
   vector<bool>    *RecHitFlag_kTowerRecovered_pho2;
   vector<bool>    *RecHitFlag_kDead_pho2;
   vector<bool>    *RecHitFlag_kKilled_pho2;
   vector<bool>    *RecHitFlag_kTPSaturated_pho2;
   vector<bool>    *RecHitFlag_kL1SpikeFlag_pho2;
   vector<bool>    *RecHitFlag_kWeird_pho2;
   vector<bool>    *RecHitFlag_kDiWeird_pho2;
   vector<bool>    *RecHitFlag_kHasSwitchToGain6_pho2;
   vector<bool>    *RecHitFlag_kHasSwitchToGain1_pho2;
   vector<bool>    *RecHitFlag_kESGood_pho2;
   vector<bool>    *RecHitFlag_kESDead_pho2;
   vector<bool>    *RecHitFlag_kESHot_pho2;
   vector<bool>    *RecHitFlag_kESPassBX_pho2;
   vector<bool>    *RecHitFlag_kESTwoGoodRatios_pho2;
   vector<bool>    *RecHitFlag_kESBadRatioFor12_pho2;
   vector<bool>    *RecHitFlag_kESBadRatioFor23Upper_pho2;
   vector<bool>    *RecHitFlag_kESBadRatioFor23Lower_pho2;
   vector<bool>    *RecHitFlag_kESTS1Largest_pho2;
   vector<bool>    *RecHitFlag_kESTS3Largest_pho2;
   vector<bool>    *RecHitFlag_kESTS3Negative_pho2;
   vector<bool>    *RecHitFlag_kESSaturated_pho2;
   vector<bool>    *RecHitFlag_kESTS2Saturated_pho2;
   vector<bool>    *RecHitFlag_kESTS3Saturated_pho2;
   vector<bool>    *RecHitFlag_kESTS13Sigmas_pho2;
   vector<bool>    *RecHitFlag_kESTS15Sigmas_pho2;
   Int_t           nPhotons;
   vector<float>   *pt;
   vector<float>   *eta;
   vector<float>   *phi;
   vector<float>   *Pho_cluster_seed_x;
   vector<float>   *Pho_cluster_seed_y;
   vector<float>   *Pho_cluster_seed_z;
   vector<float>   *Pho_cluster_seed_eta;
   vector<float>   *Pho_cluster_seed_phi;
   vector<float>   *energy;
   vector<float>   *energy_ecal_mustache;
   vector<int>     *passMediumId;
   vector<int>     *passTightId;
   vector<int>     *passMVAMediumId;
   vector<float>   *Pho_R9;
   vector<float>   *Pho_S4;
   vector<float>   *Pho_SigIEIE;
   vector<float>   *Pho_SigIPhiIPhi;
   vector<float>   *Pho_SCEtaW;
   vector<float>   *Pho_SCPhiW;
   vector<float>   *Pho_CovIEtaIEta;
   vector<float>   *Pho_CovIEtaIPhi;
   vector<float>   *Pho_ESSigRR;
   vector<float>   *Pho_SCRawE;
   vector<float>   *Pho_SC_ESEnByRawE;
   vector<float>   *Pho_HadOverEm;
   vector<float>   *Pho_PFChIso;
   vector<float>   *Pho_PFChPVIso;
   vector<float>   *Pho_PFPhoIso;
   vector<float>   *Pho_PFNeuIso;
   vector<float>   *Pho_PFChWorstVetoIso;
   vector<float>   *Pho_PFChWorstIso;
   vector<float>   *Pho_EcalPFClusterIso;
   vector<float>   *Pho_HcalPFClusterIso;
   vector<float>   *Pho_CorrectedEnergy;
   vector<float>   *Pho_CorrectedEnergyError;
   vector<float>   *A_Gen_mass;
   vector<float>   *A_Gen_pt;
   vector<float>   *A_Gen_eta;
   vector<float>   *A_Gen_phi;
   vector<float>   *Pho_Gen_Pt;
   vector<float>   *Pho_Gen_Eta;
   vector<float>   *Pho_Gen_Phi;
   vector<float>   *Pho_Gen_E;
   Float_t         rho;
   Int_t           run;
   Int_t           event;
   Int_t           lumi;

   // List of branches
   TBranch        *b_iEtaPho1;   //!
   TBranch        *b_iPhiPho1;   //!
   TBranch        *b_Hit_ES_Eta_Pho1;   //!
   TBranch        *b_Hit_ES_Phi_Pho1;   //!
   TBranch        *b_Hit_ES_X_Pho1;   //!
   TBranch        *b_Hit_ES_Y_Pho1;   //!
   TBranch        *b_Hit_ES_Z_Pho1;   //!
   TBranch        *b_ES_RecHitEnPho1;   //!
   TBranch        *b_Hit_Eta_Pho1;   //!
   TBranch        *b_Hit_Phi_Pho1;   //!
   TBranch        *b_Hit_X_Pho1;   //!
   TBranch        *b_Hit_Y_Pho1;   //!
   TBranch        *b_Hit_Z_Pho1;   //!
   TBranch        *b_RecHitEnPho1;   //!
   TBranch        *b_RecHitFracPho1;   //!
   TBranch        *b_RecHitGain1;   //!
   TBranch        *b_RecHitQuality1;   //!
   TBranch        *b_HitNoisePho1;   //!
   TBranch        *b_dRHit_Eta_Pho1;   //!
   TBranch        *b_dRHit_Phi_Pho1;   //!
   TBranch        *b_RawHit_Eta_Pho1;   //!
   TBranch        *b_RawHit_Phi_Pho1;   //!
   TBranch        *b_RawRecHitEnPho1;   //!
   TBranch        *b_RawRecHit_X_Pho1;   //!
   TBranch        *b_RawRecHit_Y_Pho1;   //!
   TBranch        *b_RawRecHit_Z_Pho1;   //!
   TBranch        *b_RawHit_Eta_Pho2;   //!
   TBranch        *b_RawHit_Phi_Pho2;   //!
   TBranch        *b_RawRecHitEnPho2;   //!
   TBranch        *b_RawRecHit_X_Pho2;   //!
   TBranch        *b_RawRecHit_Y_Pho2;   //!
   TBranch        *b_RawRecHit_Z_Pho2;   //!
   TBranch        *b_dRHit_X_Pho1;   //!
   TBranch        *b_dRHit_Y_Pho1;   //!
   TBranch        *b_dRHit_Z_Pho1;   //!
   TBranch        *b_dRRecHitEnPho1;   //!
   TBranch        *b_dRRecHitFracPho1;   //!
   TBranch        *b_dRHit_Eta_Pho2;   //!
   TBranch        *b_dRHit_Phi_Pho2;   //!
   TBranch        *b_dRHit_X_Pho2;   //!
   TBranch        *b_dRHit_Y_Pho2;   //!
   TBranch        *b_dRHit_Z_Pho2;   //!
   TBranch        *b_dRRecHitEnPho2;   //!
   TBranch        *b_dRRecHitFracPho2;   //!
   TBranch        *b_RecHitFlag_kGood_pho1;   //!
   TBranch        *b_RecHitFlag_kPoorReco_pho1;   //!
   TBranch        *b_RecHitFlag_kOutOfTime_pho1;   //!
   TBranch        *b_RecHitFlag_kFaultyHardware_pho1;   //!
   TBranch        *b_RecHitFlag_kNoisy_pho1;   //!
   TBranch        *b_RecHitFlag_kPoorCalib_pho1;   //!
   TBranch        *b_RecHitFlag_kSaturated_pho1;   //!
   TBranch        *b_RecHitFlag_kLeadingEdgeRecovered_pho1;   //!
   TBranch        *b_RecHitFlag_kNeighboursRecovered_pho1;   //!
   TBranch        *b_RecHitFlag_kTowerRecovered_pho1;   //!
   TBranch        *b_RecHitFlag_kDead_pho1;   //!
   TBranch        *b_RecHitFlag_kKilled_pho1;   //!
   TBranch        *b_RecHitFlag_kTPSaturated_pho1;   //!
   TBranch        *b_RecHitFlag_kL1SpikeFlag_pho1;   //!
   TBranch        *b_RecHitFlag_kWeird_pho1;   //!
   TBranch        *b_RecHitFlag_kDiWeird_pho1;   //!
   TBranch        *b_RecHitFlag_kHasSwitchToGain6_pho1;   //!
   TBranch        *b_RecHitFlag_kHasSwitchToGain1_pho1;   //!
   TBranch        *b_RecHitFlag_kESGood_pho1;   //!
   TBranch        *b_RecHitFlag_kESDead_pho1;   //!
   TBranch        *b_RecHitFlag_kESHot_pho1;   //!
   TBranch        *b_RecHitFlag_kESPassBX_pho1;   //!
   TBranch        *b_RecHitFlag_kESTwoGoodRatios_pho1;   //!
   TBranch        *b_RecHitFlag_kESBadRatioFor12_pho1;   //!
   TBranch        *b_RecHitFlag_kESBadRatioFor23Upper_pho1;   //!
   TBranch        *b_RecHitFlag_kESBadRatioFor23Lower_pho1;   //!
   TBranch        *b_RecHitFlag_kESTS1Largest_pho1;   //!
   TBranch        *b_RecHitFlag_kESTS3Largest_pho1;   //!
   TBranch        *b_RecHitFlag_kESTS3Negative_pho1;   //!
   TBranch        *b_RecHitFlag_kESSaturated_pho1;   //!
   TBranch        *b_RecHitFlag_kESTS2Saturated_pho1;   //!
   TBranch        *b_RecHitFlag_kESTS3Saturated_pho1;   //!
   TBranch        *b_RecHitFlag_kESTS13Sigmas_pho1;   //!
   TBranch        *b_RecHitFlag_kESTS15Sigmas_pho1;   //!
   TBranch        *b_iEtaPho2;   //!
   TBranch        *b_iPhiPho2;   //!
   TBranch        *b_Hit_ES_Eta_Pho2;   //!
   TBranch        *b_Hit_ES_Phi_Pho2;   //!
   TBranch        *b_Hit_ES_X_Pho2;   //!
   TBranch        *b_Hit_ES_Y_Pho2;   //!
   TBranch        *b_Hit_ES_Z_Pho2;   //!
   TBranch        *b_ES_RecHitEnPho2;   //!
   TBranch        *b_Hit_Eta_Pho2;   //!
   TBranch        *b_Hit_Phi_Pho2;   //!
   TBranch        *b_Hit_X_Pho2;   //!
   TBranch        *b_Hit_Y_Pho2;   //!
   TBranch        *b_Hit_Z_Pho2;   //!
   TBranch        *b_RecHitEnPho2;   //!
   TBranch        *b_RecHitFracPho2;   //!
   TBranch        *b_RecHitGain2;   //!
   TBranch        *b_RecHitQuality2;   //!
   TBranch        *b_HitNoisePho2;   //!
   TBranch        *b_RecHitFlag_kGood_pho2;   //!
   TBranch        *b_RecHitFlag_kPoorReco_pho2;   //!
   TBranch        *b_RecHitFlag_kOutOfTime_pho2;   //!
   TBranch        *b_RecHitFlag_kFaultyHardware_pho2;   //!
   TBranch        *b_RecHitFlag_kNoisy_pho2;   //!
   TBranch        *b_RecHitFlag_kPoorCalib_pho2;   //!
   TBranch        *b_RecHitFlag_kSaturated_pho2;   //!
   TBranch        *b_RecHitFlag_kLeadingEdgeRecovered_pho2;   //!
   TBranch        *b_RecHitFlag_kNeighboursRecovered_pho2;   //!
   TBranch        *b_RecHitFlag_kTowerRecovered_pho2;   //!
   TBranch        *b_RecHitFlag_kDead_pho2;   //!
   TBranch        *b_RecHitFlag_kKilled_pho2;   //!
   TBranch        *b_RecHitFlag_kTPSaturated_pho2;   //!
   TBranch        *b_RecHitFlag_kL1SpikeFlag_pho2;   //!
   TBranch        *b_RecHitFlag_kWeird_pho2;   //!
   TBranch        *b_RecHitFlag_kDiWeird_pho2;   //!
   TBranch        *b_RecHitFlag_kHasSwitchToGain6_pho2;   //!
   TBranch        *b_RecHitFlag_kHasSwitchToGain1_pho2;   //!
   TBranch        *b_RecHitFlag_kESGood_pho2;   //!
   TBranch        *b_RecHitFlag_kESDead_pho2;   //!
   TBranch        *b_RecHitFlag_kESHot_pho2;   //!
   TBranch        *b_RecHitFlag_kESPassBX_pho2;   //!
   TBranch        *b_RecHitFlag_kESTwoGoodRatios_pho2;   //!
   TBranch        *b_RecHitFlag_kESBadRatioFor12_pho2;   //!
   TBranch        *b_RecHitFlag_kESBadRatioFor23Upper_pho2;   //!
   TBranch        *b_RecHitFlag_kESBadRatioFor23Lower_pho2;   //!
   TBranch        *b_RecHitFlag_kESTS1Largest_pho2;   //!
   TBranch        *b_RecHitFlag_kESTS3Largest_pho2;   //!
   TBranch        *b_RecHitFlag_kESTS3Negative_pho2;   //!
   TBranch        *b_RecHitFlag_kESSaturated_pho2;   //!
   TBranch        *b_RecHitFlag_kESTS2Saturated_pho2;   //!
   TBranch        *b_RecHitFlag_kESTS3Saturated_pho2;   //!
   TBranch        *b_RecHitFlag_kESTS13Sigmas_pho2;   //!
   TBranch        *b_RecHitFlag_kESTS15Sigmas_pho2;   //!
   TBranch        *b_nPho;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_Pho_cluster_seed_x;   //!
   TBranch        *b_Pho_cluster_seed_y;   //!
   TBranch        *b_Pho_cluster_seed_z;   //!
   TBranch        *b_Pho_cluster_seed_eta;   //!
   TBranch        *b_Pho_cluster_seed_phi;   //!
   TBranch        *b_energy;   //!
   TBranch        *b_energy_ecal_mustache;   //!
   TBranch        *b_passMediumId;   //!
   TBranch        *b_passTightId;   //!
   TBranch        *b_passMVAMediumId;   //!
   TBranch        *b_Pho_R9;   //!
   TBranch        *b_Pho_S4;   //!
   TBranch        *b_Pho_SigIEIE;   //!
   TBranch        *b_Pho_SigIPhiIPhi;   //!
   TBranch        *b_Pho_SCEtaW;   //!
   TBranch        *b_Pho_SCPhiW;   //!
   TBranch        *b_Pho_CovIEtaIEta;   //!
   TBranch        *b_Pho_CovIEtaIPhi;   //!
   TBranch        *b_Pho_ESSigRR;   //!
   TBranch        *b_Pho_SCRawE;   //!
   TBranch        *b_Pho_SC_ESEnByRawE;   //!
   TBranch        *b_Pho_HadOverEm;   //!
   TBranch        *b_Pho_PFChIso;   //!
   TBranch        *b_Pho_PFChPVIso;   //!
   TBranch        *b_Pho_PFPhoIso;   //!
   TBranch        *b_Pho_PFNeuIso;   //!
   TBranch        *b_Pho_PFChWorstVetoIso;   //!
   TBranch        *b_Pho_PFChWorstIso;   //!
   TBranch        *b_Pho_EcalPFClusterIso;   //!
   TBranch        *b_Pho_HcalPFClusterIso;   //!
   TBranch        *b_Pho_CorrectedEnergy;   //!
   TBranch        *b_Pho_CorrectedEnergyError;   //!
   TBranch        *b_A_Gen_mass;   //!
   TBranch        *b_A_Gen_pt;   //!
   TBranch        *b_A_Gen_eta;   //!
   TBranch        *b_A_Gen_phi;   //!
   TBranch        *b_Pho_Gen_Pt;   //!
   TBranch        *b_Pho_Gen_Eta;   //!
   TBranch        *b_Pho_Gen_Phi;   //!
   TBranch        *b_Pho_Gen_E;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumi;   //!
};

#endif

#ifdef HGCNtupleVariables_cxx

void HGCNtupleVariables::Init(TTree *tree, TTree *tree2) {
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  iEtaPho1 = 0;
   iPhiPho1 = 0;
   Hit_ES_Eta_Pho1 = 0;
   Hit_ES_Phi_Pho1 = 0;
   Hit_ES_X_Pho1 = 0;
   Hit_ES_Y_Pho1 = 0;
   Hit_ES_Z_Pho1 = 0;
   ES_RecHitEnPho1 = 0;
   Hit_Eta_Pho1 = 0;
   Hit_Phi_Pho1 = 0;
   Hit_X_Pho1 = 0;
   Hit_Y_Pho1 = 0;
   Hit_Z_Pho1 = 0;
   RecHitEnPho1 = 0;
   RecHitFracPho1 = 0;
   RecHitGain1 = 0;
   RecHitQuality1 = 0;
   HitNoisePho1 = 0;
   dRHit_Eta_Pho1 = 0;
   dRHit_Phi_Pho1 = 0;
   RawHit_Eta_Pho1 = 0;
   RawHit_Phi_Pho1 = 0;
   RawRecHitEnPho1 = 0;
   RawRecHit_X_Pho1 = 0;
   RawRecHit_Y_Pho1 = 0;
   RawRecHit_Z_Pho1 = 0;
   RawHit_Eta_Pho2 = 0;
   RawHit_Phi_Pho2 = 0;
   RawRecHitEnPho2 = 0;
   RawRecHit_X_Pho2 = 0;
   RawRecHit_Y_Pho2 = 0;
   RawRecHit_Z_Pho2 = 0;
   dRHit_X_Pho1 = 0;
   dRHit_Y_Pho1 = 0;
   dRHit_Z_Pho1 = 0;
   dRRecHitEnPho1 = 0;
   dRRecHitFracPho1 = 0;
   dRHit_Eta_Pho2 = 0;
   dRHit_Phi_Pho2 = 0;
   dRHit_X_Pho2 = 0;
   dRHit_Y_Pho2 = 0;
   dRHit_Z_Pho2 = 0;
   dRRecHitEnPho2 = 0;
   dRRecHitFracPho2 = 0;
   RecHitFlag_kGood_pho1 = 0;
   RecHitFlag_kPoorReco_pho1 = 0;
   RecHitFlag_kOutOfTime_pho1 = 0;
   RecHitFlag_kFaultyHardware_pho1 = 0;
   RecHitFlag_kNoisy_pho1 = 0;
   RecHitFlag_kPoorCalib_pho1 = 0;
   RecHitFlag_kSaturated_pho1 = 0;
   RecHitFlag_kLeadingEdgeRecovered_pho1 = 0;
   RecHitFlag_kNeighboursRecovered_pho1 = 0;
   RecHitFlag_kTowerRecovered_pho1 = 0;
   RecHitFlag_kDead_pho1 = 0;
   RecHitFlag_kKilled_pho1 = 0;
   RecHitFlag_kTPSaturated_pho1 = 0;
   RecHitFlag_kL1SpikeFlag_pho1 = 0;
   RecHitFlag_kWeird_pho1 = 0;
   RecHitFlag_kDiWeird_pho1 = 0;
   RecHitFlag_kHasSwitchToGain6_pho1 = 0;
   RecHitFlag_kHasSwitchToGain1_pho1 = 0;
   RecHitFlag_kESGood_pho1 = 0;
   RecHitFlag_kESDead_pho1 = 0;
   RecHitFlag_kESHot_pho1 = 0;
   RecHitFlag_kESPassBX_pho1 = 0;
   RecHitFlag_kESTwoGoodRatios_pho1 = 0;
   RecHitFlag_kESBadRatioFor12_pho1 = 0;
   RecHitFlag_kESBadRatioFor23Upper_pho1 = 0;
   RecHitFlag_kESBadRatioFor23Lower_pho1 = 0;
   RecHitFlag_kESTS1Largest_pho1 = 0;
   RecHitFlag_kESTS3Largest_pho1 = 0;
   RecHitFlag_kESTS3Negative_pho1 = 0;
   RecHitFlag_kESSaturated_pho1 = 0;
   RecHitFlag_kESTS2Saturated_pho1 = 0;
   RecHitFlag_kESTS3Saturated_pho1 = 0;
   RecHitFlag_kESTS13Sigmas_pho1 = 0;
   RecHitFlag_kESTS15Sigmas_pho1 = 0;
   iEtaPho2 = 0;
   iPhiPho2 = 0;
   Hit_ES_Eta_Pho2 = 0;
   Hit_ES_Phi_Pho2 = 0;
   Hit_ES_X_Pho2 = 0;
   Hit_ES_Y_Pho2 = 0;
   Hit_ES_Z_Pho2 = 0;
   ES_RecHitEnPho2 = 0;
   Hit_Eta_Pho2 = 0;
   Hit_Phi_Pho2 = 0;
   Hit_X_Pho2 = 0;
   Hit_Y_Pho2 = 0;
   Hit_Z_Pho2 = 0;
   RecHitEnPho2 = 0;
   RecHitFracPho2 = 0;
   RecHitGain2 = 0;
   RecHitQuality2 = 0;
   HitNoisePho2 = 0;
   RecHitFlag_kGood_pho2 = 0;
   RecHitFlag_kPoorReco_pho2 = 0;
   RecHitFlag_kOutOfTime_pho2 = 0;
   RecHitFlag_kFaultyHardware_pho2 = 0;
   RecHitFlag_kNoisy_pho2 = 0;
   RecHitFlag_kPoorCalib_pho2 = 0;
   RecHitFlag_kSaturated_pho2 = 0;
   RecHitFlag_kLeadingEdgeRecovered_pho2 = 0;
   RecHitFlag_kNeighboursRecovered_pho2 = 0;
   RecHitFlag_kTowerRecovered_pho2 = 0;
   RecHitFlag_kDead_pho2 = 0;
   RecHitFlag_kKilled_pho2 = 0;
   RecHitFlag_kTPSaturated_pho2 = 0;
   RecHitFlag_kL1SpikeFlag_pho2 = 0;
   RecHitFlag_kWeird_pho2 = 0;
   RecHitFlag_kDiWeird_pho2 = 0;
   RecHitFlag_kHasSwitchToGain6_pho2 = 0;
   RecHitFlag_kHasSwitchToGain1_pho2 = 0;
   RecHitFlag_kESGood_pho2 = 0;
   RecHitFlag_kESDead_pho2 = 0;
   RecHitFlag_kESHot_pho2 = 0;
   RecHitFlag_kESPassBX_pho2 = 0;
   RecHitFlag_kESTwoGoodRatios_pho2 = 0;
   RecHitFlag_kESBadRatioFor12_pho2 = 0;
   RecHitFlag_kESBadRatioFor23Upper_pho2 = 0;
   RecHitFlag_kESBadRatioFor23Lower_pho2 = 0;
   RecHitFlag_kESTS1Largest_pho2 = 0;
   RecHitFlag_kESTS3Largest_pho2 = 0;
   RecHitFlag_kESTS3Negative_pho2 = 0;
   RecHitFlag_kESSaturated_pho2 = 0;
   RecHitFlag_kESTS2Saturated_pho2 = 0;
   RecHitFlag_kESTS3Saturated_pho2 = 0;
   RecHitFlag_kESTS13Sigmas_pho2 = 0;
   RecHitFlag_kESTS15Sigmas_pho2 = 0;
   pt = 0;
   eta = 0;
   phi = 0;
   Pho_cluster_seed_x = 0;
   Pho_cluster_seed_y = 0;
   Pho_cluster_seed_z = 0;
   Pho_cluster_seed_eta = 0;
   Pho_cluster_seed_phi = 0;
   energy = 0;
   energy_ecal_mustache = 0;
   passMediumId = 0;
   passTightId = 0;
   passMVAMediumId = 0;
   Pho_R9 = 0;
   Pho_S4 = 0;
   Pho_SigIEIE = 0;
   Pho_SigIPhiIPhi = 0;
   Pho_SCEtaW = 0;
   Pho_SCPhiW = 0;
   Pho_CovIEtaIEta = 0;
   Pho_CovIEtaIPhi = 0;
   Pho_ESSigRR = 0;
   Pho_SCRawE = 0;
   Pho_SC_ESEnByRawE = 0;
   Pho_HadOverEm = 0;
   Pho_PFChIso = 0;
   Pho_PFChPVIso = 0;
   Pho_PFPhoIso = 0;
   Pho_PFNeuIso = 0;
   Pho_PFChWorstVetoIso = 0;
   Pho_PFChWorstIso = 0;
   Pho_EcalPFClusterIso = 0;
   Pho_HcalPFClusterIso = 0;
   Pho_CorrectedEnergy = 0;
   Pho_CorrectedEnergyError = 0;
   A_Gen_mass = 0;
   A_Gen_pt = 0;
   A_Gen_eta = 0;
   A_Gen_phi = 0;
   Pho_Gen_Pt = 0;
   Pho_Gen_Eta = 0;
   Pho_Gen_Phi = 0;
   Pho_Gen_E = 0;
  // Set branch addresses and branch pointers
  //Modified by Somanko
   iEtaPho1 = 0;
   iPhiPho1 = 0;
   Hit_ES_Eta_Pho1 = 0;
   Hit_ES_Phi_Pho1 = 0;
   Hit_ES_X_Pho1 = 0;
   Hit_ES_Y_Pho1 = 0;
   Hit_ES_Z_Pho1 = 0;
   ES_RecHitEnPho1 = 0;
   Hit_Eta_Pho1 = 0;
   Hit_Phi_Pho1 = 0;
   Hit_X_Pho1 = 0;
   Hit_Y_Pho1 = 0;
   Hit_Z_Pho1 = 0;
   RecHitEnPho1 = 0;
   RecHitFracPho1 = 0;
   RecHitGain1 = 0;
   RecHitQuality1 = 0;
   HitNoisePho1 = 0;
   dRHit_Eta_Pho1 = 0;
   dRHit_Phi_Pho1 = 0;
   RawHit_Eta_Pho1 = 0;
   RawHit_Phi_Pho1 = 0;
   RawRecHitEnPho1 = 0;
   RawRecHit_X_Pho1 = 0;
   RawRecHit_Y_Pho1 = 0;
   RawRecHit_Z_Pho1 = 0;
   RawHit_Eta_Pho2 = 0;
   RawHit_Phi_Pho2 = 0;
   RawRecHitEnPho2 = 0;
   RawRecHit_X_Pho2 = 0;
   RawRecHit_Y_Pho2 = 0;
   RawRecHit_Z_Pho2 = 0;
   dRHit_X_Pho1 = 0;
   dRHit_Y_Pho1 = 0;
   dRHit_Z_Pho1 = 0;
   dRRecHitEnPho1 = 0;
   dRRecHitFracPho1 = 0;
   dRHit_Eta_Pho2 = 0;
   dRHit_Phi_Pho2 = 0;
   dRHit_X_Pho2 = 0;
   dRHit_Y_Pho2 = 0;
   dRHit_Z_Pho2 = 0;
   dRRecHitEnPho2 = 0;
   dRRecHitFracPho2 = 0;
   RecHitFlag_kGood_pho1 = 0;
   RecHitFlag_kPoorReco_pho1 = 0;
   RecHitFlag_kOutOfTime_pho1 = 0;
   RecHitFlag_kFaultyHardware_pho1 = 0;
   RecHitFlag_kNoisy_pho1 = 0;
   RecHitFlag_kPoorCalib_pho1 = 0;
   RecHitFlag_kSaturated_pho1 = 0;
   RecHitFlag_kLeadingEdgeRecovered_pho1 = 0;
   RecHitFlag_kNeighboursRecovered_pho1 = 0;
   RecHitFlag_kTowerRecovered_pho1 = 0;
   RecHitFlag_kDead_pho1 = 0;
   RecHitFlag_kKilled_pho1 = 0;
   RecHitFlag_kTPSaturated_pho1 = 0;
   RecHitFlag_kL1SpikeFlag_pho1 = 0;
   RecHitFlag_kWeird_pho1 = 0;
   RecHitFlag_kDiWeird_pho1 = 0;
   RecHitFlag_kHasSwitchToGain6_pho1 = 0;
   RecHitFlag_kHasSwitchToGain1_pho1 = 0;
   RecHitFlag_kESGood_pho1 = 0;
   RecHitFlag_kESDead_pho1 = 0;
   RecHitFlag_kESHot_pho1 = 0;
   RecHitFlag_kESPassBX_pho1 = 0;
   RecHitFlag_kESTwoGoodRatios_pho1 = 0;
   RecHitFlag_kESBadRatioFor12_pho1 = 0;
   RecHitFlag_kESBadRatioFor23Upper_pho1 = 0;
   RecHitFlag_kESBadRatioFor23Lower_pho1 = 0;
   RecHitFlag_kESTS1Largest_pho1 = 0;
   RecHitFlag_kESTS3Largest_pho1 = 0;
   RecHitFlag_kESTS3Negative_pho1 = 0;
   RecHitFlag_kESSaturated_pho1 = 0;
   RecHitFlag_kESTS2Saturated_pho1 = 0;
   RecHitFlag_kESTS3Saturated_pho1 = 0;
   RecHitFlag_kESTS13Sigmas_pho1 = 0;
   RecHitFlag_kESTS15Sigmas_pho1 = 0;
   iEtaPho2 = 0;
   iPhiPho2 = 0;
   Hit_ES_Eta_Pho2 = 0;
   Hit_ES_Phi_Pho2 = 0;
   Hit_ES_X_Pho2 = 0;
   Hit_ES_Y_Pho2 = 0;
   Hit_ES_Z_Pho2 = 0;
   ES_RecHitEnPho2 = 0;
   Hit_Eta_Pho2 = 0;
   Hit_Phi_Pho2 = 0;
   Hit_X_Pho2 = 0;
   Hit_Y_Pho2 = 0;
   Hit_Z_Pho2 = 0;
   RecHitEnPho2 = 0;
   RecHitFracPho2 = 0;
   RecHitGain2 = 0;
   RecHitQuality2 = 0;
   HitNoisePho2 = 0;
   RecHitFlag_kGood_pho2 = 0;
   RecHitFlag_kPoorReco_pho2 = 0;
   RecHitFlag_kOutOfTime_pho2 = 0;
   RecHitFlag_kFaultyHardware_pho2 = 0;
   RecHitFlag_kNoisy_pho2 = 0;
   RecHitFlag_kPoorCalib_pho2 = 0;
   RecHitFlag_kSaturated_pho2 = 0;
   RecHitFlag_kLeadingEdgeRecovered_pho2 = 0;
   RecHitFlag_kNeighboursRecovered_pho2 = 0;
   RecHitFlag_kTowerRecovered_pho2 = 0;
   RecHitFlag_kDead_pho2 = 0;
   RecHitFlag_kKilled_pho2 = 0;
   RecHitFlag_kTPSaturated_pho2 = 0;
   RecHitFlag_kL1SpikeFlag_pho2 = 0;
   RecHitFlag_kWeird_pho2 = 0;
   RecHitFlag_kDiWeird_pho2 = 0;
   RecHitFlag_kHasSwitchToGain6_pho2 = 0;
   RecHitFlag_kHasSwitchToGain1_pho2 = 0;
   RecHitFlag_kESGood_pho2 = 0;
   RecHitFlag_kESDead_pho2 = 0;
   RecHitFlag_kESHot_pho2 = 0;
   RecHitFlag_kESPassBX_pho2 = 0;
   RecHitFlag_kESTwoGoodRatios_pho2 = 0;
   RecHitFlag_kESBadRatioFor12_pho2 = 0;
   RecHitFlag_kESBadRatioFor23Upper_pho2 = 0;
   RecHitFlag_kESBadRatioFor23Lower_pho2 = 0;
   RecHitFlag_kESTS1Largest_pho2 = 0;
   RecHitFlag_kESTS3Largest_pho2 = 0;
   RecHitFlag_kESTS3Negative_pho2 = 0;
   RecHitFlag_kESSaturated_pho2 = 0;
   RecHitFlag_kESTS2Saturated_pho2 = 0;
   RecHitFlag_kESTS3Saturated_pho2 = 0;
   RecHitFlag_kESTS13Sigmas_pho2 = 0;
   RecHitFlag_kESTS15Sigmas_pho2 = 0;
   pt = 0;
   eta = 0;
   phi = 0;
   Pho_cluster_seed_x = 0;
   Pho_cluster_seed_y = 0;
   Pho_cluster_seed_z = 0;
   Pho_cluster_seed_eta = 0;
   Pho_cluster_seed_phi = 0;
   energy = 0;
   energy_ecal_mustache = 0;
   passMediumId = 0;
   passTightId = 0;
   passMVAMediumId = 0;
   Pho_R9 = 0;
   Pho_S4 = 0;
   Pho_SigIEIE = 0;
   Pho_SigIPhiIPhi = 0;
   Pho_SCEtaW = 0;
   Pho_SCPhiW = 0;
   Pho_CovIEtaIEta = 0;
   Pho_CovIEtaIPhi = 0;
   Pho_ESSigRR = 0;
   Pho_SCRawE = 0;
   Pho_SC_ESEnByRawE = 0;
   Pho_HadOverEm = 0;
   Pho_PFChIso = 0;
   Pho_PFChPVIso = 0;
   Pho_PFPhoIso = 0;
   Pho_PFNeuIso = 0;
   Pho_PFChWorstVetoIso = 0;
   Pho_PFChWorstIso = 0;
   Pho_EcalPFClusterIso = 0;
   Pho_HcalPFClusterIso = 0;
   Pho_CorrectedEnergy = 0;
   Pho_CorrectedEnergyError = 0;
   A_Gen_mass = 0;
   A_Gen_pt = 0;
   A_Gen_eta = 0;
   A_Gen_phi = 0;
   Pho_Gen_Pt = 0;
   Pho_Gen_Eta = 0;
   Pho_Gen_Phi = 0;
   Pho_Gen_E = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);
fChain->SetBranchAddress("iEtaPho1", &iEtaPho1, &b_iEtaPho1);
   fChain->SetBranchAddress("iPhiPho1", &iPhiPho1, &b_iPhiPho1);
   fChain->SetBranchAddress("Hit_ES_Eta_Pho1", &Hit_ES_Eta_Pho1, &b_Hit_ES_Eta_Pho1);
   fChain->SetBranchAddress("Hit_ES_Phi_Pho1", &Hit_ES_Phi_Pho1, &b_Hit_ES_Phi_Pho1);
   fChain->SetBranchAddress("Hit_ES_X_Pho1", &Hit_ES_X_Pho1, &b_Hit_ES_X_Pho1);
   fChain->SetBranchAddress("Hit_ES_Y_Pho1", &Hit_ES_Y_Pho1, &b_Hit_ES_Y_Pho1);
   fChain->SetBranchAddress("Hit_ES_Z_Pho1", &Hit_ES_Z_Pho1, &b_Hit_ES_Z_Pho1);
   fChain->SetBranchAddress("ES_RecHitEnPho1", &ES_RecHitEnPho1, &b_ES_RecHitEnPho1);
   fChain->SetBranchAddress("Hit_Eta_Pho1", &Hit_Eta_Pho1, &b_Hit_Eta_Pho1);
   fChain->SetBranchAddress("Hit_Phi_Pho1", &Hit_Phi_Pho1, &b_Hit_Phi_Pho1);
   fChain->SetBranchAddress("Hit_X_Pho1", &Hit_X_Pho1, &b_Hit_X_Pho1);
   fChain->SetBranchAddress("Hit_Y_Pho1", &Hit_Y_Pho1, &b_Hit_Y_Pho1);
   fChain->SetBranchAddress("Hit_Z_Pho1", &Hit_Z_Pho1, &b_Hit_Z_Pho1);
   fChain->SetBranchAddress("RecHitEnPho1", &RecHitEnPho1, &b_RecHitEnPho1);
   fChain->SetBranchAddress("RecHitFracPho1", &RecHitFracPho1, &b_RecHitFracPho1);
   fChain->SetBranchAddress("RecHitGain1", &RecHitGain1, &b_RecHitGain1);
   fChain->SetBranchAddress("RecHitQuality1", &RecHitQuality1, &b_RecHitQuality1);
   fChain->SetBranchAddress("HitNoisePho1", &HitNoisePho1, &b_HitNoisePho1);
   fChain->SetBranchAddress("dRHit_Eta_Pho1", &dRHit_Eta_Pho1, &b_dRHit_Eta_Pho1);
   fChain->SetBranchAddress("dRHit_Phi_Pho1", &dRHit_Phi_Pho1, &b_dRHit_Phi_Pho1);
   fChain->SetBranchAddress("RawHit_Eta_Pho1", &RawHit_Eta_Pho1, &b_RawHit_Eta_Pho1);
   fChain->SetBranchAddress("RawHit_Phi_Pho1", &RawHit_Phi_Pho1, &b_RawHit_Phi_Pho1);
   fChain->SetBranchAddress("RawRecHitEnPho1", &RawRecHitEnPho1, &b_RawRecHitEnPho1);
   fChain->SetBranchAddress("RawRecHit_X_Pho1", &RawRecHit_X_Pho1, &b_RawRecHit_X_Pho1);
   fChain->SetBranchAddress("RawRecHit_Y_Pho1", &RawRecHit_Y_Pho1, &b_RawRecHit_Y_Pho1);
   fChain->SetBranchAddress("RawRecHit_Z_Pho1", &RawRecHit_Z_Pho1, &b_RawRecHit_Z_Pho1);
   fChain->SetBranchAddress("RawHit_Eta_Pho2", &RawHit_Eta_Pho2, &b_RawHit_Eta_Pho2);
   fChain->SetBranchAddress("RawHit_Phi_Pho2", &RawHit_Phi_Pho2, &b_RawHit_Phi_Pho2);
   fChain->SetBranchAddress("RawRecHitEnPho2", &RawRecHitEnPho2, &b_RawRecHitEnPho2);
   fChain->SetBranchAddress("RawRecHit_X_Pho2", &RawRecHit_X_Pho2, &b_RawRecHit_X_Pho2);
   fChain->SetBranchAddress("RawRecHit_Y_Pho2", &RawRecHit_Y_Pho2, &b_RawRecHit_Y_Pho2);
   fChain->SetBranchAddress("RawRecHit_Z_Pho2", &RawRecHit_Z_Pho2, &b_RawRecHit_Z_Pho2);
   fChain->SetBranchAddress("dRHit_X_Pho1", &dRHit_X_Pho1, &b_dRHit_X_Pho1);
   fChain->SetBranchAddress("dRHit_Y_Pho1", &dRHit_Y_Pho1, &b_dRHit_Y_Pho1);
   fChain->SetBranchAddress("dRHit_Z_Pho1", &dRHit_Z_Pho1, &b_dRHit_Z_Pho1);
   fChain->SetBranchAddress("dRRecHitEnPho1", &dRRecHitEnPho1, &b_dRRecHitEnPho1);
   fChain->SetBranchAddress("dRRecHitFracPho1", &dRRecHitFracPho1, &b_dRRecHitFracPho1);
   fChain->SetBranchAddress("dRHit_Eta_Pho2", &dRHit_Eta_Pho2, &b_dRHit_Eta_Pho2);
   fChain->SetBranchAddress("dRHit_Phi_Pho2", &dRHit_Phi_Pho2, &b_dRHit_Phi_Pho2);
   fChain->SetBranchAddress("dRHit_X_Pho2", &dRHit_X_Pho2, &b_dRHit_X_Pho2);
   fChain->SetBranchAddress("dRHit_Y_Pho2", &dRHit_Y_Pho2, &b_dRHit_Y_Pho2);
   fChain->SetBranchAddress("dRHit_Z_Pho2", &dRHit_Z_Pho2, &b_dRHit_Z_Pho2);
   fChain->SetBranchAddress("dRRecHitEnPho2", &dRRecHitEnPho2, &b_dRRecHitEnPho2);
   fChain->SetBranchAddress("dRRecHitFracPho2", &dRRecHitFracPho2, &b_dRRecHitFracPho2);
   fChain->SetBranchAddress("RecHitFlag_kGood_pho1", &RecHitFlag_kGood_pho1, &b_RecHitFlag_kGood_pho1);
   fChain->SetBranchAddress("RecHitFlag_kPoorReco_pho1", &RecHitFlag_kPoorReco_pho1, &b_RecHitFlag_kPoorReco_pho1);
   fChain->SetBranchAddress("RecHitFlag_kOutOfTime_pho1", &RecHitFlag_kOutOfTime_pho1, &b_RecHitFlag_kOutOfTime_pho1);
   fChain->SetBranchAddress("RecHitFlag_kFaultyHardware_pho1", &RecHitFlag_kFaultyHardware_pho1, &b_RecHitFlag_kFaultyHardware_pho1);
   fChain->SetBranchAddress("RecHitFlag_kNoisy_pho1", &RecHitFlag_kNoisy_pho1, &b_RecHitFlag_kNoisy_pho1);
   fChain->SetBranchAddress("RecHitFlag_kPoorCalib_pho1", &RecHitFlag_kPoorCalib_pho1, &b_RecHitFlag_kPoorCalib_pho1);
   fChain->SetBranchAddress("RecHitFlag_kSaturated_pho1", &RecHitFlag_kSaturated_pho1, &b_RecHitFlag_kSaturated_pho1);
   fChain->SetBranchAddress("RecHitFlag_kLeadingEdgeRecovered_pho1", &RecHitFlag_kLeadingEdgeRecovered_pho1, &b_RecHitFlag_kLeadingEdgeRecovered_pho1);
   fChain->SetBranchAddress("RecHitFlag_kNeighboursRecovered_pho1", &RecHitFlag_kNeighboursRecovered_pho1, &b_RecHitFlag_kNeighboursRecovered_pho1);
   fChain->SetBranchAddress("RecHitFlag_kTowerRecovered_pho1", &RecHitFlag_kTowerRecovered_pho1, &b_RecHitFlag_kTowerRecovered_pho1);
   fChain->SetBranchAddress("RecHitFlag_kDead_pho1", &RecHitFlag_kDead_pho1, &b_RecHitFlag_kDead_pho1);
   fChain->SetBranchAddress("RecHitFlag_kKilled_pho1", &RecHitFlag_kKilled_pho1, &b_RecHitFlag_kKilled_pho1);
   fChain->SetBranchAddress("RecHitFlag_kTPSaturated_pho1", &RecHitFlag_kTPSaturated_pho1, &b_RecHitFlag_kTPSaturated_pho1);
   fChain->SetBranchAddress("RecHitFlag_kL1SpikeFlag_pho1", &RecHitFlag_kL1SpikeFlag_pho1, &b_RecHitFlag_kL1SpikeFlag_pho1);
   fChain->SetBranchAddress("RecHitFlag_kWeird_pho1", &RecHitFlag_kWeird_pho1, &b_RecHitFlag_kWeird_pho1);
   fChain->SetBranchAddress("RecHitFlag_kDiWeird_pho1", &RecHitFlag_kDiWeird_pho1, &b_RecHitFlag_kDiWeird_pho1);
   fChain->SetBranchAddress("RecHitFlag_kHasSwitchToGain6_pho1", &RecHitFlag_kHasSwitchToGain6_pho1, &b_RecHitFlag_kHasSwitchToGain6_pho1);
   fChain->SetBranchAddress("RecHitFlag_kHasSwitchToGain1_pho1", &RecHitFlag_kHasSwitchToGain1_pho1, &b_RecHitFlag_kHasSwitchToGain1_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESGood_pho1", &RecHitFlag_kESGood_pho1, &b_RecHitFlag_kESGood_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESDead_pho1", &RecHitFlag_kESDead_pho1, &b_RecHitFlag_kESDead_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESHot_pho1", &RecHitFlag_kESHot_pho1, &b_RecHitFlag_kESHot_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESPassBX_pho1", &RecHitFlag_kESPassBX_pho1, &b_RecHitFlag_kESPassBX_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESTwoGoodRatios_pho1", &RecHitFlag_kESTwoGoodRatios_pho1, &b_RecHitFlag_kESTwoGoodRatios_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESBadRatioFor12_pho1", &RecHitFlag_kESBadRatioFor12_pho1, &b_RecHitFlag_kESBadRatioFor12_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESBadRatioFor23Upper_pho1", &RecHitFlag_kESBadRatioFor23Upper_pho1, &b_RecHitFlag_kESBadRatioFor23Upper_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESBadRatioFor23Lower_pho1", &RecHitFlag_kESBadRatioFor23Lower_pho1, &b_RecHitFlag_kESBadRatioFor23Lower_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESTS1Largest_pho1", &RecHitFlag_kESTS1Largest_pho1, &b_RecHitFlag_kESTS1Largest_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESTS3Largest_pho1", &RecHitFlag_kESTS3Largest_pho1, &b_RecHitFlag_kESTS3Largest_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESTS3Negative_pho1", &RecHitFlag_kESTS3Negative_pho1, &b_RecHitFlag_kESTS3Negative_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESSaturated_pho1", &RecHitFlag_kESSaturated_pho1, &b_RecHitFlag_kESSaturated_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESTS2Saturated_pho1", &RecHitFlag_kESTS2Saturated_pho1, &b_RecHitFlag_kESTS2Saturated_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESTS3Saturated_pho1", &RecHitFlag_kESTS3Saturated_pho1, &b_RecHitFlag_kESTS3Saturated_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESTS13Sigmas_pho1", &RecHitFlag_kESTS13Sigmas_pho1, &b_RecHitFlag_kESTS13Sigmas_pho1);
   fChain->SetBranchAddress("RecHitFlag_kESTS15Sigmas_pho1", &RecHitFlag_kESTS15Sigmas_pho1, &b_RecHitFlag_kESTS15Sigmas_pho1);
   fChain->SetBranchAddress("iEtaPho2", &iEtaPho2, &b_iEtaPho2);
   fChain->SetBranchAddress("iPhiPho2", &iPhiPho2, &b_iPhiPho2);
   fChain->SetBranchAddress("Hit_ES_Eta_Pho2", &Hit_ES_Eta_Pho2, &b_Hit_ES_Eta_Pho2);
   fChain->SetBranchAddress("Hit_ES_Phi_Pho2", &Hit_ES_Phi_Pho2, &b_Hit_ES_Phi_Pho2);
   fChain->SetBranchAddress("Hit_ES_X_Pho2", &Hit_ES_X_Pho2, &b_Hit_ES_X_Pho2);
   fChain->SetBranchAddress("Hit_ES_Y_Pho2", &Hit_ES_Y_Pho2, &b_Hit_ES_Y_Pho2);
   fChain->SetBranchAddress("Hit_ES_Z_Pho2", &Hit_ES_Z_Pho2, &b_Hit_ES_Z_Pho2);
   fChain->SetBranchAddress("ES_RecHitEnPho2", &ES_RecHitEnPho2, &b_ES_RecHitEnPho2);
   fChain->SetBranchAddress("Hit_Eta_Pho2", &Hit_Eta_Pho2, &b_Hit_Eta_Pho2);
   fChain->SetBranchAddress("Hit_Phi_Pho2", &Hit_Phi_Pho2, &b_Hit_Phi_Pho2);
   fChain->SetBranchAddress("Hit_X_Pho2", &Hit_X_Pho2, &b_Hit_X_Pho2);
   fChain->SetBranchAddress("Hit_Y_Pho2", &Hit_Y_Pho2, &b_Hit_Y_Pho2);
   fChain->SetBranchAddress("Hit_Z_Pho2", &Hit_Z_Pho2, &b_Hit_Z_Pho2);
   fChain->SetBranchAddress("RecHitEnPho2", &RecHitEnPho2, &b_RecHitEnPho2);
   fChain->SetBranchAddress("RecHitFracPho2", &RecHitFracPho2, &b_RecHitFracPho2);
   fChain->SetBranchAddress("RecHitGain2", &RecHitGain2, &b_RecHitGain2);
   fChain->SetBranchAddress("RecHitQuality2", &RecHitQuality2, &b_RecHitQuality2);
   fChain->SetBranchAddress("HitNoisePho2", &HitNoisePho2, &b_HitNoisePho2);
   fChain->SetBranchAddress("RecHitFlag_kGood_pho2", &RecHitFlag_kGood_pho2, &b_RecHitFlag_kGood_pho2);
   fChain->SetBranchAddress("RecHitFlag_kPoorReco_pho2", &RecHitFlag_kPoorReco_pho2, &b_RecHitFlag_kPoorReco_pho2);
   fChain->SetBranchAddress("RecHitFlag_kOutOfTime_pho2", &RecHitFlag_kOutOfTime_pho2, &b_RecHitFlag_kOutOfTime_pho2);
   fChain->SetBranchAddress("RecHitFlag_kFaultyHardware_pho2", &RecHitFlag_kFaultyHardware_pho2, &b_RecHitFlag_kFaultyHardware_pho2);
   fChain->SetBranchAddress("RecHitFlag_kNoisy_pho2", &RecHitFlag_kNoisy_pho2, &b_RecHitFlag_kNoisy_pho2);
   fChain->SetBranchAddress("RecHitFlag_kPoorCalib_pho2", &RecHitFlag_kPoorCalib_pho2, &b_RecHitFlag_kPoorCalib_pho2);
   fChain->SetBranchAddress("RecHitFlag_kSaturated_pho2", &RecHitFlag_kSaturated_pho2, &b_RecHitFlag_kSaturated_pho2);
   fChain->SetBranchAddress("RecHitFlag_kLeadingEdgeRecovered_pho2", &RecHitFlag_kLeadingEdgeRecovered_pho2, &b_RecHitFlag_kLeadingEdgeRecovered_pho2);
   fChain->SetBranchAddress("RecHitFlag_kNeighboursRecovered_pho2", &RecHitFlag_kNeighboursRecovered_pho2, &b_RecHitFlag_kNeighboursRecovered_pho2);
   fChain->SetBranchAddress("RecHitFlag_kTowerRecovered_pho2", &RecHitFlag_kTowerRecovered_pho2, &b_RecHitFlag_kTowerRecovered_pho2);
   fChain->SetBranchAddress("RecHitFlag_kDead_pho2", &RecHitFlag_kDead_pho2, &b_RecHitFlag_kDead_pho2);
   fChain->SetBranchAddress("RecHitFlag_kKilled_pho2", &RecHitFlag_kKilled_pho2, &b_RecHitFlag_kKilled_pho2);
   fChain->SetBranchAddress("RecHitFlag_kTPSaturated_pho2", &RecHitFlag_kTPSaturated_pho2, &b_RecHitFlag_kTPSaturated_pho2);
   fChain->SetBranchAddress("RecHitFlag_kL1SpikeFlag_pho2", &RecHitFlag_kL1SpikeFlag_pho2, &b_RecHitFlag_kL1SpikeFlag_pho2);
   fChain->SetBranchAddress("RecHitFlag_kWeird_pho2", &RecHitFlag_kWeird_pho2, &b_RecHitFlag_kWeird_pho2);
   fChain->SetBranchAddress("RecHitFlag_kDiWeird_pho2", &RecHitFlag_kDiWeird_pho2, &b_RecHitFlag_kDiWeird_pho2);
   fChain->SetBranchAddress("RecHitFlag_kHasSwitchToGain6_pho2", &RecHitFlag_kHasSwitchToGain6_pho2, &b_RecHitFlag_kHasSwitchToGain6_pho2);
   fChain->SetBranchAddress("RecHitFlag_kHasSwitchToGain1_pho2", &RecHitFlag_kHasSwitchToGain1_pho2, &b_RecHitFlag_kHasSwitchToGain1_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESGood_pho2", &RecHitFlag_kESGood_pho2, &b_RecHitFlag_kESGood_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESDead_pho2", &RecHitFlag_kESDead_pho2, &b_RecHitFlag_kESDead_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESHot_pho2", &RecHitFlag_kESHot_pho2, &b_RecHitFlag_kESHot_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESPassBX_pho2", &RecHitFlag_kESPassBX_pho2, &b_RecHitFlag_kESPassBX_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESTwoGoodRatios_pho2", &RecHitFlag_kESTwoGoodRatios_pho2, &b_RecHitFlag_kESTwoGoodRatios_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESBadRatioFor12_pho2", &RecHitFlag_kESBadRatioFor12_pho2, &b_RecHitFlag_kESBadRatioFor12_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESBadRatioFor23Upper_pho2", &RecHitFlag_kESBadRatioFor23Upper_pho2, &b_RecHitFlag_kESBadRatioFor23Upper_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESBadRatioFor23Lower_pho2", &RecHitFlag_kESBadRatioFor23Lower_pho2, &b_RecHitFlag_kESBadRatioFor23Lower_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESTS1Largest_pho2", &RecHitFlag_kESTS1Largest_pho2, &b_RecHitFlag_kESTS1Largest_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESTS3Largest_pho2", &RecHitFlag_kESTS3Largest_pho2, &b_RecHitFlag_kESTS3Largest_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESTS3Negative_pho2", &RecHitFlag_kESTS3Negative_pho2, &b_RecHitFlag_kESTS3Negative_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESSaturated_pho2", &RecHitFlag_kESSaturated_pho2, &b_RecHitFlag_kESSaturated_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESTS2Saturated_pho2", &RecHitFlag_kESTS2Saturated_pho2, &b_RecHitFlag_kESTS2Saturated_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESTS3Saturated_pho2", &RecHitFlag_kESTS3Saturated_pho2, &b_RecHitFlag_kESTS3Saturated_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESTS13Sigmas_pho2", &RecHitFlag_kESTS13Sigmas_pho2, &b_RecHitFlag_kESTS13Sigmas_pho2);
   fChain->SetBranchAddress("RecHitFlag_kESTS15Sigmas_pho2", &RecHitFlag_kESTS15Sigmas_pho2, &b_RecHitFlag_kESTS15Sigmas_pho2);
   fChain->SetBranchAddress("nPhotons", &nPhotons, &b_nPho);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("eta", &eta, &b_eta);
   fChain->SetBranchAddress("phi", &phi, &b_phi);
   fChain->SetBranchAddress("Pho_cluster_seed_x", &Pho_cluster_seed_x, &b_Pho_cluster_seed_x);
   fChain->SetBranchAddress("Pho_cluster_seed_y", &Pho_cluster_seed_y, &b_Pho_cluster_seed_y);
   fChain->SetBranchAddress("Pho_cluster_seed_z", &Pho_cluster_seed_z, &b_Pho_cluster_seed_z);
   fChain->SetBranchAddress("Pho_cluster_seed_eta", &Pho_cluster_seed_eta, &b_Pho_cluster_seed_eta);
   fChain->SetBranchAddress("Pho_cluster_seed_phi", &Pho_cluster_seed_phi, &b_Pho_cluster_seed_phi);
   fChain->SetBranchAddress("energy", &energy, &b_energy);
   fChain->SetBranchAddress("energy_ecal_mustache", &energy_ecal_mustache, &b_energy_ecal_mustache);
   fChain->SetBranchAddress("passMediumId", &passMediumId, &b_passMediumId);
   fChain->SetBranchAddress("passTightId", &passTightId, &b_passTightId);
   fChain->SetBranchAddress("passMVAMediumId", &passMVAMediumId, &b_passMVAMediumId);
   fChain->SetBranchAddress("Pho_R9", &Pho_R9, &b_Pho_R9);
   fChain->SetBranchAddress("Pho_S4", &Pho_S4, &b_Pho_S4);
   fChain->SetBranchAddress("Pho_SigIEIE", &Pho_SigIEIE, &b_Pho_SigIEIE);
   fChain->SetBranchAddress("Pho_SigIPhiIPhi", &Pho_SigIPhiIPhi, &b_Pho_SigIPhiIPhi);
   fChain->SetBranchAddress("Pho_SCEtaW", &Pho_SCEtaW, &b_Pho_SCEtaW);
   fChain->SetBranchAddress("Pho_SCPhiW", &Pho_SCPhiW, &b_Pho_SCPhiW);
   fChain->SetBranchAddress("Pho_CovIEtaIEta", &Pho_CovIEtaIEta, &b_Pho_CovIEtaIEta);
   fChain->SetBranchAddress("Pho_CovIEtaIPhi", &Pho_CovIEtaIPhi, &b_Pho_CovIEtaIPhi);
   fChain->SetBranchAddress("Pho_ESSigRR", &Pho_ESSigRR, &b_Pho_ESSigRR);
   fChain->SetBranchAddress("Pho_SCRawE", &Pho_SCRawE, &b_Pho_SCRawE);
   fChain->SetBranchAddress("Pho_SC_ESEnByRawE", &Pho_SC_ESEnByRawE, &b_Pho_SC_ESEnByRawE);
   fChain->SetBranchAddress("Pho_HadOverEm", &Pho_HadOverEm, &b_Pho_HadOverEm);
   fChain->SetBranchAddress("Pho_PFChIso", &Pho_PFChIso, &b_Pho_PFChIso);
   fChain->SetBranchAddress("Pho_PFChPVIso", &Pho_PFChPVIso, &b_Pho_PFChPVIso);
   fChain->SetBranchAddress("Pho_PFPhoIso", &Pho_PFPhoIso, &b_Pho_PFPhoIso);
   fChain->SetBranchAddress("Pho_PFNeuIso", &Pho_PFNeuIso, &b_Pho_PFNeuIso);
   fChain->SetBranchAddress("Pho_PFChWorstVetoIso", &Pho_PFChWorstVetoIso, &b_Pho_PFChWorstVetoIso);
   fChain->SetBranchAddress("Pho_PFChWorstIso", &Pho_PFChWorstIso, &b_Pho_PFChWorstIso);
   fChain->SetBranchAddress("Pho_EcalPFClusterIso", &Pho_EcalPFClusterIso, &b_Pho_EcalPFClusterIso);
   fChain->SetBranchAddress("Pho_HcalPFClusterIso", &Pho_HcalPFClusterIso, &b_Pho_HcalPFClusterIso);
   fChain->SetBranchAddress("Pho_CorrectedEnergy", &Pho_CorrectedEnergy, &b_Pho_CorrectedEnergy);
   fChain->SetBranchAddress("Pho_CorrectedEnergyError", &Pho_CorrectedEnergyError, &b_Pho_CorrectedEnergyError);
   fChain->SetBranchAddress("A_Gen_mass", &A_Gen_mass, &b_A_Gen_mass);
   fChain->SetBranchAddress("A_Gen_pt", &A_Gen_pt, &b_A_Gen_pt);
   fChain->SetBranchAddress("A_Gen_eta", &A_Gen_eta, &b_A_Gen_eta);
   fChain->SetBranchAddress("A_Gen_phi", &A_Gen_phi, &b_A_Gen_phi);
   fChain->SetBranchAddress("Pho_Gen_Pt", &Pho_Gen_Pt, &b_Pho_Gen_Pt);
   fChain->SetBranchAddress("Pho_Gen_Eta", &Pho_Gen_Eta, &b_Pho_Gen_Eta);
   fChain->SetBranchAddress("Pho_Gen_Phi", &Pho_Gen_Phi, &b_Pho_Gen_Phi);
   fChain->SetBranchAddress("Pho_Gen_E", &Pho_Gen_E, &b_Pho_Gen_E);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);

  if (!tree)
    return;
  Notify();
  return;
  // End of modification by Chirayu
  //  Set branch addresses and branch pointers
  if (!tree2)
    return;
  fChain2 = tree2;
  fCurrent2 = -1;
  fChain2->SetMakeClass(1);

  Notify();
}

Bool_t HGCNtupleVariables::Notify() {
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

#endif // #ifdef HGCNtupleVariables_cxx
