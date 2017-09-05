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
STOPVARLIB     = ../StopBabyMaker/stop_variables/StopVariables.so



stopCORE.so: sysInfo.o eventWeight_bTagSF.o eventWeight_lepSF.o analyzer.o selectionInfo.o categoryInfo.o genClassyInfo.o sampleInfo.o stop_1l_babyAnalyzer.o
	$(LD) $(LDFLAGS) $(SOFLAGS) -o stopCORE.so sysInfo.o eventWeight_bTagSF.o eventWeight_lepSF.o analyzer.o selectionInfo.o categoryInfo.o genClassyInfo.o sampleInfo.o stop_1l_babyAnalyzer.o $(GLIBS) -lGenVector -lEG $(CORELIB) $(STOPVARLIB) -Wl,-rpath,./


sysInfo.o: sysInfo.h sysInfo.cc stop_1l_babyAnalyzer.h stop_1l_babyAnalyzer.cc eventWeight_lepSF.h eventWeight_lepSF.cc eventWeight_bTagSF.h eventWeight_bTagSF.cc
	$(CXX) $(CXXFLAGS) -c sysInfo.cc


eventWeight_bTagSF.o: eventWeight_bTagSF.cc eventWeight_bTagSF.h 
	$(CXX) $(CXXFLAGS) -c eventWeight_bTagSF.cc 


eventWeight_lepSF.o: eventWeight_lepSF.cc eventWeight_lepSF.h
	$(CXX) $(CXXFLAGS) -c eventWeight_lepSF.cc


analyzer.o: analyzer.cc analyzer.h
	$(CXX) $(CXXFLAGS) -c analyzer.cc


selectionInfo.o: selectionInfo.cc selectionInfo.h stop_1l_babyAnalyzer.cc stop_1l_babyAnalyzer.h
	$(CXX) $(CXXFLAGS) -c selectionInfo.cc


categoryInfo.o: categoryInfo.cc categoryInfo.h stop_1l_babyAnalyzer.cc stop_1l_babyAnalyzer.h
	$(CXX) $(CXXFLAGS) -c categoryInfo.cc


genClassyInfo.o: genClassyInfo.cc genClassyInfo.h stop_1l_babyAnalyzer.cc stop_1l_babyAnalyzer.h
	$(CXX) $(CXXFLAGS) -c genClassyInfo.cc


sampleInfo.o: sampleInfo.h sampleInfo.cc
	$(CXX) $(CXXFLAGS) -c sampleInfo.cc

stop_1l_babyAnalyzer.o: stop_1l_babyAnalyzer.cc stop_1l_babyAnalyzer.h
	$(CXX) $(CXXFLAGS) -c stop_1l_babyAnalyzer.cc

.PHONY: clean
clean:  
	rm -v -f \
	*.o *.d *.so *.pcm *~; echo "Done"
