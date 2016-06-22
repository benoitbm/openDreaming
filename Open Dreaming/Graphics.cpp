#include "Graphics.hpp"
#include "Parser.hpp"
#include "Draw.hpp"

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

/*
void drawMaison(IplImage* img, CvPoint pos, int size_x, int size_y, CvScalar color)
{
	int thickness = (rand() % 5) + 1;
	cvRectangle(img, cvPoint(pos.x - size_x, pos.y - size_y), cvPoint(pos.x + size_x, pos.y + size_y), color, thickness, 8, 0);
	cvLine(img, cvPoint(pos.x - size_x, pos.y - size_y), cvPoint(pos.x, pos.y - (2 * size_y)), color, thickness, 8, 0);
	cvLine(img, cvPoint(pos.x, pos.y - (2 * size_y)), cvPoint(pos.x + size_x, pos.y - size_y), color, thickness, 8, 0);
	cvRectangle(img, cvPoint(pos.x - size_x / 4, pos.y + size_y / 3), cvPoint(pos.x + size_x / 4, pos.y + size_y), color, thickness, 8, 0);
}*/

void Graphics::display()
{
	readFile();
	
	srand(time(NULL));
	
	width = 480;
	height = 240;

	IplImage* image = cvCreateImage(cvSize(width, height), 8, 3);
	IplImage* image2;

	cvNamedWindow(wndname, CV_WINDOW_NORMAL);
	cvSetWindowProperty(wndname, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

	bool leave = true;

	// Permet de quitter le programme
	char k = ' ';

	// Permet l'affichage mot par mot d'une phrase
	const char * temp = new const char ();

	std::queue<std::string> text;

	while (leave)
	{		

		text = recevoirPhrase();
		if (text.empty())
			break;

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

		for (i = 0; i < text.size(); i++)
		{
			pt1.x = cvRandInt(&rng) % width3 - width;
			pt1.y = cvRandInt(&rng) % height3 - height;

			// Taille des lettres, nombre de traits pour l'épaisseur
			cvInitFont( &font, 
						cvRandInt(&rng) % 8,
						(cvRandInt(&rng) % 100)*0.05 + 0.1, 
						(cvRandInt(&rng) % 100)*0.05 + 0.1,
						(cvRandInt(&rng) % 10)*0.1, 
						cvRound(cvRandInt(&rng) % 2), 
						line_type);
			
			temp = text.front().c_str();
			
			string tempcompare = text.front();
			string templower = "";

			for (int i = 0; i < tempcompare.size(); ++i)
				templower += tolower(tempcompare.at(i));

			if (templower.compare("maison") == 0)
			{

				drawMaison(image, cvPoint(width / 2, height / 2), width / 6, height / 6, random_color(&rng));
			}
			

			cvPutText(image, temp, pt1, &font, random_color(&rng));
			cvShowImage(wndname, image);

			text.pop();

			// Permet de quitter la fonction
			if (cvWaitKey(DELAY) >= 0)
			{
				k = cvWaitKey(80);

				if (int(k) == 27)
				{	
					leave=false;
					break;
				}
			}

			Sleep(200);
		}
	}
}