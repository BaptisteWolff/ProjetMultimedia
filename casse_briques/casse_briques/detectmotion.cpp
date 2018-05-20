#include "detectmotion.h"

#include "detectmotion.h"

DetectMotion::DetectMotion(int width, int height)
{
    frameWidth = width;
    frameHeight = height;

    subImageWidth= 1/3.2 * width;
    subImageHeight= 1/3.2 * height;
    templateWidth=1/12.8 * width;
    templateHeight=1/12.8 * height;

    workingRect = Rect((frameWidth-subImageWidth)/2,frameHeight/2+(frameHeight/2-subImageHeight)/2,subImageWidth,subImageHeight);
    templateRect = Rect((workingRect.width-templateWidth)/2,(workingRect.height-templateHeight)/2,templateWidth,templateHeight);
    workingCenter = Point(workingRect.x+subImageWidth/2,workingRect.y+subImageHeight/2);

    result_cols =  width-templateWidth  + 1;
    result_rows = height-templateHeight + 1;

    resultImage.create( result_cols, result_rows, CV_32FC1 );
}

DetectMotion::DetectMotion()
{

}

void DetectMotion::detect(Mat frame){
    // Get frame2
    frame2 = frame;
    // Mirror effect
    cv::flip(frame2,frame2,1);
    // Extract working rect in frame2 and convert to gray
    cv::cvtColor(Mat(frame2,workingRect),frameRect2,COLOR_BGR2GRAY);

    // Extract template image in frame1
    Mat templateImage(frameRect1,templateRect);
    // Do the Matching between the working rect in frame2 and the templateImage in frame1
    matchTemplate( frameRect2, templateImage, resultImage, TM_CCORR_NORMED );
    // Localize the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc);
    // Compute the translation vector between the origin and the matching rect
    vect = Point(maxLoc.x-templateRect.x,maxLoc.y-templateRect.y);

    // Draw green rectangle and the translation vector
    rectangle(frame2,workingRect,Scalar( 0, 255, 0),2);
    Point p(workingCenter.x+vect.x,workingCenter.y+vect.y);
    arrowedLine(frame2,workingCenter,p,Scalar(255,255,255),2);
    // Display frame2
    //imshow("WebCam", frame2);
    // Swap matrixes
    swap(frameRect1,frameRect2);
}

void DetectMotion::setFirstFrame(Mat frame)
{
    // Get frame1
    frame1 = frame.clone();
    // Mirror effect
    cv::flip(frame1,frame1,1);
    // Extract rect1 and convert to gray
    cv::cvtColor(Mat(frame1,workingRect),frameRect1,COLOR_BGR2GRAY);
}
