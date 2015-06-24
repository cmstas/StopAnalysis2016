#!/bin/bash

#samples are: ALL, stop_850_100 stop_650_325 stop_500_325 stop_425_325 ttbar ttwjets ttzjets wjets dyjets t_sch t_tch t_tW tbar_sch tbar_tch tbar_tW wzjets zz

#Choose the sample(s) you want here, separated by commmas
sampleList_in="ttbar_madgraph_25ns,ttbar_powheg_25ns"
#,WJetsToLNu_HT100to200_25ns,WJetsToLNu_HT600ToInf_25ns,T_tch_5f_25ns,WJetsToLNu_400To600_25ns,T_sch_4f_25ns,T_tbarW_5f_25ns,T_tch_4f_25ns,WW_25ns,WZ_25ns,ZZ_25ns"

#Choose the number of events (per file): 
nEvents=-1

#Decide if you want lots of printouts telling you the status
verbose="false"

#Set directory to copy results to when finished
copy_dir=/hadoop/cms/store/user/isuarez/condor/stop_1l_babies/25ns
if [ ! -d $copy_dir/merged_files ]; then
    mkdir $copy_dir/merged_files
fi

#Check that log file folder and tarball files exists
if [ ! -d logs ]; then echo "Run . copy.sh first!"; return 1; fi
if [ ! -e $HOME/forCondor_stopBabyMaker_74x.tar.gz ]; then echo "Run . copy.sh first!"; return 1; fi


#Set directory with the location of the tarball with code
tar_file=$HOME/forCondor_stopBabyMaker_74x.tar.gz

#------HERE THERE BE DRAGONS---------

#Parse sampleList
sampleList=`echo $sampleList_in | tr ',' ' ' `
nSamples=`echo "$sampleList" | wc -w`
echo "$sampleList" | grep "ALL" &>/dev/null
isAll="$?" #note this is opposite
if [ "$isAll" == "0" ] && [ "$nSamples" -gt "1" ]; then echo "Aborting! You can't have ALL as well as other sampleLists, dumbass!"; return 1; fi  
if [ "$isAll" == "0" ]
then 
  sampleList="stop_850_100 stop_650_325 stop_500_325 stop_425_325 ttbar ttwjets ttzjets wjets dyjets t_sch t_tch t_tW tbar_sch tbar_tch tbar_tW wzjets zz"
  sampleList_in="stop_850_100,stop_650_325,stop_500_325,stop_425_325,ttbar,ttwjets,ttzjets,wjets,dyjets,t_sch,t_tch,t_tW,tbar_sch,tbar_tch,tbar_tW,wzjets,zz"
fi

#nSubmitted (so you know when to quit)
nSubmitted=0

#Start by checking proxy, get path to proxy file
voms-proxy-info --all &> voms_status.txt
if grep "Couldn't find a valid proxy." voms_status.txt &>/dev/null
then 
  echo "Error: couldn't find a valid proxy!  Aborting.  Create a proxy with voms-proxy-init."
  rm voms_status.txt
  return 1
fi
lineWithPath=`sed -n /path/= voms_status.txt`
pathToProxy=`awk -v var="$lineWithPath" 'NR==var {print $3}' voms_status.txt`

#Do all this stuff once per sample
for sample in $sampleList
do
  #Make a list of all the files on hadoop you want to run on
  sample_dir=""
  
  if [ "$sample" == "stop_850_100" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/SMS-T2tt_2J_mStop-850_mLSP-100_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1/V07-02-08
  fi      
      
  if [ "$sample" == "stop_650_325" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/SMS-T2tt_2J_mStop-650_mLSP-325_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "stop_500_325" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/SMS-T2tt_2J_mStop-500_mLSP-325_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "stop_425_325" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/SMS-T2tt_2J_mStop-425_mLSP-325_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1/V07-02-08
  fi

  
  if [ "$sample" == "ttbar" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "ttwjets" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/TTWJets_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "ttzjets" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/TTZJets_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "dyjets" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_13TeV-madgraph-pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "tbar_sch" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/TBarToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "tbar_tch" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/TBarToLeptons_t-channel_Tune4C_CSA14_13TeV-aMCatNLO-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "t_sch" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/TToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "t_tch" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/TToLeptons_t-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "t_tW" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/T_tW-channel-DR_Tune4C_13TeV-CSA14-powheg-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "tbar_tW" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/Tbar_tW-channel-DR_Tune4C_13TeV-CSA14-powheg-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "wjets" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/WJetsToLNu_13TeV-madgraph-pythia8-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "wzjets" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/WZJetsTo3LNu_Tune4C_13TeV-madgraph-tauola_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "zz" ]; then
      sample_dir=/hadoop/cms/store/group/snt/phys14/ZZTo4L_Tune4C_13TeV-powheg-pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08
  fi

  if [ "$sample" == "ttbar_madgraph_25ns" ]; then
      sample_dir=/hadoop/cms/store/group/snt/run2_25ns/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-03
  fi

  if [ "$sample" == "ttbar_powheg_25ns" ]; then
      sample_dir=/hadoop/cms/store/group/snt/run2_25ns/TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-03
  fi

  if [ "$sample" == "WJetsToLNu_HT100to200_25ns" ]; then
      sample_dir=/hadoop/cms/store/group/snt/run2_25ns/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03
  fi

  if [ "$sample" == " WJetsToLNu_HT600ToInf_25ns" ]; then
      sample_dir=/hadoop/cms/store/group/snt/run2_25ns/WJetsToLNu_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03
  fi

  if [ "$sample" == "WJetsToLNu_400To600_25ns" ]; then
      sample_dir=/hadoop/cms/store/group/snt/run2_25ns/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/V07-04-03
  fi

  if [ "$sample" == "T_tch_5f_25ns" ]; then
      sample_dir=/hadoop/cms/store/group/snt/run2_25ns/ST_t-channel_5f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03
  fi
 
  if [ "$sample" == "T_sch_4f_25ns" ]; then
      sample_dir=/hadoop/cms/store/group/snt/run2_25ns/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03
  fi

  if [ "$sample" == "T_tbarW_5f_25ns" ]; then
      sample_dir=/hadoop/cms/store/group/snt/run2_25ns/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03
  fi

  if [ "$sample" == "T_tch_4f_25ns" ]; then
      sample_dir=/hadoop/cms/store/group/snt/run2_25ns/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03
  fi

  if [ "$sample" == "WW_25ns" ]; then
      sample_dir=/hadoop/cms/store/group/snt/run2_25ns/WWToLNuQQ_13TeV-powheg_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03
  fi

  if [ "$sample" == "WZ_25ns" ]; then
      sample_dir=/hadoop/cms/store/group/snt/run2_25ns/WZ_TuneCUETP8M1_13TeV-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/V07-04-03
  fi

  if [ "$sample" == "ZZ_25ns" ]; then
      sample_dir=/hadoop/cms/store/group/snt/run2_25ns/ZZ_TuneCUETP8M1_13TeV-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/V07-04-03
  fi

  for file in `/bin/ls $sample_dir/merged_ntuple_*.root`; do

    number_temp=${file##*/merged_ntuple_}
    number=${number_temp%*.root}

    #Except they've finished
    if [ -e $copy_dir/${sample}_${number}.root ] 
    then 
      if [ "$verbose" == "true" ]; then echo "-------------"; echo "${copy_dir}/${sample}_${number} already exists on hadoop, will not resubmit"; fi
      continue
    fi  

    #Status message
    if [ "$verbose" == "true" ]; then echo "-------------"; echo "Working on ${copy_dir}/${sample}_$number"; fi
    
    #Or if they're still running
    if [ -e logs/condorLog_${sample}_${number}.log ] 
    then
      while read line
      do
        if [ `echo $line | awk '{ print $1 }'` == "Cluster" ] 
        then
          cluster=`echo $line | awk '{ print $3 }'`
        elif [ `echo $line | awk '{ print $1 }'` == "Proc" ] 
        then
          process=`echo $line | awk '{ print $3 }'`
        fi  
      done < logs/condorLog_${sample}_${number}.log
      jobid="$cluster.$process"
      condor_q $jobid > temp.txt
      result=`more temp.txt | awk 'END{print $1}'`
      if [ "$result" == "$jobid" ] 
      then
        if [ "$verbose" == "true" ]; then echo "already submitted!"; fi
        let "nSubmitted=$nSubmitted+1"
        continue
      fi  
    fi  
    if [ "$verbose" == "true" ]; then echo "submitting..."; fi
    let "nSubmitted=$nSubmitted+1"

    #Then submit
    cp condorFileTemplate condorFile
    sed -i "s,ARG1,$sample,g" condorFile
    sed -i "s,ARG2,$nEvents,g" condorFile
    sed -i "s,ARG3,$number,g" condorFile
    sed -i "s,ARG4,$copy_dir,g" condorFile
    sed -i "s,USER_PROXY,$pathToProxy,g" condorFile
    sed -i "s,TARFILE,$tar_file,g" condorFile
    condor_submit condorFile
  done
done

#Clean up
rm voms_status.txt &>/dev/null
rm temp.txt &>/dev/null

#Merge
nZombies=0
if [ "$nSubmitted" == "0" ] 
then
  #Check for zombies which should be deleted in copy_dir
  echo "CHECKING FOR ZOMBIES"
  for file in `/bin/ls $copy_dir/*.root`
  do
    root -l -b -q checkForZombies.C'("'$file'")'
    if [ -e listOfZombies.txt ]; then
      zombie=""
      zombie=`tail listOfZombies.txt`
      if [ ! -z $zombie ]; then
	echo "  FOUND ZOMBIE!"
	nZombies=$((nZombies+1))
	echo "  DELETING FILE: $zombie"
	rm -rf $zombie
	echo "  JOB WILL BE RESUBMITTED"
      fi
      rm -rf listOfZombies.txt
    fi
  done

  if [ "$nZombies" == "0" ]; then
    . mergeAll.sh $copy_dir $sampleList_in
    sleep 120
    mv *.root $copy_dir/merged_files/
  fi
fi


#Timer
if [ "$verbose" == "true" ]; then 
    echo `date +"%Y%m%d_%H%M%S"`
fi

#Return exit code
if [ "$nSubmitted" == "0" ] && [ "$nZombies" == "0" ]
then 
    return 1
else 
    return 0
fi

