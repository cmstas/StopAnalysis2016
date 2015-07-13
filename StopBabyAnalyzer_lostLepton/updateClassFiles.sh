#! /bin/bash

# This will track the settings used in the makeCMS3ClassFiles.C

UPDATED_BABY_FILE=/hadoop/cms/store/user/jgwood/condor/stop_1l_babies/stop_babies__lostLeptonBabies__20150702/merged_files/ttbar.root
TREE=t
CLASS_NAME=stop_1l_babyAnalyzer
NAMESPACE=stop_1l
OBJECT=babyAnalyzer

root -l -b -q makeCMS3ClassFiles.C++'("'$UPDATED_BABY_FILE'","'$TREE'","'$CLASS_NAME'","'$NAMESPACE'","'$OBJECT'")'
rm ScanChain.C
rm doAll.C