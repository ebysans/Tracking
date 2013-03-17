/* 
*	frame.cpp
*
*
*/

//#include "stdafx.h"
#include "frame.h"

using namespace cv;
using namespace std;

frame::frame(cv::Mat _rawFrame, cv::Mat _probMap)
	:rawFrame(_rawFrame), probMap(_probMap) {}

void frame::drawBoundingBox(Scalar color)
{
	for (std::list<Object>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		rectangle(rawFrame, Point(it->boundingBox.x, it->boundingBox.y), 
							Point(it->boundingBox.x + it->width, it->boundingBox.y + it->height), 
							color, 1, 8);
	}
}

void frame::getObjects()
{
	vector<vector<Point>> contours;
	findContours( probMap, contours, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	Rect objRect;
	
	for(int i = 0; i < contours.size(); i++)
	{	
		objRect = boundingRect(contours[i]);		
		objects.push_front(Object(objRect));	
	}
}

void frame::threshMap(int threshval)
{
	int maxVal = 255;
	threshold(probMap, probMap, threshval, maxVal, THRESH_BINARY);
}

void frame::openingBinMap(int iterations)
{
	cv::Mat kernel;
	kernel = getStructuringElement( MORPH_CROSS, Size(3, 3));
	dilate(probMap, probMap, kernel, cv::Point(-1,-1), iterations);
	erode(probMap, probMap, kernel, cv::Point(-1,-1), iterations);
}

void frame::closingBinMap(int iterations)
{
	cv::Mat kernel;
	kernel = getStructuringElement( MORPH_CROSS, Size(3, 3));
	dilate(probMap, probMap, kernel, cv::Point(-1,-1), iterations);
	erode(probMap, probMap, kernel, cv::Point(-1,-1), iterations);
}


/////////////////////////////////////////////// Private Functions //////////////////////////////////////////////////////

void frame::erodeBinMap(int iterations)
{
	cv::Mat kernel;
	kernel = getStructuringElement( MORPH_CROSS, Size(3, 3));
	erode(probMap, probMap, kernel, cv::Point(-1,-1), iterations);
}

void frame::dilateBinMap(int iterations)
{
	cv::Mat kernel;
	kernel = getStructuringElement( MORPH_CROSS, Size(3, 3));
	dilate(probMap, probMap, kernel, cv::Point(-1,-1), iterations);
}

/////////////////////////////////////////////// Showimage //////////////////////////////////////////////////////

void frame::showObjects()
{
	for (std::list<Object>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		it->info();
	}
}

void frame::showImageRaw(string windowID)
{
	namedWindow( windowID, CV_WINDOW_AUTOSIZE );		// Create a window for display.
    imshow( windowID, rawFrame );						// Show our image inside it.
}

void frame::showImageProbMap(string windowID)
{
	namedWindow( windowID, CV_WINDOW_AUTOSIZE );		// Create a window for display.
    imshow( windowID, probMap );						// Show our image inside it.
}




