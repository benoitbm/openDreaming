#pragma once

#include "Dependencies/cv.h"
#include "Dependencies/highgui.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>

void drawMaison(IplImage* img, CvPoint pos, int size_x, int size_y, CvScalar color);
void drawPolySphere(IplImage* img, CvPoint pos, int nbPts, int size, CvScalar color);
void drawRectangle(IplImage* img, CvPoint pt1, CvPoint pt2, CvScalar color);
void drawCercle(IplImage* img, CvPoint center, int radius, CvScalar color);
void drawLine(IplImage* img, CvPoint pt1, CvPoint pt2, CvScalar color);