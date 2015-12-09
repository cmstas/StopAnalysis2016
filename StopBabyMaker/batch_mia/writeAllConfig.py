list=['data_double_eg_2015C_25ns',
      'data_double_eg_2015D_05Oct2015_v1_25ns',
      'data_double_eg_2015D_promptRecoV4_25ns',
      'data_double_mu_2015C_25ns',
      'data_double_mu_2015D_05Oct2015_v1_25ns',
      'data_double_mu_2015D_promptRecoV4_25ns',
      'data_muon_eg_2015C_25ns',
      'data_muon_eg_2015D_05Oct2015_v1_25ns',
      'data_muon_eg_2015D_05Oct2015_v2_25ns',
      'data_muon_eg_2015D_promptRecoV4_25ns',
      'data_single_electron_2015C_25ns',
      'data_single_electron_2015D_05Oct2015_v1_25ns',
      'data_single_electron_2015D_promptRecoV4_25ns',
      'data_single_muon_2015C_25ns',
      'data_single_muon_2015D_05Oct2015_v1_25ns',
      'data_single_muon_2015D_promptRecoV4_25ns',
      'data_met_2015C_25ns',
      'data_met_2015D_05Oct2015_v1_25ns',
      'data_met_2015D_promptRecoV4_25ns']
qcd = ['QCD_Pt-15to20_EMEnriched',
       'QCD_Pt-20to30_EMEnriched',
       'QCD_Pt-30to50_EMEnriched',
       'QCD_Pt-50to80_EMEnriched',
       'QCD_Pt-80to120_EMEnriched',
       'QCD_Pt-120to170_EMEnriched',
       'QCD_Pt-170to300_EMEnriched',
       'QCD_Pt-300toInf_EMEnriched']
ttbar = ['ttbar_powheg_pythia8_25ns','ttbar_powheg_pythia8_ext3_25ns']
wjets = ['DYJetsToLL_m50_amcnlo_pythia8_50ns',
         'WJetsToLNu_madgraph_pythia8_25ns',
         'WJetsToLNu_HT100To200_madgraph_pythia8_25ns',
         'WJetsToLNu_HT200To400_madgraph_pythia8_25ns',
         'WJetsToLNu_HT400To600_madgraph_pythia8_25ns',
          'WJetsToLNu_HT600To800_madgraph_pythia8_25ns',
          'WJetsToLNu_HT800To1200_madgraph_pythia8_25ns',
          'WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns',
          'WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns',
         'WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns']
zjets = [
         'DYJetsToLL_M-50_HT-100to200',
         'DYJetsToLL_M-50_HT-200to400',
         'DYJetsToLL_M-50_HT-400to600',
         'DYJetsToLL_M-50_HT-600toInf']
wjets_highht = [
            ]
#singletop = ['ST_t-channel_antitop',
#              'ST_t-channel_top',
#              'ST_s-channel',
#              'ST_tW_antitop_5f_inclusiveDecays',
#              'ST_tW_antitop_5f_scaledown',
#              'ST_tW_antitop_5f_scaleup',
#              'ST_tW_top_5f_inclusiveDecays',
#              'ST_tW_top_5f_scaledown',
#              'ST_tW_top_5f_scaleup']
singletop = ['tbar_tch_4f_powheg_pythia8_25ns',
             't_tch_4f_powheg_pythia8_25ns',
             't_sch_4f_amcnlo_pythia8_25ns',
             't_tbarW_5f_powheg_pythia8_25ns',
             't_tW_5f_powheg_pythia8_25ns'
             ]
print singletop
ttv = ['TTZToLLNuNu_M-10_amcnlo_pythia8_25ns']
towrite = open('towrite.sh','w')
f = open('../sample.dat')
towrite.write('source settings.sh\n')
towrite.write('TAG=${analysis_version}\n')
for line in f:
    for sample in singletop+ttv+list+ttbar+wjets+zjets:
        print 'run ', sample
    #    print 'run ',sample
        if sample in line and 'Name' in line:
           print sample
           path = next(f).split()[1]
           print './writeConfig.sh '+path + ' ${TAG}_'+sample+' '+sample
           towrite.write('./writeConfig.sh '+path + ' ${TAG}_'+sample+' '+sample+'\n')
towrite.write('mkdir -p configs_${TAG}\n')
towrite.write('mv condor_${TAG}*.cmd configs_${TAG}\n')
towrite.write('echo "#!/bin/bash" > submitAll.sh\n')
towrite.write('echo "voms-proxy-init -voms cms -valid 240:00" >> submitAll.sh\nfor file in configs_${TAG}/*.cmd\ndo\n')
towrite.write('   echo "condor_submit ${file}" >> submitAll.sh\n')
towrite.write('done\n')
towrite.write('chmod +x submitAll.sh\n')
towrite.write('echo "[writeAllConfig] wrote submit script submitAll.sh"')
towrite.close()


