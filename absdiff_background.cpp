#include <opencv2/opencv.hpp>


using namespace cv;

int main(int argc, char** argv)
{   
    /*
    Bu örnek kodda, "absdiff" fonksiyonu kullanılarak bir önceki kare
    ile mevcut kare arasındaki fark hesaplanır ve fark karesinin beyaz
    piksellerinin siyah piksellere oranı hesaplanarak bir sayaç değişkeni
    ile sayılır. Bu oran belirtilen threshold değerinin üzerindeyse,
    sayaç artırılır. Başlangıçta sayaç değişkeni sıfıra, threshold değeri 
    0.8'e ayarlanmıştır. Son olarak, program sonunda sayaç değişkeni 
    ekrana yazdırılır.
    */
    // Open the camera
    VideoCapture cap(0); 
    // cap.set(CAP_PROP_FORMAT, CV_32S);
    // If the camera can't be opened, show an error message
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open the camera." << std::endl;
        return -1;
    }

    // Create the background subtractor
    Ptr<BackgroundSubtractor> pBackSub = createBackgroundSubtractorMOG2();

    Mat frame, gray, fgMask, prevFrame, diffFrame;

    // Initialize the counter and threshold value
    int counter = 0;
    double threshold_value = 0.05;

    while (true)
    {
        // Capture the next frame
        cap >> frame;

        // If there is no data from the camera, break the loop
        if (frame.empty())
        {
            break;
        }
        // cvtColor(frame, gray, COLOR_BGR2GRAY);
        // Subtract the background
        pBackSub->apply(frame, fgMask);

        // Convert the foreground mask to grayscale
        // cvtColor(fgMask, fgMask, COLOR_BGR2GRAY);

        // Threshold the grayscale mask to create a binary mask
        threshold(fgMask, fgMask, 10, 100, THRESH_BINARY);

        // If this is not the first frame, calculate the white pixel ratio
        if (!prevFrame.empty())
        {
            absdiff(fgMask, prevFrame, diffFrame);
            double whitePixelRatio = (double) countNonZero(diffFrame) / (diffFrame.rows * diffFrame.cols);

            // If the white pixel ratio is above the threshold, increment the counter
            if (whitePixelRatio > threshold_value)
            {
                counter++;
            }
        }

        // Update the previous frame
        prevFrame = fgMask.clone();

        // Show the extracted background
        imshow("Background", fgMask);

        // Exit the loop if the user presses the ESC key
        if (waitKey(25) == 27)
        {
            break;
        }
    }

    // Print the final count
    std::cout << "Number of frames with high motion: " << counter << std::endl;

    // Release the memory
    cap.release();
    destroyAllWindows();

    return 0;
}
