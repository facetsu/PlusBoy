# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++20

# Source files
SOURCES = cartridgedebug.cpp debugger.cpp lookups.cpp

# Debug build directories
DEBUG_DIR = debug
DEBUG_OBJECTS = $(addprefix $(DEBUG_DIR)/, $(SOURCES:.cpp=.o))
DEBUG_EXECUTABLE = $(DEBUG_DIR)/debug.exe

# Release build directories
RELEASE_DIR = src
RELEASE_OBJECTS = $(addprefix $(RELEASE_DIR)/, $(SOURCES:.cpp=.o))
RELEASE_EXECUTABLE = $(RELEASE_DIR)/release.exe

# Default target
all: debug release

# Debug build
debug: $(DEBUG_EXECUTABLE)

$(DEBUG_EXECUTABLE): $(DEBUG_OBJECTS)
	$(CXX) -o $@ $(DEBUG_OBJECTS)

$(DEBUG_DIR)/%.o: %.cpp
	@mkdir -p $(DEBUG_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Release build
release: $(RELEASE_EXECUTABLE)

$(RELEASE_EXECUTABLE): $(RELEASE_OBJECTS)
	$(CXX) -o $@ $(RELEASE_OBJECTS)

$(RELEASE_DIR)/%.o: %.cpp
	@mkdir -p $(RELEASE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Target to Remove Build Artifacts
clean:
	del /f /q $(DEBUG_DIR)\*.o $(DEBUG_DIR)\*.exe $(RELEASE_DIR)\*.o $(RELEASE_DIR)\*.exe

# Phony Targets
.PHONY: all clean debug release