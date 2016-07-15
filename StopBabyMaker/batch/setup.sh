#!/bin/bash

START_DIR=`pwd`

MAKER_NAME=StopBabyMaker
MAKER_PATH=$PWD/../../../StopAnalysis/
MAKER_DIR=${MAKER_PATH}${MAKER_NAME}

CORE_NAME=CORE
CORE_PATH=$PWD/../../../
CORE_DIR=${CORE_PATH}${CORE_NAME}

#COPY_NAME=stop_babies__CMS3_V080005__BabyMaker_V0800X_v5__20160714
COPY_NAME=stop_babies__CMS3_V080005__BabyMaker_V0800X_v6__20160715
COPY_PATH=/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/
COPY_DIR=${COPY_PATH}${COPY_NAME}

#SCRATCH_NAME=temp_stopBabies__20160714
SCRATCH_NAME=temp_stopBabies__20160715
SCRATCH_PATH=/data/tmp/jgwood/
SCRATCH_DIR=${SCRATCH_PATH}${SCRATCH_NAME}

CONDOR_DIR_NAME=forCondor_stopBabyMaker_80x

USER_EMAIL=jgwood@physics.ucsd.edu

#
# Input Sanitation
#

if [ -z $START_DIR ]; then
    echo "START_DIR not set, don't know where I am starting from :(, exiting..."
    echo "Please set it in setup.sh! and do source setup.sh"
    return 1;
fi
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
if [ ! -d $MAKER_DIR ]; then
    echo "$MAKER_DIR does not exist, :( exiting..."
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
if [ ! -d $CORE_DIR ]; then
    echo "$CORE_DIR does not exist, :( exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $SCRATCH_NAME ]; then
    echo "SCRATCH_NAME not set, don't know which SCRATCH area to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $SCRATCH_PATH ]; then
    echo "SCRATCH_PATH not set, don't know which SCRATCH area to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $SCRATCH_DIR ]; then
    echo "SCRATCH_DIR not set, don't know which SCRATCH area to use :(, exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ ! -d $SCRATCH_DIR ]; then
    echo "$SCRATCH_DIR does not exist, :( exiting..."
    echo "Please set it in setup.sh and do source setup.sh!"
    return 1;
fi
if [ -z $CONDOR_DIR_NAME ]; then
    echo "CONDOR_DIR_NAME not set, don't know what name to use for your tarball :(, exiting..."
    echo "Please set it in setup.sh! and do source setup.sh"
    return 1;
fi
if [ -z $USER_EMAIL ]; then
    echo "USER_EMAIL not set, don't know where to send email notifications for condor jobs completing :(, exiting..."
    echo "Please set it in setup.sh! and do source setup.sh"
    return 1;
fi

CONDOR_ENV_READY=true

