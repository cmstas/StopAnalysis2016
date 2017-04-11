#!/bin/bash

# Welcome
echo "----------------------------------"
echo "Go Go Analyzer!"
echo ""

# Check that necesarry file structure existis
echo "Checking for valid directory structure..." 
echo ""
if [ ! -d Output/Histos ]; then mkdir -p Output/Histos; fi
if [ ! -d Output/Plots ]; then mkdir -p Output/Plots; fi
if [ ! -d Output/Tables ]; then mkdir -p Output/Tables; fi
if [ ! -d Output/BkgEstimate ]; then mkdir -p Output/BkgEstimate; fi
if [ ! -d Output/Log ]; then mkdir -p Output/Log; fi

# Compiling Looper Code
make clean
make

# Running Analyzer
./runBabyLooper 

# Create pdfs of latex files
echo ""
echo "Converting TeX to PDF..."
echo ""

sed -i 's/0\.0~-~0\.0~\\%/--/g' Output/BkgEstimate/bkgEst_lostLepton__*__uncertaintyTable__summary.tex

cd Output/Tables/
for x in `/bin/ls *.tex`; do echo $x; pdflatex -interaction=nonstopmode $x >& pass1.log; pdflatex -interaction=nonstopmode $x >& ../Log/pdf2tex_$x.log; rm *.aux; rm *.log; done
cd ../BkgEstimate/
for x in `/bin/ls *.tex`; do echo $x; pdflatex -interaction=nonstopmode $x >& pass1.log; pdflatex -interaction=nonstopmode $x >& ../Log/pdf2tex_$x.log; rm *.aux; rm *.log; done
cd ../../

# Clean up 
echo "Cleaning Up..."
echo ""
make clean

# Done!
echo ""
echo "----------------------------------"
echo " Analysis Results Written To: "
echo "   Output/ " 
echo "---------------------------------"
