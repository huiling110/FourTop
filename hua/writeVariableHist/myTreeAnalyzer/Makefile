#-----------------------------------------------------------------------------

PROGRAM = run_treeAnalyzer

OBJS = 	treeAnalyzer.o histsForRegionsMap_class.o functions.o\

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



$(PROGRAM).out: $(OBJS) $(PROGRAM).o
	@echo "building $(PROGRAM)......"
	$(LD) $(ARCHFLAGS) $(LDFLAGS) $(OBJS) $(PROGRAM).o  $(LIBS) -o$(PROGRAM).out
	@echo "done building $(PROGRAM)"

#% Wildcard
# %/%.o: %.C %.h
# 	$(CXX) -c $(CXXFLAGS) $*.C

#static pattern rule 
$(OBJS): %.o: %.C %.h
	$(CXX) -c $(CXXFLAGS) -o $@ $^ 

$(PROGRAM).o: $(PROGRAM).C
	$(CXX) -c $(CXXFLAGS) -o $(PROGRAM).o $(PROGRAM).C


clean:
	@rm -f $(OBJS) $(SHAREDLIBS).so $(PROGRAM).out 

 

#------------------------------------------------------------------------
