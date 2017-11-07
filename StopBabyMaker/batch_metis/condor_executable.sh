#!/bin/bash

# This is a baby making condor executable for CondorTask of ProjectMetis. Passed in arguments are:
# arguments = [outdir, outname_noext, inputs_commasep, index, cmssw_ver, scramarch, self.arguments]

OUTPUTDIR=$1
OUTPUTNAME=$2
INPUTFILENAMES=$3
IFILE=$4
CMSSW_VERSION=$5
SCRAM_ARCH=$6
ISFASTSIM=$7

OUTPUTNAME=$(echo $OUTPUTNAME | sed 's/\.root//')

echo Number of arguments is $#, and they are:
echo $@
echo ----------------------------------------------
ls -ltrha
echo ----------------------------------------------
# Unpack the passed in tarfile
tar -xzf package.tar.gz
cd input
ls -ltrha
echo ----------------------------------------------
# Setup Enviroment
export SCRAM_ARCH=$SCRAM_ARCH
source /cvmfs/cms.cern.ch/cmsset_default.sh
pushd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/cmssw/$CMSSW_VERSION/src/ > /dev/null
eval `scramv1 runtime -sh`
popd > /dev/null

# The output name is the sample name for stop baby
SAMPLE_NAME=$OUTPUTNAME
NEVENTS=-1

# if [ ! -z ${EXE_ARGS[1]} ]; then
#   ISFASTSIM=${EXE_ARGS[1]}
# fi

echo "Running BabyMaker:"
echo "  ./runBabyMaker $SAMPLE_NAME $NEVENTS $IMERGED ./ $INPUTFILENAMES $ISFASTSIM"
./runBabyMaker $SAMPLE_NAME $NEVENTS $IFILE ./ $INPUTFILENAMES $ISFASTSIM

echo ----------------------------------------------
ls -ltrha
echo ----------------------------------------------

# # Perform Skim
# root -l -b -q skimBaby.C++'("'${SAMPLE_NAME}_${IFILE}.root'", "'${OUTPUT_NAMES}'")'

# Copy back the output file
gfal-copy -p -f -t 4200 --verbose file://`pwd`/${OUTPUTNAME}_${IFILE}.root gsiftp://gftp.t2.ucsd.edu${OUTPUTDIR}/${OUTPUTNAME}_${IFILE}.root --checksum ADLER32

# # Need this for .so files
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD

# # Split Output files line into an array
# OUTPUT_NAMES=(`echo $OUTPUT_NAMES | sed s/,/" "/g`)
# echo "OUTPUT_NAMES=${OUTPUT_NAMES[*]}"

# # Format output for gfal transfer
# mv ${SAMPLE_NAME}_${IMERGED}.root ${OUTPUT_NAMES[0]}

# # Perform Skim
# #root -l -b -q skimBaby.C++'("'${OUTPUT_NAMES[0]}'", "'${OUTPUT_NAMES[1]}'")'

# # ls -lrtha

# #
# # Sweep Root
# #
# for output in ${OUTPUT_NAMES[@]}; do
#     RESULT=`root -l -b -q sweepRoot.C+'("'$output'")' | grep "result=" | sed s/result=//g`
#     echo "RESULT=$RESULT"
#     if [ "$RESULT" == "1" ]; then 
# 	echo "$output failed sweepRoot...deleting..."
# 	rm -rf $output
#     fi
# done

# ls -lrtha
