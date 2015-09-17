#!/bin/bash

# This stuff to drive the baby maker macro
NAME=$1
NEVENTS=$2
NUMBER=$3

#This stuff to get output back
export COPYDIR=$4
export CONDOR_DIR_NAME=$5

#Show where you are
hostname

#Environment
#Show g++ version
echo " " 
echo "G++ INFORMATION" 
g++ --version
which g++

CMSSW_VERSION=CMSSW_7_4_1_patch1

export CMS_PATH=/cvmfs/cms.cern.ch
echo "[wrapper] setting env"
export SCRAM_ARCH=slc6_amd64_gcc491
source /cvmfs/cms.cern.ch/cmsset_default.sh
OLDDIR=`pwd`
cd /cvmfs/cms.cern.ch/slc6_amd64_gcc491/cms/cmssw-patch/$CMSSW_VERSION/src
#cmsenv
eval `scramv1 runtime -sh`
cd $OLDDIR


#Set CMSSW environment

#pushd /cvmfs/cms.cern.ch/slc6_amd64_gcc481/cms/cmssw/CMSSW_7_4_1/src/
#eval `scramv1 runtime -sh`
#popd

#Untar the zip dir
echo "This this the current dir: "
THISDIR=`pwd`
echo $THISDIR
echo "LS to check that all files were transferred: "
ls
tar xzfv $CONDOR_DIR_NAME.tar.gz
echo "LS to check that tarball was unpacked: "
ls
cd $CONDOR_DIR_NAME
echo "LS to check contents of unpacked stopbabymaker: "
ls

# Make supporting libs
echo "clean CORE"
cd CORE/
ls
make clean
echo "remaking CORE"
make
cd ../

cd StopBabyMaker/stop_variables/
make clean
make
cd ../
make clean
make

# Run babyMaker
./runBabyMaker "$NAME" $NEVENTS $NUMBER "./"
ls -l `pwd`/${NAME}_${NUMBER}.root

# Copy the output to the output directory via lcg-cp
#  This preserves grid functionality
echo "copying.  LS is: "
ls -l ${NAME}_${NUMBER}.root

lcg-cp -b -D srmv2 --vo cms --connect-timeout 2400 --verbose file://`pwd`/${NAME}_$NUMBER.root srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${COPYDIR}/${NAME}_$NUMBER.root
