#include "Draw.hpp"

void drawMaison(IplImage* img, CvPoint pos, int size_x, int size_y, CvScalar color)
{
	int thickness = (rand() % 5) + 1;
	cvRectangle(img, cvPoint(pos.x - size_x, pos.y - size_y), cvPoint(pos.x + size_x, pos.y + size_y), color, thickness, 8, 0);
	cvLine(img, cvPoint(pos.x - size_x, pos.y - size_y), cvPoint(pos.x, pos.y - (2 * size_y)), color, thickness, 8, 0);
	cvLine(img, cvPoint(pos.x, pos.y - (2 * size_y)), cvPoint(pos.x + size_x, pos.y - size_y), color, thickness, 8, 0);
	cvRectangle(img, cvPoint(pos.x - size_x / 4, pos.y + size_y / 3), cvPoint(pos.x + size_x / 4, pos.y + size_y), color, thickness, 8, 0);
}
