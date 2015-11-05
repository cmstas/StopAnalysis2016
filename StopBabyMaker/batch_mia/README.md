#Condor for Babymaker

This will submit the babymaker in the parent directory on Condor

Instructions (no quotes):
  1.  set up core, babymaker and condor submission name you want to
      use in settings.sh and do source settings.sh
  2.  . copy.sh will assemble core, babymaker and make a tarball named
      forCondor_stopBabyMaker.tar.gz
  3.  Edit writeAllConfig.sh following example.
  4   Now run ./submitAll.sh
  5.  validate ntuples:
      git clone git@github.com:cmstas/NtupleTools.git
      cd NtupleTools/condorMergingTools/libC
      make
      cd ../../../ 
      ./NtupleTools/condorMergingTools/libC/sweepRoot -b -o "t" /hadoop/cms/store/user/${USER}/onelepbabies/${analysis_version}*/*root
  6.  check for failed jobs and resubmit:
      ./checkAndResubmitAll.sh  cfg_dir
  7.  merge: edit mergeHadoopFiles.sh
      add lines:
      run sample_name 
 
   
