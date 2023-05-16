// -*- C++ -*-
//
// Package:    PiZeroSampleProd/GenTreeMaker
// Class:      GenTreeMaker
//
/**\class GenTreeMaker GenTreeMaker.cc PiZeroSampleProd/GenTreeMaker/plugins/GenTreeMaker.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Chirayu Gupta
//         Created:  Tue, 28 Mar 2023 15:02:59 GMT
//
//

// system include files
#include <memory>

#include "TTree.h"
#include "Math/VectorUtil.h"
#include "TFile.h"
// user include files
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.

using reco::TrackCollection;

class GenTreeMaker : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit GenTreeMaker(const edm::ParameterSet &);
  ~GenTreeMaker();

  static void fillDescriptions(edm::ConfigurationDescriptions &descriptions);

private:
  void ClearTreeVectors();
  TTree *T;
  void beginJob() override;
  void analyze(const edm::Event &, const edm::EventSetup &) override;
  void endJob() override;
  int event;
  int lumi;
  int run;
  std::vector<float> Gen_Pt;
  std::vector<float> Gen_Eta;
  std::vector<float> Gen_Phi;
  std::vector<float> Gen_E;
  std::vector<float> A_Gen_Pt;
  std::vector<float> A_Gen_Eta;
  std::vector<float> A_Gen_Phi;
  std::vector<float> A_Gen_E;
  edm::EDGetToken genParticlesToken_;
  edm::Handle<edm::View<reco::GenParticle>> genParticles;

  // ----------member data ---------------------------
  edm::EDGetTokenT<TrackCollection> tracksToken_;  // used to select what tracks to read from configuration file
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  edm::ESGetToken<SetupData, SetupRecord> setupToken_;
#endif
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
GenTreeMaker::GenTreeMaker(const edm::ParameterSet &iConfig)
// : tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))) {
{
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif
  genParticlesToken_ = mayConsume<edm::View<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("genParticles"));
  usesResource("TFileService");
  // now do what ever initialization is needed
}

GenTreeMaker::~GenTreeMaker() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//

// ------------ method called for each event  ------------
void GenTreeMaker::analyze(const edm::Event &iEvent, const edm::EventSetup &iSetup) {
  using namespace edm;

  iEvent.getByToken(genParticlesToken_, genParticles);
  run = iEvent.id().run();
  event = iEvent.id().event();
  lumi = iEvent.luminosityBlock();
  ClearTreeVectors();
  for (size_t i = 0; i < genParticles->size(); ++i) {
    const auto part = genParticles->ptrAt(i);
	if(part->pdgId() == 22 && part->status() == 1 )
	{
	    Gen_Pt.push_back(part->pt());
	    Gen_Eta.push_back(part->eta());
	    Gen_Phi.push_back(part->phi());
	    Gen_E.push_back(part->energy());
	}
	if(part->pdgId() == 36 )
	{
	    A_Gen_Pt.push_back(part->pt());
	    A_Gen_Eta.push_back(part->eta());
	    A_Gen_Phi.push_back(part->phi());
	    A_Gen_E.push_back(part->energy());
	}
}
  T->Fill();
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  // if the SetupData is always needed
  auto setup = iSetup.getData(setupToken_);
  // if need the ESHandle to check if the SetupData was there or not
  auto pSetup = iSetup.getHandle(setupToken_);
#endif
}

// ------------ method called once each job just before starting event loop  ------------
void GenTreeMaker::beginJob() {
  edm::Service<TFileService> fs;
  T = fs->make<TTree>("T", "MyTuple");
  //Event IDS
  T->Branch("run", &run, "run/I");
  T->Branch("event", &event, "event/I");
  T->Branch("lumi", &lumi, "lumi/I");
  T->Branch("Gen_Pt", &Gen_Pt);
  T->Branch("Gen_Eta", &Gen_Eta);
  T->Branch("Gen_Phi", &Gen_Phi);
  T->Branch("Gen_E", &Gen_E);
  T->Branch("A_Gen_Pt",  &A_Gen_Pt);
  T->Branch("A_Gen_Eta", &A_Gen_Eta);
  T->Branch("A_Gen_Phi", &A_Gen_Phi);
  T->Branch("A_Gen_E",   &A_Gen_E);
}

// ------------ method called once each job just after ending the event loop  ------------
void GenTreeMaker::endJob() {
  // please remove this method if not needed
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void GenTreeMaker::fillDescriptions(edm::ConfigurationDescriptions &descriptions) {
  // The following says we do not know what parameters are allowed so do no validation
  //  Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  // Specify that only 'tracks' is allowed
  // To use, remove the default given above and uncomment below
  // ParameterSetDescription desc;
  // desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  // descriptions.addWithDefaultLabel(desc);
}

// define this as a plug-in
DEFINE_FWK_MODULE(GenTreeMaker);

void GenTreeMaker::ClearTreeVectors() {
  event = 0, run = 0, lumi = 0;
  Gen_Pt.clear();
  Gen_Eta.clear();
  Gen_Phi.clear();
  Gen_E.clear();
  A_Gen_Pt.clear();
  A_Gen_Eta.clear();
  A_Gen_Phi.clear();
  A_Gen_E.clear();
}
