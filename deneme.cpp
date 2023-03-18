#include </usr/include/opencv4/opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // Load the image file
    Mat image = imread("image.jpg");

    // Check if the image was loaded successfully
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // Convert the image to grayscale
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // Display the original image and the grayscale image
    namedWindow("Original Image", WINDOW_NORMAL);
    imshow("Original Image", image);

    namedWindow("Grayscale Image", WINDOW_NORMAL);
    imshow("Grayscale Image", grayImage);

    // Wait for a key press
    waitKey(0);

    // Destroy the windows
    destroyAllWindows();

    return 0;
}
