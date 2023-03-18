#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
void locator(int event, int x, int y, int flags, void* userdata){ //function to track mouse movement and click//
   if (event == EVENT_LBUTTONDOWN){ //when left button clicked//
      cout << "Left click has been made, Position:(" << x << "," << y << ")" << endl;
        }
//    } else if (event == EVENT_RBUTTONDOWN){ //when right button clicked//
//       cout << "Rightclick has been made, Position:(" << x << "," << y << ")" << endl;
//    } else if (event == EVENT_MBUTTONDOWN){ //when middle button clicked//
//       cout << "Middleclick has been made, Position:(" << x << "," << y << ")" << endl;
//    } else if (event == EVENT_MOUSEMOVE){ //when mouse pointer moves//
//       cout << "Current mouse position:(" << x << "," << y << ")" << endl;
//    }
}
int main() {
   Mat image = imread("winter.jpg");//loading image in the matrix//
   namedWindow("Track");//declaring window to show image//
   setMouseCallback("Track", locator, NULL);//Mouse callback function on define window//
    while (true)
    {
        // Show the frame with the tracked object
        imshow("Track", image);//showing image on the window//
        // Exit if the Q key is pressed
        if (waitKey(10) == 'q')
            break;
    }
   cout << "Burdayım" << endl;
   return 0;
}