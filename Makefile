# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Source files for debug and release builds
DEBUG_SOURCES = debug/cartridgedebug.cpp debug/debugger.cpp debug/lookups.cpp
RELEASE_SOURCES = src/cartridge.cpp src/main.cpp src/lookups.cpp src/mmu.cpp src/cpu.cpp src/opcodes.cpp

# Debug build directories
DEBUG_DIR = debug
DEBUG_OBJECTS = $(DEBUG_SOURCES:.cpp=.o)
DEBUG_EXECUTABLE = $(DEBUG_DIR)/debug.exe

# Release build directories
RELEASE_DIR = src
RELEASE_OBJECTS = $(RELEASE_SOURCES:.cpp=.o)
RELEASE_EXECUTABLE = $(RELEASE_DIR)/release.exe

# Default target
all: debug release

# Debug build
debug: $(DEBUG_EXECUTABLE)

$(DEBUG_EXECUTABLE): $(DEBUG_OBJECTS)
	$(CXX) -o $@ $(DEBUG_OBJECTS)

$(DEBUG_DIR)/%.o: $(DEBUG_DIR)/%.cpp
	if not exist $(DEBUG_DIR) mkdir $(DEBUG_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Release build
release: $(RELEASE_EXECUTABLE)

$(RELEASE_EXECUTABLE): $(RELEASE_OBJECTS)
	$(CXX) -o $@ $(RELEASE_OBJECTS)

$(RELEASE_DIR)/%.o: $(RELEASE_DIR)/%.cpp
	if not exist $(RELEASE_DIR) mkdir $(RELEASE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Target to Remove Build Artifacts
clean:
	del /f /q $(DEBUG_DIR)\*.o $(DEBUG_DIR)\*.exe $(RELEASE_DIR)\*.o $(RELEASE_DIR)\*.exe

# Phony Targets
.PHONY: all clean debug release