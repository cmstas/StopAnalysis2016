# Environment
if [ "$CMSSW_VER" == "CMSSW_8_0_5_patch1" ]; then CMSSW_VER=CMSSW_8_0_5; fi

export SCRAM_ARCH=$SCRAM_VER
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /cvmfs/cms.cern.ch/$SCRAM_VER/cms/cmssw/$CMSSW_VER/src/
eval `scramv1 runtime -sh`
cd -

# Need this for .so files
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD

# Split Output files line into an array
OUTPUT_NAMES=(`echo $OUTPUT_NAMES | sed s/,/" "/g`)
echo "OUTPUT_NAMES=${OUTPUT_NAMES[*]}"

# Split Extra Args into an array 
EXE_ARGS=(`echo $EXE_ARGS | sed s/,/" "/g`)
echo "EXE_ARGS=${EXE_ARGS[*]}"


#
# Place for user code
#

cd forCondor_stopBabyMaker_80x/StopBabyMaker/

SAMPLE_NAME=${EXE_ARGS[0]}

echo " Running BabyMaker:"
echo "    ./runBabyMaker $SAMPLE_NAME $NEVENTS $IMERGED ./ "
./runBabyMaker $SAMPLE_NAME $NEVENTS $IMERGED ./


# Format output for gfal transfer
mv ${SAMPLE_NAME}_${IMERGED}.root ${OUTPUT_NAMES[0]}

cp ${OUTPUT_NAMES[0]} ${OUTPUT_NAMES[1]}