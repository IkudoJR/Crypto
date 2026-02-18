# Define compiler and assembler
CXX = g++
ASM = nasm

# Define compilation flags
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -lboost_filesystem -lboost_system

# Define target executable name
TARGET = cryptor

# Source files
ASM_SRC = crypto.asm
CPP_SRC = main.cpp

# Object files
OBJ = cryp.o main.o

# Default target
all: $(TARGET)

# Assemble the assembly file
cryp.o: $(ASM_SRC)
	$(ASM) -f elf64 $(ASM_SRC) -o cryp.o

# Compile the C++ file
main.o: $(CPP_SRC)
	$(CXX) $(CXXFLAGS) -c $(CPP_SRC) -o main.o

# Link both object files to create the final executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets (non-file targets)
.PHONY: all clean
