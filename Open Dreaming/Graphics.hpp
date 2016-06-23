#pragma once

#include "Dependencies/OpenCV/cv.h"
#include "Dependencies/OpenCV/highgui.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>
#include <queue>

// #include <SFML/Audio.hpp>

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

		// sf::Music music;

	public : 
		Graphics ();
		~Graphics ();

		void color ();

		void display ();

		void drawRandomly();
		void draw();
};