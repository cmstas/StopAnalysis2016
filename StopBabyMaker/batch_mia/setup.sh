#BABYMAKER_DIR_NAME=$PWD/../
#CORE_DIR=$PWD/../../../CORE
#CONDOR_DIR_NAME=forCondor_stopBabyMaker_74x
BABYMAKER_DIR_NAME=
CORE_DIR=
CONDOR_DIR_NAME=
START_DIR=`pwd`

if [ -z $CMSSW_BASE ]; then
    echo "CMSSW_BASE var not set, run cmsenv, exiting..."
    return 1;
fi
if [ -z $BABYMAKER_DIR_NAME ]; then
    echo "BABYMAKER_DIR_NAME not set, don't know which babymaker to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $CORE_DIR ]; then
    echo "CORE_DIR not set, don't know which CORE to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $CONDOR_DIR_NAME ]; then
    echo "Do not know what name to use for your tarball :(, exiting..."
    echo "Please set it in setup.sh! and do source setup.sh"
    return 1;
fi



