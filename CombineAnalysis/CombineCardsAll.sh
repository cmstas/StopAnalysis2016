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

dropsigcont=false
correlated=true
fakedata=false
nosigsyst=false
nobgsyst=false

if [ $# -eq 0 ]
then
    echo If you wish to set something set
    echo CombineCardsAll.sh CORRELATED DROPSIGCONT NOSIGSYST NOBGSYST FAKEDATA
fi

if [ $# -gt 0 ]
then
    correlated=$1
fi
if [ $# -gt 1 ]
then
    dropsigcont=$2
fi
if [ $# -gt 2 ]
then
    nosigsyst=$3
fi
if [ $# -gt 3 ]
then
    nobgsyst=$4
fi
if [ $# -gt 4 ]
then
    fakedata=$5
fi

for (( a=0; a<=0; t+=1 ))
do
    bash CombineCardsAllScan.sh ${a} ${correlated} ${dropsigcont} ${nosigsyst} ${nobgsyst} ${fakedata}
done
