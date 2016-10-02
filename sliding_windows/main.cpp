#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Position.h"
#include "ImageSegment.h"
#include <stdint.h>
#include <iostream>


using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	Mat image;
	image = imread("testimg.jpg", IMREAD_GRAYSCALE);
	Mat modimage = imread("testimg.jpg", IMREAD_GRAYSCALE);

	if (!image.data)
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	std::vector<pos2d> segment = genObjectSegment(modimage, modimage.rows, modimage.cols);
	
	for (int i = 0; i < segment.size(); i++)
	{
		modimage.at<uint8_t>(segment[i].r, segment[i].c) = 0;
	}

	//for (int i = 0; i < modimage.cols; i++)
	//{
	//	modimage.at<uint8_t>(212, i) = 0;
	//}
	
	imshow("Original", image);
	imshow("Modified", modimage);

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}