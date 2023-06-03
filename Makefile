# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Executable name
TARGET = game

# Source files
SRCS = main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Default rule
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(SFML_LIBS)

# Rule to compile source files
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build
clean:
	rm -f $(OBJS) $(TARGET)
