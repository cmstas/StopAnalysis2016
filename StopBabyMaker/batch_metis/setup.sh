#! /bin/bash

METIS_PATH=~/working/ProjectMetis
BATCH_DIR=$PWD
BABYMAKER_DIR=..

# Checkout ProjectMetis, if necessary
if [ -z $METIS_PATH ] && [ ! -d ProjectMetis ]; then
    git clone git@github.com:aminnj/ProjectMetis.git
elif [ ! -d ProjectMetis ]; then
    ln -s $METIS_PATH ProjectMetis
fi

# Setup the environment for ProjectMetis
cd ProjectMetis
. setup.sh
cd ..

# Make the input tarfile

[[ `ls input/` ]] && echo "[setup] Cleaning input/" && rm -r input/*
echo "[setup] Making input tarfile... This assumes that the babymaker has been compiled and tested."
pushd $BABYMAKER_DIR > /dev/null
cp -r *.so LinkDef_rdict.pcm btagsf jecfiles json_files lepsf TopTagger puWeights_2016data_36p6fbinv.root xsec_stop_13TeV.root scale1fbs.txt runBabyMaker sample_2017.dat $BATCH_DIR/input
popd > /dev/null
tar -czf input.tar.gz input

if [ ! -f merge_scripts.tar.gz ]; then
    echo "[setup] Making tarfile for merge scripts."
    tar -czf merge_scripts.tar.gz mergeHadoopFiles.C ../skimBaby.C
fi

# Flag for successful environment setup
CONDOR_ENV_READY=true
