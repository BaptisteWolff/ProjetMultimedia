#ifndef DETECTMOTION_H
#define DETECTMOTION_H

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;


class DetectMotion
{
public:
    DetectMotion(int width, int height);
    DetectMotion();
    void detect(Mat frame);
    Mat getFrame(){return frame2;}
    void setFirstFrame(Mat frame);
    //Point getVect(){return vect;}

private:
    int frameWidth=320;
    int frameHeight=240;
    int subImageWidth=100;
    int subImageHeight=100;
    int templateWidth=25;
    int templateHeight=25;
    Rect workingRect = Rect((frameWidth-subImageWidth)/2,frameHeight/2+(frameHeight/2-subImageHeight)/2,subImageWidth,subImageHeight);
    Rect templateRect = Rect((workingRect.width-templateWidth)/2,(workingRect.height-templateHeight)/2,templateWidth,templateHeight);
    Point workingCenter = Point(workingRect.x+subImageWidth/2,workingRect.y+subImageHeight/2);

    Mat frame1,frame2,frameRect1,frameRect2;

    // Create the matchTemplate image result
    Mat resultImage;    // to store the matchTemplate result
    int result_cols =  frame1.cols-templateWidth  + 1;
    int result_rows = frame1.rows-templateHeight + 1;

    // result
    //Point vect;
};

#endif // DETECTMOTION_H
