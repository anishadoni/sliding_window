#include "ImageSegment.h"
#include <iostream>
std::vector<pos2d> genObjectSegment(const cv::Mat& img, uint16_t rows, uint16_t cols)
{
	pos2d p1(0,0);
	pos2d p2(0,0);
	pos2d p3(0,0);
	pos2d p4(0,0);

	std::vector<pos2d> segmentPos;

	bool isBoxed = false;
	bool rightBound = false;
	bool leftBound = false;
	bool bottomBound = false;
	bool topBound = false;

	std::vector<pos2d> rBoundLine;
	std::vector<pos2d> lBoundLine;
	std::vector<pos2d> tBoundLine;
	std::vector<pos2d> bBoundLine;

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			// EDIT: add threshold value for "black"
			if (img.at<uint8_t>(r, c) == 0)
			{
				p1.r = r;
				p1.c = c;
				p2.r = r;
				p2.c = c;
				p3.r = r;
				p3.c = c;
				p4.r = r;
				p4.c = c;
				break;
			}
		}
	}

	rBoundLine.push_back(p1);
	lBoundLine.push_back(p2);
	tBoundLine.push_back(p3);
	bBoundLine.push_back(p4);

	while (isBoxed = false)
	{
		while (rightBound = false)
		{							 
			for (int i = 0; i < rBoundLine.size(); i++)
			{
				rBoundLine[i].c++;
				if (img.at<uint8_t>(rBoundLine[i].r, rBoundLine[i].c) == 0)
					rightBound = true;
			}
			tBoundLine.push_back(rBoundLine.back());
			bBoundLine.push_back(pos2d (bBoundLine[0].r, p1.c));									 
			for (pos2d& d : rBoundLine)			  
				d.c += 1;
		}
		while (bottomBound = false)
		{
			p2.r++;
			if (img.at<uint8_t>(p2.r, p2.c) != 0)
				bottomBound = true;
			rBoundLine.push_back(pos2d(p2.r, rBoundLine[0].c));
			lBoundLine.push_back(pos2d(p2.r, lBoundLine[0].c));
			for (pos2d& d : bBoundLine)
				d.r += 1;
		}
		while (leftBound = false)
		{
			p3.c--;								  // move ref point one column to the right
			if (img.at<uint8_t>(p3.r, p3.c) != 0) // if ref pixel is white, set rightBound to true
				leftBound = true;
			tBoundLine.insert(tBoundLine.begin(), pos2d (tBoundLine[0].r, p3.c));
			bBoundLine.insert(bBoundLine.begin(), pos2d (bBoundLine[0].r, p3.c));									  // extend top bounding line by 1 column to the right
			for (pos2d& d : lBoundLine)			  // move right bound line one column to the right
				d.c -= 1;
		}
		while (topBound = false)
		{
			p4.r--;								  // move ref point one column to the right
			if (img.at<uint8_t>(p4.r, p4.c) != 0) // if ref pixel is white, set rightBound to true
				topBound = true;
			rBoundLine.insert(rBoundLine.begin(), pos2d(p4.r, rBoundLine[0].c));
			lBoundLine.insert(lBoundLine.begin(), pos2d(p4.r, lBoundLine[0].c));									  // extend top bounding line by 1 column to the right
			for (pos2d& d : tBoundLine)			  // move right bound line one column to the right
				d.c -= 1;
		}
		if (rightBound && bottomBound && leftBound && rightBound == true)
			isBoxed = true;
	}

	// std::cout << "(," << rBoundLine[0].r << "," << rBoundLine[0
	segmentPos.reserve(rBoundLine.size() + bBoundLine.size() + lBoundLine.size() + tBoundLine.size());
	segmentPos = rBoundLine;
	segmentPos.insert(segmentPos.end(), bBoundLine.begin(), bBoundLine.end());
	segmentPos.insert(segmentPos.end(), lBoundLine.begin(), lBoundLine.end());
	segmentPos.insert(segmentPos.end(), tBoundLine.begin(), tBoundLine.end());
	
	return segmentPos;
}

