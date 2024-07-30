FOR CMSSW_10_6_29

To generate samples in a 2D mass grid in the ECAL endcaps
./runSampleGen_EE_minus.sh [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)] [UniqueID]  (for -2.5 <=eta<= -1.44)
OR
./runSampleGen_EE_plus.sh [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)] [UniqueID] (for 1.44 <=eta<= 2.5) 

To make the samples flat in mass 

cd CMSSW_version/src
cmsenv
git cms-addpkg GeneratorInterface/Pythia8Interface
scram b -j32
In this file: GeneratorInterface/Pythia8Interface/plugins/Py8PtGun.cc
Replace: double mass = (fMasterGen->particleData).m0( particleID );
With: double mass = (massMax -massMin) * randomEngine().flat() + massMin;


Note: To run runSampleGen_EE_plus(minus).sh file please make sure the directory structure is the same as AGun directory. You will need to run : cmsrel CMSSW_10_2_16_UL to get relavant version of cmssw and make sure CMSSW_10_2_16_UL/src has the correct files. GEN-SIM: CMSSW_10_6_29. Run the sample generators from a singularity container with el7 architecture.

To use a el7 singularity container interactively, run the command 'cmssw-el7'.

cmsRun AToGG_pythia8_cfi_GEN_SIM.py mass=1.2 ptMin=0 ptMax=50 etaMin=0 etaMax=1.4 phiMin=0 phiMax=3 maxEvents=10

DIGI-PREMIX-RAW:

CMSSW_10_6_29

cmsDriver.py --python_filename genSimDigiRaw_mcProd.py --filein file:step1AToGG_Gamma0-50_M1.2_numEvent10.root --eventcontent PREMIXRAW --customise Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM-RAW --fileout file:name1.root --pileup_input dbs:/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX --conditions 106X_upgrade2018_realistic_v11_L1v1 --step DIGI,DATAMIX,L1,DIGI2RAW --procModifiers premix_stage2 --geometry DB:Extended --datamix PreMix --era Run2_2018 --runUnscheduled --no_exec --beamspot Realistic25ns13TeVEarly2018Collision --mc -n 100

HLT: CMSSW_10_2_16_UL

cmsDriver.py --python_filename hlt.py --eventcontent RAWSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM-RAW --fileout file:BPH-RunIISummer20UL18HLT-00125.root --conditions 102X_upgrade2018_realistic_v15 --customise_commands 'process.source.bypassVersionCheck = cms.untracked.bool(True)' --step HLT:2018v32 --geometry DB:Extended --filein file:name1.root --era Run2_2018 --no_exec --mc -n 100

RECO-AOD:

CMSSW_10_6_29

cmsDriver.py --python_filename recoStepUL2018.py --eventcontent AODSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier AODSIM --fileout file:BPH-RunIISummer20UL18RECO-00125.root --conditions 106X_upgrade2018_realistic_v11_L1v1 --step RAW2DIGI,L1Reco,RECO,RECOSIM,EI --geometry DB:Extended --filein file:HAA_PGun_HLT.root --era Run2_2018 --runUnscheduled --no_exec --mc -n 100 --procModifiers premix_stage2 --nThreads 8
