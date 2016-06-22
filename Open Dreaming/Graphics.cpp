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
		cout << text.size() << endl;

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

	rng = aleatoire(.9*width, 0);
	
	
	for (int i = 0; i < text.size(); i += 0)
	{
		float hauteur_lettre = (cvRandInt(&rng) % 60)*0.05+.2;
		float largeur_lettre = (cvRandInt(&rng) % 60)*0.05+.2;

		// Taille des lettres, nombre de traits pour l'épaisseur
		cvInitFont(&font,
			cvRandInt(&rng) % 8,
			hauteur_lettre, 
			largeur_lettre, 
			(cvRandInt(&rng) % 10)*0.1,
			cvRound(cvRandInt(&rng) % 2),
			line_type);

		string mot = text.front();
		text.pop();

		word = mot.c_str();

		float taille_l = largeur_lettre * mot.length();
		
		pt1.x = cvRandInt(&rng) % width;
		cout << pt1.x*largeur_lettre << " > " << .9*width << "?" << endl;
		while (pt1.x * largeur_lettre > .9*width && pt1.x > 0)
			pt1.x /= 1.5;

		pt1.y = cvRandInt(&rng) % height;
		cout << pt1.y << " < " << 50*hauteur_lettre << " ?" << endl;
		while (pt1.y < 50*hauteur_lettre)
			pt1.y++;

		cout << mot << endl;
		cout << "x = " << pt1.x << endl;
		cout << "y = " << pt1.y << endl << endl;

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