list=['data_double_eg_2015D_promptRecoV3_25ns',
      'data_double_eg_2015C_25ns',
      'data_double_eg_2015D_05Oct2015_v1_25ns',
      'data_double_eg_2015D_promptRecoV4_25ns',
      'data_double_mu_2015C_25ns',
      'data_double_mu_2015D_promptRecoV3_25ns',
      'data_double_mu_2015D_05Oct2015_v1_25ns',
      'data_double_mu_2015D_promptRecoV4_25ns',
      'data_muon_eg_2015C_25ns',
      'data_muon_eg_2015D_promptRecoV3_25ns',
      'data_muon_eg_2015D_05Oct2015_v1_25ns',
      'data_muon_eg_2015D_05Oct2015_v2_25ns',
      'data_muon_eg_2015D_promptRecoV4_25ns',
      'data_single_electron_2015C_25ns',
      'data_single_electron_2015D_promptRecoV3_25ns',
      'data_single_electron_2015D_05Oct2015_v1_25ns',
      'data_single_electron_2015D_promptRecoV4_25ns',
      'data_single_muon_2015C_25ns',
      'data_single_muon_2015D_promptRecoV3_25ns',
      'data_single_muon_2015D_05Oct2015_v1_25ns',
      'data_single_muon_2015D_promptRecoV4_25ns','data_met_2015C_25ns','data_met_2015D_05Oct2015_v1_25ns','data_met_2015D_promptRecoV4_25ns']
for item in list:
    print 'run ',item

qcd = ['QCD_Pt-15to20_EMEnriched','QCD_Pt-20to30_EMEnriched','QCD_Pt-30to50_EMEnriched','QCD_Pt-50to80_EMEnriched','QCD_Pt-80to120_EMEnriched','QCD_Pt-120to170_EMEnriched','QCD_Pt-170to300_EMEnriched','QCD_Pt-300toInf_EMEnriched']
wjets = ['WJetsToLNu_HT200To400_madgraph_pythia8_25ns',
         'DYJetsToLL_M-5to50_HT-400to600',
         'DYJetsToLL_M-5to50_HT-600toInf']
for item in wjets:
    print 'run ',item
towrite = open('towrite.sh','w')
f = open('../sample.dat')
towrite.write('source settings.sh\n')
towrite.write('TAG=${analysis_version}\n')
for line in f:
    for sample in wjets:
        if sample in line:
           print 'test ',sample
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


