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

STOPPATH       = /home/users/dsklein/projects/stop/StopAnalysis_80x/
SOFTWAREPATH   = /home/users/dsklein/tools/cmstas-software/
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

runLooper: runLooper.o looper_nu.o mergeStopBabies.o dorky.o LinkDef_out.so
	$(LD) $(LDFLAGS)  -o runLooper runLooper.o dorky.o looper_nu.o mergeStopBabies.o $(GLIBS) -lGenVector -lEG $(CORELIB) $(STOPVARLIB) $(STOPCORELIB) LinkDef_out.so -Wl,-rpath,./

runLooper.o: runLooper.C
	$(CXX) $(CXXFLAGS) -c runLooper.C

looper_nu.o: looper_nu.C met-resolution.h
	$(CXX) $(CXXFLAGS) -c looper_nu.C

mergeStopBabies.o: mergeStopBabies.C met-resolution.h
	$(CXX) $(CXXFLAGS) -c mergeStopBabies.C

dorky.o: $(DORKYPATH)/dorky.cc $(DORKYPATH)/dorky.h
	$(CXX) $(CXXFLAGS) -c $(DORKYPATH)/dorky.cc


LinkDef_out.so: LinkDef.h
	@rootcling -v -f LinkDef.cc -c -p Math/Vector4D.h LinkDef.h
	$(CXX) $(CXXFLAGS) $(SOFLAGS) LinkDef.cc -o $@

.PHONY: clean
clean:  
	rm -v -f \
	runLooper \
	LinkDef.cc \
	LinkDef_rdict.pcm \
	*.o *.d *.so *.pcm *~; echo "Done"
