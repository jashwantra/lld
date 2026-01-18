# --- Setup ---
CXX = g++
# Added -g for debugging and ensured all include paths are present
CXXFLAGS = -Wall -std=c++17 -I. -Ientities -Ienums -Iexceptions -Iobservers -Istates -Istrategies
TARGET = TicTacToeApp.exe

# --- File Discovery ---
# 1. Collect ALL source files from root and subfolders
# Using wildcard *.cpp will already include main.cpp and parkingLot.cpp
RAW_SRCS = $(wildcard *.cpp) \
           $(wildcard entities/*.cpp) \
           $(wildcard enums/*.cpp) \
		   $(wildcard exceptions/*.cpp) \
		   $(wildcard observers/*.cpp) \
		   $(wildcard states/*.cpp) \
           $(wildcard strategies/*.cpp)

# 2. Use 'sort' to remove any unintended duplicates if they occur
SRCS = $(sort $(RAW_SRCS))

# 3. Convert the list of .cpp files to .o files
OBJS = $(SRCS:.cpp=.o)

# --- Targets ---

# Default target
all: $(TARGET)

# Link the object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)
	@echo ------------------------------------------
	@echo Successfully built $(TARGET)
	@echo ------------------------------------------

# Rule to compile .cpp files to .o files
# The $< is the source file, $@ is the object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
# del /S /Q *.o will recursively find and delete all object files
clean:
	@echo Cleaning up...
	del /S /Q *.o
	if exist $(TARGET) del /Q $(TARGET)
	@echo Clean complete.