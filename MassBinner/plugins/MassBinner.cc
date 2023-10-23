// -*- C++ -*-
//
// Package:    MySampleProduction/MassBinner
// Class:      MassBinner
// 
/**\class MassBinner MassBinner.cc MySampleProduction/MassBinner/plugins/MassBinner.cc

 Desciption: Filters events that satisfy the mass range for a particle of given pdgId

 Implementation:
     [Notes on implementation]
 Parameters:
 partId, maxMass, minMass, genParticles
*/
//
// Original Author:  Chirayu Gupta
//         Created:  Thu, 28 Sep 2023 13:18:15 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

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

//
// class declaration
//

class MassBinner : public edm::stream::EDFilter<> {
   public:
      explicit MassBinner(const edm::ParameterSet&);
      ~MassBinner();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;
      double maxMass_;
      double minMass_;
      int partId_;

      edm::Handle<edm::View<reco::GenParticle> > genParticles;
      edm::EDGetTokenT<edm::View<reco::GenParticle> > genParticlesToken_;
      // ----------member data ---------------------------
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
MassBinner::MassBinner(const edm::ParameterSet& iConfig)
 :  maxMass_(iConfig.getParameter<double>("maxMass")),
    minMass_(iConfig.getParameter<double>("minMass")),
    partId_(iConfig.getParameter<int>("partId"))
{
   genParticlesToken_ = mayConsume<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("genParticles"));
   //now do what ever initialization is needed

}


MassBinner::~MassBinner()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
MassBinner::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   iEvent.getByToken(genParticlesToken_, genParticles);

  for (const reco::GenParticle& particle : *genParticles) {
    if (particle.pdgId() == partId_) {
      if (particle.mass() < maxMass_ && particle.mass() > minMass_ ) {
        return true;
      }
      else {
        return false;
      }
    }
  }

  return false;  // Event does not pass the filter
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
MassBinner::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
MassBinner::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
MassBinner::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
MassBinner::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
MassBinner::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
MassBinner::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MassBinner::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(MassBinner);
