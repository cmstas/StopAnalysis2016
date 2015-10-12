MAKER_NAME=StopBabyMaker
MAKER_PATH=$PWD/../../../StopAnalysis/
MAKER_DIR=$MAKER_PATH/$MAKER_NAME

CORE_NAME=CORE
CORE_PATH=$PWD/../../../
CORE_DIR=$CORE_PATH/$CORE_NAME

CONDOR_DIR_NAME=forCondor_stopBabyMaker_74x

START_DIR=`pwd`

if [ -z $CMSSW_BASE ]; then
    echo "CMSSW_BASE var not set, run cmsenv, exiting..."
    return 1;
fi
if [ -z $MAKER_NAME ]; then
    echo "MAKER_NAME not set, don't know which maker to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $MAKER_PATH ]; then
    echo "MAKER_PATH not set, don't know which maker to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $MAKER_DIR ]; then
    echo "MAKER_DIR not set, don't know which maker to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $CORE_NAME ]; then
    echo "CORE_NAME not set, don't know which CORE to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $CORE_PATH ]; then
    echo "CORE_PATH not set, don't know which CORE to use :(, exiting..."
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



