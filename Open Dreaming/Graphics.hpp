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

	public : 
		Graphics ();
		~Graphics ();

		void color ();

		void display ();
};