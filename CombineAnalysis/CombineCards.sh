
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

thedir='datacards/'

analysis=0

dropsigcont=false
correlated=true
fakedata=false
nosigsyst=false
nobgsyst=false
stop=100
lsp=0


if [ $# -eq 0 ]
then
    echo You should provide at least the SIGNAL.
    echo To run you use
    echo CombineCards.sh SIGNAL ANALYSIS STOPMASS LSPMASS CORRELATED DROPSIGCONT NOSIGSYST NOBGSYST FAKEDATA
    echo Use \'true\' if you want a boolean to be true - 1 does not work.
    return
fi
    
signal=$1

if [ $# -gt 1 ]
then
    analysis=$2
else
    echo You did not specify the analysis using standard one.
    echo Analysis 0 is standard one.
    echo No other analysis implemented so far.
fi

if [[ $analysis -lt 0 ]] || [[ $analysis -gt 0 ]]
then
    echo Your specified analysis has not been implemented.
    echo Analysis 0 is standard one.
    return
fi

if [ $# -gt 2 ]
then
    stop=$3
fi
if [ $# -gt 3 ]
then
    lsp=$4
fi

if [ $# -gt 4 ]
then
    correlated=$5
fi
if [ $# -gt 5 ]
then
    dropsigcont=$6
fi
if [ $# -gt 6 ]
then
    nosigsyst=$7
fi
if [ $# -gt 7 ]
then
    nobgsyst=$8
fi
if [ $# -gt 8 ]
then
    fakedata=$9
fi

if [ "$correlated" = true ]
then
    thedir=`echo ${thedir}correlated/`
fi
if [[ "$nosigsyst" = true ]] && [[ "$nobgsyst" = true ]]
then
    thedir=`echo ${thedir}nounc/`
elif [ "$nosigsyst" = true ]
then
    thedir=`echo ${thedir}nosigsyst/`
elif [ "$nobgsyst" = true ]
then
    thedir=`echo ${thedir}nobgsyst/`
fi
if [ "$dropsigcont" = true ]
then
    thedir=`echo ${thedir}dropsigcont/`
fi
if [ "$fakedata" = true ]
then
    thedir=`echo ${thedir}fakedata/`
fi

if [[ ! -d "$thedir" ]]
then
    echo The directory $thedir does not exist - exiting.
    #return
fi

outdir=`echo ${thedir}combinedcards/`
if [[ ! -d "$outdir" ]]
then
    echo The output directory $outdir does not exist - creating it.
    mkdir -p $outdir
fi

anName=std
maxbins=10
if [ $analysis -eq 0 ]
then
    anName=std
    maxbins=9
elif [ $analysis -eq 1 ]
then
     anName=test
fi
# just for testing implemented -eq 1

Name=`echo datacard_${anName}_${signal}_${stop}_${lsp}`

#echo ${Name}

combinestring=combineCards.py
validcommand=false

for i in `seq 1 ${maxbins}`;
do
    if [ ! -e "${thedir}${Name}_b${i}.txt" ] && [ ! -f "${thedir}${Name}_b${i}.txt" ] && [ ! -s "${thedir}${Name}_b${i}.txt" ]
    then
	nonvalidfile=`echo ${thedir}${Name}_b${i}.txt`
	#echo "file ${nonvalidfile} does not exist. dont combine"
	continue
    fi
    validcommand=true
    combinestring=`echo ${combinestring} ch${i}=${thedir}${Name}_b${i}.txt`
    #echo ${combinestring}
done

if [ "$validcommand" = true ]
then
    eval ${combinestring} -S > ${thedir}combinedcards/${Name}.txt
    #echo ${combinestring}
    echo "Combined cards for ${Name} into ${thedir}combinedcards/${Name}.txt (old file replaced)"
#else
#    echo "No inputfiles for ${Name}"
fi
