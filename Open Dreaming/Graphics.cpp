#include "Graphics.hpp"
#include "Parser.hpp"
#include "Draw.hpp"
#include "Random.hpp"
#include "Musique.hpp"

using namespace std;

//Tableau contenant les mots cl�s pour dessiner un �l�ment sp�cial (uniquement hors phrases)
string motsClesDessin[] = {
"maison", "maisons"
"ocean","oceans", //Fonction bulles
"mer", "mers",
"lac", "lacs"
"bulle", "bulles",
};

string motsClesMusique[] = {
	//Birth/Naissance
	"naitre", "na�tre",
	"naissance", "naissances",
	"bebe", "bebes",
	"b�b�", "b�b�s",


	//Dark / desespoir
	"pleurs",
	"pleurer",
	"d�sespoir", "desespoir",

	//Mort / Death
	"deceder", "d�c�der",
	"deces", "d�c�s",
	"mort", "morte", "morts", "mortes",
	"mourir",
	"sacrifier", "sacrifice", "sacrifices",
	"tuer", "tuez", "tuez-moi",

	//R�ve / dream
	"reve", "reves", "r�ve", "r�ves",
	"r�ver","rever", "reveur", "r�veur",
	"songe", "songes",
	"sommeil",
	"dormir",

	//Famille / familly
	"famille", "familles",
	"pere", "p�re",
	"mere", "m�re",
	"enfant", "enfants",
	"fr�re", "frere", "soeur",

	//Paix / Imagine
	"paix",
	"imaginer",
	"imagination",

	//Joie
	"bonheur",
	"joie", "joyeux",
	"heureux", "heureuse", "heureuses",

	//Amour
	"aimer",
	"aime",
	"amour",
	"amant", "amants",

	//Argent
	"argent",

	//Queen
	"roi", "rois",
	"reine", "reines",
	"royal", "royale", "royaux",

	//revolution
	"revolte", "r�volte",
	"revolution", "r�volution",

	//meteo
	"meteo", "m�t�o",
	"soleil",
	"nuage", "nuages",
	"pluie", "pleuvoir",
	"orage",
	"neige", "neiger",
	"ciel", "cieux",

	//who
	"qui",

	//will
	"volonte", "volont�",
	"continuer",

	//education
	"�ducation", "education",
	"�duquer", "eduquer",
	"�cole", "ecole",

	//food / nourriture
	"nourriture",
	"nourrir",

	//game / jeux video
	"jeu", "jeux",
	"jouer",

	//hope / espoir
	"espoir", "esp�rer", "esperer",

	//movie / films
	"film",
	"filmer",

	//music / musique
	"musique",
	"�couter", "ecouter"

	// night / nuit
	"lune",
	"astre", "astres"
	"nuit",

	//ocean
	"oc�an", "ocean",
	"mer",

	//religion
	"religion",
	"�glise", "eglise",
	"prier", "pri�re", "priere",

	//travel / voyage
	"voyage", "voyages",
	"voyager"

};

bool sombre = false;
bool clair = false;
string lastWord;

Graphics::Graphics()
	: wndname("Open Dreaming"), image(NULL), image2(NULL), capture(NULL), key(' '), leave(true), word(NULL)
{
	capture = cvCaptureFromCAM(0);
}

Graphics::~Graphics()
{
	cvReleaseImage(&image);
	cvReleaseImage(&image2);
	cvReleaseCapture(&capture);
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

	creerListe();

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

		if (determinerChoix() == 0)
			draw();
		else
			drawRandomly();

	}

	Sleep(350 + generateNumber(0, 250));
}

void fadeIn(char * wndname, IplImage * dst, IplImage * src)
{
	for (int i = 0; i < 10; i++)
	{
		double fadein = i / 10.0;
		cvAddWeighted(src, fadein, dst, fadein, 0, dst);
		cvShowImage(wndname, dst);
		cvWaitKey(1);
		Sleep(100);
	}

}

int getAverageLum(IplImage * img)
{
	int moy = 0;
	int j = 0;
	char * data = img->imageData;

	for (int i = 0; i < img->imageSize / 3; i++)
	{
		unsigned char r = data[j++];
		unsigned char g = data[j++];
		unsigned char b = data[j++];

		moy += (unsigned int(r) + unsigned int(g) + unsigned int(b)) / 3;
	}

	moy /= (img->imageSize / 3);
	if (moy <= 75 && !sombre)
	{
		sombre = true;
		clair = false;
		if(getMusique()->getStatus() == 3 || lastWord != "sombre")
			musiqueMot("sombre");
		lastWord = "sombre";
	}
	else if (moy >= 170 && !clair)
	{
		sombre = false;
		clair = true;
		if (getMusique()->getStatus() == 3 || lastWord != "lumiere")
			musiqueMot("lumiere");
		lastWord = "lumiere";
	}
	else
	{
		sombre = false;
		clair = false;
	}

	return moy;
}

void Graphics::drawRandomly()
{
	int moy = 0;
	int line_type = CV_AA;

	CvSize text_size;
	cvZero(image);
	cvShowImage(wndname, image);

	rng = aleatoire(width*1.5, 0);

	for (int i = 0; i < text.size(); i += 0)
	{
		string mot = text.front();
		text.pop();

		string motlow = mot;

		for (int l = 0; l < mot.length(); ++l)
			motlow.at(l) = tolower(mot.at(l));

		bool motMusical = false;
		for (int m = 0; m < sizeof(motsClesMusique) / sizeof(motsClesMusique[0]); ++m)
			motMusical = motMusical || (motlow.compare(motsClesMusique[m]) == 0);

		if (motMusical)
		{
			lastWord = motlow;
			musiqueMot(motlow);
		}

		bool motCle = false;

		for (int i = 0; i < sizeof(motsClesDessin) / sizeof(motsClesDessin[0]); ++i)
			motCle = motCle || (motlow.compare(motsClesDessin[i]) == 0);

		if (motCle && moy > 75 && moy < 200)
		{
			//Rajoutez les fonctions de dessin de mot cl� ici
			if (motlow.compare("maison") == 0 || motlow.compare("maisons") == 0)
			{
				pt1.x = width / 2;
				pt1.y = height / 2;
				drawMaison(image, pt1, width / 4, width / 4, random_color(&rng));
			}
		}

		float hauteur_lettre = (cvRandInt(&rng) % 80)*0.02 + .2;
		float largeur_lettre = (cvRandInt(&rng) % 80)*0.02 + .2;

		word = mot.c_str();

		float taille_l = largeur_lettre * mot.length() * 0.02;

		pt1.x = cvRandInt(&rng) % width;

		if (largeur_lettre > 1.2)
			largeur_lettre /= 1.4;

		while ((pt1.x + (taille_l * 150) > (0.7 * width)) && pt1.x > 0)
		{
			pt1.x = cvRandInt(&rng) % width;

			if ((pt1.x + (taille_l * 150) > (0.9 * width)))
				pt1.x = 10;
		}

		pt1.y = cvRandInt(&rng) % height;
		while (pt1.y < 50 * hauteur_lettre)
			pt1.y++;

		// Taille des lettres, nombre de traits pour l'�paisseur
		cvInitFont(&font,
			cvRandInt(&rng) % 8,
			hauteur_lettre,
			largeur_lettre,
			(cvRandInt(&rng) % 10)*0.1,
			cvRound(cvRandInt(&rng) % 2),
			line_type);

		//Affiche les t�ches

		image2 = cvQueryFrame(capture);
		moy = getAverageLum(image2);

		pt2.x = cvRandInt(&rng) % width;
		pt2.y = cvRandInt(&rng) % height;

		//drawCercle(image, cvPoint(width / 2, height / 2), 100, cvScalar(moy, moy, moy));

		// Affiche le mot
		cvPutText(image, word, pt1, &font, random_color(&rng));
		cvShowImage(wndname, image);

		//Dessine des spheres � piques variables
		drawPolySphere(image, pt2, rand() % 42 + 21, 64 - moy / 2, -2 + moy / 18, random_color(&rng));

		int choix = typeForme();

		//D�finition des tailles g�n�r� par le mot actuel
		pt1.x = (int)mot.at(0) * 2 % width;
		pt1.y = mot.length() * 500 % height;
		pt2.x = 0;
		for (int b = 0; b < mot.length(); ++b)
			pt2.x += (int)mot.at(b);
		pt2.x %= (int)(1.1*width);
		pt2.y = ((int)mot.at(0) * mot.length()) % (int)(1.1 * height);

		switch (choix)
		{
		case 1:
			drawRectangle(image, pt1, pt2, random_color(&rng));
			break;

		case 2:
			drawLine(image, pt1, pt2, random_color(&rng));
			break;

		case 3:
			drawCercle(image, pt1, mot.length() * 10, random_color(&rng));
			break;

		case 4:
			drawPolySphere(image, pt2, rand() % 42 + 21, 64 - moy / 2, -2 + moy / 18, random_color(&rng));
			break;

		default:
			break;
		}

		cvShowImage(wndname, image);

		//------------------

		// Permet de quitter la fonction
		if (cvWaitKey(DELAY) >= 0)
		{
			key = cvWaitKey(80);

			if (int(key) == 27)
			{
				leave = false;
				exit(0);
			}
		}
		Sleep(moy * generateNumber(1, 2) + 100);
	}

	Sleep(moy * generateNumber(1, 2) + 100);
}

///<summary>
///Fonction pour �crire une phrase en ligne.
///</summary>
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

	char * previousWord = new char[max];
	float * previousSize = new float[max];

	int pos = 0;

	for (int i = 0; i < text.size(); i += 0)
	{
		if (text.size() == 1)
		{
			IplImage * tmp = cvCloneImage(image);
			fadeIn(wndname, image, tmp);
			cvShowImage(wndname, image);
			cvReleaseImage(&tmp);
		}
		else
			cvShowImage(wndname, image);

		float hauteur_lettre = (rand() % 10)*0.01 + 0.95;
		float largeur_lettre = (rand() % 10)*0.01 + 0.95;

		previousSize[max - text.size()] = largeur_lettre;

		string mot = text.front();

		string motlow = mot; //Pour la musique
		for (int l = 0; l < mot.length(); l++)
			motlow.at(l) = tolower(mot.at(l));

		bool motMusical = false;
		for (int m = 0; m < sizeof(motsClesMusique) / sizeof(motsClesMusique[0]); ++m)
			motMusical = motMusical || (motlow.compare(motsClesMusique[m]) == 0);

		if (motMusical)
			musiqueMot(motlow);

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
		pt1.x = pos * 20;

		// Positionne les mots
		if ((pos + 1) * 20 > (0.9 * width))
		{
			pt1.x = 5;
			pos = 0;
			pt1.y = countLine++ * 40 + 30;
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
			IplImage * tmp = cvCloneImage(image);
			fadeIn(wndname, image, tmp);
			cvShowImage(wndname, image);
			cvReleaseImage(&tmp);
			Sleep(150);
			cvZero(image);
		}

		// Tentative de dessin d'un coeur
		cv::Mat imgM;
		//drawHeart(imgM);

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
				arretMusique();
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

		Sleep(100 + generateNumber(0, 100));
	}
	delete[] previousSize;
	delete[] previousWord;
	Sleep(350 + generateNumber(0, 250));
}