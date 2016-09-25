#pragma once
#include <stdint.h>

struct pos2d{
	uint16_t r;
	uint16_t c;

	pos2d(uint16_t row, uint16_t column)
	{
		r = row;
		c = column;
	};
};


