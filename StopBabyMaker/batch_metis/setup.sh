#! /bin/bash

METIS_PATH=~/working/ProjectMetis
BATCH_DIR=$PWD
BABYMAKER_DIR=..

# Checkout ProjectMetis, if necessary
if [ -z $METIS_PATH ] && [ ! -d ProjectMetis ]; then
    git clone git@github.com:aminnj/ProjectMetis.git
else
    ln -s $METIS_PATH ProjectMetis
fi

# Setup the environment for ProjectMetis
cd ProjectMetis
. setup.sh
cd ..

# Make the input tarfile

echo "[setup] Making tarfile... This assumes that the babymaker has been compiled and tested"
rm -r input/*
pushd $BABYMAKER_DIR > /dev/null
cp -r *.so LinkDef_rdict.pcm btagsf jecfiles json_files lepsf puWeights_2016data_36p6fbinv.root runBabyMaker sample_2017.dat $BATCH_DIR/input
popd > /dev/null
tar -czf input.tar.gz input


# Flag for successful environment setup
CONDOR_ENV_READY=true
