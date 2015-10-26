#!/bin/bash

path2=$1
samples=$2
samples=`echo $samples | tr ',' ' '`
maxBabiesPerMerge=2000

# loop over samples
for sname in $samples
do

  # get number of files
  numberOfFiles=0
  for files in `/bin/ls $path2/$sname*.root`; do
    numberOfFiles=$((numberOfFiles+1))
  done
    
  # case of only 1 file
  if [ "$numberOfFiles" == "1" ]
  then
    cp $path2/${sname}_1.root $sname.root & 
    echo "Copying $sname.root in background, may be delay even after this program finishes...."
    continue
  fi

  # case of <= maxBabiesPerMerge files
  if [ "$numberOfFiles" -le "$maxBabiesPerMerge" ]
  then
    for (( counter=0; counter<=$maxBabiesPerMerge; counter++ )); do file1[$counter]=""; done
    #Write array with file names
    for (( counter=1; counter<=$numberOfFiles; counter++ ))
    do
      file1[$(( $counter - 1 )) ]="$path2/${sname}_${counter}.root"
    done
    hadd $sname.root ${file1[*]}
    continue
  fi

  # case of >maxBabiesPerMerge files
  numberOfFilesLeft=$numberOfFiles
  fileNumber=1
  mergeFileNumber=1
  while [ "$numberOfFilesLeft" -gt "0" ]
  do
    for (( counter=0; counter<=$maxBabiesPerMerge; counter++ )); do file1[$counter]=""; done
    #Write arrawy with file names
    counterLimit=$maxBabiesPerMerge
    if [ "$numberOfFilesLeft" -lt "$maxBabiesPerMerge" ]; then counterLimit=$numberOfFilesLeft; fi
    for (( counter=0; counter<$counterLimit; counter++ ))
    do
      file1[$counter]="$path2/${sname}_${fileNumber}.root"
      fileNumber=$((fileNumber+1))
      numberOfFilesLeft=$((numberOfFilesLeft-1))
    done
    hadd ${sname}_mergedBaby_${mergeFileNumber}.root ${file1[*]}
    mergeFileNumber=$((mergeFileNumber+1))
  done

done 

#clean up
rm null &>/dev/null
