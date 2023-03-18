#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

class ObjectTracker {
public:
    ObjectTracker(int width, int height);
    void initialize(Point2f intialPosition);
    void update(Mat frame);
private:
    KalmanFilter kf;
    Point2f position;
    Mat measure;
};

ObjectTracker::ObjectTracker(int width, int height){
    // Determine matrix dimensions required for Kalman filter

    int state_dim = 4;
    int measure_dim = 2;
    int control_dim = 0;

    // Create Kalman filter object
    kf = KalmanFilter(state_dim, measure_dim, control_dim);

    // Create measurement matrix
    this->measure = Mat(measure_dim, 1, CV_32F);

    // Set other parameters required for Kalman filter
    // ...

    /*
    setTransitionMatrix(const Mat& transMat) : geçiş matrisini ayarlar.
    setMeasurementMatrix(const Mat& measMat) : ölçüm matrisini ayarlar.
    setProcessNoiseCov(const Mat& covMat) : işlem gürültüsü kovaryans matrisini ayarlar.
    setMeasurementNoiseCov(const Mat& covMat) : ölçüm gürültüsü kovaryans matrisini ayarlar.
    setErrorCovPost(const Mat& covMat) : hata kovaryans matrisini ayarlar.
    setInitialState(const Mat& state) : filtreleme başlangıç durumunu ayarlar.
    Örneğin, işlem gürültüsü kovaryans matrisini 0.1 olarak ayarlamak için şu satır kullanılabilir:
    */

    // Initialize position to (0, 0)
    position = Point2d(0, 0);
}

void ObjectTracker::initialize(Point2f initialPosition){
    // Update initial position

    position = initialPosition;
    std::cout << "Position:(" << position << ")" << std::endl;

    // Set initial state for Kalman filter
    kf.statePost.at<float>(0, 0) = position.x;
    kf.statePost.at<float>(0, 0) = position.y;

    //...
    
    // Set initial covariance for Kalman filter
    // ...
    //this->measure = Mat::zeros(2, 1, CV_32F);
}

void ObjectTracker::update(Mat frame){
    // Update measurement matrix
    measure.at<float>(0, 0) = position.x;
    measure.at<float>(1, 0) = position.y;

    // Update Kalman filter
    Mat prediction = kf.predict();
    Mat corrected = kf.correct(measure);

    // Get filtered matrix and use as output
    //...
    // Update position
    position.x = corrected.at<float>(0,0);
    position.y = corrected.at<float>(0,0);

    // Show image and track object
    // ...
}
void onMouse(int event, int x, int y, int flags, void* param)
{
    if (event == EVENT_LBUTTONDOWN) // sol mouse tuşuna tıklandı
    {
        ObjectTracker* tracker = static_cast<ObjectTracker*>(param);
        tracker->initialize(Point2f(x, y));
        std::cout << "Left click has been made, Position:(" << x << "," << y << ")" << std::endl;
    }
}
int main()
{
    // Open video file
    VideoCapture cap("sample_video1.mp4");
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open the video file." << std::endl;
        return -1;
    }
    double fps = cap.get(CAP_PROP_FPS);
    // set fps
    // cap.set(cv::CAP_PROP_FPS, 1);

    // Create object tracker
    namedWindow("Tracking");
    ObjectTracker tracker(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));
    setMouseCallback("Tracking", onMouse, &tracker);
    while (true)
    {
        // Read the next frame from the video
        Mat frame;
        cap >> frame;
        // Stop the loop if the video is over
        if (frame.empty())
            break;

        // Track the object
        tracker.update(frame);
        // Get current frame time
        double t = cap.get(CAP_PROP_POS_MSEC) / 1000.0;

        // Draw FPS on frame
        std::stringstream ss;
        ss << "FPS: " << std::fixed << std::setprecision(1) << fps;
        putText(frame, ss.str(), Point(10, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2);

        // Show the frame with the tracked object
        imshow("Tracking", frame);

        // Exit if the Q key is pressed
        if (waitKey(30) == 'q')
            break;
    }

    // Release the video file
    cap.release();

    return 0;
}

// int main()
// {
//     // Open camera device
//     VideoCapture cap(0);
//     if (!cap.isOpened())
//     {
//         std::cerr << "Failed to open the camera." << std::endl;
//         return -1;
//     }
//     // std::cerr << "Biz burdayızz." << std::endl;
//     // if (cap.isOpened())
//     // {
//     //     std::cerr << "Opened the camera." << std::endl;
//     //     return -1;
//     // }
//     // Create object tracker

//     ObjectTracker tracker(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));


//     while (true)
//     {
//         // Read the camera image
//         Mat frame;
//         cap >> frame;

//         // Track the object
//         tracker.update(frame);

//         // Exit if the Q key is pressed
//         if (waitKey(1) == 'q')
//             break;
//     }

//     // Release the camera device
//     cap.release();

//     return 0;

// }