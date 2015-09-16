#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <cv.h>
//#include <highgui.h>
using namespace cv;
using namespace std;
char key;
int main()
{
  namedWindow("Camera_Output", 1); //Create window
  VideoCapture capture(CV_CAP_ANY); //Capture using any camera connected to your system
  if(!capture.isOpened()) {  // check if we succeeded
    return -1;
  }

  //capture.set(CV_CAP_PROP_FPS,10);

  int i = 0;
  auto begin = std::chrono::high_resolution_clock::now();
  while(1){ //Create infinte loop for live streaming
    Mat frame;
    capture >> frame;
    imshow("Camera_Output", frame); //Show image frames on created window
    key = cvWaitKey(10); //Capture Keyboard stroke
    i ++;
    if (char(key) == 27){
      break; //If you hit ESC key loop will break.
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << i/((float)std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count()/1000) << " fps" << std::endl;

  //  cout << "FPS " << capture.get(CV_CAP_PROP_FPS) << endl;
  return 0;
}
