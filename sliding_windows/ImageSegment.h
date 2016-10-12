#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Position.h"
#include <stdint.h>
#include <vector>

std::vector<std::vector<pos2d>> genObjectSegment(const cv::Mat &img);
std::vector<cv::Mat>genImageSegments(cv::Mat &img);
cv::Mat imageSegmentVecToMat(const cv::Mat &img, std::vector<std::vector<pos2d>> segments);
const int threshold_val = 100;