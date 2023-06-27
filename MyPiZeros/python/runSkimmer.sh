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
folder=numEvents4000;
mkdir Skimmed_$folder/;
for ((i=$1 ; i<=$2 ; i+=$3));
do
echo "Running Skimmer on $folder/AToGG_RECO_M$i.0.root"
cmsRun Photon_MINIAODSIM_cfg.py inputFile=$folder/AToGG_RECO_M$i.0.root
echo Done
done
