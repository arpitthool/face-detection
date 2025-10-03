#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void showMenu(int faces_size, string menu_window_name) {
    // show the menu
    // we use Mat::zeros to create a black image, with height and width as input
    // CV_8UC3 means 3 channels (RGB) and 8 bits per channel
    // we use CV_8UC3 because we want to display the text in color
    string faces_detected =  to_string(faces_size) + ( faces_size == 1 ? " face detected" : " faces detected");
    Mat menu_image = Mat::zeros(300, 300, CV_8UC3);
    putText(menu_image, faces_detected, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
    putText(menu_image, "Menu", Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
    putText(menu_image, "Press H to show/hide hat", Point(10, 90), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
    putText(menu_image, "Press R to show/hide rectangles around faces", Point(10, 120), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
    putText(menu_image, "Press ESC or Q to quit", Point(10, 150), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
    imshow(menu_window_name, menu_image);
}

int main() {
    // VideoCapture is a class that captures video from a camera
    VideoCapture video(0);
    // we can also use a video file by passing the path to the video file
    // VideoCapture video("path/to/video.mp4");

    // check if the camera is opened
    if (!video.isOpened()) {
        cout << "Error: Could not open camera" << endl;
        return -1;
    }
    
    // declare the image
    Mat image;

    // we use the CascadeClassifier class to detect the faces. CascadeClassifier is a class that detects objects in an image 
    // using a cascade of classifiers.
    CascadeClassifier face_cascade;

    // load the face cascade classifier. The xml file is a pre-trained model that is used to detect faces. 
    // It contains a list of features that are used to detect faces.
    face_cascade.load("../haarcascade_frontalface_default.xml");

    // we initialize a vector of Rects to store the faces
    vector<Rect> faces;

    // Define the path to the overlay image file
    string overlay_image_path = "../images/hat.png";
    
    // Load the overlay image from the file
    // imread() reads an image file and stores it in memory, IMREAD_UNCHANGED means keep the image exactly as it is (including transparency if it's a PNG)
    Mat overlay_image_original = imread(overlay_image_path, IMREAD_UNCHANGED);

    bool show_overlay = false, show_rectangles = false;

    // create a window to show the overlay image
    string window_name = "Face Detection Window";
    namedWindow(window_name, WINDOW_NORMAL);

    // create a window to show the menu
    string menu_window_name = "Face Detection Menu Window";
    namedWindow(menu_window_name, WINDOW_NORMAL); 

    while (true) {
        // read the image from the video
        video >> image; // same as video.read(image);

        // detect the faces in the image. Here, 1.3 is the scale factor and 5 is the minNeighbors.
        // scaleFactor is the factor by which the image is scaled down at each level of the cascade.
        // minNeighbors is the minimum number of neighbors a candidate rectangle should have to be considered a face.
        face_cascade.detectMultiScale(image, faces, 1.3, 5);

        // draw the rectangle around the faces in the image
        for (Rect face : faces) {
            if (show_rectangles) {
                rectangle(image, face.tl(), face.br(), Scalar(0, 255, 0), 2);
            }

            if (show_overlay) {
                // overlayBGR will hold the overlay image without transparency (just colors)
                // mask will hold the transparency information (which parts are see-through)
                // overlay_image_resized will hold the resized overlay image
                Mat overlayBGR, mask, overlay_image_resized;
                
                // Resize the overlay image to match the face size
                int overlayWidth = face.width;
                int overlayHeight = face.height;
                // here INTER_AREA is the method used to resize to get the best quality
                resize(overlay_image_original, overlay_image_resized, Size(overlayWidth, overlayHeight), 0, 0, INTER_AREA);

                // PNG images can have transparent parts, JPEG images cannot
                // channels() == 4 means the image has 4 channels: Blue, Green, Red, and Alpha (transparency)
                if (overlay_image_resized.channels() == 4) {
                    
                    // Separate the colors from the transparency
                    // cvtColor() converts the image format
                    // COLOR_BGRA2BGR removes the transparency channel, keeping only Blue, Green, Red
                    cvtColor(overlay_image_resized, overlayBGR, COLOR_BGRA2BGR);
                    
                    // split() separates the image into individual color channels
                    // channels[0] = Blue, channels[1] = Green, channels[2] = Red, channels[3] = Alpha (transparency)
                    vector<Mat> channels;
                    split(overlay_image_resized, channels);
                    
                    // Get the transparency information as mask
                    mask = channels[3];
                    
                } else {
                    // If the image doesn't have transparency, use it as is, (ex: JPEG images)
                    overlayBGR = overlay_image_resized;
                    
                    // Create a mask from a grayscale version
                    // Since there's no transparency, we make everything visible (no transparent parts)
                    cvtColor(overlayBGR, mask, COLOR_BGR2GRAY);
                }
                
                // Calculate where to place the overlay on the face : above the face
                int x = face.tl().x;                    //  x position = face's left edge
                int y = face.tl().y - (overlayHeight);  //  y position = above the face (face top minus overlay height)

                // We need to check if the overlay would go outside the camera view
                if (x >= 0 &&  overlayWidth >= 0 && x + overlayWidth <= image.cols && y >= 0 && overlayHeight >= 0 && y + overlayHeight <= image.rows) { // TODO: debug why this is not working
                    
                    // Create a region of interest (ROI) on the camera image
                    // This is the area on the camera image where we'll place the overlay
                    Mat region = image(Rect(x, y, overlayWidth, overlayHeight));
                    
                    // Place the overlay on the camera image using the transparency mask
                    // copyTo() copies the overlay image to the camera image
                    // The mask tells it which parts of the overlay are transparent (don't copy those parts)
                    overlayBGR.copyTo(region, mask);
                }
            }
        }

        // show the number of faces detected on the image along with the menu
        showMenu(faces.size(), menu_window_name);

        // show the image
        imshow(window_name, image);

        // wait for 20ms and check if a key is pressed
        char key = waitKey(40);
        
        // Exit if 'q' is pressed or window is closed
        if (key == 'q' || key == 'Q' || key == 27) { // 27 is ESC key
            cout << "Exiting..." << endl;
            break;
        } else if (key == 'h' || key == 'H') { // 'h' for hat
            show_overlay = !show_overlay;
        } else if (key == 'r' || key == 'R') { // 'r' for rectangles
            show_rectangles = !show_rectangles;
        }
    }

    return 0;
}