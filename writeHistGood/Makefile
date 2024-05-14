
# PROGRAM = run_treeAnalyzer
PROGRAM = run_WH_forDataMC




TARGET = $(BIN_DIR)/$(PROGRAM).out

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


ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)

TMVALIBS = -lTMVA

MYLIB = -L/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/myLibrary/ -lcommenFunction


# Directories
HEADRDIR = .
SOURCE = src/


CXX = g++
# CXXFLAGS = -O3 -Wall -fPIC -g -std=c++17
CXXFLAGS = -O0 -Wall -fPIC -g -std=c++17 #lower optimization for debugging
LD = g++
# LDFLAGS = -O3 -Wall -g 
LDFLAGS = -O0 -Wall -g 
SOFLAGS = -shared
ARCHFLAGS =

#
CXXFLAGS += $(ROOTCFLAGS) -I$(HEADRDIR)
LIBS = $(ROOTLIBS)
LIBS += $(TMVALIBS)
LIBS += $(MYLIB)



.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) apps/$(PROGRAM).C
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) apps/$(PROGRAM).C -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.C $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
 

#------------------------------------------------------------------------
