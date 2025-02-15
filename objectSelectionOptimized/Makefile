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
TARGET = $(BIN_DIR)/run_objectSelection.out


ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)

CORRECTIONLIB_FLAGS = $(shell correction config --cflags)
CORRECTIONLIB_LIB = $(shell correction config --ldflags --rpath )
TMVALIBS = -lTMVA

XGBOOST_LIB=-L/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/lib/ -lxgboost
XGBOOST_FLAGS=-I/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/rabit/include/

MYLIB = -L/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/myLibrary/ -lcommenFunction
RoccoRLIB = -L/workfs2/cms/huahuil/CMSSW_10_6_20/src/roccor/ -lRoccoR
RoccoRInclude = -I/workfs2/cms/huahuil/CMSSW_10_6_20/src/roccor/
# Directories
HEADRDIR = .
SOURCE = src/

# debug option: -g
# no exceptions: -fno-exceptions
DEBUGLEVEL = O0

CXX = g++
CXXFLAGS = -$(DEBUGLEVEL) -Wall -fPIC -g -std=c++17
LD = g++
LDFLAGS = -$(DEBUGLEVEL) -Wall -g 
SOFLAGS = -shared
ARCHFLAGS =

#
CXXFLAGS += $(ROOTCFLAGS) -I$(HEADRDIR)
CXXFLAGS += $(CORRECTIONLIB_FLAGS)
CXXFLAGS += $(XGBOOST_FLAGS)
CXXFLAGS += $(RoccoRInclude)
LIBS = $(ROOTLIBS)
LIBS += $(CORRECTIONLIB_LIB)
LIBS += $(TMVALIBS)
LIBS += $(XGBOOST_LIB)
LIBS += $(MYLIB)
LIBS += $(RoccoRLIB)
GLIBS = $(ROOTGLIBS)



.PHONY: all clean

all: $(TARGET)

# $(CXX) $(LDFLAGS) $(OBJECTS) apps/run_objectSelection.C $(LIBS) -o $(TARGET)
$(TARGET): $(OBJECTS) apps/run_objectSelection.C
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) apps/run_objectSelection.C -o $(TARGET)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.C
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.C $(wildcard $(INC_DIR)/*.h)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.C $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)






