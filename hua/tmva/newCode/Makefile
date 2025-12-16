# Name of the output executable
OUTPUT = my_program

# Compiler
CC = g++

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)

TMVALIBS = -lTMVA

# Local library path (updated)
MYLIB = -L/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/myLibrary/ -lcommenFunction

# WH (writeHistGood) directories for selection/weight consistency
WH_DIR = ../../../writeHistGood
WH_INC = -I$(WH_DIR)/include -I$(WH_DIR)
WH_OBJ = $(WH_DIR)/obj/commenSelectionAndWeight.o

# Compiler flags (optional)
CXXFLAGS = -O3 -Wall -fPIC -g -std=c++17
CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += $(WH_INC)

LIBS = $(ROOTLIBS)
LIBS += $(TMVALIBS)
LIBS += $(MYLIB)
LIBS += $(WH_OBJ)

# Source file
SOURCE = tmvaBDT_training.C

# Compile the source file to create the executable
$(OUTPUT): $(SOURCE)
	$(CC) $(CXXFLAGS) $(LIBS) -o $(OUTPUT) $(SOURCE)

# Clean up object files and the executable
clean:
	rm -f $(OUTPUT)

# Phony target to run the program
run: $(OUTPUT)
	./$(OUTPUT)
