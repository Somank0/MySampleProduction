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


#Trache1
#folder=/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/rchatter/Particle_Gun/;
#files=( 9007189 9007195 9025723 9029467 9007190 9007196 9025724 9029468 9007191 9007197 9025725 9007192 9007198 9025726 9007193 9025721 9025729 9007194 9025722 9029461 )
#for i in ${files[@]};
#do
#echo "Running Skimmer on $folder/${i}_AToGG_RECO_M2000.0.root"
#cmsRun Photons_rajdeep_dr_cfg.py inputFile=$folder/${i}_AToGG_RECO_M2000.0.root
#echo "Trache1 done"
#done

#Trache2
#folder=/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/rchatter/Particle_Gun/Tranche2/;
#files=( 9029460 9029469 9080449 9108981 9029462 9080445 9080450 9108983 9029463 9080446 9080451 9108987 9029464 9080447 9080452 9108988 9029466 9080448 9108980 9108989 )

#for i in ${files[@]};
#do
#echo "Running Skimmer on $folder/${i}_AToGG_RECO_M2000.0.root"
#cmsRun Photons_rajdeep_dr_cfg.py inputFile=$folder/${i}_AToGG_RECO_M2000.0.root
#echo "Trache1 done"
#done

#Trache3
#folder=/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/rchatter/Particle_Gun/Tranche3/;
#files=( 9120502 9120508 9131188 9131195 9120503 9120509 9131191 9131196 9120504 9120510 9131192 9131197 9120505 9120511 9131193 9139968 9120506 )
#files=( 9120512 ) 
#files=( 9131194 9139969 )

#Trache4
#folder=/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/rchatter/Particle_Gun/Tranche4/;
#files=( 9155515 9155523 9164382 9164387 9155516 9155524 9164383 9164388 9155519 9164378 9164384 9201337 9155520 9164380 9164385 9201338 9155522 9164381 9164386 9201342 )
folder=/eos/user/s/sosaha/CMSSW_13_0_13/src/MySampleProduction/MyPiZeros/test/120.0_SinglePi0E10+SinglePi0E10+DIGI+RECO/AGun
#files=(00012 3657458  3657463 3657462 3657460 3657461)
#files=(3657459)
#files=(3658340 3658265 3658264 3658266 3658339 3659970 3659972 3659974 3660530 3658263 3660526 3659967 3668449 3668445 3668446 3668448 3660973 3668451 3668447 3668450 3668453)
#files=(3668918 3668917 3660972 3660971 3669818 3669820 3670733 3670731 3669801 3669799 3669791 3669803 3669797 3673558 3673577)
#files=(3673549 3673570 3677903 3677902 3678132)
#files=(3693126)
#files=(3878706 3878705)
#files=( 3695346  3695344 3695470 3695347  3695469  3695466 3695343 3695463  3695471  3695467 3695468 3785285  3785286 3785283 3785284 3813420 3813419 3813417)
files=(0000)
for i in ${files[@]};
do
echo "Running Skimmer on $folder/${i}_AToGG_RECO_M1000.0.root"
cmsRun Photons_rajdeep_dr_cfg.py inputFile=$folder/${i}_AToGG_RECO_M1000.0.root
echo "Trache1 done"
done
