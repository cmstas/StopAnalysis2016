#! /bin/bash

# This will track the settings used in the makeCMS3ClassFiles.C
UPDATED_BABY_FILE=/nfs-7/userdata/stopRun2/StopBabies__CMS3_V07-08-00-XX/StopBabyMaker__v8p0x_v2/ttbar_diLept_madgraph_pythia8_ext1_25ns.root
TREE=t
CLASS_NAME=stop_1l_babyAnalyzer
NAMESPACE=stop_1l
OBJECT=babyAnalyzer

root -l -b -q makeCMS3ClassFiles.C++'("'$UPDATED_BABY_FILE'","'$TREE'","'$CLASS_NAME'","'$NAMESPACE'","'$OBJECT'")'
rm ScanChain.C
rm doAll.C