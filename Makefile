CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
OPENCV_CFLAGS = `pkg-config --cflags opencv4`
OPENCV_LIBS = `pkg-config --libs opencv4`
TARGET = hello_world
SOURCE = hello_world.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(OPENCV_CFLAGS) -o $(TARGET) $(SOURCE) $(OPENCV_LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
