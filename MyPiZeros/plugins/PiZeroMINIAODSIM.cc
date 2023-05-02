// -*- C++ -*-
//
// Package:    PiZeroSampleProd/PiZeroMINIAODSIM
// Class:      PiZeroMINIAODSIM
//
/**\class PiZeroMINIAODSIM PiZeroMINIAODSIM.cc PiZeroSampleProd/PiZeroMINIAODSIM/plugins/PiZeroMINIAODSIM.cc

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

class PiZeroMINIAODSIM : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit PiZeroMINIAODSIM(const edm::ParameterSet &);
  ~PiZeroMINIAODSIM();

  static void fillDescriptions(edm::ConfigurationDescriptions &descriptions);

private:
  void ClearTreeVectors();
  TTree *T;
  std::vector<float> Pho_pt_;
  std::vector<float> Pho_eta_;
  std::vector<float> Pho_phi_;
  std::vector<float> Pho_energy_;
  std::vector<float> Pho_Gen_Pt;
  std::vector<float> Pho_Gen_Eta;
  std::vector<float> Pho_Gen_Phi;
  std::vector<float> Pho_Gen_E;
  void beginJob() override;
  void analyze(const edm::Event &, const edm::EventSetup &) override;
  void endJob() override;
  int event;
  int lumi;
  int run;
  edm::EDGetToken genParticlesToken_;
  edm::EDGetToken photonsToken_;
  edm::EDGetToken electronsToken_;
  edm::Handle<edm::View<reco::GenParticle>> genParticles;
  edm::Handle<edm::View<reco::GsfElectron>> electrons;
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
PiZeroMINIAODSIM::PiZeroMINIAODSIM(const edm::ParameterSet &iConfig)
// : tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))) {
{
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif
  photonsToken_ = mayConsume<edm::View<reco::Photon>>(iConfig.getParameter<edm::InputTag>("photons"));
  electronsToken_ = mayConsume<edm::View<reco::GsfElectron>>(iConfig.getParameter<edm::InputTag>("electrons"));
  genParticlesToken_ = mayConsume<edm::View<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("genParticles"));
  usesResource("TFileService");
  // now do what ever initialization is needed
}

PiZeroMINIAODSIM::~PiZeroMINIAODSIM() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//

// ------------ method called for each event  ------------
void PiZeroMINIAODSIM::analyze(const edm::Event &iEvent, const edm::EventSetup &iSetup) {
  using namespace edm;

  iEvent.getByToken(photonsToken_, photons);
  iEvent.getByToken(electronsToken_, electrons);
  iEvent.getByToken(genParticlesToken_, genParticles);
  run = iEvent.id().run();
  event = iEvent.id().event();
  lumi = iEvent.luminosityBlock();
  std::cout << "=====================================" << std::endl;
  std::cout << "Run: " << run << " , Event: " << event << " , Lumi: " << lumi << std::endl;
  std::cout << "Size of gen particles: " << genParticles->size() << std::endl;
  std::cout << "Size of reco photons: " << photons->size() << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Reco Photons" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  for (size_t i = 0; i < photons->size(); ++i) {
    // if (nPhotons_ == 2) break;
    const auto pho = photons->ptrAt(i);
    std::cout << "Pt: " << pho->pt() << " , Eta: " << pho->eta() << " , Phi: " << pho->phi()
              << " , Energy: " << pho->energy() << std::endl;
    Pho_pt_.push_back(pho->pt());
    Pho_eta_.push_back(pho->eta());
    Pho_phi_.push_back(pho->phi());
    Pho_energy_.push_back(pho->energy());

    /*   for (const auto& track : iEvent.get(tracksToken_)) {
        // do something with track parameters, e.g, plot the charge.
         int eta = track.charge();
      } */
  }

  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Reco Converted Electrons" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  for (size_t i = 0; i < electrons->size(); ++i) {
    // if (nPhotons_ == 2) break;
    const auto pho = electrons->ptrAt(i);
    std::cout << "Pt: " << pho->pt() << " , Eta: " << pho->eta() << " , Phi: " << pho->phi()
              << " , Energy: " << pho->energy() << std::endl;
    Pho_pt_.push_back(pho->pt());
    Pho_eta_.push_back(pho->eta());
    Pho_phi_.push_back(pho->phi());
    Pho_energy_.push_back(pho->energy());

    /*   for (const auto& track : iEvent.get(tracksToken_)) {
        // do something with track parameters, e.g, plot the charge.
         int eta = track.charge();
      } */
  }
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Gen Particles" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  for (size_t i = 0; i < genParticles->size(); ++i) {
    const auto part = genParticles->ptrAt(i);
    auto mother = part->mother();
    std::cout << "pdgID: " << part->pdgId() << " , Status: " << (part->status()) << " , Pt: " << part->pt()
              << " , Eta: " << part->eta() << " , Phi: " << part->phi() << " , Energy: " << part->energy() << std::endl;
    if (part->pdgId() == 22) {
      std::cout << "Mother Info" << std::endl;
      std::cout << "pdgID: " << mother->pdgId() << " , Status: " << (mother->status()) << " , Pt: " << mother->pt()
                << " , Eta: " << mother->eta() << " , Phi: " << mother->phi() << " , Energy: " << mother->energy()
                << std::endl;
    }
    if (part->status() == 1 && abs(part->pdgId()) == 22) {
      Pho_Gen_Pt.push_back(part->pt());
      Pho_Gen_Eta.push_back(part->eta());
      Pho_Gen_Phi.push_back(part->phi());
      Pho_Gen_E.push_back(part->energy());
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
void PiZeroMINIAODSIM::beginJob() {
  edm::Service<TFileService> fs;
  T = fs->make<TTree>("T", "MyTuple");
  //Reco
  T->Branch("pt", &Pho_pt_);
  T->Branch("eta", &Pho_eta_);
  T->Branch("phi", &Pho_phi_);
  T->Branch("energy", &Pho_energy_);
  //Event IDS
  T->Branch("run", &run, "run/I");
  T->Branch("event", &event, "event/I");
  T->Branch("lumi", &lumi, "lumi/I");
  //GEN
  T->Branch("Pho_Gen_Pt", &Pho_Gen_Pt);
  T->Branch("Pho_Gen_Eta", &Pho_Gen_Eta);
  T->Branch("Pho_Gen_Phi", &Pho_Gen_Phi);
  T->Branch("Pho_Gen_E", &Pho_Gen_E);
}

// ------------ method called once each job just after ending the event loop  ------------
void PiZeroMINIAODSIM::endJob() {
  // please remove this method if not needed
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void PiZeroMINIAODSIM::fillDescriptions(edm::ConfigurationDescriptions &descriptions) {
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
DEFINE_FWK_MODULE(PiZeroMINIAODSIM);

void PiZeroMINIAODSIM::ClearTreeVectors() {
  event = 0, run = 0, lumi = 0;
  Pho_pt_.clear();
  Pho_eta_.clear();
  Pho_phi_.clear();
  Pho_energy_.clear();

  Pho_Gen_Pt.clear();
  Pho_Gen_Eta.clear();
  Pho_Gen_Phi.clear();
  Pho_Gen_E.clear();
}
