#include "ImageSegment.h"
#include <stdint.h>
#include <iostream>

std::vector<pos2d> genObjectSegment(const cv::Mat& img)
{
	// pos2d 
	pos2d p1(0,0); // starting pixel for bounding box

	std::vector<pos2d> segmentPos;  // container for bounding box positions

	const int threshold_val = 100;

	bool isBoxed = false;
	bool rightBound = false;
	bool leftBound = false;
	bool bottomBound = false;
	bool topBound = false;

	bool start = false;

	std::vector<pos2d> rBoundLine;		// container for right bouding line
	std::vector<pos2d> lBoundLine;		// container for left bounding line
	std::vector<pos2d> tBoundLine;		// container for bottom bounding line
	std::vector<pos2d> bBoundLine;		// container for top bounding line


	// iterate through image and set p1 to position first detected black pixel
	for (int a = 0; (!start) && (a < img.rows); a++)
	{
		for (int b = 0; (!start) && (b < img.cols); b++)
		{
			if (img.at<uint8_t>(a, b) <= threshold_val)
			{
				p1.r = a;
				p1.c = b;
				start = true;
			}
		}
	}

	// init each bound line with starting pixel
	rBoundLine.push_back(p1); 
	lBoundLine.push_back(p1);
	tBoundLine.push_back(p1);
	bBoundLine.push_back(p1);


	// main loop for detecting if an object is segmented
	while (isBoxed == false)
	{
		// if rightBound is not true
		while (rightBound == false)
		{		
			rightBound = true;
			// loop through right bound line positions and increase column number by one. 
			for (int i = 0; i < rBoundLine.size(); i++)  // EDIT: possibly make more efficient. 
			{
				rBoundLine[i].c++;
				if (img.at<uint8_t>(rBoundLine[i].r, rBoundLine[i].c) <= threshold_val)
					rightBound = false;
			}
			/*for (int i = 0; i < rBoundLine.size(); i++)
			{
				if (img.at<uint8_t>(rBoundLine[i].r, rBoundLine[i].c) <= threshold_val)
				{
					rightBound = false;
					break;
				}
			}*/
			tBoundLine.push_back(rBoundLine.front());
			bBoundLine.push_back(rBoundLine.back());									 
		}

		while (bottomBound == false)
		{
			bottomBound = true;
			// loop through bottom bound line positions and increase row number by one. 
			for (int i = 0; i < bBoundLine.size(); i++)
			{
				bBoundLine[i].r++;
				if (img.at<uint8_t>(bBoundLine[i].r, bBoundLine[i].c) <= threshold_val)
					bottomBound = false;
			}	
			/*for (int i = 0; i < bBoundLine.size(); i++)
			{
				if (img.at<uint8_t>(bBoundLine[i].r, bBoundLine[i].c) <= threshold_val)
				{
					bottomBound = false; 
					break;
				}
			}*/
			rBoundLine.push_back(bBoundLine.back());
			lBoundLine.push_back(bBoundLine.front());
		}
		
		while (leftBound == false)
		{
			leftBound = true;
			// loop through left bound line positions and decrease column number by one. 
			for (int i = 0; i < lBoundLine.size(); i++)
			{
				lBoundLine[i].c--;
				if (img.at<uint8_t>(lBoundLine[i].r, lBoundLine[i].c) <= threshold_val)
					leftBound = false;
			}
		/*	for (int i = 0; i < lBoundLine.size(); i++)
			{
				if (img.at<uint8_t>(lBoundLine[i].r, lBoundLine[i].c) <= threshold_val)
				{
					leftBound = false;
					break;
				}	
			}*/
			tBoundLine.insert(tBoundLine.begin(), lBoundLine.front());
			bBoundLine.insert(bBoundLine.begin(), lBoundLine.back());									
		}

		while (topBound == false)
		{
			topBound = true;
			// loop through top bound line positions and decrease row number by one. 
			for (int i = 0; i < tBoundLine.size(); i++)
			{
				tBoundLine[i].r--;
				if (img.at<uint8_t>(tBoundLine[i].r, tBoundLine[i].c) <= threshold_val)
					topBound = false;
			}
			/*for (int i = 0; i < tBoundLine.size(); i++)
			{
				if (img.at<uint8_t>(tBoundLine[i].r, tBoundLine[i].c) <= threshold_val)
				{
					topBound = false;
					break;
				}		
			}*/
			rBoundLine.insert(rBoundLine.begin(), tBoundLine.back());
			lBoundLine.insert(lBoundLine.begin(), tBoundLine.front());									  
		}

		for (int i = 0; i < rBoundLine.size() && rightBound == true; i++)
		{
			if (img.at<uint8_t>(rBoundLine[i].r, rBoundLine[i].c) <= threshold_val)
				rightBound = false;
		}
		for (int i = 0; i < bBoundLine.size() && bottomBound == true; i++)
		{
			if (img.at<uint8_t>(bBoundLine[i].r, bBoundLine[i].c) <= threshold_val)
				bottomBound = false;
		}
		for (int i = 0; i < lBoundLine.size() && leftBound == true; i++)
		{
			if (img.at<uint8_t>(lBoundLine[i].r, lBoundLine[i].c) <= threshold_val)
				leftBound = false;
		}
		for (int i = 0; i < tBoundLine.size() && topBound == true; i++)
		{
			if (img.at<uint8_t>(tBoundLine[i].r, tBoundLine[i].c) <= threshold_val)
				topBound = false;
		}
		if (rightBound && bottomBound && leftBound && rightBound == true)
			isBoxed = true;
	}

	// delete duplicate pixel values

	rBoundLine.pop_back();
	lBoundLine.pop_back();
	rBoundLine.erase(rBoundLine.begin());
	lBoundLine.erase(lBoundLine.begin());
	std::cout << "(" << p1.r << "," << p1.c << ")" << std::endl;
	for (int i = 0; i < rBoundLine.size(); i++)
	{
		std::cout << "(" << rBoundLine[i].r << "," << rBoundLine[i].c << ")" << std::endl;
	}
	for (int i = 0; i < bBoundLine.size(); i++)
	{
		std::cout << "(" << bBoundLine[i].r << "," << bBoundLine[i].c << ")" << std::endl;
	}
	for (int i = 0; i < lBoundLine.size(); i++)
	{
		std::cout << "(" << lBoundLine[i].r << "," << lBoundLine[i].c << ")" << std::endl;
	}
	for (int i = 0; i < tBoundLine.size(); i++)
	{
		std::cout << "(" << tBoundLine[i].r << "," << tBoundLine[i].c << ")" << std::endl;
	}

	
	//segmentPos.reserve(rBoundLine.size() + bBoundLine.size() + lBoundLine.size() + tBoundLine.size());
	segmentPos = rBoundLine;
	segmentPos.insert(segmentPos.end(), bBoundLine.begin(), bBoundLine.end());
	segmentPos.insert(segmentPos.end(), lBoundLine.begin(), lBoundLine.end());
	segmentPos.insert(segmentPos.end(), tBoundLine.begin(), tBoundLine.end());
	
	return segmentPos;
}

pos2d operator + (pos2d a, pos2d b)
{
	pos2d c(0, 0);
	c.r = a.r + b.r;
	c.c = a.c + b.c;
	return c;
}