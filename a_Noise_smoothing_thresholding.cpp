#include </usr/include/opencv4/opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

const int max_value_H = 360/2;
const int max_value = 255;

int main()
{   
    string image_path1 = "/home/selman/Desktop/winter.jpg";
    string image_path2 = "";
    string image_path3 = "";

    Mat image1 = imread(image_path1,IMREAD_COLOR);
    resize(image1,image1,{500,500});

    if (image1.empty())
    {
        cout << "could not read the image: " << endl;
        return 1;
    }

    vector<int> lower_bound = { 170,80,50 };

    int low_H = lower_bound[0], low_S = lower_bound[1], low_V = lower_bound[2];
    int high_H = max_value_H, high_S = max_value, high_V = max_value;
    // additional matrix header 
    Mat hsvIMG, imgThreshold;

    cvtColor(image1, hsvIMG, COLOR_BGR2HSV);
    //detect the object based on HSV Range Values
    inRange(hsvIMG, Scalar(low_H,low_S,low_V), Scalar(high_H,high_S,high_V), imgThreshold);
    Mat medianBlurImg, gaussianBlurIMG;
    medianBlur(image1, medianBlurImg, 9);
    GaussianBlur(image1, gaussianBlurIMG, Size(1,1), 9, 9);

    imshow("Original Image", image1);
    imshow("Median Blurred Image", medianBlurImg);
    imshow("Gaussian Blur Image", gaussianBlurIMG);

    imshow("Original Image", image1);
    imshow("Hsv Image", hsvIMG);
    imshow("Threshold Image", imgThreshold);

    int k = waitKey(0);

    if (k == 'q'){
        destroyAllWindows();
    }
}