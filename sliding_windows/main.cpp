#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Position.h"
#include "ImageSegment.h"
#include <stdint.h>
#include <vector>
#include <iostream>
#include <string>


using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	Mat image;
	image = imread("./testimg.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat modimage = imread("./testimg.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	if (!image.data)
	{
		std::cout << "Could not open or find the original image" << std::endl;
		return -1;
	}

	if (!modimage.data)
	{
		std::cout << "Could not open or find the mod image" << std::endl;
		return -1;
	}

	std::vector<cv::Mat> imageSegments = genImageSegments(modimage);
	cout << imageSegments.size() << endl;
	imshow("Original", image);
	for (int i = 0; i < imageSegments.size(); i++)
	{
		imshow("Image Segment", imageSegments[i]);
	}
	
	imwrite("imgseg1.jpg", imageSegments[0]);
	imwrite("imgseg2.jpg", imageSegments[1]);
	imwrite("imgseg3.jpg", imageSegments[2]);

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}