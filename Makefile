# Folder with '.hpp' files (declarations)
INCLUDE_DIR=./include

# Folder with '.cpp' files (definitions)
VPATH=./src

# Compilation flags
CXXFLAGS=-std=c++17 -Wall -I$(INCLUDE_DIR) #-Werror -O3

# Linked libraries
LINKFLAGS = -lX11 -lGL -lpthread -lpng -lstdc++fs -lm

# Files to be included
DEPENDENCIES=main.cpp olcPixelGameEngine.cpp ButtonGUI.cpp TextGUI.cpp FuncPloter.cpp

# Executable
TARGETS=func_ploter

build: $(TARGETS)

$(TARGETS): $(DEPENDENCIES)
	$(CXX) $(CXXFLAGS) -o $(TARGETS) $^ $(LINKFLAGS)

.PHONY: clean
clean:
	-rm -f $(TARGETS)
