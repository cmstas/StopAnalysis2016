#!/bin/bash

# Parses cutflow event counts from batch-submission stdout logs
#
# Usage: ./parseLogs.sh [-lt] some/directory/containing/logs/
#  Use option -l to format output for a LaTeX table
#  Use option -t to format output for a TWiki table
#  Use no option to format output for human reading

outtype="screen"

# Get command-line options
while getopts "lt" opt; do
	case $opt in
		l) outtype="latex" ;;
		t) outtype="twiki" ;;
		\?) exit 1 ;;
	esac
done
shift $((OPTIND-1))


# Check for valid target directory
if [ "$1" = "" ]; then
	echo Please specify a directory in which to look for stdout logs!
	exit 1
elif [ -d $1 ]; then
	targetDir=$1
else
	echo $1 is not a valid directory!
	exit 1
fi


# Set the table delimiters to be used
if [ "$outtype" = "latex" ]; then
	startLine=""
	separator="&"
	endLine=" \\\\"
elif [ "$outtype" = "twiki" ]; then
	startLine="|"
	separator="|"
	endLine="|"
else
	startLine=""
	separator=""
	endLine=""
fi


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
			printf $startLine" Events processed                   "$separator"  %8s %s\n"  $countProc $endLine
			printf $startLine" Events with 1 Good Vertex          "$separator"  %8s %s\n"  $countVtx  $endLine
			printf $startLine" Events with MET > 30 GeV           "$separator"  %8s %s\n"  $countMet  $endLine
			printf $startLine" Events with at least 1 Good Lepton "$separator"  %8s %s\n"  $countLep  $endLine
			printf $startLine" Events with at least 2 Good Jets   "$separator"  %8s %s\n"  $countJet  $endLine

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
printf $startLine" Events processed                   "$separator"  %8s %s\n"  $countProc $endLine
printf $startLine" Events with 1 Good Vertex          "$separator"  %8s %s\n"  $countVtx  $endLine
printf $startLine" Events with MET > 30 GeV           "$separator"  %8s %s\n"  $countMet  $endLine
printf $startLine" Events with at least 1 Good Lepton "$separator"  %8s %s\n"  $countLep  $endLine
printf $startLine" Events with at least 2 Good Jets   "$separator"  %8s %s\n"  $countJet  $endLine
