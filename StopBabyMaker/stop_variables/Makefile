include Makefile.arch

ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

#######################################
# -- DEFINE ARCH to something sensible!
#######################################

#
CXX           = g++
CXXFLAGS      = -g -Wall -fPIC -Wno-unused-but-set-variable
LD            = g++
LDFLAGS       = -g
SOFLAGS       = -shared


CXXFLAGS      += $(ROOTCFLAGS)
LIBS           = $(ROOTLIBS)

NGLIBS         = $(ROOTGLIBS)
NGLIBS        += -lMinuit
GLIBS          = $(filter-out -lNew, $(NGLIBS))

LIB=StopVariables.so

$(LIB): Davismt2.o mt2w_bisect.o mt2w.o chi2.o topness.o MT2_implementations.o JetUtil.o
	$(LD) $(LDFLAGS) $(SOFLAGS) $(ROOTLIBS) Davismt2.o mt2w.o mt2w_bisect.o chi2.o topness.o MT2_implementations.o JetUtil.o $(GLIBS) -lGenVector -o $@

Davismt2.o: Davismt2.cc Davismt2.h
	$(CXX) $(CXXFLAGS) -c Davismt2.cc

mt2w.o: mt2w.cc mt2w.h mt2w_bisect.h JetUtil.h
	$(CXX) $(CXXFLAGS) -c mt2w.cc

mt2w_bisect.o:  mt2w_bisect.cpp mt2w_bisect.h
	$(CXX) $(CXXFLAGS) -c mt2w_bisect.cpp

chi2.o: chi2.cc chi2.h
	$(CXX) $(CXXFLAGS) -c chi2.cc

topness.o: topness.cc topness.h JetUtil.h
	$(CXX) $(CXXFLAGS) -c topness.cc

MT2_implementations.o: MT2_implementations.cc MT2_implementations.h  Davismt2.h JetUtil.h
	$(CXX) $(CXXFLAGS) -c MT2_implementations.cc

JetUtil.o: JetUtil.cc JetUtil.h
	$(CXX) $(CXXFLAGS) -c JetUtil.cc


.PHONY: clean
clean:
	rm -v -f \
	*.o *.d *.so
