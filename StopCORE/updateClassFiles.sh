#! /bin/bash

# This will track the settings used in the makeCMS3ClassFiles.C
UPDATED_BABY_FILE=/nfs-7/userdata/stopRun2/stop_babies__CMS3_V080005__BabyMaker_V0800X_v4__20160710/ttbar_diLept_madgraph_pythia8_ext1_25ns.root
TREE=t
CLASS_NAME=stop_1l_babyAnalyzer
NAMESPACE=stop_1l
OBJECT=babyAnalyzer

root -l -b -q makeCMS3ClassFiles.C++'("'$UPDATED_BABY_FILE'","'$TREE'","'$CLASS_NAME'","'$NAMESPACE'","'$OBJECT'")'
rm ScanChain.C
rm doAll.C