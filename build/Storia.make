# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g

# Automatically find all .cpp files in the src directory
SOURCES = $(wildcard src/*.cpp) main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Define the output directory
OUTPUT_DIR = ../bin/Release

# Define the final executable
TARGET = $(OUTPUT_DIR)/Storia.exe

# Ensure the output directory exists (Windows-compatible with forward slashes)
$(OUTPUT_DIR):
	if not exist "$(OUTPUT_DIR)" mkdir "$(OUTPUT_DIR)"

# Default target to build the executable
all: $(OUTPUT_DIR) $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."  # Debugging message
	$(CXX) $(OBJECTS) -o $(TARGET)  # Tab indentation is required here

# Compile source files into object files
%.o: %.cpp
	@echo "Compiling $<..."  # Debugging message
	$(CXX) $(CXXFLAGS) -c $< -o $@  # Tab indentation is required here

# Clean up generated files
clean:
	del /f $(OBJECTS) $(TARGET)  # Windows-compatible clean command
