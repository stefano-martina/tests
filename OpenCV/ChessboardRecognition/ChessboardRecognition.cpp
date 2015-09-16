#include <iostream>
#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/xfeatures2d/nonfree.hpp>
int main() {
  char key;
  int i = 0;
  int j = 0;
  bool boardFound = false;
  cv::Mat currFrame;
  std::vector<cv::Point2f> boardCorners;
  
  cv::namedWindow("Camera_Output", 1);

  //cv::VideoCapture capture(CV_CAP_ANY); //Capture using any camera connected to your system
  cv::VideoCapture capture(1); //Capture using any camera connected to your system
  if(!capture.isOpened()) {  // check if we succeeded
    return -1;
  }

  while(1) { //Create infinte loop for live streaming
    capture >> currFrame;

    bool boardFound = findChessboardCorners(currFrame, cv::Size(5,7), boardCorners, CV_CALIB_CB_ADAPTIVE_THRESH );

    if (boardFound) {
      for(i=0, j=1; j<boardCorners.size(); ++i, ++j) {
        cv::line(currFrame, boardCorners[i], boardCorners[j], cv::Scalar(0, 255, 0), 4);
      }
    }
    
    cv::imshow("Camera_Output", currFrame);

    key = cv::waitKey(10); //Capture Keyboard stroke
    if ((char(key) == 27) || (char(key) == 'q')){
      break; //If you hit ESC key loop will break.
    }
  }
  return 0;
}
