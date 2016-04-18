# Welcome to the StopLooper

This is the common StopLooper. It is based on the SnT software
"makeCMS3ClassFiles".

The idea of the common looper is to get ALL histograms needed to run
the background estimates / datacard makers.

The calling function is
"root -l -b -q runStopLooper.C" 
(We might consider modifying this to an executable)
It has all options you need to choose:
- run over data, or SM-MC, or any signal
- run over which signal
- run over standard MC, or JES up/down

The files "StopNTuple.cc/StopNTuple.h" are the  tree defininition
files made by makeCMS3ClassFiles. This uses namespace "tas"
(or more precise, the function called was:
makeCMS3ClassFiles("myLatestGreatestFile.root","t","StopNTuple","tas") )

On top of that stop specific functions (a la isSignalRegion) are
defined in "StopFunctions.cc/.h".
Its namespace is "StF" (for STopFunctions).

Utilities (like DeltaR) are defined in "Utilities.hh". Here, namespace
"Util" is used.

The main codes are GetSignalHistos.C / GetSRandCRHistos.C.
The latter runs on data / SM-MC, the former on signal.
They are separated as signal has 3 dimensions (mStop,mLSP,SR),
while SM/data has only one SR.

Finally, a small helper script haddJES.sh / haddAllJES.sh does
hadd of the output files with standard JES, and JES up/down (for JES
uncertainty).
A similar helper script haddSMLeps.sh adds the lepton-binned
histograms ("eq1l,ge2l,Znunu,1ltop,1lnottop,1lW,1lnotW") for all
SM samples.
