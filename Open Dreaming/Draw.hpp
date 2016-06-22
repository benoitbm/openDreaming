#pragma once

#include "Dependencies/cv.h"
#include "Dependencies/highgui.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>

void drawMaison(IplImage* img, CvPoint pos, int size_x, int size_y, CvScalar color);