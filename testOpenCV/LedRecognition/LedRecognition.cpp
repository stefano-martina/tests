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
  double max_dist, min_dist, dist;
  std::stringstream stringThresh, stringFps;
  std::chrono::high_resolution_clock::time_point beginTime, endTime;
  int i = 0;
  cv::Mat tmpFrame, currFrame, prevFrame, outFrame;
  bool stoppedFrame = false;
  //cv::SiftFeatureDetector detector;
  //cv::StarFeatureDetector detector;
  //Ptr<FeatureDetector> detector = FeatureDetector::create("SIFT");
  cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create();
  cv::FlannBasedMatcher matcher;
  std::vector< cv::DMatch > matches;
  std::vector< cv::DMatch > good_matches;
  cv::Mat descriptorsVideo, descriptorsLeds;//, H;
  std::vector<cv::KeyPoint> keypointsVideo, keypointsLeds;
  std::vector<cv::Point2f> obj;
  std::vector<cv::Point2f> scene;
  //std::vector<cv::Point2f> obj_corners(4);
  //std::vector<cv::Point2f> scene_corners(4);

  //initModules_nonfree();
  
  cv::namedWindow("Diff_Output", 1); //Create window
  cv::namedWindow("Camera_Output", 1);
  cv::namedWindow("Leds_Output", 1);
  cv::Mat leds = cv::imread("leds.ppm", CV_LOAD_IMAGE_GRAYSCALE );

  detector->detect(leds, keypointsLeds);
  detector->compute(leds, keypointsLeds, descriptorsLeds);
  cv::drawKeypoints(leds, keypointsLeds, leds);

  cv::imshow("Leds_Output", leds);


  
  cv::VideoCapture capture(CV_CAP_ANY); //Capture using any camera connected to your system
  //VideoCapture capture(1); //Capture using any camera connected to your system
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

    detector->detect(outFrame, keypointsVideo);
    detector->compute(outFrame, keypointsVideo, descriptorsVideo);
    cv::drawKeypoints(tmpFrame, keypointsVideo, tmpFrame);
    matches.clear();
    if((! descriptorsVideo.empty()) && (! descriptorsLeds.empty())) {
      matcher.match( descriptorsLeds, descriptorsVideo, matches );

      max_dist = 0;
      min_dist = 100;

      //-- Quick calculation of max and min distances between keypoints
      for(i = 0; i < descriptorsLeds.rows; i++ ) {
        dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
      }

      //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
      good_matches.clear();
      for(i = 0; i < descriptorsLeds.rows; i++ ) {
        if( matches[i].distance < 3*min_dist ) {
          good_matches.push_back( matches[i]);
        }
      }

      if(good_matches.size() > 0) {
        //std::cout << "good matches: " << good_matches.size() << std::endl;
        //-- Localize the object
        obj.clear();
        scene.clear();
        for(i = 0; i < good_matches.size(); i++ ) {
          //-- Get the keypoints from the good matches
          obj.push_back( keypointsLeds[ good_matches[i].queryIdx ].pt );
          scene.push_back( keypointsVideo[ good_matches[i].trainIdx ].pt );
        }

        cv::Mat H = cv::findHomography( obj, scene, CV_RANSAC );

        if(! H.empty()) {
          //-- Get the corners from the image_1 ( the object to be "detected" )
          std::vector<cv::Point2f> obj_corners(4);
          //obj_corners.clear();
          obj_corners[0] = cv::Point2f(0,0);
          obj_corners[1] = cv::Point2f( leds.cols, 0 );
          obj_corners[2] = cv::Point2f( leds.cols, leds.rows );
          obj_corners[3] = cv::Point2f( 0, leds.rows );
          std::vector<cv::Point2f> scene_corners(4);
          //scene_corners.clear();
          //std::cout << "H rows:" << H.rows << "; cols:" << H.cols << std::endl;
          cv::perspectiveTransform( obj_corners, scene_corners, H);
          //-- Draw lines between the corners (the mapped object in the scene - image_2 )
          cv::line(tmpFrame, scene_corners[0], scene_corners[1], cv::Scalar(0, 255, 0), 4 );
          cv::line(tmpFrame, scene_corners[1], scene_corners[2], cv::Scalar(0, 255, 0), 4 );
          cv::line(tmpFrame, scene_corners[2], scene_corners[3], cv::Scalar(0, 255, 0), 4 );
          cv::line(tmpFrame, scene_corners[3], scene_corners[0], cv::Scalar(0, 255, 0), 4 );
        }
      }
    }
    
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
    } else if (char(key) == 'p') {
      cv::imwrite("test.ppm", outFrame);
    }
  }
  return 0;
}
