#!/bin/bash

#
# All MT2 related datasets available on hadoop
#

# compile files
#cd ..
#make -j25
#cd -

# copy compiled files
#cp -r ../*.so ../jetCorrections ../processBaby ../json_270715_golden.txt job_input/ 

source settings.sh 

# update tag
TAG=${analysis_version}

##########
# Example#
##########

#./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_MuonEG_MINIAOD_PromptReco-v1/merged/V07-04-08/  ${TAG}_data_muon_eg_2015C_25ns data_muon_eg_2015C_25ns

#########
# DATA  #
#########
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SingleElectron_MINIAOD_PromptReco-v4/merged/V07-04-11/ ${TAG}_data_single_electron_2015D_promptRecoV4_25ns data_single_electron_2015D_promptRecoV4_25ns
./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SingleMuon_MINIAOD_PromptReco-v4/merged/V07-04-11/ ${TAG}_data_single_muon_2015D_promptRecoV4_25ns data_single_muon_2015D_promptRecoV4_25ns
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/ ${TAG}_WJetsToLNu_amcnlo_pythia8_25ns WJetsToLNu_amcnlo_pythia8_25ns
./writeConfig.sh  /hadoop/cms/store/group/snt/run2_25ns/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/ ${TAG}_DYJetsToLL_m10To50_amcnlo_pythia8_25ns DYJetsToLL_m10To50_amcnlo_pythia8_25ns
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/V07-04-08/ ${TAG}_DYJetsToLL_m50_amcnlo_pythia8_25ns DYJetsToLL_m50_amcnlo_pythia8_25ns
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-08/ ${TAG}_ttbar_madgraph_pythia8_25ns ttbar_madgraph_pythia8_25ns
./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/QCD_Pt-20toInf_MuEnrichedPt15_TuneCUETP8M1_13TeV_pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-08/ ${TAG}_QCD_25ns QCD_25ns 
#./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015B_DoubleEG_MINIAOD_PromptReco-v1/merged/V07-04-06/   ${TAG}_data_50ns_ee
#./writeConfig.sh /hadoop/cms/store/user/cwelke/run2_data/SinglePhoton_Run2015B-PromptReco-v1/V07-04-06/            ${TAG}_data_50ns_ph
#./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015B_DoubleMuon_MINIAOD_PromptReco-v1/merged/V07-04-06/ ${TAG}_data_50ns_mm
#./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015B_MuonEG_MINIAOD_PromptReco-v1/merged/V07-04-06/     ${TAG}_data_50ns_em
#./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015B_SingleElectron_MINIAOD_PromptReco-v1/merged/V07-04-06/ ${TAG}_data_50ns_se
#./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015B_SingleMuon_MINIAOD_PromptReco-v1/merged/V07-04-06/	   ${TAG}_data_50ns_sm

#./writeConfig.sh /hadoop/cms/store/group/snt/run2_50ns/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-07/  ${TAG}_wjets_50ns_incl
#./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_MuonEG_MINIAOD_PromptReco-v1/merged/V07-04-08/  ${TAG}_data_muon_eg_2015C_25ns data_muon_eg_2015C_25ns
#./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_MuonEG_MINIAOD_PromptReco-v3/merged/V07-04-09/  ${TAG}_data_muon_eg_2015D_25ns data_muon_eg_2015D_25ns
#./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_SingleElectron_MINIAOD_PromptReco-v1/merged/V07-04-08/  ${TAG}_data_single_electron_2015C_25ns  data_single_electron_2015C_25ns
#./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015C_SingleMuon_MINIAOD_PromptReco-v1/merged/V07-04-08/ ${TAG}_data_single_muon_2015C_25ns data_single_muon_2015C_25ns
#./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SingleElectron_MINIAOD_PromptReco-v3/merged/V07-04-09/ ${TAG}_data_single_electron_2015D_25ns data_single_electron_2015D_25ns
#./writeConfig.sh /hadoop/cms/store/group/snt/run2_data/Run2015D_SingleMuon_MINIAOD_PromptReco-v3/merged/V07-04-09/ ${TAG}_data_single_muon_2015D_25ns data_single_muon_2015D_25ns
# # ./writeConfig.sh /hadoop/cms/store/group/snt/run2_50ns/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/ ${TAG}_ttall_50ns_mgp8
# # ./writeConfig.sh /hadoop/cms/store/group/snt/run2_50ns/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/ ${TAG}_ttall_50ns_nlo
# # ./writeConfig.sh /hadoop/cms/store/group/snt/run2_50ns/TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v4/V07-04-03/ ${TAG}_ttall_50ns_php8


# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03/  ${TAG}_dyjetsll_25ns_m1050nlo
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/V07-04-03/      ${TAG}_dyjetsll_25ns_m50nlo

# # 50 ns samples
# ################################################

# #
# # TTBAR
# #

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_50ns/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/ ${TAG}_ttall_50ns_mgp8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_50ns/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/ ${TAG}_ttall_50ns_nlo
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_50ns/TTTo2L2Nu_13TeV-powheg_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/V07-04-03/ ${TAG}_tt2lnu_50ns_php8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_50ns/TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v4/V07-04-03/ ${TAG}_ttall_50ns_php8

# #
# # SINGLE TOP
# #

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_50ns/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/V07-04-03/ ${TAG}_t_50ns_bartw
# # ./writeConfig.sh         ${TAG}_t_50ns_toptw

# #
# # DY+JETS
# #

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/ ${TAG}_dyjetsll_50ns_m1050nlo
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_13TeV-madgraph-pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08                   ${TAG}_dyjetsll_m50inc
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_HT-100to200_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08 ${TAG}_dyjetsll_ht100to200
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_HT-200to400_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08 ${TAG}_dyjetsll_ht200to400
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_HT-400to600_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08 ${TAG}_dyjetsll_ht400to600
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_HT-600toInf_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08 ${TAG}_dyjetsll_ht600toinf
# # # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/DYJetsToMuMu_PtZ-180_M-50_13TeV-madgraph_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v3/V07-02-08             ${TAG}_dyjetsmm_ptz180


# #
# # DIBOSON
# #

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_50ns/WZ_TuneCUETP8M1_13TeV-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/V07-04-03/ ${TAG}_wzincl_50ns
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_50ns/WWTo2L2Nu_13TeV-powheg_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/V07-04-03/        ${TAG}_ww2l2nu_50ns_php8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_50ns/ZZ_TuneCUETP8M1_13TeV-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/V07-04-03/ ${TAG}_zzincl_50ns_php8

# # #
# # # GAMMA + JETS
# # #

# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/GJet_Pt40_doubleEMEnriched_TuneZ2star_13TeV-pythia6_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08 ${TAG}_gjet_pt40_doubleEM
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/GJets_HT-100to200_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08      ${TAG}_gjet_ht100to200
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/GJets_HT-200to400_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08      ${TAG}_gjet_ht200to400
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/GJets_HT-400to600_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08      ${TAG}_gjet_ht400to600
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/GJets_HT-600toInf_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08      ${TAG}_gjet_ht600toinf

# # #
# # # TTV
# # #

# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/TTWJets_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08           ${TAG}_ttw
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/TTZJets_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08           ${TAG}_ttz
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v2/V07-02-08 ${TAG}_tth

# # 25 ns samples
# ################################################

# #
# # TTBAR
# #

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-03/  ${TAG}_ttall_25ns_mgp8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03/ ${TAG}_ttall_25ns_nlo
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/TTTo2L2Nu_13TeV-powheg_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03/                         ${TAG}_tt2lnu_25ns_php8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-03/           ${TAG}_ttall_25ns_php8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/TT_TuneZ2star_13TeV-powheg-pythia6-tauola_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03/      ${TAG}_ttall_25ns_php6tauola

# #
# # SINGLE TOP
# #

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03/ ${TAG}_tincl_25ns_bartw_php8
# # ./writeConfig.sh         ${TAG}_t_50ns_toptw

# #
# # DY+JETS
# #

# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_13TeV-madgraph-pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08                   ${TAG}_dyjetsll_m50inc
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_HT-100to200_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08 ${TAG}_dyjetsll_ht100to200
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_HT-200to400_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08 ${TAG}_dyjetsll_ht200to400
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_HT-400to600_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08 ${TAG}_dyjetsll_ht400to600
# # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_HT-600toInf_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08 ${TAG}_dyjetsll_ht600toinf
# # # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/DYJetsToMuMu_PtZ-180_M-50_13TeV-madgraph_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v3/V07-02-08             ${TAG}_dyjetsmm_ptz180


# #
# # DIBOSON
# #

# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/WZ_TuneCUETP8M1_13TeV-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03/ ${TAG}_wzincl_25ns
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/WWTo2L2Nu_13TeV-powheg_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03/         ${TAG}_ww2l2nu_25ns_php8
# ./writeConfig.sh /hadoop/cms/store/group/snt/run2_25ns/ZZ_TuneCUETP8M1_13TeV-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/V07-04-03/  ${TAG}_zzincl_25ns_php8

# # #
# # # VH
# # #

# # # ./writeConfig.sh /hadoop/cms/store/group/snt/phys14/WH_HToBB_WToLNu_M-125_13TeV_powheg-herwigpp_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1/V07-02-03 ${TAG}_wh_lnubb

# # #
# # # SIGNAL
# # #

# # # /hadoop/cms/store/group/snt/phys14/SMS-T1bbbb_2J_mGl-1000_mLSP-900_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1
# # # /hadoop/cms/store/group/snt/phys14/SMS-T1bbbb_2J_mGl-1500_mLSP-100_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1
# # # /hadoop/cms/store/group/snt/phys14/SMS-T1qqqq_2J_mGl-1000_mLSP-800_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1
# # # /hadoop/cms/store/group/snt/phys14/SMS-T1qqqq_2J_mGl-1400_mLSP-100_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1
# # # /hadoop/cms/store/group/snt/phys14/SMS-T1tttt_2J_mGl-1200_mLSP-800_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1
# # # /hadoop/cms/store/group/snt/phys14/SMS-T1tttt_2J_mGl-1500_mLSP-100_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1
# # # /hadoop/cms/store/group/snt/phys14/SMS-T2bb_2J_mStop-600_mLSP-580_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1
# # # /hadoop/cms/store/group/snt/phys14/SMS-T2bb_2J_mStop-900_mLSP-100_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1
# # # /hadoop/cms/store/group/snt/phys14/SMS-T2qq_2J_mStop-1200_mLSP-100_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1
# # # /hadoop/cms/store/group/snt/phys14/SMS-T2qq_2J_mStop-600_mLSP-550_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1
# # # /hadoop/cms/store/group/snt/phys14/SMS-T2tt_2J_mStop-425_mLSP-325_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1
# # # /hadoop/cms/store/group/snt/phys14/SMS-T2tt_2J_mStop-500_mLSP-325_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1
# # # /hadoop/cms/store/group/snt/phys14/SMS-T2tt_2J_mStop-650_mLSP-325_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1
# # # /hadoop/cms/store/group/snt/phys14/SMS-T2tt_2J_mStop-850_mLSP-100_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1


# --- write submit script ---
mkdir -p configs_${TAG}

mv condor_${TAG}*.cmd configs_${TAG}
echo "#!/bin/bash" > submitAll.sh
echo "voms-proxy-init -voms cms -valid 240:00" >> submitAll.sh
for file in configs_${TAG}/*.cmd
do 
    echo "condor_submit ${file}" >> submitAll.sh
done
chmod +x submitAll.sh
echo "[writeAllConfig] wrote submit script submitAll.sh"
