#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
    string image_path1 = "/home/selman/Desktop/ss.png";
    string image_path2 = "/home/selman/Desktop/winter.jpg";
    string image_path3 = "/home/selman/Desktop/sid_wallpaper.jpg";
    string image_path4 = "/home/selman/Desktop/winter2.png";
    string image_path5 = "/home/selman/Desktop/winter3.png";
    // resize fonksiyonu oluştur.
    Mat image1 = imread(image_path1, IMREAD_COLOR);
    resize(image1, image1, { 500,500 }, 0,0, cv::INTER_NEAREST);
    Mat image2 = imread(image_path2, IMREAD_COLOR);
    resize(image2, image2, { 500,500 }, 0,0, cv::INTER_NEAREST);
    Mat image3 = imread(image_path3, IMREAD_COLOR);
    resize(image3, image3, { 500,500 }, 0,0, cv::INTER_NEAREST);
    Mat image4 = imread(image_path4, IMREAD_COLOR);
    resize(image4, image4, { 500,500 }, 0,0, cv::INTER_NEAREST);
    Mat image5 = imread(image_path5, IMREAD_COLOR);
    resize(image5, image5, { 500,500 }, 0,0, cv::INTER_NEAREST);

    MatND histogram;
    int histSize = 256;
    const int* channel_numbers = { 0 };
    float channel_range[] = { 0.0, 256.0};
    const float* ranges[] = { channel_range };
    int number_bins = histSize;

    cvtColor(image3,image3,cv::COLOR_BGR2GRAY);
    calcHist(&image3, 1, 0, Mat(), histogram, 1, &number_bins, ranges);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
    normalize(histogram, histogram, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    for (int i = 1; i < histSize; i++){
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
        Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))),
        Scalar(255, 0, 0), 2, 8, 0);
    }

    MatND histogram2;
    cv::cvtColor(image5,image5, COLOR_BGR2GRAY);
    calcHist(&image5, 1, 0, Mat(), histogram2, 1, &number_bins, ranges);

    Mat histImage2(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    normalize(histogram2, histogram2, 0, histImage2.rows, NORM_MINMAX, -1, Mat());
    for (int i = 1; i < histSize; i++){

        line(histImage2, Point(bin_w * (i - 1), hist_h - cvRound(histogram2.at<float>(i - 1))),
        Point(bin_w * (i), hist_h - cvRound(histogram2.at<float>(i))),
        Scalar(255, 0, 0), 2, 8, 0);
    }
    
    double histMatchingCorrelation = compareHist(histogram, histogram2, HISTCMP_CORREL);
    double histMatchingChiSquare = compareHist(histogram, histogram2, HISTCMP_CHISQR);
    double histMatchingIntersect = compareHist(histogram, histogram2, HISTCMP_INTERSECT);
    double histMatchingBhattacharyya = compareHist(histogram, histogram2, HISTCMP_BHATTACHARYYA);
    /*
    imshow("Source image 1", image3);
    imshow("CalcHist 1", histImage);
    imshow("Source image 2", image5);
    imshow("CalcHist 2", histImage2);
    waitKey();
    */
    
    Mat histEqualized;
    cvtColor(image4, image4, COLOR_BGR2GRAY);
    equalizeHist(image4, histEqualized);
    imshow("Source image", image4);
    imshow("calcHist Demo", histEqualized);
    waitKey();


}