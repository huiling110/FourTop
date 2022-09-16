#-----------------------------------------------------------------------------

# PROGRAM = Analysis
PROGRAM = objectTSelectorForNanoAOD


HDRS = objectTSelectorForNanoAOD.h\
	utilityFunctions.h\

#PROGRAM depend on OBJS 
OBJS = objectTSelectorForNanoAOD.o\
		utilityFunctions.o\
        dict_$(PROGRAM).o\
		# run_objectTSelectorForNanoAOD.o\
		# ../TauPOG/TauIDSFs/src/TauIDSFTool.o\

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
CXXFLAGS = -O3 -Wall -fPIC -g -std=c++17  # -wall: turn on "all" Warnings
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

#Pattern-specific variable values
#This rule can be applied to any pair of .o and .C files.
%/%.o: %.C
	$(CXX) -c $(CXXFLAGS) $*.C
 
#The @ in front of echo is to suppress the print out of the recipe itself in the terminal window
$(PROGRAM).so: $(OBJS)
	@echo "Linking $(PROGRAM).so ..." 
	$(LD) $(ARCHFLAGS) $(LDFLAGS) $(SOFLAGS) $(OBJS) $(LIBS) -o$(PROGRAM).so
	@echo "linking done"

dict_$(PROGRAM).C: $(HDRS)
	@echo "Generating dictionary ..."
	rootcint -f dict_$(PROGRAM).C -c -p -I$(HEADRDIR) $(CORRECTIONLIB_FLAGS) $(HDRS) Linkdef.h 

clean:
	@rm -f $(OBJS) $(PROGRAM).so dict_*
 

#------------------------------------------------------------------------
