CC := g++

# Compiler flags
ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)
CXXFLAGS = -O3 -Wall -fPIC -g -std=c++17
CXXFLAGS += $(ROOTCFLAGS)
LIBS = $(ROOTLIBS)

# Source files
SOURCES := commenFunction.C

# Object files
# OBJECTS := $(SOURCES:.cpp=.o)
OBJECTS := $(SOURCES:.C=.o)

# Output library name
LIBRARY := libcommenFunction.so

# Default target
all: $(LIBRARY)

# Compile object files
%.o: %.C
	$(CC) $(CXXFLAGS) -c $< -o $@

# Link the shared library
$(LIBRARY): $(OBJECTS)
	$(CC) $(CXXFLAGS) $(LIBS) -shared $(OBJECTS) -o $(LIBRARY)

# Clean the generated files
clean:
	rm -f $(OBJECTS) $(LIBRARY)