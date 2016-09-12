#!/bin/bash

FILENAME=$1

echo "    sweepRooting: \"$FILENAME\""
RESULT=`root -l -b -q sweepRoot.C+'("'$FILENAME'")' | grep "result=" | sed s/result=//g`

#echo "RESULT=$RESULT"
    
if [ "$RESULT" == "0" ]; then 
    exit 0
else
    exit 1
fi
