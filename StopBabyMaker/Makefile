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

COREPATH       = $(HOME)/CORE
FWLIBPATH      = $(HOME)/Software/MiniFWLite

CXXFLAGS       += -I$(COREPATH)

FWLIB	       = $(FWLIBPATH)/libMiniFWLite.so 
CORELIB        = $(COREPATH)/CMS3_CORE.so

runBabyMaker: runBabyMaker.o looper.o EventTree.o LeptonTree.o JetTree.o IsoTracksTree.o TauTree.o GenParticleTree.o StopSelections.o
	$(LD) $(LDFLAGS)  -o runBabyMaker runBabyMaker.o looper.o EventTree.o JetTree.o LeptonTree.o IsoTracksTree.o TauTree.o GenParticleTree.o StopSelections.o $(GLIBS) -lGenVector -lTMVA -lEG $(CORELIB) $(FWLIB)

runBabyMaker.o: runBabyMaker.C looper.h 
	$(CXX) $(CXXFLAGS) -c runBabyMaker.C 

looper.o: looper.C looper.h EventTree.h TauTree.h IsoTracksTree.h GenParticleTree.h LeptonTree.h StopSelections.h
	$(CXX) $(CXXFLAGS) -c looper.C

EventTree.o: EventTree.cc EventTree.h StopSelections.h 
	$(CXX) $(CXXFLAGS) -c EventTree.cc 

LeptonTree.o: LeptonTree.cc LeptonTree.h StopSelections.h
	$(CXX) $(CXXFLAGS) -c LeptonTree.cc 

JetTree.o: JetTree.cc JetTree.h StopSelections.h
	$(CXX) $(CXXFLAGS) -c JetTree.cc

TauTree.o: TauTree.cc TauTree.h
	$(CXX) $(CXXFLAGS) -c TauTree.cc

IsoTracksTree.o: IsoTracksTree.cc IsoTracksTree.h
	$(CXX) $(CXXFLAGS) -c IsoTracksTree.cc

GenParticleTree.o: GenParticleTree.cc GenParticleTree.h
	$(CXX) $(CXXFLAGS) -c GenParticleTree.cc

StopSelections.o: StopSelections.cc StopSelections.h
	$(CXX) $(CXXFLAGS) -c StopSelections.cc
.PHONY: clean
clean:  
	rm -v -f \
	runBabyMaker \
	*o *d *.so; echo "Done"
