#-----------------------------------------------------------------------------

PROGRAM = run_objectTSelectorForNanoAOD
SHAREDLIBS = objectTSelectorForNanoAOD


HDRS = objectTSelectorForNanoAOD.h\
	utilityFunctions.h\



#PROGRAM depend on OBJS 
OBJS = objectTSelectorForNanoAOD.o\
		utilityFunctions.o\
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
#g++ -c -o: compile indepentent .C
#g++ -o: link and complile into exutables
#-g - turn on debugging (so GDB gives more friendly output)

%/%.o: %.C
	$(CXX) -c $(CXXFLAGS) $*.C
 



$(PROGRAM).out: $(OBJS) $(SHAREDLIBS).so $(PROGRAM).C
	@echo "building $(PROGRAM)......"
	$(CXX) -c $(CXXFLAGS) -o $(PROGRAM).o $(PROGRAM).C
	$(LD) $(ARCHFLAGS) $(LDFLAGS) $(OBJS) $(PROutGRAM).o $(LIBS) $(SHAREDLIBS).so  -o$(PROGRAM).out
	@echo "done building $(PROGRAM)"

#The @ in front of echo is to suppress the print out of the recipe itself in the terminal window
$(SHAREDLIBS).so: $(OBJS)
	@echo "Linking $(SHAREDLIBS).so ..." 
	$(LD) $(ARCHFLAGS) $(LDFLAGS) $(SOFLAGS) $(OBJS) $(LIBS) -o$(SHAREDLIBS).so
	@echo "linking done"


dict_$(SHAREDLIBS).C: $(HDRS)
	@echo "Generating dictionary ..."
	rootcint -f dict_$(SHAREDLIBS).C -c -p -I$(HEADRDIR) $(CORRECTIONLIB_FLAGS) $(HDRS) Linkdef.h 

clean:
	@rm -f $(OBJS) $(SHAREDLIBS).so $(PROGRAM).o dict_*
 

#------------------------------------------------------------------------
