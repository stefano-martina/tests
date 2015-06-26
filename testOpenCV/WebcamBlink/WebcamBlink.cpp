#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
//using namespace cv;
//using namespace std;
//using namespace xfeatures2d;
char key;
int main() {
  int thresh = 100;
  float fps = 0.;
  std::stringstream stringThresh, stringFps;
  std::chrono::high_resolution_clock::time_point beginTime, endTime;
  int i = 0;
  cv::Mat tmpFrame, currFrame, prevFrame, outFrame;
  bool stoppedFrame = false;
  //cv::SiftFeatureDetector detector;
  //cv::StarFeatureDetector detector;
  //Ptr<FeatureDetector> detector = FeatureDetector::create("SIFT");
  cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create();
  std::vector<cv::KeyPoint> keypoints;

  //initModules_nonfree();
  
  cv::namedWindow("Diff_Output", 1); //Create window
  cv::namedWindow("Camera_Output", 1);
  cv::VideoCapture capture(CV_CAP_ANY); //Capture using any camera connected to your system
  //cv::VideoCapture capture(1); //Capture using any camera connected to your system
  if(!capture.isOpened()) {  // check if we succeeded
    return -1;
  }

  capture >> tmpFrame;
  cv::cvtColor(tmpFrame, prevFrame, cv::COLOR_BGR2GRAY);
  beginTime = std::chrono::high_resolution_clock::now();
  while(1) { //Create infinte loop for live streaming
    capture >> tmpFrame;
    cv::cvtColor(tmpFrame, currFrame, cv::COLOR_BGR2GRAY);
    cv::absdiff(prevFrame, currFrame, outFrame);
    cv::threshold(outFrame, outFrame, thresh, 255, cv::THRESH_BINARY); //THRESH_TOZERO);

    stringThresh.str(std::string());
    stringThresh.clear();
    stringThresh << "Tresh=" << thresh;
    cv::putText(tmpFrame, stringThresh.str(), cv::Point(0, 30),  cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255));

    stringFps.str(std::string());
    stringFps.clear();
    stringFps << "Fps=" << fps;
    cv::putText(tmpFrame, stringFps.str(), cv::Point(0, 60),  cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255));

    detector->detect(outFrame, keypoints);
    cv::drawKeypoints(tmpFrame, keypoints, tmpFrame);
    
    cv::imshow("Camera_Output", tmpFrame);
    cv::imshow("Diff_Output", outFrame); //Show image frames on created window
    if(!stoppedFrame) {
      prevFrame = currFrame.clone();
    }
    if(i++ == 100) {
      endTime = std::chrono::high_resolution_clock::now();
      fps = i/((float)std::chrono::duration_cast<std::chrono::milliseconds>(endTime-beginTime).count()/1000);
      beginTime = std::chrono::high_resolution_clock::now();
      i = 0;
    }
    
    key = cv::waitKey(10); //Capture Keyboard stroke
    if ((char(key) == 27) || (char(key) == 'q')){
      break; //If you hit ESC key loop will break.
    } else if ((char(key) == '+') && (thresh < 255)) {
      thresh ++;
    } else if ((char(key) == '-') && (thresh > 0)) {
      thresh --;
    } else if (char(key) == 's') {
      stoppedFrame = ! stoppedFrame;
    }
  }
  return 0;
}
