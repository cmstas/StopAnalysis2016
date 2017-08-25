# StopBabyMaker

This code makes stop babies from CMS3 or CMS4 ntuples.

## Setup

Check out the [CORE](https://github.com/cmstas/CORE) repository somewhere. If you
already have it checked out, make sure your local copy is up to
date. Compile CORE.

Edit the `Makefile` so that the variable `COREPATH` points to your local
CORE instance.

Then do:
```
cd stop_variables
make
cd ..
make
```

(If you already have some compiled code, you may wish to run `make
clean` first).

## Running the babymaker

The main exectuable is `runBabyMaker`. To run it, you need to provide at least the first argument, and a maximum of six arguments.

`./runBabyMaker sample_name nevents file_number outpath sampleList isFastsim`

- **sample\_name**: This is the compact name for the sample you want to run on. These sample names are defined in the various sample\*.dat files.
- **nevents**: This is how many events you want to run over. A value of -1 means all events in the ntuple. If you don't provide a value, -1 is used automatically.
- **file\_number**: This number specifies which file you want to run over (i.e. merged\_ntuple\_X.root). The default value is -1, which means all files.
- **outpath**: This is the path where you want the stop babies to be written. The default value is `/nfs-7/userdata/stopRun2`.
- **sampleList**: This parameter tells the babyMaker which .dat file contains the sample\_name you want to run on. The default value is sample_2017.dat.
- **isFastsim**: Put a 1 if your desired sample is a fastSim sample. The default value is 0 (not fastSim).

