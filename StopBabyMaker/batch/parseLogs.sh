#!/bin/bash

targetDir=$1

oldSample="null"

countProc=0
countVtx=0
countMet=0
countLep=0
countJet=0

#Loop through all the stdout logs in specified directory
for file in `ls -1 $targetDir/*.stdout | sort`;do

	filename=${file##*/condorLog_}    #e.g. wjets_18.stdout
	shortName=${filename%.stdout}     #e.g. wjets_18

	sample=${shortName%_*}            #e.g. wjets
	fileNum=${shortName#*_}           #e.g. 18

	#If this isn't the sample we were looking at in the previous loop,
	# then print out the results from the previous sample, and reset the counters
	if [ "$sample" != "$oldSample" ]; then

		if [ "$oldSample" != "null" ]; then
			echo
			echo $oldSample
			printf "Events processed                     %s\n" $countProc
			printf "Events with 1 Good Vertex            %s\n" $countVtx
			printf "Events with MET > 30 GeV             %s\n" $countMet
			printf "Events with at least 1 Good Lepton   %s\n" $countLep
			printf "Events with at least 2 Good Jets     %s\n" $countJet
		fi

		oldSample=$sample
		
		countProc=0
		countVtx=0
		countMet=0
		countLep=0
		countJet=0
	fi

	# Grab the event counts from this file
	#  and add them to the running tallies
	countProc=$(( countProc + `awk '/Events Processed/ {print $3}' $file ` ))
	countVtx=$(( countVtx + `awk '/Events with 1 Good Vertex/ {print $6}' $file ` ))
	countMet=$(( countMet + `awk '/Events with MET > 30 GeV/ {print $7}' $file ` ))
	countLep=$(( countLep + `awk '/Events with at least 1 Good Lepton/ {print $8}' $file ` ))
	countJet=$(( countJet + `awk '/Events with at least 2 Good Jets/ {print $8}' $file ` ))	
	
done

echo
echo $sample
printf "Events processed                     %s\n" $countProc
printf "Events with 1 Good Vertex            %s\n" $countVtx
printf "Events with MET > 30 GeV             %s\n" $countMet
printf "Events with at least 1 Good Lepton   %s\n" $countLep
printf "Events with at least 2 Good Jets     %s\n" $countJet
