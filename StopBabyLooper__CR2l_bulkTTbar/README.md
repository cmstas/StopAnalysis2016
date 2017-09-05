# StopBabyLooper__CR2l_bulkTTbar

This code performs the necessary tasks for the bulk ttbar e/mu control regions:
- Loop over all standard babies
- Calculate yields, and generate LaTeX and PDF yield tables
- Make histograms, and arrange into stacked plots
- Perform background estimates
- Calculate systematic uncertainties

To compile the code, do: `make`
(This code depends on StopCORE, so be sure that's compiled too before you run).
To clean up compiled code: `make clean`

To compile and run everything, do: `. go_go_analyzer.sh`
Tables, plots, and raw histograms will be placed in a directory called 'Output'.


## Description of code

The script **go\_go\_analyzer.sh** performs the following steps:

1. Make sure the 'Output' directory exists
2. Compile everything using make
3. Run the executable runBabyLooper\_\_CR2l\_bulkTTbar. Derived from **runBabyLooper\_\_CR2l\_bulkTTbar.C**, it does the following:
    1. Run the main macro from **stopBabyLooper\_\_CR2l\_bulkTTbar.C**. This loops over all babies, generating raw histograms.
    2. In case of aMC@NLO samples, zero out any negative yields, using **zeroOutNegativeYields.C**
	3. Merge the output from individual samples (e.g. ZZto2L2Nu) into backgrounds (e.g. diBoson), using **mergeStopBabies.C**
	4. Generate LaTeX yield tables using **tableMaker\_summedInputs.C**
	5. Make stacked histograms using **plotMaker.C**
	6. Calculate trigger efficiencies using **diLepTriggerEfficiency\_analyzer.C**
	7. Calculate ttbar system pT scale factors using **ttbarSystemPt\_analyzer.C**
	8. Make ttbar system pT plots using **ttbarSystemPt\_plotMaker.C**
4. Run LaTeX to make PDFs of all the yield tables
5. Clean everything up using 'make clean'


## Currently unused macros

- calcErrors.C
- getPileupWeights.C
- scaleSamples.C
- tableMaker_allInputs.C
