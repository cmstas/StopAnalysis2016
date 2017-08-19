#
# stuff to make
#
ifndef ROOTSYS
all:
	@echo "ROOTSYS is not set. Please set ROOT environment properly"; echo
else

all: 	build
help:
	@echo "Available Targets:";\
	cat Makefile | perl -ne 'printf("\t%-15s %s\n",$$1,$$2) if(/^(\S+):[^#]+(#.*)$$/)'

ifndef VERBOSE
  QUIET := @
endif

#ROOFITINCLUDE =
#ifdef CMSSW_VERSION
#	ROOFITINCLUDE = $(shell scramv1 tool info roofitcore | grep INCLUDE | sed 's/^INCLUDE=/-I/')
#endif

CC = g++
CMSROOT = ./
INCLUDE = $(shell root-config --cflags) -I$(CMSROOT) -I$(CMSROOT)/CORE
CFLAGS = -Wall -Wno-unused-function -g -O3 -fPIC $(INCLUDE) $(EXTRACFLAGS)
ROOTLIBS = $(shell root-config --ldflags --cflags --libs) -lTMVA #-lEG -lGenVector
COREDIR = CORE

DICTINCLUDE = $(ROOTSYS)/include/Math/QuantFuncMathCore.h $(ROOTSYS)/include/TLorentzVector.h $(ROOTSYS)/include/Math/Vector4D.h

LINKER = g++
LINKERFLAGS = $(shell root-config --ldflags --libs) -lEG -lGenVector -lTMVA -lRooFit

DIR = ./

SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
LIB = libStopLooper.so

CORESOURCES = $(wildcard ../StopCORE/*.cc)
COREOBJECTS = $(CORESOURCES:.cc=.o)
CORELIB = $(wildcard ../StopCORE/libStopCORE.so)

TOOLSSOURCES = $(wildcard ../CORE/Tools/*.cc) $(wildcard ../CORE/Tools/dorky/*.cc)
TOOLSOBJECTS = $(TOOLSSOURCES:.cc=.o)
TOOLSLIB = libStopLooperTools.so
# TOOLSLIB = $(wildcard ../CORE/Tools/*.o) $(wildcard ../CORE/Tools/dorky/*.o)

LIBS = $(LIB) $(CORELIB) $(TOOLSLIB)

EXE = runStopLooper

#
# how to make it
#

# $(CORELIB): $(DICT) $(COREOBJECTS)
# 	$(QUIET) echo "Linking $@"; \
# 	echo "$(LINKER) -shared -o $@ $(COREOBJECTS) $(DICT) $(LINKERFLAGS)"; \
# 	$(LINKER) -shared -o $@ $(COREOBJECTS) $(DICT) $(LINKERFLAGS)

$(TOOLSLIB): $(DICT) $(TOOLSOBJECTS)
	$(QUIET) echo "Linking $@"; \
	echo "$(LINKER) -shared -o $@ $(TOOLSOBJECTS) $(DICT) $(LINKERFLAGS)"; \
	$(LINKER) -shared -o $@ $(TOOLSOBJECTS) $(DICT) $(LINKERFLAGS)

$(LIB):	$(DICT) $(OBJECTS)
	$(QUIET) echo "Linking $@"; \
	echo "$(LINKER) -shared -o $@ $(OBJECTS) $(DICT) $(LINKERFLAGS)"; \
	$(LINKER) -shared -o $@ $(OBJECTS) $(DICT) $(LINKERFLAGS)

# the option "-Wl,-rpath,./" adds ./ to the runtime search path for libraries
$(EXE):  $(LIBS)
	$(QUIET) echo "Building $@"; \
	echo "$(CC) -o $@ $(LIBS) $(ROOTLIBS) -Wl,-rpath,./"; \
	$(CC) -o $@ $(LIBS) $(ROOTLIBS) -Wl,-rpath,./

%.o: 	%.cc %.h
	$(QUIET) echo "Compiling $<"; \
	$(CC) $(CFLAGS) $< -c -o $@

%.o: 	%.C %.h
	$(QUIET) echo "Compiling $<"; \
	$(CC) $(CFLAGS) $< -c -o $@

%.o: 	%.cc
	$(QUIET) echo "Compiling $<"; \
	$(CC) $(CFLAGS) $< -c -o $@

%.o: 	%.C
	$(QUIET) echo "Compiling $<"; \
	$(CC) $(CFLAGS) $< -c -o $@

%.o:    %.cxx
	$(QUIET) echo "Compiling $<"; \
	$(CC) $(CFLAGS) $< -c -o $@

libs:	$(LIBS)

build:  $(EXE)

b: build

clean:
	rm -f \
	LinkDef_out* \
	*.o \
	$(LIBS) \
	$(EXE) \
        ../CORE/Tools/*.o \
	../CORE/Tools/*.d \
        ../CORE/Tools/*.so \
        ../CORE/Tools/dorky/*.o \
	../CORE/Tools/dorky/*.d \
        ../CORE/Tools/dorky/*.so

endif
