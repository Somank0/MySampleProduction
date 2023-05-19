
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
// -*- C++ -*-
//
// Package:    Demo/DemoAnalyzer_AOD_CutID
// Class:      DemoAnalyzer_AOD_CutID
// 
/**\class DemoAnalyzer_AOD_CutID DemoAnalyzer_AOD_CutID.cc Demo/DemoAnalyzer_AOD_CutID/plugins/DemoAnalyzer_AOD_CutID.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Rajdeep Mohan Chatterjee
//         Created:  Fri, 20 Jan 2017 09:56:20 GMT
//
//


// system include files
#include <memory>
#include <iostream>
#include "TTree.h"
#include "Math/VectorUtil.h"
#include "TFile.h"
#include "TH1F.h"
// user include files

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"


class DemoAnalyzer_AOD_CutID : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit DemoAnalyzer_AOD_CutID(const edm::ParameterSet&);
      ~DemoAnalyzer_AOD_CutID();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

//   clear the vectors 
     void ClearTreeVectors();

// ----------- Handles -----------------------
	edm::Handle<reco::VertexCollection>            _primaryVertexHandle; // for _nPV
        edm::Handle<std::vector< PileupSummaryInfo > > _PupInfo;

// --------------- Histogram ---------------
	TH1F* Pileup_dist;

// ----------member data ---------------------------
	TTree* T;
      //pileup
	UChar_t  _nPV;    ///< nVtx
	UChar_t  _nPU;    ///< number of PU (filled only for MC)

	UInt_t    _runNumber;     ///< run number
	UShort_t  _lumiBlock;     ///< lumi section
	Long64_t  _eventNumber;   ///< event number
	UShort_t  _nBX;           ///< bunch crossin
      Float_t rho;
      edm::Handle<double> rhoHandle;
      edm::EDGetTokenT<double> rhoToken_;




      // -----------------Tokens--------------------------
      edm::EDGetTokenT<reco::VertexCollection>           _vtxCollectionToken;
      edm::EDGetTokenT<std::vector<PileupSummaryInfo> > _pileupInfoToken;

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
DemoAnalyzer_AOD_CutID::DemoAnalyzer_AOD_CutID(const edm::ParameterSet& iConfig):
   rhoToken_(consumes<double>(iConfig.getParameter<edm::InputTag>("rhoFastJet"))),
//	_vtxCollectionToken(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertexCollection"))),
        _pileupInfoToken(consumes<std::vector<PileupSummaryInfo>>(iConfig.getParameter<edm::InputTag>("pileupInfo")))
{
   //now do what ever initialization is needed
   usesResource("TFileService");

}


DemoAnalyzer_AOD_CutID::~DemoAnalyzer_AOD_CutID()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DemoAnalyzer_AOD_CutID::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

//   iEvent.getByToken(_vtxCollectionToken, _primaryVertexHandle);
   iEvent.getByToken(_pileupInfoToken, _PupInfo);
   iEvent.getByToken(rhoToken_, rhoHandle);


//Clear all vectors to be written to the tree
   ClearTreeVectors();

        _nPV = 255;
        _nPU = 255;
   rho = *rhoHandle;


//   if(_prhmaryVertexHandle->size() > 0) {
//	   _nPV = 0;
//	   for(reco::VertexCollection::const_iterator v = _primaryVertexHandle->begin(); v != _primaryVertexHandle->end(); ++v) {
//		   _nPV++;
//	   }
//   }

   std::vector<PileupSummaryInfo>::const_iterator PVI;
   for(PVI = _PupInfo->begin(); PVI != _PupInfo->end(); ++PVI) {
	   int BX = PVI->getBunchCrossing();
	   if(BX == 0) { // in-time pu
		   _nPU = PVI->getTrueNumInteractions();
		Pileup_dist->Fill( PVI->getTrueNumInteractions() );
	   }
   }


/////////////////////////Run, event, lumi ...//////////////////////////////////

        _runNumber = (UInt_t) iEvent.run();
        _eventNumber = (Long64_t) iEvent.id().event();
//      _nBX = (UShort_t) (iEvent.isRealData()) ? iEvent.bunchCrossing() : 0;
	_nBX = (UShort_t)  iEvent.bunchCrossing();
	_lumiBlock = (UShort_t) iEvent.luminosityBlock();
//////////////////////////////////////////////////////////////////////////

  T->Fill();	

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}// analyze method ends here


// ------------ method called once each job just before starting event loop  ------------
void 
DemoAnalyzer_AOD_CutID::beginJob()
{
	edm::Service<TFileService> fs;
	Pileup_dist = fs->make<TH1F>("Pileup_dist", "Pileup_dist", 100, 0., 100.);
	T=fs->make<TTree>("T","MyTuple");
//branches for PU related variables
        T->Branch("nPV", &_nPV, "nPV/b");
        T->Branch("nPU", &_nPU, "nPU/b");
//branches for Run info.
	T->Branch("nBX",           &_nBX,           "nBX/s");
   T->Branch("rho", &rho, "rho/F");

}

// ------------ method called once each job just after ending the event loop  ------------
void 
DemoAnalyzer_AOD_CutID::endJob() 
{
}

//Clear tree vectors each time analyze method is called
void DemoAnalyzer_AOD_CutID::ClearTreeVectors()
{

}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DemoAnalyzer_AOD_CutID::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DemoAnalyzer_AOD_CutID);
