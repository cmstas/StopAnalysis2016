#!/bin/bash
function run () {
    echo root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\)
    nohup nice -n 19 root -b -q mergeHadoopFiles.C\(\"${HADOOPDIR}/${TAG}_$1/\",\"${OUTPUTDIR}/$1.root\"\) >& merge_logs_${TAG}/log_merge_$1.txt &
}

source settings.sh 

mkdir -p $OUTPUTDIR
chmod -R a+wrx $OUTPUTDIR

if [ ! -d "merge_logs_${TAG}" ]; then
  mkdir merge_logs_${TAG}
fi
run  tbar_tch_4f_powheg_pythia8_25ns
run  t_tch_4f_powheg_pythia8_25ns
run  t_sch_4f_amcnlo_pythia8_25ns
run  t_tbarW_5f_powheg_pythia8_25ns
run  t_tW_5f_powheg_pythia8_25ns
run  TTZToLLNuNu_M-10_amcnlo_pythia8_25ns
run  data_double_eg_2015C_25ns
run  data_double_eg_2015D_05Oct2015_v1_25ns
run  data_double_eg_2015D_promptRecoV4_25ns
run  data_double_mu_2015C_25ns
run  data_double_mu_2015D_05Oct2015_v1_25ns
run  data_double_mu_2015D_promptRecoV4_25ns
run  data_muon_eg_2015C_25ns
run  data_muon_eg_2015D_05Oct2015_v1_25ns
run  data_muon_eg_2015D_05Oct2015_v2_25ns
run  data_muon_eg_2015D_promptRecoV4_25ns
run  data_single_electron_2015C_25ns
run  data_single_electron_2015D_05Oct2015_v1_25ns
run  data_single_electron_2015D_promptRecoV4_25ns
run  data_single_muon_2015C_25ns
run  data_single_muon_2015D_05Oct2015_v1_25ns
run  data_single_muon_2015D_promptRecoV4_25ns
run  data_met_2015C_25ns
run  data_met_2015D_05Oct2015_v1_25ns
run  data_met_2015D_promptRecoV4_25ns
run  ttbar_powheg_pythia8_25ns
run  ttbar_powheg_pythia8_ext3_25ns
run  DYJetsToLL_m50_amcnlo_pythia8_50ns
run  WJetsToLNu_madgraph_pythia8_25ns
run  WJetsToLNu_HT100To200_madgraph_pythia8_25ns
run  WJetsToLNu_HT200To400_madgraph_pythia8_25ns
run  WJetsToLNu_HT400To600_madgraph_pythia8_25ns
run  WJetsToLNu_HT600To800_madgraph_pythia8_25ns
run  WJetsToLNu_HT800To1200_madgraph_pythia8_25ns
run  WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns
run  WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns
run  WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns
run  DYJetsToLL_M-50_HT-100to200
run  DYJetsToLL_M-50_HT-200to400
run  DYJetsToLL_M-50_HT-400to600
run  DYJetsToLL_M-50_HT-600toInf
# # #

# # #
# # # W+JETS
# # #

# # # run wjets_lnu
# # # run wjets_ht100to200
# # # run wjets_ht200to400
# # # run wjets_ht400to600
# # # run wjets_ht600toinf
# # # run wjets_enu
# # # run wjets_mnu

# # # #
# # # # Z INVISIBLE
# # # #

# # # run zinv_ht100to200
# # # run zinv_ht200to400
# # # run zinv_ht400to600
# # # run zinv_ht600toinf

# #
# # DIBOSON
# #

# run wz_3lnu
# run zz_4l

# # #
# # # TRIBOSON
# # #

# # #
# # # TTV
# # #

# run ttw
# run ttz
# run tth
