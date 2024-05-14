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

#folder=/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/rchatter/Particle_Gun/Tranche3/;
folder=/eos/user/c/cgupta/MyProjects/flashgg/CMSSW_10_6_29/src/MySampleProduction/MyPiZeros/test/120.0_SinglePi0E10+SinglePi0E10+DIGI+RECO/AGun/SingleMassSamples;
files=( "3139403_AToGG_RECO_M1200.0.root" "3140699_AToGG_RECO_M1000.0.root" "3140701_AToGG_RECO_M800.0.root" "3140703_AToGG_RECO_M1800.0.root" "3139403_AToGG_RECO_M1500.0.root" "3140700_AToGG_RECO_M900.0.root" "3140702_AToGG_RECO_M700.0.root" )


for i in ${files[@]};
do
echo "Running Skimmer on $folder/${i}"
cmsRun Photons_rajdeep_dr_cfg.py inputFile=$folder/${i}
echo "Done"
done
