#include </usr/include/opencv4/opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    /*
    Bu örnek kod, 'VideoCapture' sınıfını kullanarak kamerayı açar. 
    Ardından, 'createBackgroundSubtractorMOG2()' fonksiyonunu kullanarak
    arka plan çıkarıcıyı oluşturur. Her karede 'apply()' yöntemi 
    kullanılarak arka plan çıkarılır ve 'imshow()' yöntemi kullanılarak 
    çıkarılmış arka plan gösterilir. Son olarak, kullanıcının ESC tuşuna 
    basması durumunda program sonlandırılır ve bellek serbest bırakılır.
    
    */
    // Open the camera
    VideoCapture cap(0); 
    
    // If the camera can't be opened, show an error message
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open the camera." << std::endl;
        return -1;
    }

    // Create the background subtractor
    Ptr<BackgroundSubtractor> pBackSub = createBackgroundSubtractorMOG2();

    Mat frame, fgMask;

    while (true)
    {
        // Capture the next frame
        cap >> frame;

        // If there is no data from the camera, break the loop
        if (frame.empty())
        {
            break;
        }

        // Subtract the background
        pBackSub->apply(frame, fgMask);

        // Show the extracted background
        imshow("Background", fgMask);

        // Exit the loop if the user presses the ESC key
        if (waitKey(25) == 27)
        {
            break;
        }
    }

    // Release the memory
    cap.release();
    destroyAllWindows();

    return 0;
}
