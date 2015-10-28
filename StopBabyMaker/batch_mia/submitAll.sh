#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V00-00-01/condor_V00-00-01_data_single_electron_2015C_25ns.cmd
condor_submit configs_V00-00-01/condor_V00-00-01_data_single_electron_2015D_25ns.cmd
condor_submit configs_V00-00-01/condor_V00-00-01_data_single_muon_2015C_25ns.cmd
condor_submit configs_V00-00-01/condor_V00-00-01_data_single_muon_2015D_25ns.cmd
