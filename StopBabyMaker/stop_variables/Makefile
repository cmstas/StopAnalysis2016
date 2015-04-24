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

StopVariables.so: mt2w_bisect.o mt2w.o chi2.o
	$(CXX) $(CXXFLAGS) -c $<
	$(LD) $(LDFLAGS)  -o  mt2w.o mt2w_bisect.o chi2.o $(GLIBS) -lGenVector

mt2w.o: mt2w.cc mt2w.h mt2w_bisect.h
	$(CXX) $(CXXFLAGS) -c mt2w.cc

mt2w_bisect.o:  mt2w_bisect.cpp mt2w_bisect.h 
	$(CXX) $(CXXFLAGS) -c mt2w_bisect.cpp

chi2.o: chi2.cc chi2.h
	$(CXX) $(CXXFLAGS) -c chi2.cc

.PHONY: clean
clean:  
	rm -v -f \
	*o *d *.so; echo "Done"
