#include "Graphics.hpp"

Graphics::Graphics()
	: wndname("Open Dreaming")
{}

Graphics::~Graphics()
{
	delete wndname;
}

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

void Graphics::display(const char * text)
{
	srand(time(NULL));
	
	width = 480;
	height = 240;

	IplImage* image = cvCreateImage(cvSize(width, height), 8, 3);
	IplImage* image2;

	cvNamedWindow(wndname, CV_WINDOW_NORMAL);
	cvSetWindowProperty(wndname, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

	bool leave = true;

	char k = ' ';

	while (leave)
	{		
		int line_type = CV_AA;

		// Utiliser pour les boucles for
		int i;

		CvPoint pt1, pt2;

		CvSize sz;
		CvPoint  ptt[6];
		CvPoint* pt[2];

		CvFont font;
		CvRNG rng;
		int width3 = width * 3, height3 = height * 3;
		CvSize text_size;

		cvZero(image);
		cvShowImage(wndname, image);

		rng = aleatoire (width, 0);
		pt[0] = &(ptt[0]);
		pt[1] = &(ptt[3]);

		for (i = 1; i < NUMBER; i++)
		{
			pt1.x = cvRandInt(&rng) % width3 - width;
			pt1.y = cvRandInt(&rng) % height3 - height;

			cvInitFont( &font, 
						cvRandInt(&rng) % 8,
						(cvRandInt(&rng) % 100)*0.05 + 0.1, 
						(cvRandInt(&rng) % 100)*0.05 + 0.1,
						(cvRandInt(&rng) % 10)*0.1, 
						cvRound(cvRandInt(&rng) % 2), 
						line_type);

			cvPutText(image, text, pt1, &font, random_color(&rng));
			cvShowImage(wndname, image);
			if (cvWaitKey(DELAY) >= 0)
			{
				k = cvWaitKey(80);

				if (int(k) == 27)
				{	
					leave=false;
					break;
				}
			}

			Sleep (50);

		}
	}
}