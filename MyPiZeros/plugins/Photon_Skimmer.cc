
// -*- C++ -*-
//
// Package:    Electron_GNN_Regression/Photon_Skimmer
// Class:      Photon_Skimmer
//
/**\class Photon_Skimmer Photon_Skimmer.cc Electron_GNN_Regression/Photon_Skimmer/plugins/Photon_Skimmer.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Rajdeep Mohan Chatterjee
//         Created:  Fri, 21 Feb 2020 11:38:58 GMT
//
//


// system include files
#include <memory>
#include <iostream>
#include "TTree.h"
#include "Math/VectorUtil.h"
#include "TFile.h"
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/TruncatedPyramid.h"
#include "Geometry/EcalAlgo/interface/EcalPreshowerGeometry.h"
#include "Geometry/CaloTopology/interface/EcalPreshowerTopology.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"
#include "Geometry/CaloTopology/interface/CaloTopology.h"

#include "CondFormats/EcalObjects/interface/EcalPedestals.h"
#include "CondFormats/DataRecord/interface/EcalPedestalsRcd.h"

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/PatCandidates/interface/VIDCutFlowResult.h"

#include "DataFormats/EgammaReco/interface/SuperCluster.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "RecoEcal/EgammaCoreTools/interface/PositionCalc.h"

#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "TLorentzVector.h"

//
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


//using reco::TrackCollection;
using namespace edm;
using namespace std;
using namespace reco;

class Photon_Skimmer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit Photon_Skimmer(const edm::ParameterSet&);
      ~Photon_Skimmer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

      std::vector<std::vector<float>> Hit_ES_Eta;
      std::vector<std::vector<float>> Hit_ES_Phi;
      std::vector<std::vector<float>> Hit_ES_X;
      std::vector<std::vector<float>> Hit_ES_Y;
      std::vector<std::vector<float>> Hit_ES_Z;
      std::vector<std::vector<float>> ES_RecHitEn;

      std::vector<float> mHit_ES_Eta;
      std::vector<float> mHit_ES_Phi;
      std::vector<float> mHit_ES_X;
      std::vector<float> mHit_ES_Y;
      std::vector<float> mHit_ES_Z;
      std::vector<float> mES_RecHitEn;

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;


      bool DEBUG = false;


      //   cluster tools
      EcalClusterLazyTools *clustertools;
      EcalClusterLazyTools *clustertools_NoZS;
      edm::ESHandle<EcalPedestals> _ped;

      //   Identify if the SC lies in EB OR EE based on its seed
      bool isEB = 0;
      bool isEE = 0; // !isEB not sufficient since later will try to include the preshower as well


      //     bool GetGenMatchType(const reco::Photon& Photon, const reco::GenParticle& GenColl, int pdgId, double dRThresh);
      // Get the hits from the ES
      //     std::vector<GlobalPoint> GetESPlaneRecHits(const reco::SuperCluster& sc, unsigned int planeIndex) const;
      void GetESPlaneRecHits(const reco::SuperCluster& sc, const CaloGeometry* &geo, unsigned int phonum, unsigned int planeIndex);

      //   clear the vectors 
      void ClearTreeVectors();
      // ----------member data ---------------------------
      TTree* T;

      // Variables for Run info.
      int run;
      int event;
      int lumi;

      // Electron variables
      int nPhotons_;
      Float_t rho;
      std::vector<std::vector<float>> iEta;
      std::vector<std::vector<float>> iPhi;
      std::vector<std::vector<float>> Hit_Eta;
      std::vector<std::vector<float>> Hit_Phi;
      std::vector<std::vector<float>> Hit_X;
      std::vector<std::vector<float>> Hit_Y;
      std::vector<std::vector<float>> Hit_Z;
 	std::vector<float> recoPhotonIdx;


      std::vector<std::vector<float>> RecHitFrac;
      std::vector<std::vector<float>> RecHitEn;
      std::vector<std::vector<int>>   RecHitGain;
      std::vector<bool>  RecHitQuality;
      std::vector<std::vector<float>> HitNoise;

      // individual flags
      std::vector<bool> RecHitFlag_kGood;                   // channel ok, the energy and time measurement are reliable
      std::vector<bool> RecHitFlag_Endcap;                   // True if rechit belongs to an endcap supercluster
      std::vector<bool> RecHitFlag_kPoorReco;                 // the energy is available from the UncalibRecHit, but approximate (bad shape, large chi2)
      std::vector<bool> RecHitFlag_kOutOfTime;                // the energy is available from the UncalibRecHit (sync reco), but the event is out of time
      std::vector<bool> RecHitFlag_kFaultyHardware;           // The energy is available from the UncalibRecHit, channel is faulty at some hardware level (e.g. noisy)
      std::vector<bool> RecHitFlag_kNoisy;                    // the channel is very noisy
      std::vector<bool> RecHitFlag_kPoorCalib;                // the energy is available from the UncalibRecHit, but the calibration of the channel is poor
      std::vector<bool> RecHitFlag_kSaturated;                // saturated channel (recovery not tried)
      std::vector<bool> RecHitFlag_kLeadingEdgeRecovered;     // saturated channel: energy estimated from the leading edge before saturation
      std::vector<bool> RecHitFlag_kNeighboursRecovered;      // saturated/isolated dead: energy estimated from neighbours
      std::vector<bool> RecHitFlag_kTowerRecovered;           // channel in TT with no data link, info retrieved from Trigger Primitive
      std::vector<bool> RecHitFlag_kDead;                     // channel is dead and any recovery fails
      std::vector<bool> RecHitFlag_kKilled;                   // MC only flag: the channel is killed in the real detector
      std::vector<bool> RecHitFlag_kTPSaturated;              // the channel is in a region with saturated TP
      std::vector<bool> RecHitFlag_kL1SpikeFlag;              // the channel is in a region with TP with sFGVB = 0
      std::vector<bool> RecHitFlag_kWeird;                    // the signal is believed to originate from an anomalous deposit (spike) 
      std::vector<bool> RecHitFlag_kDiWeird;                  // the signal is anomalous, and neighbors another anomalous signal  
      std::vector<bool> RecHitFlag_kHasSwitchToGain6;         // at least one data frame is in G6
      std::vector<bool> RecHitFlag_kHasSwitchToGain1;         // at least one data frame is in G1

      // individual ES flags
      std::vector<bool> RecHitFlag_kESGood;
      std::vector<bool> RecHitFlag_kESDead;
      std::vector<bool> RecHitFlag_kESHot;
      std::vector<bool> RecHitFlag_kESPassBX;
      std::vector<bool> RecHitFlag_kESTwoGoodRatios;
      std::vector<bool> RecHitFlag_kESBadRatioFor12;
      std::vector<bool> RecHitFlag_kESBadRatioFor23Upper;
      std::vector<bool> RecHitFlag_kESBadRatioFor23Lower;
      std::vector<bool> RecHitFlag_kESTS1Largest;
      std::vector<bool> RecHitFlag_kESTS3Largest;
      std::vector<bool> RecHitFlag_kESTS3Negative;
      std::vector<bool> RecHitFlag_kESSaturated;
      std::vector<bool> RecHitFlag_kESTS2Saturated;
      std::vector<bool> RecHitFlag_kESTS3Saturated;
      std::vector<bool> RecHitFlag_kESTS13Sigmas;
      std::vector<bool> RecHitFlag_kESTS15Sigmas;

      std::vector<float> Pho_pt_;
      std::vector<float> Pho_eta_;
      std::vector<float> Pho_phi_;
      std::vector<float> Pho_energy_;
      std::vector<float> Pho_ecal_mustache_energy_;

      std::vector<float> Pho_R9;
      std::vector<float> Pho_S4;
      std::vector<float> Pho_SigIEIE;
      std::vector<float> Pho_SigIPhiIPhi;
      std::vector<float> Pho_SCEtaW;
      std::vector<float> Pho_SCPhiW;
      std::vector<float> Pho_CovIEtaIEta;
      std::vector<float> Pho_CovIEtaIPhi;
      std::vector<float> Pho_ESSigRR;
      std::vector<float> Pho_SCRawE;
      std::vector<float> Pho_SC_ESEnByRawE;
      std::vector<float> Pho_HadOverEm;

      std::vector<float> Pho_Gen_Pt;
      std::vector<float> Pho_Gen_Eta;
      std::vector<float> Pho_Gen_Phi;
      std::vector<float> Pho_Gen_E;
      std::vector<int> Pho_Gen_matchedIndex;
	std::vector<double> drminLead;
	std::vector<double> drminSubLead;
	std::vector<double> drminOther;


      std::vector<float> A_Gen_Pt;
      std::vector<float> A_Gen_Eta;
      std::vector<float> A_Gen_Phi;
      std::vector<float> A_Gen_E;

      std::vector<int> passLooseId_;
      std::vector<int> passMediumId_;
      std::vector<int> passTightId_;
      std::vector<int> passMVAMediumId_;

      std::vector<int> isTrue_;

      // -----------------Handles--------------------------
      edm::Handle<double> rhoHandle;
      edm::Handle<EcalRecHitCollection> EBRechitsHandle;
      edm::Handle<EcalRecHitCollection> EERechitsHandle;
      edm::Handle<EcalRecHitCollection> ESRechitsHandle;
      edm::Handle<edm::View<reco::Photon> > photons;
      edm::Handle<edm::View<reco::GenParticle> > genParticles;
      edm::Handle<edm::ValueMap<bool> > medium_id_decisions;
      edm::Handle<edm::ValueMap<bool> > tight_id_decisions;
      //---------------- Input Tags-----------------------
      edm::EDGetTokenT<double> rhoToken_;
      edm::EDGetTokenT<EcalRecHitCollection> recHitCollectionEBToken_;
      edm::EDGetTokenT<EcalRecHitCollection> recHitCollectionEEToken_;
      edm::EDGetTokenT<EcalRecHitCollection> recHitCollectionESToken_;
      edm::EDGetToken photonsToken_;
      edm::EDGetTokenT<edm::View<reco::GenParticle> > genParticlesToken_;
      edm::EDGetTokenT<edm::ValueMap<bool> > eleMediumIdMapToken_;
      edm::EDGetTokenT<edm::ValueMap<bool> > eleTightIdMapToken_;


};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
Photon_Skimmer::Photon_Skimmer(const edm::ParameterSet& iConfig):
   rhoToken_(consumes<double>(iConfig.getParameter<edm::InputTag>("rhoFastJet"))),
   recHitCollectionEBToken_(consumes<EcalRecHitCollection>(edm::InputTag("reducedEcalRecHitsEB"))),
   recHitCollectionEEToken_(consumes<EcalRecHitCollection>(edm::InputTag("reducedEcalRecHitsEE"))),
   recHitCollectionESToken_(consumes<EcalRecHitCollection>(edm::InputTag("reducedEcalRecHitsES"))),
   eleMediumIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleMediumIdMap"))),
   eleTightIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleTightIdMap")))
{
   //now do what ever initialization is needed
   photonsToken_ = mayConsume<edm::View<reco::Photon> >(iConfig.getParameter<edm::InputTag>("photons"));
   genParticlesToken_ = mayConsume<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("genParticles"));
   usesResource("TFileService");
}


Photon_Skimmer::~Photon_Skimmer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)




}


//
// member functions
//

// ------------ method called for each event  ------------
double MDeltaPhi(double phi1, double phi2) {
  double result = phi1 - phi2;
  while (result > M_PI)
    result -= 2 * M_PI;
  while (result <= -M_PI)
    result += 2 * M_PI;
  return result;
}

double MDeltaR(double eta1, double phi1, double eta2, double phi2) {
  double deta = eta1 - eta2;
  double dphi = MDeltaPhi(phi1, phi2);
  return std::sqrt(deta * deta + dphi * dphi);
}
bool photonsCompare(const reco::GenParticle& p1,const reco::GenParticle& p2)
{
	return ( p1.pt() > p2.pt());
}
   void
Photon_Skimmer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

   iEvent.getByToken(rhoToken_, rhoHandle);
   iEvent.getByToken(recHitCollectionEBToken_, EBRechitsHandle);
   iEvent.getByToken(recHitCollectionEEToken_, EERechitsHandle);
   iEvent.getByToken(recHitCollectionESToken_, ESRechitsHandle);
   iEvent.getByToken(photonsToken_, photons);
   iEvent.getByToken(genParticlesToken_, genParticles);
   iEvent.getByToken(eleMediumIdMapToken_, medium_id_decisions);
   iEvent.getByToken(eleTightIdMapToken_ , tight_id_decisions);


   ESHandle<CaloGeometry> pG;
   iSetup.get<CaloGeometryRecord>().get(pG);
   iSetup.get<EcalPedestalsRcd>().get(_ped);
   const CaloGeometry* geo = pG.product();
   const CaloSubdetectorGeometry* ecalEBGeom = static_cast<const CaloSubdetectorGeometry*>(geo->getSubdetectorGeometry(DetId::Ecal, EcalBarrel));
   const CaloSubdetectorGeometry* ecalEEGeom = static_cast<const CaloSubdetectorGeometry*>(geo->getSubdetectorGeometry(DetId::Ecal, EcalEndcap));

   /////////////////////////////PU related variables////////////////////////////////////////////////////
   rho = *rhoHandle;
   ///////////////////////////////////////////////////////////////////////////////////////////////////////


   clustertools_NoZS = new EcalClusterLazyTools(iEvent, iSetup, recHitCollectionEBToken_, recHitCollectionEEToken_);

   //Clear all vectors to be written to the tree
   ClearTreeVectors();
   run=0;  event=0;  lumi=0;

   ///////////////////////////Fill Electron/Photon related stuff/////////////////////////////////////////////////////
   nPhotons_ = 0;
//   const EcalRecHitCollection *recHitsEB = clustertools_NoZS->getEcalEBRecHitCollection();
 //  const EcalRecHitCollection *recHitsEE = clustertools_NoZS->getEcalEERecHitCollection();
const EcalRecHitCollection *recHitsEB = EBRechitsHandle.product();
const EcalRecHitCollection *recHitsEE = EERechitsHandle.product() ;
	
   for (size_t i = 0; i < photons->size(); ++i){
      //if (nPhotons_ == 2) break;
      const auto pho = photons->ptrAt(i);
      //if( pho->pt() < 10 ) continue;
      const SuperClusterRef& sc = pho->superCluster(); 
      //const SuperClusterRef& sc = pho->parentSuperCluster(); // mustache cluster
      std::vector< std::pair<DetId, float> > hitsAndFractions = sc->hitsAndFractions();
	//cout<<"Hits Size:"<<hitsAndFractions.size()<<endl;
      isEB = ((*sc->seed()).hitsAndFractions().at(0).first.subdetId() == EcalBarrel);
      isEE = ((*sc->seed()).hitsAndFractions().at(0).first.subdetId() == EcalEndcap);
      EBDetId* DidEB;
      EEDetId* DidEE;
      EcalRecHitCollection::const_iterator oneHit;
      std::vector<float> miEta;
      std::vector<float> miPhi;
      std::vector<float> mHit_Eta;
      std::vector<float> mHit_Phi;
      std::vector<float> mHit_X;
      std::vector<float> mHit_Y;
      std::vector<float> mHit_Z;

      std::vector<float> mRecHitFrac;
      std::vector<float> mRecHitEn;
      std::vector<int>   mRecHitGain;
      //std::vector<bool>  mRecHitQuality;
      std::vector<float> mHitNoise;
      for (const auto&  detitr : hitsAndFractions) {
         if(isEB){
            DidEB = new EBDetId(detitr.first.rawId());
            DetId Did   = detitr.first.rawId();
            shared_ptr<const CaloCellGeometry> geom = ecalEBGeom->getGeometry(Did);
            oneHit = recHitsEB->find( (detitr.first) ) ;
            miEta.push_back(DidEB->ieta());
            miPhi.push_back(DidEB->iphi());
            mHit_Eta.push_back(geom->etaPos());
            mHit_Phi.push_back(geom->phiPos());
            mHit_X.push_back(geom->getPosition().x());
            mHit_Y.push_back(geom->getPosition().y());
            mHit_Z.push_back(geom->getPosition().z());
         }
         else if(isEE){
            DidEE = new EEDetId(detitr.first.rawId());
            DetId Did   = detitr.first.rawId();
            shared_ptr<const CaloCellGeometry> geom = ecalEEGeom->getGeometry(Did);
            oneHit = recHitsEE->find( (detitr.first) ) ;
            miEta.push_back(DidEE->ix());
            miPhi.push_back(DidEE->iy());
            mHit_Eta.push_back(geom->etaPos());
            mHit_Phi.push_back(geom->phiPos());
            mHit_X.push_back(geom->getPosition().x());
            mHit_Y.push_back(geom->getPosition().y());
            mHit_Z.push_back(geom->getPosition().z());
         }
	recoPhotonIdx.push_back(i);

         mRecHitEn.push_back(oneHit->energy());
         mRecHitFrac.push_back(detitr.second);
//         if(oneHit->checkFlag(EcalRecHit::kGood))	mRecHitQuality.push_back(1);
 //        else mRecHitQuality.push_back(0);

//         for (int iflag=0; iflag<EcalRecHit::kHasSwitchToGain1+1; iflag++){
//           RecHitFlag_container[iflag]->push_back(oneHit->checkFlag(iflag));
//       }

         if (DEBUG) cout<<endl<<" Reco Flags = "<<oneHit->recoFlag()<<endl;

         if(oneHit->checkFlag(EcalRecHit::kHasSwitchToGain6)) 		mRecHitGain.push_back(6);
         else if(oneHit->checkFlag(EcalRecHit::kHasSwitchToGain1))            mRecHitGain.push_back(1);
         else mRecHitGain.push_back(12);
         mHitNoise.push_back(_ped->find(detitr.first)->rms(1));
      } //End of Rechit Loop 

	mHit_ES_X.clear();
	mHit_ES_Y.clear();
	mHit_ES_Z.clear();
	mHit_ES_Eta.clear();
        mES_RecHitEn.clear();
	mHit_ES_Phi.clear();
      if(isEE){
         GetESPlaneRecHits(*sc, geo, i, 1);     
         GetESPlaneRecHits(*sc, geo, i, 2);
      }
	
	
    	RecHitFlag_Endcap.push_back(isEE);
	Hit_ES_X.push_back(mHit_ES_X);
	Hit_ES_Y.push_back(mHit_ES_Y);
	Hit_ES_Z.push_back(mHit_ES_Z);
	Hit_ES_Eta.push_back(mHit_ES_Eta);
	Hit_ES_Phi.push_back(mHit_ES_Phi);
	ES_RecHitEn.push_back(mES_RecHitEn);

	Hit_X.push_back(mHit_X);
	Hit_Y.push_back(mHit_Y);
	Hit_Z.push_back(mHit_Z);
	Hit_Eta.push_back(mHit_Eta);
	Hit_Phi.push_back(mHit_Phi);

	iEta.push_back(miEta);
	iPhi.push_back(miPhi);

RecHitFrac.push_back(mRecHitFrac);
RecHitEn.push_back(mRecHitEn);
RecHitGain.push_back(mRecHitGain);
//RecHitQuality.push_back(mRecHitQuality);
HitNoise.push_back(mHitNoise);
      nPhotons_++;
      Pho_pt_.push_back( pho->pt() );
      Pho_eta_.push_back( sc->eta() );
      Pho_phi_.push_back( sc->phi() );
      Pho_energy_.push_back( pho->energy() );
      Pho_ecal_mustache_energy_.push_back( sc->energy() );
      Pho_R9.push_back(pho->full5x5_r9());
      Pho_SigIEIE.push_back(pho->full5x5_sigmaIetaIeta());
      Pho_SigIPhiIPhi.push_back(pho->full5x5_showerShapeVariables().sigmaIphiIphi);
      Pho_SCEtaW.push_back(sc->etaWidth());
      Pho_SCPhiW.push_back(sc->phiWidth());
      Pho_HadOverEm.push_back(pho->hadronicOverEm());
      const CaloClusterPtr seed_clu = sc->seed();
      //        if (!seed_clu) continue;
      //        Pho_CovIEtaIEta.push_back(clustertools_NoZS->localCovariances(*seed_clu)[0]);
      //        Pho_CovIEtaIPhi.push_back(clustertools_NoZS->localCovariances(*seed_clu)[1]);
      //	Pho_ESSigRR.push_back(clustertools->eseffsirir( *(sc) ) );
      Pho_SCRawE.push_back(sc->rawEnergy());
      Pho_SC_ESEnByRawE.push_back( (sc->preshowerEnergy())/(sc->rawEnergy()) );
      //        Pho_S4.push_back(clustertools_NoZS->e2x2( *seed_clu ) / clustertools_NoZS->e5x5( *seed_clu ) );

      ////// Look up and save the ID decisions
      //        bool isPassMedium = (*medium_id_decisions)[pho];
      //        bool isPassTight  = (*tight_id_decisions)[pho];
      //        passMediumId_.push_back( (int) isPassMedium);
      //        passTightId_.push_back ( (int) isPassTight );

   }

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////


   //////////////////////// Gen Stuff hardcaded for status 1 photons for now /////////////////////////////////////



 //  for(edm::View<GenParticle>::const_iterator part = genParticles->begin(); part != genParticles->end(); ++part){
 //     if( part->status()==1 && abs(part->pdgId())==22 ){
 //     }
 //  }

//std::sort(genParticles->begin(), genParticles->end(), photonsCompare);
      std::vector<reco::GenParticle> sortedParticles(genParticles->begin(), genParticles->end());
      std::sort(sortedParticles.begin(), sortedParticles.end(), photonsCompare);
using namespace std;
int matchedIdx[photons->size()];
std::fill(matchedIdx,matchedIdx+photons->size(), 0);
int genitr=0;
const reco::Candidate* mother;
mother = nullptr;
//   for(edm::View<GenParticle>::const_iterator part = genParticles->begin(); part != genParticles->end(); ++part){
for (const reco::GenParticle& part : sortedParticles) {
      if( part.status()==1 && abs(part.pdgId())==22 && part.mother()->pdgId() == 36 && genitr<2){
	double mindr=999;
	int matchedPhoton=-1;
	if(genitr == 0 )
	{
		mother = part.mother();
	}	
	if(genitr == 1 && part.mother() != mother)
	{
		continue;
	}
		
	   for (size_t i = 0; i < photons->size(); ++i){

		if(matchedIdx[i] == 1)
		{
			continue;
		}
		auto recopho = photons->ptrAt(i)->superCluster();
		double dr = MDeltaR(part.eta(),part.phi(),recopho->eta(),recopho->phi()); 
		if(dr < mindr)
		{
			mindr = dr;
			matchedPhoton=i;
		}
		
	}
	if(matchedPhoton>=0)
	{
		matchedIdx[matchedPhoton]=1;
	}
	if(matchedPhoton<0)
	{
		mindr=-999;
	}
if(genitr==0)
{
	drminLead.push_back(mindr);	
}
else if(genitr==1)
{
	drminSubLead.push_back(mindr);
}
else
{
	drminOther.push_back(mindr);
}

         Pho_Gen_Pt.push_back(part.pt());
         Pho_Gen_Eta.push_back(part.eta());
         Pho_Gen_Phi.push_back(part.phi());
         Pho_Gen_E.push_back(part.energy());
	 Pho_Gen_matchedIndex.push_back(matchedPhoton);
	 genitr++;
	}
}
	if(mother != nullptr)
	{
         A_Gen_Pt.push_back(mother->pt());
         A_Gen_Eta.push_back(mother->eta());
         A_Gen_Phi.push_back(mother->phi());
         A_Gen_E.push_back(mother->energy());
	}

	
	
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /////////////////////////Run, event, lumi//////////////////////////////////
   run=iEvent.id().run();
   event=iEvent.id().event();
   lumi=iEvent.luminosityBlock();
   ///////////////////////////////////////////////////////////////////////////



   T->Fill(); // Write out the events
   delete clustertools_NoZS;

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
   void
Photon_Skimmer::beginJob()
{
   edm::Service<TFileService> fs;
   T=fs->make<TTree>("T","MyTuple");
   T->Branch("iEta"  ,  &(iEta));
   T->Branch("iPhi"  ,  &(iPhi));
   T->Branch("Hit_ES_Eta"  ,  &(Hit_ES_Eta));
   T->Branch("Hit_ES_Phi"  ,  &(Hit_ES_Phi));
   T->Branch("Hit_ES_X"  ,  &(Hit_ES_X));
   T->Branch("Hit_ES_Y"  ,  &(Hit_ES_Y));
   T->Branch("Hit_ES_Z"  ,  &(Hit_ES_Z));
   T->Branch("ES_RecHitEn"  ,  &(ES_RecHitEn));
   T->Branch("recoPhotonIdx",&(recoPhotonIdx));

   T->Branch("Hit_Eta"  ,  &(Hit_Eta));
   T->Branch("Hit_Phi"  ,  &(Hit_Phi));
   T->Branch("Hit_X"  ,  &(Hit_X));
   T->Branch("Hit_Y"  ,  &(Hit_Y));
   T->Branch("Hit_Z"  ,  &(Hit_Z));
   T->Branch("RecHitEn"  ,  &(RecHitEn));
   T->Branch("RecHitFrac"  ,  &(RecHitFrac));
   T->Branch("RecHitGain1"  ,  &(RecHitGain));
   T->Branch("RecHitQuality1", &(RecHitQuality));
   T->Branch("HitNoise", &(HitNoise));

   T->Branch("RecHitFlag_kGood", &(RecHitFlag_kGood));
   T->Branch("RecHitFlag_Endcap", &(RecHitFlag_Endcap));
   T->Branch("RecHitFlag_kPoorReco", &(RecHitFlag_kPoorReco));
   T->Branch("RecHitFlag_kOutOfTime", &(RecHitFlag_kOutOfTime));
   T->Branch("RecHitFlag_kFaultyHardware", &(RecHitFlag_kFaultyHardware));
   T->Branch("RecHitFlag_kNoisy", &(RecHitFlag_kNoisy));
   T->Branch("RecHitFlag_kPoorCalib", &(RecHitFlag_kPoorCalib));
   T->Branch("RecHitFlag_kSaturated", &(RecHitFlag_kSaturated));
   T->Branch("RecHitFlag_kLeadingEdgeRecovered", &(RecHitFlag_kLeadingEdgeRecovered));
   T->Branch("RecHitFlag_kNeighboursRecovered", &(RecHitFlag_kNeighboursRecovered));
   T->Branch("RecHitFlag_kTowerRecovered", &(RecHitFlag_kTowerRecovered));
   T->Branch("RecHitFlag_kDead", &(RecHitFlag_kDead));
   T->Branch("RecHitFlag_kKilled", &(RecHitFlag_kKilled));
   T->Branch("RecHitFlag_kTPSaturated", &(RecHitFlag_kTPSaturated));
   T->Branch("RecHitFlag_kL1SpikeFlag", &(RecHitFlag_kL1SpikeFlag));
   T->Branch("RecHitFlag_kWeird", &(RecHitFlag_kWeird));
   T->Branch("RecHitFlag_kDiWeird", &(RecHitFlag_kDiWeird));
   T->Branch("RecHitFlag_kHasSwitchToGain6", &(RecHitFlag_kHasSwitchToGain6));
   T->Branch("RecHitFlag_kHasSwitchToGain1", &(RecHitFlag_kHasSwitchToGain1));

   T->Branch("RecHitFlag_kESGood", &(RecHitFlag_kESGood));
   T->Branch("RecHitFlag_kESDead", &(RecHitFlag_kESDead));
   T->Branch("RecHitFlag_kESHot", &(RecHitFlag_kESHot));
   T->Branch("RecHitFlag_kESPassBX", &(RecHitFlag_kESPassBX));
   T->Branch("RecHitFlag_kESTwoGoodRatios", &(RecHitFlag_kESTwoGoodRatios));
   T->Branch("RecHitFlag_kESBadRatioFor12", &(RecHitFlag_kESBadRatioFor12));
   T->Branch("RecHitFlag_kESBadRatioFor23Upper", &(RecHitFlag_kESBadRatioFor23Upper));
   T->Branch("RecHitFlag_kESBadRatioFor23Lower", &(RecHitFlag_kESBadRatioFor23Lower));
   T->Branch("RecHitFlag_kESTS1Largest", &(RecHitFlag_kESTS1Largest));
   T->Branch("RecHitFlag_kESTS3Largest", &(RecHitFlag_kESTS3Largest));
   T->Branch("RecHitFlag_kESTS3Negative", &(RecHitFlag_kESTS3Negative));


	T->Branch("DrminLead",&drminLead);
	T->Branch("DrminSubLead",&drminSubLead);
	T->Branch("DrminOther",&drminOther);

   T->Branch("nPhotons",  &nPhotons_ , "nPho/I");
   T->Branch("pt"  ,  &Pho_pt_);
   T->Branch("eta" ,  &Pho_eta_ );
   T->Branch("phi" ,  &Pho_phi_ );
   T->Branch("energy", &Pho_energy_);
   T->Branch("energy_ecal_mustache", &Pho_ecal_mustache_energy_);

   T->Branch("passMediumId" ,  &passMediumId_ );
   T->Branch("passTightId"  ,  &passTightId_ );
   T->Branch("passMVAMediumId", &passMVAMediumId_);

   T->Branch("Pho_R9"  ,  &Pho_R9);
   T->Branch("Pho_S4"  ,  &Pho_S4);
   T->Branch("Pho_SigIEIE"  ,  &Pho_SigIEIE);
   T->Branch("Pho_SigIPhiIPhi" , &Pho_SigIPhiIPhi);
   T->Branch("Pho_SCEtaW"  ,  &Pho_SCEtaW);
   T->Branch("Pho_SCPhiW"  ,  &Pho_SCPhiW);
   T->Branch("Pho_CovIEtaIEta"  ,  &Pho_CovIEtaIEta);
   T->Branch("Pho_CovIEtaIPhi"  ,  &Pho_CovIEtaIPhi);
   T->Branch("Pho_ESSigRR"  ,  &Pho_ESSigRR);
   T->Branch("Pho_SCRawE"  ,  &Pho_SCRawE);
   T->Branch("Pho_SC_ESEnByRawE"  ,  &Pho_SC_ESEnByRawE);
   T->Branch("Pho_HadOverEm"  ,  &Pho_HadOverEm);

   T->Branch("Pho_Gen_Pt" , &Pho_Gen_Pt);
   T->Branch("Pho_Gen_Eta" , &Pho_Gen_Eta);
   T->Branch("Pho_Gen_Phi" , &Pho_Gen_Phi);
   T->Branch("Pho_Gen_E" , &Pho_Gen_E);
   T->Branch("Pho_Gen_matchedIndex" , &Pho_Gen_matchedIndex);

   T->Branch("rho", &rho, "rho/F");

   T->Branch("run",&run,"run/I");
   T->Branch("event",&event,"event/I");
   T->Branch("lumi",&lumi,"lumi/I");

   T->Branch("A_Gen_Pt" , &A_Gen_Pt);
   T->Branch("A_Gen_Eta" , &A_Gen_Eta);
   T->Branch("A_Gen_Phi" , &A_Gen_Phi);
   T->Branch("A_Gen_E" , &A_Gen_E);
}

// ------------ method called once each job just after ending the event loop  ------------
   void
Photon_Skimmer::endJob()
{
}

/*
//Evaluate if the gen particle dR matched to a reco photon is also a photon
bool Photon_Skimmer::GetGenMatchType(const reco::Photon& Photon, const reco::GenParticle& GenColl, int pdgId, double dRThresh){


}
*/


// Extract the rechits of the SC from the ES layers
void Photon_Skimmer::GetESPlaneRecHits(const reco::SuperCluster& sc, const CaloGeometry* &geo, unsigned int phonum, unsigned int planeIndex) {
   double RawenergyPlane = 0.;
   double pfRawenergyPlane = 0.;
   //      if(!_ESRechitsHandle.isValid())
   //              return RawenergyPlane;

   //        if (!sc.preshowerClusters().isAvailable()) //protection for miniAOD
   //                break;

   int NumHits = 0;

   const CaloSubdetectorGeometry* ecalESGeom = static_cast<const CaloSubdetectorGeometry*>(geo->getSubdetectorGeometry(DetId::Ecal, EcalPreshower));


   for(auto iES = sc.preshowerClustersBegin(); iES != sc.preshowerClustersEnd(); ++iES) {//loop over preshower clusters
      const std::vector< std::pair<DetId, float> > hits = (*iES)->hitsAndFractions();
      for(std::vector<std::pair<DetId, float> >::const_iterator rh = hits.begin(); rh != hits.end(); ++rh) { // loop over recHits of the cluster
         //      std::cout << "print = " << (*iES)->printHitAndFraction(iCount);
         //      ++iCount;
         for(ESRecHitCollection::const_iterator esItr = ESRechitsHandle->begin(); esItr != ESRechitsHandle->end(); ++esItr) {//loop over ES rechits to find the one in the cluster
            ESDetId rhid = ESDetId(esItr->id());
            if(rhid == (*rh).first) { // found ESrechit
               //                                        std::cout << " ES energy = " << esItr->energy() << " pf energy = " << (*rh).second << std::endl;
               if((int) rhid.plane() == (int) planeIndex) {
                  std::shared_ptr<const CaloCellGeometry> geom = ecalESGeom->getGeometry(rhid);
                  mHit_ES_Eta.push_back( geom->etaPos() );
                  mHit_ES_Phi.push_back( geom->phiPos() );
                  mHit_ES_X.push_back( geom->getPosition().x() );
                  mHit_ES_Y.push_back( geom->getPosition().y() );
                  mHit_ES_Z.push_back( geom->getPosition().z() ) ;
                  mES_RecHitEn.push_back(esItr->energy());
	// recoPhotonIdx.push_back(phonum);

            //      for (int iflag=EcalRecHit::kESGood; iflag<EcalRecHit::kESTS15Sigmas+1; iflag++){
             //        bool check_bit = esItr->checkFlag(iflag);
              //       RecHitESFlag_container[iflag]->push_back(check_bit);

               //      if (DEBUG) cout<< "ES Flag: "<<iflag<<endl;
                //  }
						std::cout << "Preshower" <<std::setprecision(4) << " Eta = " <<geom->etaPos() << " : " <<" Phi = "<< geom->phiPos() << " 3D position" << geom->getPosition().z() << std::endl;
                  RawenergyPlane += esItr->energy();
                  pfRawenergyPlane += rh->second;
                  NumHits++;
               }
               break;
            }
         }
      }

      //		std::cout<<std::endl<<" Number of ES hits in plane 1 = "<<NumHits<<std::endl;
   }

   //       return RawenergyPlane;
}


//Clear tree vectors each time analyze method is called
void Photon_Skimmer::ClearTreeVectors()
{
	drminLead.clear();
drminSubLead.clear();
drminOther.clear();
   nPhotons_ = 0;
   iEta.clear();
   iPhi.clear();
   recoPhotonIdx.clear();


   Hit_ES_Eta.clear();
   Hit_ES_Phi.clear();
   Hit_ES_X.clear();
   Hit_ES_Y.clear();
   Hit_ES_Z.clear();
   ES_RecHitEn.clear();


   Hit_Eta.clear();
   Hit_Phi.clear();
   Hit_X.clear();
   Hit_Y.clear();
   Hit_Z.clear();
   RecHitEn.clear();
   RecHitFrac.clear();
   RecHitGain.clear();
   RecHitQuality.clear();
   HitNoise.clear();

   RecHitFlag_kGood.clear();
   RecHitFlag_Endcap.clear();
   RecHitFlag_kPoorReco.clear();
   RecHitFlag_kOutOfTime.clear();
   RecHitFlag_kFaultyHardware.clear();
   RecHitFlag_kNoisy.clear();
   RecHitFlag_kPoorCalib.clear();
   RecHitFlag_kSaturated.clear();
   RecHitFlag_kLeadingEdgeRecovered.clear();
   RecHitFlag_kNeighboursRecovered.clear();
   RecHitFlag_kTowerRecovered.clear();
   RecHitFlag_kDead.clear();
   RecHitFlag_kKilled.clear();
   RecHitFlag_kTPSaturated.clear();
   RecHitFlag_kL1SpikeFlag.clear();
   RecHitFlag_kWeird.clear();
   RecHitFlag_kDiWeird.clear();
   RecHitFlag_kHasSwitchToGain6.clear();
   RecHitFlag_kHasSwitchToGain1.clear();

   RecHitFlag_kESGood.clear();
   RecHitFlag_kESDead.clear();
   RecHitFlag_kESHot.clear();
   RecHitFlag_kESPassBX.clear();
   RecHitFlag_kESTwoGoodRatios.clear();
   RecHitFlag_kESBadRatioFor12.clear();
   RecHitFlag_kESBadRatioFor23Upper.clear();
   RecHitFlag_kESBadRatioFor23Lower.clear();
   RecHitFlag_kESTS1Largest.clear();
   RecHitFlag_kESTS3Largest.clear();
   RecHitFlag_kESTS3Negative.clear();
   RecHitFlag_kESSaturated.clear();
   RecHitFlag_kESTS2Saturated.clear();
   RecHitFlag_kESTS3Saturated.clear();
   RecHitFlag_kESTS13Sigmas.clear();
   RecHitFlag_kESTS15Sigmas.clear();

   Pho_pt_.clear();
   Pho_eta_.clear();
   Pho_phi_.clear();
   Pho_energy_.clear();
   Pho_ecal_mustache_energy_.clear();
   Pho_R9.clear();
   Pho_S4.clear();
   Pho_SigIEIE.clear();
   Pho_SigIPhiIPhi.clear();
   Pho_SCEtaW.clear();
   Pho_SCPhiW.clear();
   Pho_CovIEtaIEta.clear();
   Pho_CovIEtaIPhi.clear();
   Pho_ESSigRR.clear();
   Pho_SCRawE.clear();
   Pho_SC_ESEnByRawE.clear();
   Pho_HadOverEm.clear();

   Pho_Gen_Pt.clear();
   Pho_Gen_Eta.clear();
   Pho_Gen_Phi.clear();
   Pho_Gen_E.clear();
   Pho_Gen_matchedIndex.clear();

   passMediumId_.clear();
   passTightId_ .clear();
   passMVAMediumId_.clear();

   isTrue_.clear();
   A_Gen_Pt.clear();
   A_Gen_Eta.clear();
   A_Gen_Phi.clear();
   A_Gen_E.clear();
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Photon_Skimmer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
   //The following says we do not know what parameters are allowed so do no validation
   // Please change this to state exactly what you do use, even if it is no parameters
   edm::ParameterSetDescription desc;
   desc.setUnknown();
   descriptions.addDefault(desc);

   //Specify that only 'tracks' is allowed
   //To use, remove the default given above and uncomment below
   //ParameterSetDescription desc;
   //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
   //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(Photon_Skimmer);
