#! /bin/bash

# This will track the settings used in the makeCMS3ClassFiles.C
UPDATED_BABY_FILE=/hadoop/cms/store/user/haweber/AutoTwopler_babies/Stop_1l_v24_trulyunmerged/MuonEG_Run2016B-03Feb2017_ver2-v2/skim/skim_1.root 
#UPDATED_BABY_FILE=/nfs-7/userdata/isuarez/tupler_babies/merged/Stop_1l/v18/skim/ttbar_diLept_madgraph_pythia8_ext1_25ns.root
#UPDATED_BABY_FILE=/nfs-7/userdata/isuarez/tupler_babies/merged/Stop_1l/v16_Moriond17MC/skim/ttbar_diLept_madgraph_pythia8_ext1_25ns.root
#UPDATED_BABY_FILE=/nfs-7/userdata/isuarez/tupler_babies/merged/Stop_1l/v11/skim/ttbar_diLept_madgraph_pythia8_ext1_25ns.root
#UPDATED_BABY_FILE=/nfs-7/userdata/jgwood/tupler_babies/merged/Stop_1l/v8.0x_v10/output/ttbar_diLept_madgraph_pythia8_ext1_25ns.root
#UPDATED_BABY_FILE=/nfs-7/userdata/jgwood/tupler_babies/merged/Stop_1l/v10/output/ttbar_diLept_madgraph_pythia8_ext1_25ns.root
#UPDATED_BABY_FILE=/nfs-7/userdata/stopRun2/stop_babies__CMS3_V080005__BabyMaker_V0800X_v7__20160722/ttbar_diLept_madgraph_pythia8_ext1_25ns.root
#UPDATED_BABY_FILE=/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__CMS3_V080005__BabyMaker_V0800X_v6__20160715/merged_files/ttbar_diLept_madgraph_pythia8_ext1_25ns.root
#UPDATED_BABY_FILE=/nfs-7/userdata/stopRun2/stop_babies__CMS3_V080005__BabyMaker_V0800X_v4__20160710/ttbar_diLept_madgraph_pythia8_ext1_25ns.root
TREE=t
CLASS_NAME=stop_1l_babyAnalyzer
NAMESPACE=stop_1l
OBJECT=babyAnalyzer

root -l -b -q makeCMS3ClassFiles.C++'("'$UPDATED_BABY_FILE'","'$TREE'","'$CLASS_NAME'","'$NAMESPACE'","'$OBJECT'")'
rm ScanChain.C
rm doAll.C