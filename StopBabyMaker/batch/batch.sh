#!/bin/bash

#samples are: ALL, stop_850_100 stop_650_325 stop_500_325 stop_425_325 ttbar ttwjets ttzjets wjets dyjets t_sch t_tch t_tW tbar_sch tbar_tch tbar_tW wzjets zz

#Choose the sample(s) you want here, separated by commmas
sampleList_in=ALL

#Choose the number of events (per file): 
nEvents=-1

#Decide if you want lots of printouts telling you the status
verbose="false"

#Set directory to copy results to when finished
copy_dir=/hadoop/cms/store/user/jgwood/condor/stop_1l_babies
if [ ! -d $copy_dir/merged_files ]; then
    mkdir $copy_dir/merged_files
fi

#Check that log file folder and tarball files exists
if [ ! -d logs ]; then echo "Run . copy.sh first!"; return 1; fi
if [ ! -e $HOME/forCondor_stopBabyMaker.tar.gz ]; then echo "Run . copy.sh first!"; return 1; fi


#Set directory with the location of the tarball with code
tar_file=$HOME/forCondor_stopBabyMaker.tar.gz

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

  #number of lines in sample.dat
  nLines=`wc -l < ../sample.dat`

  samplename=""
  sampledir=""

  #loop to find sample_dir
  for (( i = 1; i <= $nLines; i++ ))
  do

    #get string in sample.dat, temptwo is either the samplename or the sampledirectory
    temp=`awk "NR==$i" ../sample.dat`
    tempone=`echo $temp |cut -d' ' -f1`
    temptwo=`echo $temp |cut -d' ' -f2`

    #store the sample name
    if [ "$tempone" == "Name" ]; then
        samplename="$temptwo"
    fi

    #store the sampledir
    if [ "$tempone" == "Path" ]; then
        sampledir="$temptwo"
	#if sampledir is in the list make it sample_dir
        if [ "$sample" == "$samplename" ]; then
           sample_dir="$sampledir"
        fi
    fi
    #sample_dir already found
    if [ "$sample_dir$" == "$sampledir" ]; then
       break
    fi

  done

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

