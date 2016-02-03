#!/bin/bash

if [ -z $CONDOR_ENV_READY ]; then
    echo ""
    echo "CONDOR_ENV_READY not set :(, exiting..."
    echo "please do source setup.sh!"
    echo ""
    return 1;
fi

echo "SCRATCH DIR: "
echo "  $SCRATCH_DIR"

echo "COPY DIR: "
echo "  $COPY_DIR"

. parseLogs.sh $SCRATCH_DIR/logs/ > parseLogs_temp.log
#. parseLogs_JEC.sh $SCRATCH_DIR/logs/ > parseLogs_temp.log

BAD_LOG_FILES=`more parseLogs_temp.log | grep "/data/tmp"`
echo "BAD LOG FILES: "
echo "  $BAD_LOG_FILES" 

for x in $BAD_LOG_FILES; do
    filename=${x##*/condorLog_}    #e.g. wjets_18.stdout 
    file=${filename%.stdout}       #e.g. wjets_18     
    output_name=$COPY_DIR/$file.root
    echo "BAD OUTPUT FILE: "
    echo "  $output_name" 
    if [ -e $output_name ]; then 
	echo "  exists in COPY_DIR, removing..."
	rm $output_name
    fi
done


# clean up
rm parseLogs_temp.log