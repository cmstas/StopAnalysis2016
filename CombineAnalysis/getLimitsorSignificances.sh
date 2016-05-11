
#check cmssw and if it contains HiggsCombine
if [ -z $CMSSW_BASE ]; then
    echo "CMSSW_BASE var not set, run cmsenv, exiting..."
    exit 0;
fi
DIRECTORY=`echo $CMSSW_BASE/src/HiggsAnalysis`
if [ ! -d "$DIRECTORY" ]; then
    echo "Your CMSSW release does not have HiggsCombined installed. Please do."
    echo "Please read https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit"
    echo "You should have ${DIRECTORY}. Exiting..."
    exit 0;
fi

#this is only the base, rest will be added depending on fakedata, etc
INPUTDIR="datacards/"

#note that no further code is implemented as the rest is done with batch/condor
if [ $# -lt 3 ]
then
    echo You should provide at least the SIGNAL, STOPMASS, LSPMASS. Analysis is chosen as default, else give at least 4 arguments.
    return
fi
Signal=$1
stopmass=$2
lspmass=$3


analysis=0
runsignif=false
observed=true
#observed only used if runsignif=true
postfit=true
#postfit also includes posteriori for significance running
correlated=true
dropsigcont=false
nosigsyst=false
nobgsyst=false
fakedata=false

if [ $# -gt 3 ]
then
    analysis=$4
fi
if [ $# -gt 4 ]
then
    runsignif=$5
fi
if [ $# -gt 5 ]
then
    observed=$6
fi
if [ $# -gt 6 ]
then
    postfit=$7
fi
if [ $# -gt 7 ]
then
    correlated=$8
fi
if [ $# -gt 8 ]
then
    dropsigcont=$9
fi
if [ $# -gt 9 ]
then
    nosigsyst=$10
fi
if [ $# -gt 10 ]
then
    nobgsyst=$11
fi
if [ $# -gt 11 ]
then
    fakedata=$12
fi

DATACARD_DIR=datacards/
if [ "$correlated" = true ]
then
    DATACARD_DIR=`echo ${DATACARD_DIR}correlated/`
fi
if [[ "$nosigsyst" = true ]] && [[ "$nobgsyst" = true ]]
then
    DATACARD_DIR=`echo ${DATACARD_DIR}nounc/`
elif [ "$nosigsyst" = true ]
then
    DATACARD_DIR=`echo ${DATACARD_DIR}nosigsyst/`
elif [ "$nobgsyst" = true ]
then
    DATACARD_DIR=`echo ${DATACARD_DIR}nobgsyst/`
fi
if [ "$dropsigcont" = true ]
then
    DATACARD_DIR=`echo ${DATACARD_DIR}dropsigcont/`
fi
if [ "$fakedata" = true ]
then
    DATACARD_DIR=`echo ${DATACARD_DIR}fakedata/`
fi
DATACARD_DIR=`echo ${DATACARD_DIR}combinedcards/`

methodcmd="--noFitAsimov"
methodname="PreFit"
if [ "${runsignif}" = true ]
then
    methodcmd=""
    methodname="Priori"
    if [ "${postfit}" = true ]
    then
	methodcmd="--toysFreq"
	methodname="Posteriori"
    fi
else
    if [ "${postfit}" = true ]
    then
	methodcmd=" "
	methodname="PostFit"
    fi
fi

analysisstring=std
if [ "$analysis" = 0 ]
then
    analysisstring=std
else
    return
    #currently no other analysis implemented
fi

mycard=`echo ${DATACARD_DIR}datacard_${analysisstring}_${Signal}_${stopmass}_${lspmass}.txt`

if [ ! -e "${mycard}" ] && [ ! -f "${mycard}" ] && [ ! -s "${mycard}" ]
then
    echo "File ${mycard} does not exist. Stop."
    echo "Did you create the datacards / also ran the combinedcards script?"
    return;
else
    if [ "${runsignif}" = true ]
    then
	if [ "${observed}" = true ]
	then
	    echo "runing combine  -M ProfileLikelihood --significance ${mycard} -n Obs_${analysisstring}_${Signal}_${stopmass}_${lspmass} > /dev/null 2>&1"
	    combine  -M ProfileLikelihood --uncapped 1 --rMin -50 --rMax 50 --significance ${mycard} -n Obs_${analysisstring}_${Signal}_${stopmass}_${lspmass} #> /dev/null 2>&1
	    mv higgsCombineObs_${analysisstring}_${Signal}_${stopmass}_${lspmass}.ProfileLikelihood.mH120.root Signif_ProfileLikelihood_Obs_${analysisstring}_${Signal}_${stopmass}_${lspmass}.root
	else
	    echo "runing  combine  -M ProfileLikelihood --significance ${mycard} -n Exp${methodname}_${analysisstring}_${Signal}_${stopmass}_${lspmass} -t -1 --expectSignal=1 ${methodcmd} > /dev/null 2>&1"
	    combine  -M ProfileLikelihood --uncapped 1 --rMin -50 --rMax 50 --significance ${mycard} -n Exp${methodname}_${analysisstring}_${Signal}_${stopmass}_${lspmass} -t -1 --expectSignal=1 ${methodcmd} #> /dev/null 2>&1
	    mv higgsCombineExp${methodname}_${analysisstring}_${Signal}_${stopmass}_${lspmass}.ProfileLikelihood.mH120.root Signif_ProfileLikelihood_Exp${methodname}_${analysisstring}_${Signal}_${stopmass}_${lspmass}.root
	fi
    else
	echo "get limit for $Signal"
	#computes automatically observed and expected limit together
	combine  -M Asymptotic ${mycard} ${methodcmd} -n ${methodname}_${analysisstring}_${Signal}_${stopmass}_${lspmass} #> /dev/null 2>&1
	mv higgsCombine${methodname}_${analysisstring}_${Signal}_${stopmass}_${lspmass}.Asymptotic.mH120.root Limits_Asymptotic_${methodname}_${analysisstring}_${Signal}_${stopmass}_${lspmass}.root
    fi
fi
