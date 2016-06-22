#ifdef _CH_
#pragma package <opencv>
#endif

#define CV_NO_BACKWARD_COMPATIBILITY

#ifndef _EiC
	#include "Dependencies/cv.h"
	#include "Dependencies/highgui.h"
	#include <stdlib.h>
	#include <stdio.h>
	#include <time.h>
	#include <string>
#endif

#define NUMBER 100
#define DELAY 5
char wndname[] = "Projet M4202 - BIRABEN BIANCHI Hugo";


int aleatoire(int x, int i)
{
	return rand() % x + i;
}

CvScalar random_color(CvRNG* rng)
{
	int rouge = (unsigned)aleatoire(256, 0);
	int vert = (unsigned)aleatoire(256, 0);
	int bleu = (unsigned)aleatoire(256, 0);
	return CV_RGB(rouge, vert, bleu);
}


void affichage()
{
	int width = 1280, height = 720;
	IplImage* image = cvCreateImage(cvSize(width, height), 8, 3);
	IplImage* image2;
	cvNamedWindow(wndname, 1);

	int var = 1;
	music.play();
	while (var == 1)
	{
		int alea = aleatoire(5, 0);
		int timer = aleatoire(4, 2);

		int line_type = CV_AA;

		// Utiliser pour les boucles for
		int i;
		CvPoint pt1, pt2;
		double angle;
		CvSize sz;
		CvPoint  ptt[6];
		CvPoint* pt[2];
		int  arr[2];
		CvFont font;
		CvRNG rng;
		int width3 = width * 3, height3 = height * 3;
		CvSize text_size;
		int ymin = 0;

		cvZero(image);
		cvShowImage(wndname, image);
		cvWaitKey(DELAY);

		rng = aleatoire(1000, 0);
		pt[0] = &(ptt[0]);
		pt[1] = &(ptt[3]);

		arr[0] = 3;
		arr[1] = 3;

			for (i = 1; i < NUMBER*timer; i++)
			{
				pt1.x = cvRandInt(&rng) % width3 - width;
				pt1.y = cvRandInt(&rng) % height3 - height;

				cvInitFont(&font, cvRandInt(&rng) % 8,
					(cvRandInt(&rng) % 100)*0.05 + 0.1, (cvRandInt(&rng) % 100)*0.05 + 0.1,
					(cvRandInt(&rng) % 5)*0.1, cvRound(cvRandInt(&rng) % 10), line_type);

				cvPutText(image, " Sons et couleurs ", pt1, &font, random_color(&rng));
				cvShowImage(wndname, image);
				if (cvWaitKey(DELAY) >= 0)
					Sleep(500);
			}

	// Wait for a key stroke; the same function arranges events processing
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&image2);
	cvDestroyWindow(wndname);
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	affichage();

	return 0;
}

#ifdef _EiC
main(1, "drawing.c");
#endif