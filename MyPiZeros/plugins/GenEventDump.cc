// -*- C++ -*-
//
// Package:    PiZeroSampleProd/GenEventDump
// Class:      GenEventDump
//
/**\class GenEventDump GenEventDump.cc PiZeroSampleProd/GenEventDump/plugins/GenEventDump.cc

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
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.

using reco::TrackCollection;

class GenEventDump : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit GenEventDump(const edm::ParameterSet &);
  ~GenEventDump();

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
  edm::EDGetToken genParticlesToken_;
  edm::EDGetToken photonsToken_;
  edm::Handle<edm::View<reco::GenParticle>> genParticles;
  edm::Handle<edm::View<reco::Photon>> photons;

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
GenEventDump::GenEventDump(const edm::ParameterSet &iConfig)
// : tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))) {
{
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif
  photonsToken_ = mayConsume<edm::View<reco::Photon>>(iConfig.getParameter<edm::InputTag>("photons"));
  genParticlesToken_ = mayConsume<edm::View<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("genParticles"));
  usesResource("TFileService");
  // now do what ever initialization is needed
}

GenEventDump::~GenEventDump() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//

// ------------ method called for each event  ------------
void GenEventDump::analyze(const edm::Event &iEvent, const edm::EventSetup &iSetup) {
  using namespace edm;

  iEvent.getByToken(genParticlesToken_, genParticles);
  iEvent.getByToken(photonsToken_, photons);
  run = iEvent.id().run();
  event = iEvent.id().event();
  lumi = iEvent.luminosityBlock();
  std::cout << "=====================================" << std::endl;
  std::cout << "Run: " << run << " , Event: " << event << " , Lumi: " << lumi << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Gen Particles" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  for (size_t i = 0; i < genParticles->size(); ++i) {
    const auto part = genParticles->ptrAt(i);
    auto mother = part->mother();
    std::cout << "pdgID: " << part->pdgId() << " , Status: " << (part->status()) << " , Pt: " << part->pt()
              << " , Eta: " << part->eta() << " , Phi: " << part->phi() << " , Energy: " << part->energy();
    if (mother) {
    std::cout << " , MotherID: "<<mother->pdgId() << " , MotherStatus: "<<mother->status()<<" , MotherPt: "<<mother->pt();
//    if (mother) {
//      std::cout << "Mother Info" << std::endl;
//      std::cout << "pdgID: " << mother->pdgId() << " , Status: " << (mother->status()) << " , Pt: " << mother->pt()
//                << " , Eta: " << mother->eta() << " , Phi: " << mother->phi() << " , Energy: " << mother->energy()
//                << std::endl;
//	std::cout<<std::endl;
    }
    std::cout<<std::endl;
  }
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Size of reco photons: " << photons->size() << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Reco Photons" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  for (size_t i = 0; i < photons->size(); ++i) {
    // if (nPhotons_ == 2) break;
    const auto pho = photons->ptrAt(i);
    std::cout << "Pt: " << pho->pt() << " , Eta: " << pho->eta() << " , Phi: " << pho->phi()
              << " , Energy: " << pho->energy() << std::endl;
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
void GenEventDump::beginJob() {
  edm::Service<TFileService> fs;
  T = fs->make<TTree>("T", "MyTuple");
  //Event IDS
  T->Branch("run", &run, "run/I");
  T->Branch("event", &event, "event/I");
  T->Branch("lumi", &lumi, "lumi/I");
}

// ------------ method called once each job just after ending the event loop  ------------
void GenEventDump::endJob() {
  // please remove this method if not needed
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void GenEventDump::fillDescriptions(edm::ConfigurationDescriptions &descriptions) {
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
DEFINE_FWK_MODULE(GenEventDump);

void GenEventDump::ClearTreeVectors() {
  event = 0, run = 0, lumi = 0;
}
