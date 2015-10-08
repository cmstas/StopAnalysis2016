#! /bin/bash

configdir=$1

./checkAllConfig.sh $configdir

for file in `ls $configdir/*resubmit*`; do

	echo "resubmitting files for $file"
    condor_submit $configdir$file

done
