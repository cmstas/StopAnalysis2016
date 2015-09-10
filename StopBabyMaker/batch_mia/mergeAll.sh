#!/bin/bash

path2=$1
samples=$2
samples=`echo $samples | tr ',' ' '`

for sname in $samples
do

  numberOfFiles=0
  for files in `/bin/ls $path2/$sname*.root`; do
    numberOfFiles=$((numberOfFiles+1))
  done
    
  if [ "$numberOfFiles" == "1" ]
  then
    cp $path2/${sname}_1.root $sname.root & 
    echo "Copying $sname.root in background, may be delay even after this program finishes...."
    continue
  fi

  for (( counter=0; counter<=500; counter++ )); do file1[$counter]=""; done

  #Write array with file names
  for (( counter=1; counter<=$numberOfFiles; counter++ ))
  do
    file1[$(( $counter - 1 )) ]="$path2/${sname}_${counter}.root"
  done

  hadd $sname.root ${file1[*]}

 done 

#clean up
rm null &>/dev/null
