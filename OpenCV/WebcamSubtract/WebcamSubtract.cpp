#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <queue>

using namespace std;
char key;
int main()
{
  cvNamedWindow("Camera_Output", 1); //Create window
  CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY); //Capture using any camera connected to your system
  IplImage* frame;
  IplImage* prevFrame = NULL;
  IplImage* subtFrame;
  bool stopFrame = false;
  queue<IplImage*> prevFrames;
  unsigned int desiredSize = 10;
  CvFont font;
  double hScale=1.0;
  double vScale=1.0;
  int    lineWidth=1;

  stringstream stringStreamDelay;
  
  cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);
  

  for(int i=0; i<desiredSize; ++i) {
    prevFrames.push(cvCloneImage(cvQueryFrame(capture)));
  }
  
  //prevFrame = prevFrames.front();
  //prevFrames.pop();
  subtFrame = cvCloneImage(prevFrames.front());
  while(1){ //Create infinte loop for live streaming
    frame = cvQueryFrame(capture); //Create image frames from capture
    if((stopFrame == false) || (prevFrame == NULL)) {
      cvSub(prevFrames.front(), frame, subtFrame);
    } else {
      cvSub(prevFrame, frame, subtFrame);
    }

    stringStreamDelay.str( std::string() );
    stringStreamDelay.clear();
    stringStreamDelay << "Delay " << desiredSize;
    cvPutText(subtFrame, stringStreamDelay.str().c_str(), cvPoint(0, 30), &font, cvScalar(255,255,255));
    cvShowImage("Camera_Output", subtFrame); //Show image frames on created window

    prevFrames.push(cvCloneImage(frame));
    while(prevFrames.size() > desiredSize) {
      if((stopFrame == false) && (prevFrame != NULL)) {
        cvReleaseImage(&prevFrame);
        prevFrame = NULL;
      }else if((stopFrame == true) && (prevFrame == NULL)) {
        prevFrame = cvCloneImage(prevFrames.front());
      }
      cvReleaseImage(&prevFrames.front());
      prevFrames.pop();
    }
    
    key = cvWaitKey(10); //Capture Keyboard stroke
    if (char(key) == 27 || char(key) == 'q'){
      break; //If you hit ESC key loop will break.
    } else if (char(key) == 's'){
      stopFrame = ! stopFrame;
    } else if (char(key) == '+'){
      desiredSize ++;
    } else if (char(key) == '-'){
      if(desiredSize > 1) {
        desiredSize --;
      }
    }
  }
  cvReleaseCapture(&capture); //Release capture.
  cvDestroyWindow("Camera_Output"); //Destroy Window
  return 0;
}
