#CombineAnalysis for stop1l

###makeDataCards.C:
- make single-bin datacards: need input files from all backgrounds, data and signal to work
- the functions creating datacards (either a single one- or a group up to all scans for all mass points) are the functions called makeDataCards*.
All other functions are helper functions
- Usually I use makeDataCardsOneScan() that makes all datacards for one scan (e.g. T2tt) for one analysis (e.g. general or compressed): The analysisID has however to be defined. Currently only the general/standard analysis is defined.
- All default settings for flags is what we also use as default.
- functions called analyis* are specific to each analysis (e.g. general) and need to be defined beforehand.
- For filenames/histogram names, you need to go through the load* functions, the main makeDataCardsOneBinBasis() function, as well as the UpdatePlottingHisto() - that last one makes histograms for plotting/table making.

Currently, if one histogram name is spelled wrongly, the code just crashes.
Also if the file/histogram defined in UpdatePlottingHisto() does not exist, the code crashes.


###CombineCards.sh:
combine all SR of single-bin datacards into a combined datacard.
- Please note, that the combinedcards/ need to exists, else the program will literally do nothing
- You need to define signal such as "std_T2tt_850_150" as argument
- the directory where the single-bin datacards are stored is hardcoded "thedir"
- the maximal number of bins is hardcoded - in principle one could set this very high - program will just run slower. Should make this an argument

###CombineCardsScan.sh:
helper function to run on a complete scan. There is a bunch of hardcoded stuff, but you can overwrite those with arguments.
- some variables don't do anything, as the script uses those defined in CombineCards.sh

###CombineCardsAllScans.sh:
obvious

###Make2DSignifHistos.C:
out of the Combine output make 2D histograms with p-value and significances (sigma). Currently written that you need to run expected priori/posteriori and observed first.
- in here, the signaltype string also contains analysisID, e.g. "std_T2tt"
- main function is Make2DSignifHistos() with default flags being correct.
- expect as input the combine output tars as done by the batch submission scripts in the subdirectories.

###Make2DLimitHistos.C:
as Make2DSignifHistos.C, but for limits
- in here, the signaltype string also contains analysisID, e.g. "std_T2tt"
- main function is Make2DLimitHistos () with default flags being correct.
- expect as input the combine output tars as done by the batch submission scripts in the subdirectories.

###CovarianceAndCorrelation:
Out of a set of one big datacard containing all SR bins (signal is not important here - only background), create combine output that allows to make a covariance matrix histogram, that then can be transformed into a correlation matix histogram.
- This one does not run on a tagged version of combine - need untagged version...

###batchlimit:
batch submission for running combine on condor using datacards:
- setup.sh: Define all the ALLCAPS variables on top
- batch.sh: This is what you need to run, but define before "NAME" (analyisID_ScanName) and "postfit" (true used for final results, for studies use false)
- cleanup.sh: each time you run batch.sh - this will create tar files from the datacarddir - WAIT until all your jobs are running, then you can cleanup.
ALSO WAIT before rerunning batch.sh until all jobs are running.

###batchsignificance:
batch submission for running combine on condor using datacards
- similar to batchlimit - in batch.sh instead of "postfit" you need to define "observed" and "posteriori"
