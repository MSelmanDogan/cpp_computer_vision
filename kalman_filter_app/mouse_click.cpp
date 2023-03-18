#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Point2f selectedPoint = Point2f(-1,-1); // mouse tıklaması ile seçilen koordinat
bool pointSelected = false; // koordinatın seçilip seçilmediği bilgisi
bool paused = true; // video duraklatma durumu


// Mouse tıklaması ile koordinat seçimi işlemi
static void onMouse(int event, int x, int y, int, void*) {
    if (event == EVENT_LBUTTONDOWN) {
        selectedPoint.x = x;
        selectedPoint.y = y;
        pointSelected = true;
        paused = false;
    }
}
int main(int argc, char** argv)
{
    // Video açma işlemi
    VideoCapture cap("sample_video.mp4");

    // Hata kontrolü
    if (!cap.isOpened()) {
        cerr << "Error opening video file" << endl;
        return -1;
    }

    // İlk frame okunuyor
    Mat frame;
    cap >> frame;

    // Video penceresi açılıyor
    // namedWindow("Video Player", WINDOW_NORMAL);

    // Video boyutları
    int video_width = frame.size().width;
    int video_height = frame.size().height;


    // Mouse callback fonksiyonu tanımlanıyor
    setMouseCallback("Video Player", onMouse, 0);

    // Kalman Filtresi
    KalmanFilter KF(4, 2, 0);
    Mat_<float> state(4, 1); /* (x, y, Vx, Vy) */
    Mat_<float> measurement(2, 1); measurement.setTo(Scalar(0));
    KF.statePre.setTo(0);
    KF.statePre.at<float>(0) = selectedPoint.x;
    KF.statePre.at<float>(1) = selectedPoint.y;
    KF.transitionMatrix = (Mat_<float>(4, 4) << 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1);
    setIdentity(KF.measurementMatrix);
    setIdentity(KF.processNoiseCov, Scalar::all(1e-4));
    setIdentity(KF.measurementNoiseCov, Scalar::all(10));
    setIdentity(KF.errorCovPost, Scalar::all(1));

    // Kalman Filtresi sonuçlarının çizimi için renk tanımlamaları
    Scalar color(0, 255, 0);

    // FPS hesaplama için değişkenler
    int frame_count = 0;
    double t_start = 0;
    double fps = 0;

    while (true) {
        // Video duraklatılmış ise bekleniyor
        while (paused) {
            waitKey(10);
        }
        imshow("Tracking", frame);

        // FPS hesabı
        if (frame_count == 0) {
            t_start = (double)getTickCount();
        }
    }

}