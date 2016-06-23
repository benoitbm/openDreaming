#include "Graphics.hpp"
#include "Parser.hpp"
#include "Draw.hpp"

//Tableau contenant les mots cl�s pour les fonctions sp�ciales
string motsCles[] = {
	"maison",
	"ocean","oceans", //Fonction bulles
	"mer", "mers",
	"lac", "lacs"
	"bulle", "bulles",
	"roi", "rois", //Fonction roi pour la musique
	"reine", "reines"
};

Graphics::Graphics()
	: wndname("Open Dreaming"), image(NULL), image2(NULL), key(' '), leave(true), word(NULL)
{}

Graphics::~Graphics()
{
	delete wndname;
}

///<summary>
///Fonction pour g�n�rer un nombre al�atoire.
///</summary>
///<param name="x">Maximum du nombre � g�n�rer</param>
///<param name="i">Minimum du nombre � g�n�rer</param>
///<returns> Renvoie un int g�n�r� al�atoirement. </returns>
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
	
	// Taille en pixel de l'image (m�me si l'affichage peut �tre plus grand)
	width = 480;
	height = 240;

	image = cvCreateImage(cvSize(width, height), 8, 4);
	
	cvNamedWindow(wndname, CV_WINDOW_NORMAL);
	cvSetWindowProperty(wndname, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

	while (leave)
	{		
		text = recevoirPhrase();

		if (text.empty())
			break;

		//drawRandomly();	
		draw();
	}

	Sleep(500);
}

int getAverageLum(IplImage * img)
{
	int moy = 0;
	int j = 0;
	char * data = img->imageData;

	for (int i = 0; i < img->imageSize/3; i++)
	{
		unsigned char r = data[j++];
		unsigned char g = data[j++];
		unsigned char b = data[j++];

		moy += (unsigned int(r) + unsigned int(g) + unsigned int(b)) / 3;
	}

	moy /= (img->imageSize / 3);
	return moy;
}

void Graphics::drawRandomly()
{
	int moy = 0;
	int line_type = CV_AA;
	CvCapture * capture = cvCaptureFromCAM(0);

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

		// Taille des lettres, nombre de traits pour l'�paisseur
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

		//Affiche les t�ches

		image2 = cvQueryFrame(capture);
		moy = getAverageLum(image2);

		pt2.x = cvRandInt(&rng) % width;
		pt2.y = cvRandInt(&rng) % height;

		drawPolySphere(image, pt2, rand() % 42 + 21, 64-moy/2, -2+moy/18, random_color(&rng));

		//------------------

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
		Sleep(moy*1.8+rand()%120);
	}

	Sleep(moy*1.8);
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

	pt1.y = 30;

	const char max = text.size();

	char * previousWord = new char [max];
	float * previousSize = new float[max];

	int pos = 0;

	for (int i = 0; i < text.size(); i += 0)
	{
		
		float hauteur_lettre = (rand() % 10)*0.01 + 0.95;
		float largeur_lettre = (rand() % 10)*0.01 + 0.95;

		previousSize[max - text.size()] = largeur_lettre;

		string mot = text.front();
		
		word = mot.c_str();

		previousWord[max - text.size()] = mot.length();

		text.pop();

		float taille_l = previousWord[max - text.size() - 1] * 0.02 * previousSize[max - text.size() - 1];

		// Taille des lettres, nombre de traits pour l'�paisseur
		cvInitFont(&font,
			cvRandInt(&rng) % 8,
			hauteur_lettre,
			largeur_lettre,
			(cvRandInt(&rng) % 10)*0.1,
			cvRound(cvRandInt(&rng) % 2),
			line_type);

		//pt1.x += (previousSize[max - text.size() - 1] * previousWord[max - text.size() - 1] + 150);
		pt1.x = pos*20;

		// Positionne les mots
		if ((pos+1)*20> (0.9 * width))
		{
			pt1.x = 5;
			pos = 0;
			pt1.y = countLine++  * 40 + 30;
		}
		else if (beginLine == true)
		{
			pt1.x = 5;
			pos = 0;
			countLine++;
			beginLine = false;
		}

		if (countLine > 4)
		{
			countLine = 0;
			pt1.y = countLine++ * 40 + 30;
			Sleep(150);
			cvZero(image);
		}

		// Tentative de dessin d'un coeur
		cv::Mat imgM;
		drawHeart(imgM);

		// Affiche le mot
		cvPutText(image, word, pt1, &font, random_color(&rng));
		cvShowImage(wndname, image);

		pos += (mot.length() + 1);

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
			pt1.y = 30;
		}

		Sleep (150);
	}

	Sleep(500);
}