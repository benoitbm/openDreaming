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
	// Lit le fichier que l'utilisateur souhaite
	readFile();
	
	srand(time(NULL));
	
	// Taille en pixel de l'image (même si l'affichage peut être plus grand)
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

	Sleep(500);
}

void Graphics::drawRandomly()
{

	int line_type = CV_AA;

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

		// Affiche le mot
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
		Sleep(500);
	}

	Sleep(500);
}

void Graphics::draw()
{
	int line_type = CV_AA;

	CvSize text_size;

	cvZero(image);
	cvShowImage(wndname, image);

	rng = aleatoire(width*1.5, 0);

	bool beginLine = true;

	unsigned char countLine = 0;

	pt1.y = 20;

	const char max = text.size();

	char * previousWord = new char [max];
	float * previousSize = new float[max];

	for (int i = 0; i < text.size(); i += 0)
	{
		
		float hauteur_lettre = (cvRandInt(&rng) % 80)*0.02 + .2;
		float largeur_lettre = (cvRandInt(&rng) % 80)*0.02 + .2;

		previousSize[max - text.size()] = largeur_lettre;

		string mot = text.front();
		
		word = mot.c_str();

		previousWord[max - text.size()] = mot.length();

		text.pop();

		float taille_l = previousWord[max - text.size() - 1] * 0.02 * previousSize[max - text.size() - 1];

		// Taille des lettres, nombre de traits pour l'épaisseur
		cvInitFont(&font,
			cvRandInt(&rng) % 8,
			hauteur_lettre,
			largeur_lettre,
			(cvRandInt(&rng) % 10)*0.1,
			cvRound(cvRandInt(&rng) % 2),
			line_type);

		pt1.x += (previousSize[max - text.size() - 1] * previousWord[max - text.size() - 1] * 30);

		// Positionne les mots
		if ((pt1.x + (taille_l * 100) > (0.9 * width)))
		{
			pt1.x = 5;
			countLine++;
			pt1.y += countLine * 20;
		}
		else if (beginLine == true)
		{
			pt1.x = 5;
			countLine++;
			beginLine = false;
		}

		// Affiche le mot
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

		
		if (text.size() == 0)
		{
			beginLine = true;
			countLine = 0;
			pt1.y = 20;
		}

		Sleep (150);
	}

	Sleep(500);
}