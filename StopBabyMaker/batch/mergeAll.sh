#!/bin/bash

inPath=$1
samples=$2
samples=`echo $samples | tr ',' ' '`

# loop over samples
for sname in $samples
do

    # get number of files
    numberOfFiles=0
    for files in `/bin/ls $inPath/$sname*.root`; do
	numberOfFiles=$((numberOfFiles+1))
    done
    
    # case of only 1 file
    if [ "$numberOfFiles" == "1" ]
    then
	cp $inPath/${sname}_1.root $sname.root & 
	echo "Copying $sname.root in background, may be delay even after this program finishes...."
	continue
    fi

    echo root -l -b -q mergeHadoopFiles.C++\(\"$inPath\",\"$sname\",\"./$sname.root\"\)
    #nohup nice -n 19 root -l -b -q mergeHadoopFiles.C++\(\"$inPath\",\"$sname\",\"./$sname.root\"\)
    root -l -b -q mergeHadoopFiles.C++\(\"$inPath\",\"$sname\",\"./$sname.root\"\)
    
done 

#clean up
rm null &>/dev/null
