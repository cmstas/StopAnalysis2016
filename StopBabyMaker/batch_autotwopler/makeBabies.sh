#! /bin/bash

if [ -z $CONDOR_ENV_READY ]; then
    echo ""
    echo "Condor_ENV_READY not set :(, exiting..."
    echo "do source setup.sh!"
    echo ""
    return 1;
fi

START_DIR=`pwd`

cd ../../../NtupleTools/AutoTwopler/

python batch.py

cd $START_DIR