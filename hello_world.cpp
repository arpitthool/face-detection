// Include the standard input/output stream library for console operations
#include <iostream>
// Include the string class for string manipulation and handling
#include <string>
// Include the vector container class for dynamic arrays
#include <vector>
// Include the main OpenCV header that provides access to all OpenCV modules
#include <opencv2/opencv.hpp>

// method to show the image
void show_image(cv::Mat image, std::string window_name) {
    cv::imshow(window_name, image);
    cv::waitKey(0);
}



// Main function - the entry point of the C++ program, returns an integer
int main() {
    // Output a header message to the console using the stream insertion operator
    std::cout << "=== OpenCV Installation Verification ===" << std::endl;
    
    // Display the OpenCV version by accessing the CV_VERSION macro defined in OpenCV headers
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    
    // Begin a try-catch block to handle any exceptions that might occur during OpenCV operations
    try {
        // Create a 100x100 pixel image matrix with 3 channels (BGR color) and 8-bit unsigned integer data type
        // cv::Mat::zeros() creates a matrix filled with zeros
        // CV_8UC3 means: 8-bit unsigned integer, 3 channels (Blue, Green, Red)
        cv::Mat test_image = cv::Mat::zeros(1000, 1000, CV_8UC3);

        // Output a success message indicating that the test image is working
        std::cout << "✓ Test image created" << std::endl;

        // show the test image
        show_image(test_image, "Test Image");
        
        // Draw a green rectangle on the test image
        // Parameters: image, top-left corner (20,20), bottom-right corner (80,80), 
        // color (BGR format: 0=Blue, 255=Green, 0=Red), thickness=2 pixels
        cv::rectangle(test_image, cv::Point(200, 200), cv::Point(800, 800), cv::Scalar(0, 255, 0), 2);

        // show the test image
        show_image(test_image, "Test Image");
        
        // Draw a filled blue circle on the test image
        // Parameters: image, center point (50,50), radius=15 pixels,
        // color (BGR format: 255=Blue, 0=Green, 0=Red), thickness=-1 (filled circle)
        cv::circle(test_image, cv::Point(50, 50), 15, cv::Scalar(255, 0, 0), -1);

        show_image(test_image, "Test Image");
        
        // Output a success message indicating that matrix operations are working
        std::cout << "✓ OpenCV matrix operations working" << std::endl;
        
        // Display the dimensions of the created test image
        // test_image.rows gives the height, test_image.cols gives the width
        std::cout << "✓ Test image created: " << test_image.rows << "x" << test_image.cols << " pixels" << std::endl;
        
        // Declare a new Mat object to store the grayscale version of the image
        cv::Mat gray_image;
        
        // Convert the color image to grayscale using OpenCV's color conversion function
        // Parameters: source image, destination image, conversion code (BGR to GRAY)
        cv::cvtColor(test_image, gray_image, cv::COLOR_BGR2GRAY);

        show_image(gray_image, "Gray Image");

        
        // Output a success message indicating that color conversion is working
        std::cout << "✓ Color conversion working" << std::endl;
        
        // Declare a new Mat object to store the blurred version of the image
        cv::Mat blurred;
        
        // Apply Gaussian blur filter to the test image
        // Parameters: source image, destination image, kernel size (5x5), sigma X=0 (auto-calculated)
        cv::GaussianBlur(test_image, blurred, cv::Size(25, 25), 0);

        show_image(blurred, "Blurred Image");

        
        // Output a success message indicating that Gaussian blur is working
        std::cout << "✓ Gaussian blur working" << std::endl;
        
        // Output a final success message with an emoji to indicate OpenCV is working properly
        std::cout << "\n🎉 OpenCV is properly installed and working!" << std::endl;
        
    // Catch block for OpenCV-specific exceptions
    // cv::Exception is the base class for all OpenCV exceptions
    } catch (const cv::Exception& e) {
        // Output error message to standard error stream (stderr) instead of stdout
        // e.what() returns a C-string describing the error
        std::cerr << "❌ OpenCV Error: " << e.what() << std::endl;
        
        // Return error code 1 to indicate program failure
        return 1;
        
    // Catch block for general C++ exceptions (fallback for non-OpenCV errors)
    // std::exception is the base class for all standard C++ exceptions
    } catch (const std::exception& e) {
        // Output error message to standard error stream
        std::cerr << "❌ General Error: " << e.what() << std::endl;
        
        // Return error code 1 to indicate program failure
        return 1;
    }
    
    // Return 0 to indicate successful program execution
    return 0;
}


