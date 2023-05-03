import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryRecoDB_cff")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(100))

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(2500)

# options = VarParsing.VarParsing('standard')
options = VarParsing.VarParsing("analysis")

# options.register('inputFile',
#        "~/",
#        VarParsing.VarParsing.multiplicity.singleton,
#        VarParsing.VarParsing.varType.string,
#        "File containing a list of the EXACT location of the output file  (default = ~/)"
#        )


options.parseArguments()
# options.inputFile = 'root://eoscms//' + options.inputFile
# print(options.inputFile)
process.source = cms.Source(
    "PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames=cms.untracked.vstring(
        #"file:step3pionsUncompressed.root"
        "file:step1WNoTauUncompressed.root"
        #'root://cms-xrd-global.cern.ch///store/mc/RunIISummer20UL18RECO/GluGluHToGG_M-125_TuneCP5_13TeV-powheg-pythia8/AODSIM/106X_upgrade2018_realistic_v11_L1v1-v2/40000/52EA6B6E-16AD-8141-8F44-B20F1AE8F7A3.root',
        #'root://cms-xrd-global.cern.ch///store/mc/RunIISummer20UL18RECO/GluGluHToGG_M-125_TuneCP5_13TeV-powheg-pythia8/AODSIM/106X_upgrade2018_realistic_v11_L1v1-v2/40000/5BAC5863-D457-1147-A9BC-859465E10114.root',
        #'root://cms-xrd-global.cern.ch///store/mc/RunIISummer20UL18RECO/GluGluHToGG_M-125_TuneCP5_13TeV-powheg-pythia8/AODSIM/106X_upgrade2018_realistic_v11_L1v1-v2/40000/913ED97A-F22E-8E43-AEB3-D9722EF35C55.root'
        #'root://cms-xrd-global.cern.ch///store/mc/RunIISummer20UL18RECO/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/106X_upgrade2018_realistic_v11_L1v1_ext1-v1/40000/73BD758C-D31C-C74B-8FAB-3C71CDE05363.root' ## worked
        #'root://cms-xrd-global.cern.ch///store/mc/RunIISummer20UL18RECO/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/106X_upgrade2018_realistic_v11_L1v1_ext1-v1/40004/78B82965-2C56-4349-871C-D8ABAEEDD678.root'
        #'root://cms-xrd-global.cern.ch//store/mc/RunIISummer20UL18RECO/GluGluHToGG_M-125_TuneCP5_13TeV-powheg-pythia8/AODSIM/106X_upgrade2018_realistic_v11_L1v1-v2/40000/913ED97A-F22E-8E43-AEB3-D9722EF35C55.root'
        #'root://cms-xrd-global.cern.ch//store/mc/RunIISummer20UL16RECO/ADDmonoPhoton_MD-1_d-3_TuneCP5_13TeV-pythia8/AODSIM/106X_mcRun2_asymptotic_v13-v2/2550000/32C57B10-227A-F44D-98CA-15F6F6C8ABDC.root' #site dataset=/ADDmonoPhoton_MD-1_d-3_TuneCP5_13TeV-pythia8/RunIISummer20UL16RECO-106X_mcRun2_asymptotic_v13-v2/AODSIM
        # -ss-#'root://cms-xrd-global.cern.ch//store/mc/RunIISummer20UL16MiniAOD/ADDmonoPhoton_MD-1_d-3_TuneCP5_13TeV-pythia8/MINIAODSIM/106X_mcRun2_asymptotic_v13-v2/2550000/145BA6C6-BDDC-2347-BFD6-535DBE7A2594.root' #file dataset=/ADDmonoPhoton_MD-1_d-3_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAOD-106X_mcRun2_asymptotic_v13-v2/MINIAODSIM
        #'root://cms-xrd-global.cern.ch//store/mc/RunIISummer19UL18RECO/DoubleElectron_FlatPt-1To300/AODSIM/FlatPU0to70RAW_106X_upgrade2018_realistic_v11_L1v1_ext2-v2/40000/FF912577-7001-DE41-BDB0-6FF06EC01DA6.root'
        #'root://cms-xrd-global.cern.ch///store/mc/RunIISummer19UL18RECO/DoublePhoton_FlatPt-5To300/AODSIM/FlatPU0to70RAW_106X_upgrade2018_realistic_v11_L1v1_ext1-v2/00000/6F7BDF5D-2A6A-7342-993F-E8DBABF920C8.root'
        #'root://cms-xrd-global.cern.ch///store/mc/RunIISummer19UL18RECO/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/AODSIM/106X_upgrade2018_realistic_v11_L1v1-v1/250000/35BAE18A-E8EA-254E-B693-9212D3725212.root'
        #'root://cms-xrd-global.cern.ch///store/mc/RunIISummer19UL18RECO/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/AODSIM/106X_upgrade2018_realistic_v11_L1v1-v1/250000/26B3A9F9-290D-6346-8862-2BE71645C57D.root'
        #          options.inputFiles
    ),
)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

from Configuration.AlCa.GlobalTag import GlobalTag

process.GlobalTag = GlobalTag(process.GlobalTag, "106X_upgrade2018_realistic_v6", "")


from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

dataFormat = DataFormat.AOD
switchOnVIDPhotonIdProducer(process, dataFormat)

# define which IDs we want to produce
my_id_modules = [
    "RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Fall17_94X_V1_cff",
    "RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Fall17_94X_V1p1_cff",
    "RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Fall17_94X_V2_cff",
]

for idmod in my_id_modules:
    setupAllVIDIdsInModule(process, idmod, setupVIDPhotonSelection)

process.nTuplelize = cms.EDAnalyzer(
    "GenEventDump",
    #rhoFastJet=cms.InputTag("fixedGridRhoFastjetAll"),
    genParticles=cms.InputTag("genParticles"),
    # photons=cms.InputTag("caloStage2Digis:EGamma"),
    # genParticles=cms.InputTag("prunedGenParticles"),
    # MVA Based Id
    #eleMediumIdMap=cms.InputTag(""),
    #eleTightIdMap=cms.InputTag(""),
)


process.TFileService = cms.Service(
    "TFileService",
    #fileName=cms.string("GammaRecHits_ntuple.root"),
    fileName=cms.string("GenParticles.root"),
    #     fileName = cms.string("Tree_Gamma_ABCD.root"),
    closeFileFast=cms.untracked.bool(True),
)


process.p = cms.Path(process.egmPhotonIDSequence * process.nTuplelize)
