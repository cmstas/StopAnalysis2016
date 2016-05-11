# Welcome to the CombineAnalysis (for stop)

All the interpretation hard-work (i.e. all but plotting) is done here.

- makeDataCards.C: takes input of the StopLooper (currently from 8 TeV input files, i.e. slightly changes expected in file names and histogram names) and makes your favorite one-bin datacards. Has various options (with/out signal contamination, correlation, signal/background systematics). Also makes the outputfile for final result table/plot maker (as here it is easiest to correctly add systematic uncertainties).

- CombineCards.sh: uses single bin makeDataCards.C and combines them (fakes shapes). Has options (with/out signal contamination, correlation, signal/background systematics) and need to specify signal and analysis: "CombineCards.sh SIGNAL ANALYSIS STOPMASS LSPMASS CORRELATED DROPSIGCONT NOSIGSYST NOBGSYST FAKEDATA"

- Other combine's: CombineCardsScan.sh - does full scan for one analysis, CombineCardsAllScans.sh - does all scans for all analysis, CombineCardsOneScanAllAnalysis.sh - does one scan for all analyses, CombineCardsAll.sh - does all scans for all analyses.

- batch submission code: Running limits on condor.

- one simple wrapper for running HiggsCombine: getLimitsorSignificances.sh - for one datacard, else use batch submission.

Still to be done

- using results of HiggsCombine and fill them into usable format to make final plot (includes some post processing)

- possibly an automated smoothing (no basis of code existing here - was done by hand during 8 TeV)

