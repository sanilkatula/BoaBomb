# Makefile for OpenGL application

# Compiler settings
CXX = clang++
CXXFLAGS = -framework OpenGL -framework GLUT -lglfw -lGLEW

# Target executable name
TARGET = play

# Source files
SOURCES = main.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

# To obtain object files
%.o: %.cpp
	$(CXX) -c $< -o $@

# To remove generated files
clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean