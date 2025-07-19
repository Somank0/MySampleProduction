How to run:
cmsrel CMSSW_10_6_29
cd CMSSW_10_6_29/src
git clone https://github.com/Somank0/MySampleProduction
cd MySampleProduction
cmsenv
scram b
cd MyPiZeros/test/120.0_SinglePi0E10+SinglePi0E10+DIGI+RECO
# for generating HToGG
cmsRun HToGG_pythia8_cfi_GEN_SIM.py
cp step1HToGGUncompressed.root ../../python/
cd ../../python/
# Now skim this using GenEventDump.cc module which is my pi0 edanalyser stripped of reco quantities
# Edit line 33 to specify required file for event dump ( In this case step1HToGGUncompressed.root )
cmsRun Photon_MINIAODSIM_cfg.py > eventlisting.log

#To generate A to gamma-gamma samples in the ECAL endcaps:

cd MySampleProduction/MyPiZeros/test/120.0_SinglePi0E10+SinglePi0E10+DIGI+RECO/AGun/HomeDirScripts

#Change the afs and eos paths in the runSampleGen_EE_plus.sh (or runSampleGen_EE_minus.sh).
./runSampleGen_EE_plus(minus).sh [Massmin] [Massmax] [Stepsize] [UniqueID]

#To make the ntuples from the reco file :

cd MySampleProduction/MyPiZeros/python

#Edit the 'folder'="path to the RECO file" and 'files'=(UniqueID)
./runSkimmer_unclustered.sh 1 1 1

#Analyze the ntuplelized/skimmed file using the analyzer.

cd /MySampleProduction/MyPiZeros/python/Skimmed/Analyzer

