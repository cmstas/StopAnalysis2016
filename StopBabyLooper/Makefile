ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

#######################################
# -- DEFINE ARCH to something sensible!
#######################################
 
#
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

STOPPATH       = /home/users/fgolf/stop/debug/StopAnalysis/
COREPATH       = $(STOPPATH)/../CORE
TOOLSPATH      = $(COREPATH)/Tools
DORKYPATH      = $(TOOLSPATH)/dorky
BABYPATH       = $(STOPPATH)/StopBabyMaker

CXXFLAGS       += -I$(COREPATH)
CXXFLAGS       += -I$(TOOLSPATH)
CXXFLAGS       += -I$(DORKYPATH)

CORELIB        = $(COREPATH)/CMS3_CORE.so
STOPVARLIB     = $(STOPPATH)/StopBabyMaker/stop_variables/StopVariables.so
STOPCORELIB    = $(STOPPATH)/StopCORE/stopCORE.so

runBabyLooper: runBabyLooper.o stopBabyLooper.o dorky.o LinkDef_out.so
	$(LD) $(LDFLAGS)  -o runBabyLooper runBabyLooper.o stopBabyLooper.o dorky.o $(GLIBS) -lGenVector -lEG $(CORELIB) $(STOPVARLIB) $(STOPCORELIB) LinkDef_out.so -Wl,-rpath,./

stopBabyLooper.so: stopBabyLooper.o
	$(LD) $(LDFLAGS) $(SOFLAGS) -o stopBabyLooper.so stopBabyLooper.o $(GLIBS) -lGenVector -lEG $(CORELIB) $(STOPVARLIB) $(STOPCORELIB) -Wl,-rpath,./

runBabyLooper.o: runBabyLooper.C
	$(CXX) $(CXXFLAGS) -c runBabyLooper.C

stopBabyLooper.o: stopBabyLooper.C stopBabyLooper.h
	$(CXX) $(CXXFLAGS) -c stopBabyLooper.C 

dorky.o: $(DORKYPATH)/dorky.cc $(DORKYPATH)/dorky.h
	$(CXX) $(CXXFLAGS) -c $(DORKYPATH)/dorky.cc 

LinkDef_out.so: LinkDef.h
	@rootcling -v -f LinkDef.cc -c -p Math/Vector4D.h LinkDef.h
	$(CXX) $(CXXFLAGS) $(SOFLAGS) LinkDef.cc -o $@

.PHONY: clean
clean:  
	rm -v -f \
	runBabyMaker \
	LinkDef.cc \
	LinkDef_rdict.pcm \
	*.o *.d *.so; echo "Done"
