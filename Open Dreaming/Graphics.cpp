#include "Graphics.hpp"
#include "Parser.hpp"

Graphics::Graphics()
	: wndname("Open Dreaming"), image(NULL), image2(NULL), key(' '), leave(true), word(NULL)
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

void Graphics::display()
{
	readFile();
	
	srand(time(NULL));
	
	width = 480;
	height = 240;

	image = cvCreateImage(cvSize(width, height), 8, 3);
	
	cvNamedWindow(wndname, CV_WINDOW_NORMAL);
	cvSetWindowProperty(wndname, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

	while (leave)
	{		
		text = recevoirPhrase();

		if (text.empty())
			break;

		draw();	
	}
}

void Graphics::draw()
{
	
	int line_type = CV_AA;

	width3 = width * 3;
	height3 = height * 3;

	CvSize text_size;

	cvZero(image);
	cvShowImage(wndname, image);

	rng = aleatoire(width, 0);
	
	for (int i = 0; i < text.size(); i++)
	{
		pt1.x = cvRandInt(&rng) % width;
		pt1.y = cvRandInt(&rng) % height;

		// Taille des lettres, nombre de traits pour l'épaisseur
		cvInitFont(&font,
			cvRandInt(&rng) % 8,
			(cvRandInt(&rng) % 100)*0.05 + 0.1,
			(cvRandInt(&rng) % 100)*0.05 + 0.1,
			(cvRandInt(&rng) % 10)*0.1,
			cvRound(cvRandInt(&rng) % 2),
			line_type);

		word = text.front().c_str();

		cvPutText(image, word, pt1, &font, random_color(&rng));
		cvShowImage(wndname, image);

		text.pop();

		// Permet de quitter la fonction
		if (cvWaitKey(DELAY) >= 0)
		{
			key = cvWaitKey(80);

			if (int(key) == 27)
			{
				leave = false;
				break;
			}
		}

		Sleep(150);
	}
}