#pragma once

#include "Dependencies/cv.h"
#include "Dependencies/highgui.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>

class Draw
{
	void drawRectangle(Point pos = Point(0, 0), int width, int height, CV_RGB color);
};
