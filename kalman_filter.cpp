#include <opencv2/opencv.hpp>

int main()
{
    // Kalman filter parameters
    int state_dim = 2;
    int measure_dim = 1;
    cv::KalmanFilter kf(state_dim, measure_dim, 0);

    // Initialize Kalman filter parameters
    cv::Mat state(state_dim, 1, CV_32F);
    cv::Mat measure(measure_dim, 1, CV_32F);
    // cv::setIdentity(), satırı ve sütunu eşit olan 
    // öğeler dışında dizinin tüm öğelerini 0'a ayarlar; 
    // bu öğeler 1'e (veya sağlanmışsa değere) ayarlanır.
    cv::setIdentity(kf.transitionMatrix);
    cv::setIdentity(kf.measurementMatrix);
    cv::setIdentity(kf.processNoiseCov, cv::Scalar::all(1e-5));
    cv::setIdentity(kf.measurementNoiseCov, cv::Scalar::all(1e-5));
    cv::setIdentity(kf.errorCovPost, cv::Scalar::all(1));

    //Random measurement ve control girdileri giriyoruz.
    // vermek istediğim görüntüyü muhtemelen burada girmeliyim.
    srand(time(NULL));
    float control_input = (float)(rand() % 100) / 100.0f;
    measure.at<float>(0) = (float)(rand() % 100) / 100.0f;

    // Update Kalman filter
    cv::Mat prediction = kf.predict();
    cv::Mat estimation = kf. correct(measure);

    return 0;
}