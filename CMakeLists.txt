cmake_minimum_required(VERSION 3.10)
project(FaceDetection)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable for OpenCV test
add_executable(test_opencv test_opencv.cpp)

# Link OpenCV libraries
target_link_libraries(test_opencv ${OpenCV_LIBS})

# Add executable for face detection (will be created later)
# add_executable(face_detection face_detection.cpp)
# target_link_libraries(face_detection ${OpenCV_LIBS})

