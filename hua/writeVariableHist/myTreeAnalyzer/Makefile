#-----------------------------------------------------------------------------

PROGRAM = run_treeAnalyzer


HDRS = treeAnalyzer.h\
		# ../src_cpp/usefulFuction.h\
 
OBJS = 	treeAnalyzer.o run_treeAnalyzer.o\
		# ../src_cpp/usefulFuction.o\
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


#The @ in front of echo is to suppress the print out of the recipe itself in the terminal window
# $(SHAREDLIBS).so: $(OBJS) $(HDRS)
# 	@echo "Linking $(SHAREDLIBS).so ..." 
# 	$(LD) $(ARCHFLAGS) $(LDFLAGS) $(SOFLAGS) $(OBJS) $(LIBS) -o$(SHAREDLIBS).so
# 	@echo "linking done"




# dict_$(PROGRAM).C: $(HDRS)
# 	@echo "Generating dictionary ..."
# 	# rootcint -f dict_$(PROGRAM).C -c -p -I$(HEADRDIR) $(CORRECTIONLIB_FLAGS) $(HDRS) Linkdef.h 
# 	rootcint -f dict_$(PROGRAM).C -c -p -I$(HEADRDIR) $(CXXFLAGS) $(HDRS) Linkdef.h 

clean:
	@rm -f $(OBJS) $(SHAREDLIBS).so $(PROGRAM).out 

 

#------------------------------------------------------------------------
