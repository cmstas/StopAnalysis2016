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
TOOLSPATH      = $(COREPATH)/Tools
DORKYPATH      = $(TOOLSPATH)/dorky


CXXFLAGS       += -I$(COREPATH)
CXXFLAGS       += -I$(TOOLSPATH)
CXXFLAGS       += -I$(DORKYPATH)

CORESOURCE     = $(COREPATH)/CMS3_CORE.so
CORELIB        = ./CMS3_CORE.so

STOPVARSOURCE  = $(wildcard stop_variables/*.cc)
STOPVARLIB     = StopVariables.so

#
# Make rules
#

runBabyMaker: runBabyMaker.o looper.o EventTree.o LeptonTree.o JetTree.o IsoTracksTree.o TauTree.o GenParticleTree.o PhotonTree.o StopSelections.o LinkDef_out.so $(CORELIB) $(STOPVARLIB)
	$(LD) $(LDFLAGS)  -o runBabyMaker runBabyMaker.o looper.o EventTree.o JetTree.o LeptonTree.o PhotonTree.o IsoTracksTree.o TauTree.o GenParticleTree.o StopSelections.o $(GLIBS) -lGenVector -lEG $(CORELIB) $(STOPVARLIB) LinkDef_out.so -Wl,-rpath,./

$(CORELIB): $(CORESOURCE)
	cp $(CORESOURCE) .

$(STOPVARLIB): $(STOPVARSOURCE) $(STOPVARSOURCE:.cc=.h)
	cd stop_variables && $(MAKE) -j4 && cd ..; \
	mv stop_variables/StopVariables.so .

runBabyMaker.o: runBabyMaker.C looper.h
	$(CXX) $(CXXFLAGS) -c runBabyMaker.C

looper.o: looper.C looper.h EventTree.h TauTree.h IsoTracksTree.h GenParticleTree.h LeptonTree.h PhotonTree.h StopSelections.h
	$(CXX) $(CXXFLAGS) -c looper.C

EventTree.o: EventTree.cc EventTree.h StopSelections.h
	$(CXX) $(CXXFLAGS) -c EventTree.cc

LeptonTree.o: LeptonTree.cc LeptonTree.h StopSelections.h
	$(CXX) $(CXXFLAGS) -c LeptonTree.cc

PhotonTree.o: PhotonTree.cc PhotonTree.h StopSelections.h
	$(CXX) $(CXXFLAGS) -c PhotonTree.cc

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

LinkDef_out.so: LinkDef.h
	@rootcling -v -f LinkDef.cc -c -p Math/Vector4D.h LinkDef.h
	$(CXX) $(CXXFLAGS) $(SOFLAGS) LinkDef.cc -o $@

.PHONY: clean
clean:
	rm -v -f \
	runBabyMaker \
	LinkDef.cc \
	LinkDef_rdict.pcm \
	*.o *.d *.so
