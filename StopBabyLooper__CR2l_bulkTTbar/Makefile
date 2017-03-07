ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

#######################################
# -- DEFINE ARCH to something sensible!
#######################################

CXX           = g++
CXXFLAGS      = -g -Wall -fPIC
LD            = g++
LDFLAGS       = -g
SOFLAGS       = -shared


CXXFLAGS      += $(ROOTCFLAGS)
LIBS           = $(ROOTLIBS) 

NGLIBS         = $(ROOTGLIBS) 
NGLIBS        += -lMinuit
GLIBS          = $(filter-out -lNew, $(NGLIBS))

STOPPATH       = /home/users/jgwood/Stop_1Lepton/analysis2016__fullYear/CMSSW_8_0_5_patch1/src/StopAnalysis/
SOFTWAREPATH   = $(STOPPATH)/../Software
COREPATH       = $(STOPPATH)/../CORE
TOOLSPATH      = $(COREPATH)/Tools
DORKYPATH      = $(TOOLSPATH)/dorky

CXXFLAGS       += -I$(SOFTWAREPATH)
CXXFLAGS       += -I$(COREPATH)
CXXFLAGS       += -I$(TOOLSPATH)
CXXFLAGS       += -I$(DORKYPATH)

CORELIB        = $(COREPATH)/CMS3_CORE.so
STOPVARLIB     = $(STOPPATH)/StopBabyMaker/stop_variables/StopVariables.so
STOPCORELIB    = $(STOPPATH)/StopCORE/stopCORE.so

runBabyLooper__CR2l_bulkTTbar: runBabyLooper__CR2l_bulkTTbar.o stopBabyLooper__CR2l_bulkTTbar.o dorky.o scaleSamples.o mergeStopBabies.o tableMaker_allInputs.o zeroOutNegativeYields.o tableMaker_summedInputs.o calcErrors.o dataMCplotMaker.o plotMaker.o diLepTriggerEfficiency_analyzer.o ttbarSystemPt_analyzer.o ttbarSystemPt_plotMaker.o LinkDef_out.so
	$(LD) $(LDFLAGS)  -o runBabyLooper__CR2l_bulkTTbar runBabyLooper__CR2l_bulkTTbar.o stopBabyLooper__CR2l_bulkTTbar.o dorky.o scaleSamples.o mergeStopBabies.o tableMaker_allInputs.o zeroOutNegativeYields.o tableMaker_summedInputs.o calcErrors.o dataMCplotMaker.o plotMaker.o diLepTriggerEfficiency_analyzer.o ttbarSystemPt_analyzer.o ttbarSystemPt_plotMaker.o $(GLIBS) -lGenVector -lEG $(CORELIB) $(STOPVARLIB) $(STOPCORELIB) LinkDef_out.so -Wl,-rpath,./

runBabyLooper__CR2l_bulkTTbar.o: runBabyLooper__CR2l_bulkTTbar.C
	$(CXX) $(CXXFLAGS) -c runBabyLooper__CR2l_bulkTTbar.C

stopBabyLooper__CR2l_bulkTTbar.o: stopBabyLooper__CR2l_bulkTTbar.C stopBabyLooper__CR2l_bulkTTbar.h
	$(CXX) $(CXXFLAGS) -c stopBabyLooper__CR2l_bulkTTbar.C 

dorky.o: $(DORKYPATH)/dorky.cc $(DORKYPATH)/dorky.h
	$(CXX) $(CXXFLAGS) -c $(DORKYPATH)/dorky.cc 

scaleSamples.o: scaleSamples.C stopBabyLooper__CR2l_bulkTTbar.h
	$(CXX) $(CXXFLAGS) -c scaleSamples.C

mergeStopBabies.o: mergeStopBabies.C stopBabyLooper__CR2l_bulkTTbar.h
	$(CXX) $(CXXFLAGS) -c mergeStopBabies.C

tableMaker_allInputs.o: tableMaker_allInputs.C stopBabyLooper__CR2l_bulkTTbar.h
	$(CXX) $(CXXFLAGS) -c tableMaker_allInputs.C

zeroOutNegativeYields.o: zeroOutNegativeYields.C stopBabyLooper__CR2l_bulkTTbar.h
	$(CXX) $(CXXFLAGS) -c zeroOutNegativeYields.C

tableMaker_summedInputs.o: tableMaker_summedInputs.C stopBabyLooper__CR2l_bulkTTbar.h
	$(CXX) $(CXXFLAGS) -c tableMaker_summedInputs.C

calcErrors.o: calcErrors.C stopBabyLooper__CR2l_bulkTTbar.h
	$(CXX) $(CXXFLAGS) -c calcErrors.C

dataMCplotMaker.o: $(SOFTWAREPATH)/dataMCplotMaker/dataMCplotMaker.h $(SOFTWAREPATH)/dataMCplotMaker/dataMCplotMaker.cc
	$(CXX) $(CXXFLAGS) -c $(SOFTWAREPATH)/dataMCplotMaker/dataMCplotMaker.cc

plotMaker.o: plotMaker.C stopBabyLooper__CR2l_bulkTTbar.h
	$(CXX) $(CXXFLAGS) -c plotMaker.C

diLepTriggerEfficiency_analyzer.o: diLepTriggerEfficiency_analyzer.C stopBabyLooper__CR2l_bulkTTbar.h
	$(CXX) $(CXXFLAGS) -c diLepTriggerEfficiency_analyzer.C

ttbarSystemPt_analyzer.o: ttbarSystemPt_analyzer.C stopBabyLooper__CR2l_bulkTTbar.h
	$(CXX) $(CXXFLAGS) -c ttbarSystemPt_analyzer.C

ttbarSystemPt_plotMaker.o: ttbarSystemPt_plotMaker.C stopBabyLooper__CR2l_bulkTTbar.h
	$(CXX) $(CXXFLAGS) -c ttbarSystemPt_plotMaker.C

LinkDef_out.so: LinkDef.h
	@rootcling -v -f LinkDef.cc -c -p Math/Vector4D.h LinkDef.h
	$(CXX) $(CXXFLAGS) $(SOFLAGS) LinkDef.cc -o $@

.PHONY: clean
clean:  
	rm -v -f \
	runBabyLooper__CR2l_bulkTTbar \
	LinkDef.cc \
	LinkDef_rdict.pcm \
	*.o *.d *.so *.pcm *~; echo "Done"
