# Name of the output executable
OUTPUT = my_program

# Compiler
CC = g++

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)

TMVALIBS = -lTMVA

# MYLIB = -L/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/myLibrary/ -lcommenFunction
MYLIB = -L/workfs2/cms/huahuil/4topCode/CMSSW_10_6_20/src/FourTop/myLibrary/ -lcommenFunction
# Compiler flags (optional)
CXXFLAGS = -O3 -Wall -fPIC -g -std=c++17
CXXFLAGS += $(ROOTCFLAGS) 

LIBS = $(ROOTLIBS)
LIBS += $(TMVALIBS)
LIBS += $(MYLIB)

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
