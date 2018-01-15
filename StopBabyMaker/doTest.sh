#!/bin/bash

[[ -f Makefile ]] && { make -j 12 || return $?; }

./runBabyMaker stopbaby 3000 4 ./ /hadoop/cms/store/user/sicheng/ProjectMetis/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v3_MINIAODSIM_CMS4_V00-00-07_test/merged_ntuple_12.root 0 
