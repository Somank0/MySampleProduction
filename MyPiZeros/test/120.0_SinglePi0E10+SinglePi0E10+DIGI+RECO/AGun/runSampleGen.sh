#!/usr/bin/bash
if [ -z $1 ] ; then
  echo "Please use: ./runSampleGen [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)]" && exit 1;
fi
if [ -z $2 ] ; then
  echo "Please use: ./runSampleGen [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)]" && exit 2;
fi
if [ -z $3 ] ; then
  echo "Please use: ./runSampleGen [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)]" && exit 3;
fi
cmsenv;
for ((i=$1 ; i<=$2 ; i+=$3));
do
	
	echo "==============================Starting Sample generation for mass $i. GEN-SIM step=============================="
	echo "------------------------------Using CMSSW_10_6_29------------------------------"
	cmsRun AToGG_pythia8_cfi_GEN_SIM.py mass=$i ptMin=20 ptMax=100 etaMin=-1.4 etaMax=1.4 maxEvents=4000;
	echo "==============================GEN-SIM step complete! Starting DIGI-PREMIX-RAW step=============================="
	cmsRun genSimDigiRaw_mcProd.py mass=$i;
	echo "==============================DIGI-PREMIX-RAW step complete! Starting HLT step=============================="
	cd CMSSW_10_2_16_UL/src;
	cmsenv;
	echo "------------------------------Using CMSSW_10_2_16_UL------------------------------"
	cmsRun hlt.py mass=$i;
	echo "==============================HLT step complete! Starting RECO-AOD step=============================="
	cd ../../;
	cmsenv;
	echo "------------------------------Using CMSSW_10_6_29------------------------------"
	rm AToGG_DIGI_*;
	cmsRun recoStepUL2018.py mass=$i;
	rm AToGG_HLT_*;
	echo "==============================RECO-AOD step complete! Sample generation complete !=============================="
done
