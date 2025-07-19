How to run:
```
cmsrel CMSSW_10_6_29
cd CMSSW_10_6_29/src
git clone https://github.com/Somank0/MySampleProduction
cd MySampleProduction
cmsenv
scram b
cd MyPiZeros/test/120.0_SinglePi0E10+SinglePi0E10+DIGI+RECO
```

```
To produce flat mass samples :
cd CMSSW_version/src
cmsenv
git cms-addpkg GeneratorInterface/Pythia8Interface
scram b -j32
```

In this file: GeneratorInterface/Pythia8Interface/plugins/Py8PtGun.cc

Replace: double mass = (fMasterGen->particleData).m0( particleID );

With: double mass = ([massmax] - [mass_min]) * randomEngine().flat() + [massmin];    replace massmax and massmin with their values


# for generating HToGG

cmsRun HToGG_pythia8_cfi_GEN_SIM.py

# To run AtoGG sample, go to the AGun/HomeDirScripts 

# Change the afs and eos paths in the runSampleGen_EE_plus.sh (or runSampleGen_EE_minus.sh).

./runSampleGen_EE_plus(minus).sh [Massmin] [Massmax] [Stepsize] [UniqueID]

## For AtoGG :

### GEN-SIM step file : AToGG_GEN_SIM_MeV_mass_fixed.py

### DIGI step file : genSimDigiRaw_mcProd_SS.py

### HLT step file :  CMSSW_10_2_16_UL/src/hlt_SS.py

### RECO step file : recoStepUL2018_SS.py

# To make the ntuples from the reco file :

cd MySampleProduction/MyPiZeros/python

#Edit the 'folder'="path to the RECO file" and 'files'=(UniqueID)
./runSkimmer_unclustered.sh 1 1 1

#Analyze the ntuplelized/skimmed file using the analyzer.

cd /MySampleProduction/MyPiZeros/python/Skimmed/Analyzer


## Older instructions from Chirayu are in the README_old.md
