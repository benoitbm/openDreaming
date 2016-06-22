#include "Draw.hpp"

void Draw::drawRectangle(Mat& img, Point pos, int width, int height, Scalar& color)
{
	int thickness = (rand() % 5) + 1;
	int line_type = 8;
	int shift = 0;
	rectangle(img, pos, Point(pos.x, pos.y), color, thickness, line_type, shift);
}
