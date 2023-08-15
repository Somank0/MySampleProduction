#!/usr/bin/bash
if [ -z $1 ] ; then
  echo "Please use: ./runSkimmer [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)]" && exit 1;
fi
if [ -z $2 ] ; then
  echo "Please use: ./runSkimmer [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)]" && exit 2;
fi
if [ -z $3 ] ; then
  echo "Please use: ./runSkimmer [massMin(MeV)] [massMax(MeV)] [stepSize(MeV)]" && exit 3;
fi
cmsenv;
folder=/eos/user/a/abala/Chirayu/CMSSW_10_6_29/src/;
#folder=testsamplev5/
mkdir Skimmed_endcaps/;
for ((i=$1 ; i<=$2 ; i+=$3));
do
echo "Running Skimmer on $folder/${i}_AToGG_RECO_M2000.0.root"
cmsRun Photon_MINIAODSIM_cfg.py inputFile=$folder/${i}_AToGG_RECO_M2000.0.root
echo Done
done
