#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    
    // Test basic OpenCV functionality
    cv::Mat test_image = cv::Mat::zeros(100, 100, CV_8UC3);
    test_image.setTo(cv::Scalar(255, 0, 0)); // Blue image
    
    if (test_image.empty()) {
        std::cerr << "Error: Could not create test image" << std::endl;
        return -1;
    }
    
    std::cout << "OpenCV test successful!" << std::endl;
    std::cout << "Image size: " << test_image.rows << "x" << test_image.cols << std::endl;
    
    return 0;
}

