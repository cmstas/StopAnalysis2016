#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V00-00-01/condor_V00-00-01_data_single_electron_2015D_promptRecoV4_25ns.cmd
condor_submit configs_V00-00-01/condor_V00-00-01_data_single_muon_2015D_promptRecoV4_25ns.cmd
condor_submit configs_V00-00-01/condor_V00-00-01_DYJetsToLL_m10To50_amcnlo_pythia8_25ns.cmd
condor_submit configs_V00-00-01/condor_V00-00-01_DYJetsToLL_m50_amcnlo_pythia8_25ns.cmd
condor_submit configs_V00-00-01/condor_V00-00-01_QCD_25ns.cmd
condor_submit configs_V00-00-01/condor_V00-00-01_ttbar_madgraph_pythia8_25ns.cmd
condor_submit configs_V00-00-01/condor_V00-00-01_WJetsToLNu_amcnlo_pythia8_25ns.cmd
