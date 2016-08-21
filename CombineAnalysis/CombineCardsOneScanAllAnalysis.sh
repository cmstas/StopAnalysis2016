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

analysis=0
dropsigcont=false
correlated=true
fakedata=false
nosigsyst=false
nobgsyst=false

if [ $# -eq 0 ]
then
    echo Please provide at least the signal as input.
    echo CombineCardsAllScans.sh SIGNAL CORRELATED DROPSIGCONT NOSIGSYST NOBGSYST FAKEDATA
    return
fi
signal=$1


if [ $# -gt 1 ]
then
    correlated=$2
fi
if [ $# -gt 2 ]
then
    dropsigcont=$3
fi
if [ $# -gt 3 ]
then
    nosigsyst=$4
fi
if [ $# -gt 4 ]
then
    nobgsyst=$5
fi
if [ $# -gt 5 ]
then
    fakedata=$6
fi

bash CombineCardsScan.sh ${signal} 0 ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
#no further analysis scan implemented yet
