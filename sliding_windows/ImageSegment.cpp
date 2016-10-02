#include "ImageSegment.h"
#include <iostream>
std::vector<pos2d> genObjectSegment(const cv::Mat& img, uint16_t rows, uint16_t cols)
{
	pos2d p1(0,0);

	std::vector<pos2d> segmentPos;

	const int threshold_val = 12;

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
			if (img.at<uint8_t>(r, c) <= threshold_val)
			{
				p1.r = r;
				p1.c = c;
				break;
			}
		}
	}

	rBoundLine.push_back(p1); //Adds element at end of vector with value p1
	lBoundLine.push_back(p1);
	tBoundLine.push_back(p1);
	bBoundLine.push_back(p1);

	while (isBoxed == false)
	{
		while (rightBound == false)
		{							 
			for (int i = 0; i < rBoundLine.size(); i++)
			{
				rBoundLine[i].c++;
				if (img.at<uint8_t>(rBoundLine[i].r, rBoundLine[i].c) > threshold_val)
					rightBound = true;
			}
			tBoundLine.push_back(rBoundLine.front());
			bBoundLine.push_back(rBoundLine.back());									 
		}

		while (bottomBound == false)
		{
			for (int i = 0; i < bBoundLine.size(); i++)
			{
				bBoundLine[i].r++;
				if (img.at<uint8_t>(bBoundLine[i].r, bBoundLine[i].c) > threshold_val)
				bottomBound = true;
		}
			rBoundLine.push_back(bBoundLine.back());
			lBoundLine.push_back(bBoundLine.front());
		}
		
		while (leftBound == false)
		{
			for (int i = 0; i < lBoundLine.size(); i++)
			{
				lBoundLine[i].c--;
				if (img.at<uint8_t>(lBoundLine[i].r, lBoundLine[i].c) > threshold_val)
				leftBound = true;
		}
			tBoundLine.insert(tBoundLine.begin(), lBoundLine.front());
			bBoundLine.insert(bBoundLine.begin(), lBoundLine.back());									
		}

		while (topBound == false)
		{
			for (int i = 0; i < tBoundLine.size(); i++)
			{
				(tBoundLine[i].r)--;
				if (img.at<uint8_t>(tBoundLine[i].r, tBoundLine[i].c) > threshold_val)
				topBound = true;
			}
			rBoundLine.insert(rBoundLine.begin(), tBoundLine.back());
			lBoundLine.insert(lBoundLine.begin(), tBoundLine.front());									  
		}

		for (int i = 0; i < rBoundLine.size(); i++)
		{
			if (img.at<uint8_t>(rBoundLine[i].r, rBoundLine[i].c) <= threshold_val)
				rightBound = false;
		}
		for (int i = 0; i < bBoundLine.size(); i++)
		{
			if (img.at<uint8_t>(bBoundLine[i].r, bBoundLine[i].c) <= threshold_val)
				bottomBound = false;
		}
		for (int i = 0; i < lBoundLine.size(); i++)
		{
			if (img.at<uint8_t>(lBoundLine[i].r, lBoundLine[i].c) <= threshold_val)
				leftBound = false;
		}
		for (int i = 0; i < tBoundLine.size(); i++)
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

