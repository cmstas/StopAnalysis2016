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

OUTPUTDIR=`dirname $OUTPUTDIR`
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

# Unpack the passed in tarfile
tar -xzf package.tar.gz
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

echo "Running Merge Jobs:"
mergeout_folder=$OUTPUTDIR/merged
skimout_folder=$OUTPUTDIR/skimmed
mkdir -p $mergeout_folder
mkdir -p $skimout_folder

# Perform Merge
# out_file=${mergeout_folder}/merged_${OUTPUTNAME}.root
out_file=${OUTPUTNAME}.root
in_folder=${OUTPUTDIR}
echo "Will merge $in_folder/*.root into $out_file"
echo root -l -n -b -q mergeHadoopFiles.C\(\"${in_folder}\",\"${out_file}\"\)
root -l -n -b -q mergeHadoopFiles.C\(\"${in_folder}\",\"${out_file}\"\)

# Perform Skim
out_file=${skimout_folder}/skimmed_${OUTPUTNAME}.root

for in_file in ${OUTPUTNAME}*.root; do
    echo "Will skim $in_folder/*.root into $out_file"
    root -l -b -q skimBaby.C++'("'${in_file}'", "skimmed_'${in_file}'")'
done
rename skimmed_merged skimmed *.root

echo ----------------------------------------------
ls -ltrha
echo ----------------------------------------------

# # Rigorous sweeproot which checks ALL branches for ALL events.
# # If GetEntry() returns -1, then there was an I/O problem, so we will delete it
# python << EOL
# import ROOT as r
# import os
# import traceback
# foundBad = False
# try:
#     f1 = r.TFile("${OUTPUTNAME}_${IFILE}.root")
#     t = f1.Get("t")
#     nevts = t.GetEntries()
#     print "[SweepRoot] ntuple has %i events." % t.GetEntries()
#     if int(t.GetEntries()) <= 0:
#         foundBad = True
#     for i in range(0,t.GetEntries(),1):
#         if t.GetEntry(i) < 0:
#             foundBad = True
#             print "[RSR] found bad event %i" % i
#             break
# except Exception as ex:
#     msg = traceback.format_exc()
#     print "Encounter error during SweepRoot:"
#     print msg
# if foundBad:
#     print "[RSR] removing output file because it does not deserve to live"
#     os.system("rm ${OUTPUTNAME}_${IFILE}.root")
# else:
#     print "[RSR] passed the rigorous sweeproot"
# EOL

echo -e "\n--- end running ---\n" #                             <----- section division

[[ ! -f ${OUTPUTNAME}_1.root ]] && mv ${OUTPUTNAME}.root ${OUTPUTNAME}_1.root

# Copy back the output file
for mergeout in ${OUTPUTNAME}*.root; do
    gfal-copy -p -f -t 4200 --verbose file://`pwd`/$mergeout gsiftp://gftp.t2.ucsd.edu${mergeout_folder}/${mergeout} --checksum ADLER32
done

for skimout in skimmed_*.root; do
    gfal-copy -p -f -t 4200 --verbose file://`pwd`/$skimout gsiftp://gftp.t2.ucsd.edu${skimout_folder}/${mergeout} --checksum ADLER32
done

echo -e "\n--- cleaning up ---\n" #                             <----- section division
rm -r *.root
