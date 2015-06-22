#Stop Analysis

Please check if CORE and Software from common TAS repository are up-to-date,
and that the directory matches the one in the makefile

then do:
```
cd stop_variables
make
cd ..
make
```

(don't forget make clean if you have compiled code)

runBabyMaker takes four arguments: ./runBabyMaker sample_name nevents file_number outpath sampledat

The sampledat contains the directory to the CMS3 ntuples.

Need to provide at least sample_name; nevents=-1 (-1=all events), file_number=0 (0=merged_ntuple_*.root),output=/nfs-7/userdata/stopRun2/, sampledat=sample.dat  by default

samplenames are hardcoded to
* ttbar
* stop_850_100
* stop_650_325
* stop_500_325
* stop_425_325
* ttwjets
* ttzjets
* dyjets
* tbar_sch
* tbar_tch
* t_sch
* t_tch
* t_tW
* tbar_tW
* wjets
* wjetsHT100
* wjetsHT200
* wjetsHT400
* wjetsHT600
* wzjets
* zz
