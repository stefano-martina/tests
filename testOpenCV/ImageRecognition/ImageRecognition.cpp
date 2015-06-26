#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
int main() {
  int ransacThresh = 10;
  double accumulateThresh = 0.8;
  double max_dist, min_dist, dist;
  char key;
  int i = 0;
  cv::Mat tmpFrame, currFrame, prevFrame;
  //cv::SiftFeatureDetector detector;
  //cv::StarFeatureDetector detector;
  //Ptr<FeatureDetector> detector = FeatureDetector::create("SIFT");
  cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create();
  cv::FlannBasedMatcher matcher;
  std::vector< cv::DMatch > matches;
  std::vector< cv::DMatch > good_matches;
  cv::Mat descriptorsVideo, descriptorsModel, H, Htmp;
  std::vector<cv::KeyPoint> keypointsVideo, keypointsModel;
  std::vector<cv::Point2f> obj;
  std::vector<cv::Point2f> scene;
  std::vector<cv::Point2f> obj_corners(4);
  std::vector<cv::Point2f> scene_corners(4);

  //initModules_nonfree();
  
  cv::namedWindow("Camera_Output", 1);
  cv::namedWindow("Model_Output", 1);
  cv::moveWindow("Model_Output", 800, 100);
  cv::Mat model = cv::imread("model.pgm", CV_LOAD_IMAGE_GRAYSCALE );

  detector->detect(model, keypointsModel);
  detector->compute(model, keypointsModel, descriptorsModel);
  cv::drawKeypoints(model, keypointsModel, model);

  cv::imshow("Model_Output", model);


  
  cv::VideoCapture capture(CV_CAP_ANY); //Capture using any camera connected to your system
  //VideoCapture capture(1); //Capture using any camera connected to your system
  if(!capture.isOpened()) {  // check if we succeeded
    return -1;
  }

  while(1) { //Create infinte loop for live streaming
    capture >> tmpFrame;
    cv::cvtColor(tmpFrame, currFrame, cv::COLOR_BGR2GRAY);

    detector->detect(currFrame, keypointsVideo);
    detector->compute(currFrame, keypointsVideo, descriptorsVideo);
    cv::drawKeypoints(tmpFrame, keypointsVideo, tmpFrame);
    //matches.clear();
    std::vector<cv::DMatch>().swap(matches);
    if((! descriptorsVideo.empty()) && (! descriptorsModel.empty())) {
      matcher.match( descriptorsModel, descriptorsVideo, matches );

      // max_dist = 0;
      // min_dist = 100;

      // //-- Quick calculation of max and min distances between keypoints
      // for(i = 0; i < descriptorsModel.rows; i++ ) {
      //   dist = matches[i].distance;
      //   if( dist < min_dist ) min_dist = dist;
      //   if( dist > max_dist ) max_dist = dist;
      // }

      //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
      //good_matches.clear();
      /*
      std::vector<cv::DMatch>().swap(good_matches);
      for(i = 0; i < descriptorsModel.rows; i++ ) {
        //if( matches[i].distance < 3*min_dist ) {
        if( matches[i].distance < distanceThresh ) {
          good_matches.push_back( matches[i]);
        }
      }
      */

      if(/*good_*/matches.size() > 0) {
        //std::cout << "good matches: " << good_matches.size() << std::endl;
        //-- Localize the object
        obj.clear();
        scene.clear();
        for(i = 0; i < /*good_*/matches.size(); i++ ) {
          //-- Get the keypoints from the good matches
          obj.push_back( keypointsModel[ /*good_*/matches[i].queryIdx ].pt );
          scene.push_back( keypointsVideo[ /*good_*/matches[i].trainIdx ].pt );
        }

        H = cv::findHomography( obj, scene, CV_RANSAC, ransacThresh );
        /*
        Htmp = cv::findHomography( obj, scene, CV_RANSAC, ransacThresh );
        if(H.empty()) {
          Htmp.copyTo(H);
        }
        cv::accumulateWeighted(Htmp, H, accumulateThresh);
        */

        if(! H.empty()) {
          //-- Get the corners from the image_1 ( the object to be "detected" )
          //std::vector<cv::Point2f> obj_corners(4);
          //obj_corners.clear();
          std::vector<cv::Point2f>(4).swap(obj_corners);
          obj_corners[0] = cv::Point2f(0,0);
          obj_corners[1] = cv::Point2f( model.cols, 0 );
          obj_corners[2] = cv::Point2f( model.cols, model.rows );
          obj_corners[3] = cv::Point2f( 0, model.rows );
          //std::vector<cv::Point2f> scene_corners(4);
          //scene_corners.clear();
          std::vector<cv::Point2f>(4).swap(scene_corners);
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

    key = cv::waitKey(10); //Capture Keyboard stroke
    if ((char(key) == 27) || (char(key) == 'q')){
      break; //If you hit ESC key loop will break.
    } else if ((char(key) == '+') && (ransacThresh < 255)) {
      ransacThresh ++;
      std::cout << "Distance threshold = " << ransacThresh << std::endl;
    } else if ((char(key) == '-') && (ransacThresh > 0)) {
      ransacThresh --;
      std::cout << "Distance threshold = " << ransacThresh << std::endl;
    } else if ((char(key) == ']') && (accumulateThresh < 255.)) {
      accumulateThresh += 0.1;
      std::cout << "Accumulate threshold = " << accumulateThresh << std::endl;
    } else if ((char(key) == '[') && (accumulateThresh > 0.)) {
      accumulateThresh -= 0.1;
      std::cout << "Accumulate threshold = " << accumulateThresh << std::endl;
    } else if (char(key) == 'p') {
      cv::imwrite("screenshot.pgm", currFrame);
    }
  }
  return 0;
}
