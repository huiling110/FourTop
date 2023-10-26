#-----------------------------------------------------------------------------

PROGRAM = run_objectTSelectorForNanoAOD
SHAREDLIBS = objectTSelectorForNanoAOD


HDRS = objectTSelectorForNanoAOD.h\
	utilityFunctions.h\
	inputMap.h\



#PROGRAM depend on OBJS 
OBJS = objectTSelectorForNanoAOD.o\
		utilityFunctions.o\
		inputMap.o\
        dict_$(SHAREDLIBS).o\
		# run_objectTSelectorForNanoAOD.o\

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

# XGBOOST_LIB = -L/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/xgboost/1.3.3/lib64/ -lxgboost
# XGBOOST_FLAGS = -I/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/xgboost/1.3.3/include
XGBOOST_LIB=-L/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/lib/ -lxgboost
XGBOOST_FLAGS=-I/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/rabit/include/

# Directories
HEADRDIR = .

# debug option: -g
# no exceptions: -fno-exceptions

CXX = g++
# CXXFLAGS = -O3 -Wall -fPIC -g -std=c++17  # -wall: turn on "all" Warnings
CXXFLAGS = -O0 -Wall -fPIC -g -std=c++17  # -wall: turn on "all" Warnings
LD = g++
# LDFLAGS = -O3 -Wall -g 
LDFLAGS = -O0 -Wall -g 
SOFLAGS = -shared
ARCHFLAGS =

#
CXXFLAGS += $(ROOTCFLAGS) -I$(HEADRDIR)
CXXFLAGS += $(CORRECTIONLIB_FLAGS)
CXXFLAGS += $(XGBOOST_FLAGS)
LIBS = $(ROOTLIBS)
LIBS += $(CORRECTIONLIB_LIB)
LIBS += $(XGBOOST_LIB)
GLIBS = $(ROOTGLIBS)

#Pattern-specific variable values
#This rule can be applied to any pair of .o and .C files.
#g++ -c -o: compile indepentent .C
#g++ -o: link and complile into exutables
#-g - turn on debugging (so GDB gives more friendly output)

#???need to configure it so that objectTSelectorForNanoAOD.h changes objectTSelectorForNanoAOD.o recompiles

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


dict_$(SHAREDLIBS).C: $(HDRS)
	@echo "Generating dictionary ..."
	rootcint -f dict_$(SHAREDLIBS).C -c -p -I$(HEADRDIR) $(CORRECTIONLIB_FLAGS) $(XGBOOST_FLAGS) $(HDRS) Linkdef.h 

clean:
	@rm -f $(OBJS) $(SHAREDLIBS).so $(PROGRAM).o dict_*
 

#------------------------------------------------------------------------
