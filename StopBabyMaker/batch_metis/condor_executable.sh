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

echo -e "\n--- begin header output ---\n" #                     <----- section division
echo "OUTPUTDIR: $OUTPUTDIR"
echo "OUTPUTNAME: $OUTPUTNAME"
echo "INPUTFILENAMES: $INPUTFILENAMES"
echo "IFILE: $IFILE"
echo "CMSSW_VERSION: $CMSSW_VERSION"
echo "SCRAM_ARCH: $SCRAM_ARCH"

echo "hostname: $(hostname)"
echo "uname -a: $(uname -a)"
echo "time: $(date +%s)"
echo "args: $@"

echo -e "\n--- end header output ---\n" #                       <----- section division
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

# Rigorous sweeproot which checks ALL branches for ALL events.
# If GetEntry() returns -1, then there was an I/O problem, so we will delete it
python << EOL
import ROOT as r
import os
import traceback
foundBad = False
try:
    f1 = r.TFile("${OUTPUTNAME}_${IFILE}.root")
    t = f1.Get("t")
    nevts = t.GetEntries()
    print "[SweepRoot] ntuple has %i events." % t.GetEntries()
    if int(t.GetEntries()) <= 0:
        foundBad = True
    for i in range(0,t.GetEntries(),1):
        if t.GetEntry(i) < 0:
            foundBad = True
            print "[RSR] found bad event %i" % i
            break
except Exception as ex:
    msg = traceback.format_exc()
    print "Encounter error during SweepRoot:"
    print msg
if foundBad:
    print "[RSR] removing output file because it does not deserve to live"
    os.system("rm ${OUTPUTNAME}_${IFILE}.root")
else:
    print "[RSR] passed the rigorous sweeproot"
EOL

echo -e "\n--- end running ---\n" #                             <----- section division

# Copy back the output file

# Go to a enviroment that gfal-copy doesn't just fail
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
pushd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/cmssw/CMSSW_9_2_8/src/ > /dev/null
eval `scramv1 runtime -sh`
popd > /dev/null

gfal-copy -p -f -t 4200 --verbose file://`pwd`/${OUTPUTNAME}_${IFILE}.root gsiftp://gftp.t2.ucsd.edu${OUTPUTDIR}/${OUTPUTNAME}_${IFILE}.root --checksum ADLER32

echo -e "\n--- cleaning up ---\n" #                             <----- section division
cd ..
rm -r package.tar.gz input/
