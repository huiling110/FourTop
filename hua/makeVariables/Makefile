#-----------------------------------------------------------------------------

# PROGRAM = Analysis
PROGRAM = run_makeVaribles_forBDT
SHAREDLIBS = makeVaribles_forBDT


HDRS = makeVaribles_forBDT.h\
	variablesFunctions.h\
	weightCal.h\
 
OBJS = 	makeVaribles_forBDT.o\
		variablesFunctions.o\
		weightCal.o\
        dict_$(PROGRAM).o\

#-----------------------------------------------------------------------------
ObjSuf = o
SrcSuf = C
ExeSuf = exe
DllSuf = so
OutPutOpt = -o

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)

CORRECTIONLIB_FLAGS = $(shell correction config --cflags)
CORRECTIONLIB_LIB = $(shell correction config --ldflags --rpath )

# Directories
HEADRDIR = .

# debug option: -g
# no exceptions: -fno-exceptions

CXX = g++
# CXX = /cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/gcc/7.0.0-omkpbe2/bin/g++
CXXFLAGS = -O3 -Wall -fPIC -g -std=c++17
# CXXFLAGS = -O3 -Wall -fPIC -g 
LD = g++
LDFLAGS = -O3 -Wall -g 
SOFLAGS = -shared
ARCHFLAGS =

#
CXXFLAGS += $(ROOTCFLAGS) -I$(HEADRDIR)
CXXFLAGS += $(CORRECTIONLIB_FLAGS)
LIBS = $(ROOTLIBS)
LIBS += $(CORRECTIONLIB_LIB)
GLIBS = $(ROOTGLIBS)


%/%.o: %.C $(HDRS)
	$(CXX) -c $(CXXFLAGS) $*.C


$(PROGRAM).out: $(OBJS) $(SHAREDLIBS).so $(PROGRAM).C
	@echo "building $(PROGRAM)......"
	$(CXX) -c $(CXXFLAGS) -o $(PROGRAM).o $(PROGRAM).C
	$(LD) $(ARCHFLAGS) $(LDFLAGS) $(OBJS) $(PROGRAM).o $(LIBS) $(SHAREDLIBS).so  -o$(PROGRAM).out
	@echo "done building $(PROGRAM)"

#The @ in front of echo is to suppress the print out of the recipe itself in the terminal window
$(SHAREDLIBS).so: $(OBJS) $(HDRS)
	@echo "Linking $(SHAREDLIBS).so ..." 
	$(LD) $(ARCHFLAGS) $(LDFLAGS) $(SOFLAGS) $(OBJS) $(LIBS) -o$(SHAREDLIBS).so
	@echo "linking done"




dict_$(PROGRAM).C: $(HDRS)
	@echo "Generating dictionary ..."
	rootcint -f dict_$(PROGRAM).C -c -p -I$(HEADRDIR) $(CORRECTIONLIB_FLAGS) $(HDRS) Linkdef.h 

clean:
	@rm -f $(OBJS) $(SHAREDLIBS).so $(PROGRAM).o dict_*
 

#------------------------------------------------------------------------
