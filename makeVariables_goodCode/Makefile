
# Source directory
SRC_DIR = src
INC_DIR = include
# Object directory
OBJ_DIR = obj
# Executable directory
BIN_DIR = apps

# Source files
SOURCES := $(wildcard $(SRC_DIR)/*.C)
# Object files
OBJECTS := $(patsubst $(SRC_DIR)/%.C, $(OBJ_DIR)/%.o, $(SOURCES))

# Final executable
TARGET = $(BIN_DIR)/run_makeVariables.out


ROOTCFLAGS = $(shell root-config --cflags)
# ROOTLIBS = $(shell root-config --libs) #correction config --cflags --ldflags
# ROOTLIBS = -L/scratchfs/cms/huahuil/myenv/lib64/python3.9/site-packages/correctionlib/lib -lcorrectionlib
ROOTLIBS = $(shell root-config --libs) 
ROOTGLIBS = $(shell root-config --glibs)

# CORRECTIONLIB_FLAGS = $(shell correction config --cflags) #-I/scratchfs/cms/huahuil/myenv/lib64/python3.9/site-packages/correctionlib/include 
#-std=c++17 -I/scratchfs/cms/huahuil/myenv/lib64/python3.9/site-packages/correctionlib/include
CORRECTIONLIB_FLAGS = -I/scratchfs/cms/huahuil/myenv/lib64/python3.9/site-packages/correctionlib/include 
# CORRECTIONLIB_LIB = $(shell correction config --ldflags --rpath )
CORRECTIONLIB_LIB = $(shell correction config --ldflags )


# TMVALIBS = -lTMVA
# Add this to your linker command:
# TMVALIBS = -L/cvmfs/cms.cern.ch/el9_amd64_gcc14/lcg/root/6.36.01-fd214bf9b7a010bf699f6444925c3f56/lib -lTMVA

MYLIB = -L/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/myLibrary/ -lcommenFunction #!seems still needed event set by setEnv.sh

# XGBOOST_LIB=-L/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/lib/ -lxgboost
# XGBOOST_FLAGS=-I/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/rabit/include/

# Directories
HEADRDIR = .
SOURCE = src/


CXX = g++
# CXXFLAGS = -O3 -Wall -fPIC -g -std=c++17
#!!!-std=c++20 already set in ROOTCFLAGS
CXXFLAGS = -O3 -Wall -fPIC -g 
# CXXFLAGS = -O3 -Wall -fPIC -g 
LD = g++
LDFLAGS = -O3 -Wall -g 
SOFLAGS = -shared
ARCHFLAGS =

#
CXXFLAGS += $(ROOTCFLAGS) -I$(HEADRDIR)
CXXFLAGS += $(CORRECTIONLIB_FLAGS)
CXXFLAGS += $(XGBOOST_FLAGS)
# LIBS = $(ROOTLIBS)
# LIBS += $(CORRECTIONLIB_LIB)
LIBS = $(CORRECTIONLIB_LIB)
LIBS += $(ROOTGLIBS)
LIBS += $(TMVALIBS)
LIBS += $(MYLIB)



.PHONY: all clean

all: $(TARGET)

# $(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) apps/run_makeVariables.C -o $(TARGET)
$(TARGET): $(OBJECTS) apps/run_makeVariables.C
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBS) apps/run_makeVariables.C -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.C $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)






