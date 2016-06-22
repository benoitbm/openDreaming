#pragma once

#include "Dependencies/cv.h"
#include "Dependencies/highgui.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>
#include <queue>

#define CV_NO_BACKWARD_COMPATIBILITY

#define DELAY 5

struct Color
{
	unsigned char red, green, blue;
};

class Graphics
{
	private :
		char * wndname;
		unsigned int width, height;
		int width3, height3;

		CvFont font;
		CvRNG rng;
		CvPoint pt1, pt2;

		IplImage* image;
		IplImage* image2;

		// Structure dans laquelle on stocke les phrases
		std::queue<std::string> text;

		// Pour quitter le programme
		char key;

		bool leave;

		const char * word;

	public : 
		Graphics ();
		~Graphics ();

		void color ();

		void draw ();
		void display ();
};