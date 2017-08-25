# StopCORE

StopCORE is a collection of classes that support the various StopBabyLoopers. All the major parameters of the analysis, including SR and CR definitions, cuts, event weights, etc. are all defined here.

To compile StopCORE into a shared library: `make`

To clean up compiled code: `make clean`

## Description of classes

| Class | Description |
| ---- | ---- |
| analyzer.h/cc | A class that unfies functions from categoryInfo, selectionInfo, genClassyInfo, and sysInfo, to define each distinct segment of the data (e.g. corridor signal regions, bulk 2L control regions). |
| categoryInfo.h/cc | Contains the definitions for each set of signal regions (or "categories"). |
| eventWeight\_bTagSF.h/cc | Used for on-the-fly b-tag SF calculations. |
| eventWeight\_lepSF.cc | Used for on-the-fly lepton SF calculations. |
| genClassyInfo.h/cc | Used to classify events as dilepton, 1l-from-top, etc. based on gen-level info. |
| sampleInfo.h/cc | Contains file locations and meta-data for each sample used in the analysis. |
| selectionInfo.h/cc | Provides functions used to make cuts and selections in the loopers. |
| stop\_1l\_babyAnalyzer.h/cc | Provides functions that read branches from the babies. Equivalent to CMS3.h/cc. |
| sysInfo.h/cc | Calculates nominal and all systematic weights for events. |
