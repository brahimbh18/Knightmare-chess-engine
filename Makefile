# Chess Engine Makefile

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude

# Directories
SRCDIR = src
BUILDDIR = build

# Find all source files in src/ (recursively)
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

# Test target
TEST_SRC = tests/test_api.cpp
TEST_OBJ = $(patsubst %.cpp, $(BUILDDIR)/%.o, $(TEST_SRC))
TEST_TARGET = $(BUILDDIR)/test_api

# Default target
all: $(TEST_TARGET)

# Ensure build directory exists
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Build the test executable
$(TEST_TARGET): $(OBJECTS) $(TEST_OBJ) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(TEST_OBJ) -o $(TEST_TARGET)

# Compile .cpp to .o (mirror folder structure inside build/)
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile tests separately
$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILDDIR)

# Run the tests
test-api: $(TEST_TARGET)
	./$(TEST_TARGET)

.PHONY: all clean test-api
