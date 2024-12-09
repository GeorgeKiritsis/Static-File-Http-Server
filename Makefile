# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -std=c++17 -I./HttpLogger -I./HttpParser -I./HttpRouter -I./HttpServer -I./Utils

# Output binary and object directory
TARGET := server
OBJDIR := bin

# Source files (automatically finds all .cpp files in directories)
SRC := main.cpp $(wildcard HttpLogger/*.cpp HttpParser/*.cpp HttpRouter/*.cpp HttpServer/*.cpp)
OBJ := $(SRC:%.cpp=$(OBJDIR)/%.o)

# Default rule to build the project
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

# Compile .cpp files into .o files in $(OBJDIR)
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)  # Ensure the subdirectory exists for the object file
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the server
exec: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	rm -rf $(OBJDIR) $(TARGET)
