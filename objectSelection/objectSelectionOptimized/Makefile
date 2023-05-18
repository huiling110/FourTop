#-----------------------------------------------------------------------------

PROGRAM = run_objectSelection


HDRS = objectSelectionNano.h
 
OBJS = 	objectSelectionNano.o run_objectSelection.o 

#-----------------------------------------------------------------------------
ObjSuf = o
SrcSuf = C
ExeSuf = exe
DllSuf = so
OutPutOpt = -o

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)

# CORRECTIONLIB_FLAGS = $(shell correction config --cflags)
# CORRECTIONLIB_LIB = $(shell correction config --ldflags --rpath )
TMVALIBS = -lTMVA

# Directories
HEADRDIR = .

# debug option: -g
# no exceptions: -fno-exceptions

CXX = g++
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
LIBS += $(TMVALIBS)
GLIBS = $(ROOTGLIBS)



# $(PROGRAM).out: $(OBJS) $(PROGRAM).C
# $(CXX) -c $(CXXFLAGS) -o $(PROGRAM).o $(PROGRAM).C
# $(LD) $(ARCHFLAGS) $(LDFLAGS) $(OBJS) $(PROGRAM).o $(LIBS) -o$(PROGRAM).out
$(PROGRAM).out: $(OBJS) 
	@echo "building $(PROGRAM)......"
	$(LD) $(ARCHFLAGS) $(LDFLAGS) $(OBJS)  $(LIBS) -o$(PROGRAM).out
	@echo "done building $(PROGRAM)"

#
# %/%.o: %.C $(HDRS)
%/%.o: %.C %.h
	$(CXX) -c $(CXXFLAGS) $*.C



clean:
	@rm -f $(OBJS) $(SHAREDLIBS).so $(PROGRAM).out 

 

#------------------------------------------------------------------------
