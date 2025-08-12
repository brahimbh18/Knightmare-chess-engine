# Chess Engine Makefile

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Directories
SRCDIR = .
PIECESDIR = Pieces
BUILDDIR = build

# Source files
SOURCES = main.cpp \
          Piece.cpp \
          Board.cpp \
          GameState.cpp \
          Helpers/Position.cpp \
          Helpers/MoveValidator.cpp \
          Helpers/MoveGenerator.cpp \
          Helpers/EngineAPI.cpp

# Object files in build directory
OBJECTS = $(addprefix $(BUILDDIR)/, $(SOURCES:.cpp=.o))

# Target executable in build directory
TARGET = $(BUILDDIR)/chess_engine
TEST_TARGET = $(BUILDDIR)/test_api

# Default target
all: $(TARGET)

# Ensure build directory exists
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Link the executable
$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Build test API program
$(TEST_TARGET): test_api.cpp $(filter-out build/main.o, $(OBJECTS)) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) test_api.cpp $(filter-out build/main.o, $(OBJECTS)) -o $(TEST_TARGET)

# Compile source files to object files in build directory
$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILDDIR)

# Run the program (example with FEN string)
run: $(TARGET)
	./$(TARGET) "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

# Test the API functions
test-api: $(TEST_TARGET)
	./$(TEST_TARGET)

# Quick tests of API
run-move: $(TARGET)
	@echo "Applying e2e4..."
	@./$(TARGET) >/dev/null || true

run-legal: $(TARGET)
	@echo "Listing legal moves for e2..."
	@./$(TARGET) >/dev/null || true

# Phony targets
.PHONY: all clean run test-api run-move run-legal 