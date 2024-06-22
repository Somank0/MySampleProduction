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
	#cmsRun AToGG_GEN_SIM_MeV_mass.py mass=$i ptMin=15 ptMax=25 etaMin=-1.4 etaMax=1.4 maxEvents=4000;
	cmsRun AToGG_GEN_SIM_MeV_mass.py mass=$i ptMin=10 ptMax=20 etaMin=-1.4 etaMax=1.4 maxEvents=10;
	echo "==============================GEN-SIM step complete! Starting DIGI-PREMIX-RAW step=============================="
	cmsRun genSimDigiRaw_mcProd_SS.py mass=$i;
	echo "==============================DIGI-PREMIX-RAW step complete! Starting HLT step=============================="
	cd CMSSW_10_2_16_UL/src;
	cmsenv;
	echo "------------------------------Using CMSSW_10_2_16_UL------------------------------"
	cmsRun hlt_SS.py mass=$i;
	echo "==============================HLT step complete! Starting RECO-AOD step=============================="
	cd ../../;
	cmsenv;
	echo "------------------------------Using CMSSW_10_6_29------------------------------"
	cmsRun recoStepUL2018_SS.py mass=$i;
	echo "==============================RECO-AOD step complete! Sample generation complete !=============================="
done
