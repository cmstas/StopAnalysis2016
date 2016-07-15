#!/bin/bash

# Track time job begins
RIGHT_NOW=`date +"%Y%m%d %H%M%S"`
echo ""
echo "*************************************"
echo "  Beginning Condor Job "
echo "    TIME = $RIGHT_NOW "
echo "*************************************"
echo ""

# This stuff to drive the baby maker macro
NAME=$1
NEVENTS=$2
NUMBER=$3

#This stuff to get output back
export COPYDIR=$4
export CONDOR_DIR_NAME=$5
export MAKER_NAME=$6


# Setup Environment
RIGHT_NOW=`date +"%Y%m%d %H%M%S"`
echo ""
echo "*************************************"
echo "  Setting up environment... "
echo "    TIME = $RIGHT_NOW "
echo "*************************************"
echo ""

# Show where you are
hostname

# Show g++ version
echo " " 
echo "G++ INFORMATION" 
g++ --version
which g++

CMSSW_VERSION=CMSSW_8_0_5_patch1

export CMS_PATH=/cvmfs/cms.cern.ch
echo "CMSENV"
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
OLDDIR=`pwd`
cd /cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw-patch/$CMSSW_VERSION/src
eval `scramv1 runtime -sh`
cd $OLDDIR


# Untar the zip dir
RIGHT_NOW=`date +"%Y%m%d %H%M%S"`
echo ""
echo "*************************************"
echo "  Unpack the tarball... "
echo "    TIME = $RIGHT_NOW "
echo "*************************************"
echo ""

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

cd $MAKER_NAME/


# Run babyMaker
RIGHT_NOW=`date +"%Y%m%d %H%M%S"`
echo ""
echo "*************************************"
echo "  Running babyMaker... "
echo "    TIME = $RIGHT_NOW "
echo "*************************************"
echo ""

./runBabyMaker "$NAME" $NEVENTS $NUMBER "./"
ls -l `pwd`/${NAME}_${NUMBER}.root


# Copy the output to the output directory via gfal-copy new
RIGHT_NOW=`date +"%Y%m%d %H%M%S"`
echo ""
echo "*************************************"
echo "  Copy output file with gfal-copy... "
echo "    TIME = $RIGHT_NOW "
echo "*************************************"
echo ""

#  This preserves grid functionality
echo "copying.  LS is: "
ls -l ${NAME}_${NUMBER}.root

#gfal-copy -b -D srmv2 --vo cms --connect-timeout 2400 --verbose file://`pwd`/${NAME}_${NUMBER}.root srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${COPYDIR}/${NAME}_${NUMBER}.root
gfal-copy -p -f -t 4200 --verbose file://`pwd`/${NAME}_${NUMBER}.root srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${COPYDIR}/${NAME}_${NUMBER}.root

# Job Complete
RIGHT_NOW=`date +"%Y%m%d %H%M%S"`
echo ""
echo "*************************************"
echo "  JOB COMPLETE! "
echo "    TIME = $RIGHT_NOW "
echo "*************************************"
echo ""
