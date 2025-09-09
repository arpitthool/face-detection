// Include the standard input/output stream library for console operations
#include <iostream>
// Include the string class for string manipulation and handling
#include <string>
// Include the vector container class for dynamic arrays
#include <vector>
// Include the main OpenCV header that provides access to all OpenCV modules
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// method to show the image
void show_image(Mat image, string window_name) {
    imshow(window_name, image);
    waitKey(0);
}



// Main function - the entry point of the C++ program, returns an integer
int main() {
    // Begin a try-catch block to handle any exceptions that might occur during OpenCV operations
    try {
        // Create a 100x100 pixel image matrix with 3 channels (BGR color) and 8-bit unsigned integer data type
        // Mat::zeros() creates a matrix filled with zeros
        // CV_8UC3 means: 8-bit unsigned integer, 3 channels (Blue, Green, Red)
        Mat test_image = Mat::zeros(1000, 1000, CV_8UC3);

        // show the test image
        show_image(test_image, "Test Image");
        
        // Draw a green rectangle on the test image
        // Parameters: image, top-left corner (200,200), bottom-right corner (800,800), 
        // color (BGR format: 0=Blue, 255=Green, 0=Red), thickness=2 pixels
        rectangle(test_image, Point(200, 200), Point(800, 800), Scalar(0, 255, 0), 2);

        // show the test image
        show_image(test_image, "Test Image");
        
        // Draw a filled blue circle on the test image
        // Parameters: image, center point (50,50), radius=15 pixels,
        // color (BGR format: 255=Blue, 0=Green, 0=Red), thickness=-1 (filled circle)
        circle(test_image, Point(50, 50), 15, Scalar(255, 0, 0), -1);

        show_image(test_image, "Test Image");
        
        // Display the dimensions of the created test image
        // test_image.rows gives the height, test_image.cols gives the width
        cout << "✓ Test image created: " << test_image.rows << "x" << test_image.cols << " pixels" << endl;
        
        // Declare a new Mat object to store the grayscale version of the image
        Mat gray_image;
        
        // Convert the color image to grayscale using OpenCV's color conversion function
        // Parameters: source image, destination image, conversion code (BGR to GRAY)
        cvtColor(test_image, gray_image, COLOR_BGR2GRAY);

        show_image(gray_image, "Gray Image");
        
        // Declare a new Mat object to store the blurred version of the image
        Mat blurred;
        
        // Apply Gaussian blur filter to the test image
        // Parameters: source image, destination image, kernel size (25x25), sigma X=0 (auto-calculated)
        GaussianBlur(test_image, blurred, Size(25, 25), 0);

        show_image(blurred, "Blurred Image");
        
    // Catch block for OpenCV-specific exceptions
    // Exception is the base class for all OpenCV exceptions
    } catch (const Exception& e) {
        // Output error message to standard error stream (stderr) instead of stdout
        // e.what() returns a C-string describing the error
        cerr << "❌ OpenCV Error: " << e.what() << endl;
        
        // Return error code 1 to indicate program failure
        return 1;
        
    // Catch block for general C++ exceptions (fallback for non-OpenCV errors)
    // exception is the base class for all standard C++ exceptions
    } catch (const exception& e) {
        // Output error message to standard error stream
        cerr << "❌ General Error: " << e.what() << endl;
        
        // Return error code 1 to indicate program failure
        return 1;
    }
    
    // Return 0 to indicate successful program execution
    return 0;
}


