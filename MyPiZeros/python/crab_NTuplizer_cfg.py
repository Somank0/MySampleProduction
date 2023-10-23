from CRABClient.UserUtilities import config
import FWCore.ParameterSet.Config as cms

config = config()

config.General.requestName = ""
config.General.workArea = "crab_projects"
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = "Analysis"

# config.JobType.outputFiles= [
#    'nTupleMC.root'
# ]

config.JobType.psetName = "Photon_MINIAODSIM_cfg.py"  # Change to whatever python cfg you are using with cmsRun

config.JobType.allowUndistributedCMSSW = True
config.JobType.maxJobRuntimeMin = 2750
# config.JobType.sendPythonFolder = True

#config.Data.inputDataset = "/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18RECO-106X_upgrade2018_realistic_v11_L1v1_ext1-v1/AODSIM"
config.Data.inputDataset = "/HAHMHToAA_AToGG_MA-0p1GeV_TuneCUETP8M1_PSweights_13TeV-madgraph_pythia8/RunIISummer16DR80Premix-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/AODSIM"
config.Data.inputDBS = "global"
config.Data.splitting = "FileBased"  #'LumiBased'
config.Data.unitsPerJob = 10  # 30000
config.Data.outLFNDirBase = "/eos/user/c/cgupta/MyProjects/flashgg/CMSSW_10_6_29/src/MySampleProduction/MyPiZeros/python/crabstuff"  # change to the full eos path of the folder you write to in CERNBox. Make sure to have sufficient permissions for a write operation.
config.Data.publication = False

# GRID
config.Site.storageSite = "T3_CH_CERNBOX"
# config.Site.whitelist     = ['T3_CH_CERN_CAF']
# config.Site.blacklist     = ['T1_US_FNAL','T2_UA_KIPT','T2_UK_London_Brunel','T2_CH_CSCS','T2_US_*']
# config.Site.ignoreGlobalBlacklist = True
