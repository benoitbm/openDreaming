#include "Graphics.hpp"
#include "Parser.hpp"

Graphics::Graphics()
	: wndname("Open Dreaming"), image(NULL), image2(NULL), key(' '), leave(true), word(NULL)
{}

Graphics::~Graphics()
{
	delete wndname;
}

///<summary>
///Fonction pour générer un nombre aléatoire.
///</summary>
///<param name="x">Maximum du nombre à générer</param>
///<param name="i">Minimum du nombre à générer</param>
///<returns> Renvoie un int généré aléatoirement. </returns>
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

		/*
		if (!music.openFromFile("w1.flac"))
		{	}
		else
		{
			music.play();
		}
		*/

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

	rng = aleatoire(width*1.5, 0);

	for (int i = 0; i < text.size(); i += 0)
	{
		float hauteur_lettre = (cvRandInt(&rng) % 80)*0.02 + .2;
		float largeur_lettre = (cvRandInt(&rng) % 80)*0.02 + .2;

		string mot = text.front();
		text.pop();

		word = mot.c_str();

		float taille_l = largeur_lettre * mot.length() * 0.02;

		pt1.x = cvRandInt(&rng) % width;

		if (largeur_lettre > 1.2)
			largeur_lettre /= 1.4;

		while ( (pt1.x + (taille_l*150) > (0.7 * width) ) && pt1.x > 0)
		{
			pt1.x = cvRandInt(&rng) % width;
			
			if ((pt1.x + (taille_l * 150) > (0.9 * width)))
				pt1.x = 10;	
		}

		pt1.y = cvRandInt(&rng) % height;
		while (pt1.y < 50*hauteur_lettre)
			pt1.y++;

		// Taille des lettres, nombre de traits pour l'épaisseur
		cvInitFont(&font,
			cvRandInt(&rng) % 8,
			hauteur_lettre,
			largeur_lettre,
			(cvRandInt(&rng) % 10)*0.1,
			cvRound(cvRandInt(&rng) % 2),
			line_type);

		cvPutText(image, word, pt1, &font, random_color(&rng));
		cvShowImage(wndname, image);

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

		//system("pause");
		Sleep(400 + aleatoire(350,0));
	}
}