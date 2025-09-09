#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    // image path
    string image_path = "/home/arpit/Downloads/profile-pic.jpeg";

    // read the image. Mat is a matrix of pixels.
    Mat image = imread(image_path);

    // Check if the image was loaded successfully
    if (image.empty()) {
        cout << "Error: Could not load image from " << image_path << endl;
        cout << "Please check if the file exists and is a valid image format." << endl;
        return -1;
    }

    // show the image
    imshow("Image", image); 

    // wait for a key to be pressed
    waitKey(0); 

    return 0;
}