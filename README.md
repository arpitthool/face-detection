# Face Detection C++ App

A C++ application for detecting faces in images using OpenCV. Currently includes an OpenCV installation verification program.

## Requirements

- OpenCV 4.x
- CMake 3.10+
- C++11 compatible compiler (g++, clang++, etc.)

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Running

```bash
cd build
./hello_world
```

## What it does

The `hello_world` program verifies OpenCV installation by:
- Creating test images with geometric shapes
- Testing color conversion (BGR to grayscale)
- Applying Gaussian blur filters
- Displaying results in separate windows

## Planned Features

- Detect single or multiple faces in images
- Real-time face detection from webcam
- Support for common image formats (jpg, png, etc.)

## Project Structure

- `hello_world.cpp` - OpenCV verification program
- `CMakeLists.txt` - CMake build configuration
- `README.md` - This file
