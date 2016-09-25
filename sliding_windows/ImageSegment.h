#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Position.h"
#include <stdint.h>
#include <vector>

std::vector<pos2d> genObjectSegment(const cv::Mat &img, uint16_t rows, uint16_t cols);
