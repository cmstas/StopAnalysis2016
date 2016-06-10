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

#COREPATH       = $(HOME)/CORE
COREPATH       = ../../CORE
TOOLSPATH      = $(COREPATH)/Tools
DORKYPATH      = $(TOOLSPATH)/dorky


CXXFLAGS       += -I$(COREPATH)
CXXFLAGS       += -I$(TOOLSPATH)
CXXFLAGS       += -I$(DORKYPATH)

CORELIB        = $(COREPATH)/CMS3_CORE.so
STOPVARLIB     = stop_variables/StopVariables.so



stopCORE.so: histogramInfo.o systematicInfo.o eventWeightInfo.o eventWeight_bTagSF.o eventWeight_lepSF.o selectionInfo.o categoryInfo.o recoClassyInfo.o genClassyInfo.o sampleInfo.o analyzerInfo.o stop_1l_babyAnalyzer.o
	$(LD) $(LDFLAGS) $(SOFLAGS) -o stopCORE.so histogramInfo.o systematicInfo.o eventWeightInfo.o eventWeight_bTagSF.o eventWeight_lepSF.o selectionInfo.o categoryInfo.o recoClassyInfo.o genClassyInfo.o sampleInfo.o analyzerInfo.o stop_1l_babyAnalyzer.o $(GLIBS) -lGenVector -lEG $(CORELIB) -Wl,-rpath,./


histogramInfo.o: histogramInfo.cc histogramInfo.h systematicInfo.h systematicInfo.cc categoryInfo.h categoryInfo.cc recoClassyInfo.h recoClassyInfo.cc genClassyInfo.h genClassyInfo.cc
	$(CXX) $(CXXFLAGS) -c histogramInfo.cc


systematicInfo.o: systematicInfo.cc systematicInfo.h eventWeightInfo.h eventWeightInfo.cc stop_1l_babyAnalyzer.cc stop_1l_babyAnalyzer.h analyzerInfo.h analyzerInfo.cc
	$(CXX) $(CXXFLAGS) -c systematicInfo.cc


eventWeightInfo.o: eventWeightInfo.cc eventWeightInfo.h eventWeight_lepSF.h eventWeight_lepSF.cc eventWeight_bTagSF.h eventWeight_bTagSF.cc sampleInfo.h sampleInfo.cc stop_1l_babyAnalyzer.cc stop_1l_babyAnalyzer.h
	$(CXX) $(CXXFLAGS) -c eventWeightInfo.cc


eventWeight_bTagSF.o: eventWeight_bTagSF.cc eventWeight_bTagSF.h
	$(CXX) $(CXXFLAGS) -c eventWeight_bTagSF.cc


eventWeight_lepSF.o: eventWeight_lepSF.cc eventWeight_lepSF.h
	$(CXX) $(CXXFLAGS) -c eventWeight_lepSF.cc


selectionInfo.o: selectionInfo.cc selectionInfo.h analyzerInfo.h analyzerInfo.cc sampleInfo.cc sampleInfo.h stop_1l_babyAnalyzer.cc stop_1l_babyAnalyzer.h
	$(CXX) $(CXXFLAGS) -c selectionInfo.cc


categoryInfo.o: categoryInfo.cc categoryInfo.h analyzerInfo.h analyzerInfo.cc stop_1l_babyAnalyzer.cc stop_1l_babyAnalyzer.h
	$(CXX) $(CXXFLAGS) -c categoryInfo.cc


recoClassyInfo.o: recoClassyInfo.cc recoClassyInfo.h analyzerInfo.h analyzerInfo.cc stop_1l_babyAnalyzer.cc stop_1l_babyAnalyzer.h
	$(CXX) $(CXXFLAGS) -c recoClassyInfo.cc


genClassyInfo.o: genClassyInfo.cc genClassyInfo.h analyzerInfo.h analyzerInfo.cc stop_1l_babyAnalyzer.cc stop_1l_babyAnalyzer.h
	$(CXX) $(CXXFLAGS) -c genClassyInfo.cc


sampleInfo.o: sampleInfo.cc sampleInfo.h analyzerInfo.h analyzerInfo.cc
	$(CXX) $(CXXFLAGS) -c sampleInfo.cc


analyzerInfo.o: analyzerInfo.cc analyzerInfo.h
	$(CXX) $(CXXFLAGS) -c analyzerInfo.cc

stop_1l_babyAnalyzer.o: stop_1l_babyAnalyzer.cc stop_1l_babyAnalyzer.h
	$(CXX) $(CXXFLAGS) -c stop_1l_babyAnalyzer.cc

.PHONY: clean
clean:  
	rm -v -f \
	*.o *.d *.so; echo "Done"
