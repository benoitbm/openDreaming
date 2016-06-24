#include "Draw.hpp"


void drawMaison(IplImage* img, CvPoint pos, int size_x, int size_y, CvScalar color)
{
	int thickness = (rand() % 5) + 1;
	cvRectangle(img, cvPoint(pos.x - size_x, pos.y - size_y), cvPoint(pos.x + size_x, pos.y + size_y), color, thickness, 8, 0);
	cvLine(img, cvPoint(pos.x - size_x, pos.y - size_y), cvPoint(pos.x, pos.y - (2 * size_y)), color, thickness, 8, 0);
	cvLine(img, cvPoint(pos.x, pos.y - (2 * size_y)), cvPoint(pos.x + size_x, pos.y - size_y), color, thickness, 8, 0);
	cvRectangle(img, cvPoint(pos.x - size_x / 4, pos.y + size_y / 3), cvPoint(pos.x + size_x / 4, pos.y + size_y), color, thickness, 8, 0);
}

void drawPolySphere(IplImage* img, CvPoint pos, int nbPts, int size, int attenuation, CvScalar color)
{
	int thickness = (rand() % 2);
	
	CvPoint * pts = new CvPoint[nbPts];
	size++;			//La solution du flemard pour eviter les divisions par zero.
	attenuation++;	//pareil
	if (attenuation <= 0)
		attenuation = 1;
	if (size == 0)
		size = 1;
	for (unsigned int i = 0; i < nbPts; ++i)
	{
		int random1 = ((rand() % size) - size/2) / attenuation;
		int random2 = ((rand() % size) - size/2) / attenuation;
		pts[i] = (cvPoint(cos((2*i*3.14159)/nbPts)*size+pos.x+random1, sin((2*i*3.14159)/nbPts)*size+pos.y+random2));
	}
	//int npts = Mat(contour).rows;

	IplImage* tmp = cvCloneImage(img);
	// draw the polygon 
	//int mode = rand() % 2 + 1
	int mode = 1;
	double opacity = 0.2;
	if (mode == 1)
	{
		cvFillPoly(tmp, &pts, &nbPts, 
			1,		// draw closed contour (i.e. joint end to start) 
			color,	// colour RGB ordering (here = green) 
			8,		// line thickness
			0);
	}
	else
	{
		cvPolyLine(tmp, &pts, &nbPts, 1,
			true, 	// draw closed contour (i.e. joint end to start) 
			color,	// colour RGB ordering (here = green) 
			thickness, 		        
			8, 0);
	}
	cvAddWeighted(tmp, opacity, img, 1 - opacity, 0, img);
	delete [] pts;
	cvReleaseImage(&tmp);
}

///<summary>
///Fonction pour dessiner un rectangle (contours uniquement).
///</summary>
///<param name ="img">Image sur laquelle dessiner.</param>
///<param name ="pt1">Point de départ (haut à gauche)</param>
///<param name ="pt2">Point d'arrivée (bas à droite)</param>
///<param name ="color">Couleur du rectangle.</param>
void drawRectangle(IplImage * img, CvPoint pt1, CvPoint pt2, CvScalar color)
{
	IplImage* tmp = cvCloneImage(img);
	double opacity = 0.2;
	cvRectangle(tmp, pt1, pt2, color);
	cvAddWeighted(tmp, opacity, img, 1 - opacity, 0, img);
	cvReleaseImage(&tmp);
}

///<summary>
///Fonction pour dessiner un cercle (contours uniquement).
///</summary>
///<param name ="img">Image sur laquelle dessiner.</param>
///<param name ="center">Point representant le centre du cercle.</param>
///<param name ="radius">Rayon du cercle.</param>
///<param name ="color">Couleur du cercle.</param>
void drawCercle(IplImage * img, CvPoint center, int radius, CvScalar color)
{
	IplImage* tmp = cvCloneImage(img);
	double opacity = 0.2;
	cvCircle(tmp, center, radius, color);
	cvAddWeighted(tmp, opacity, img, 1 - opacity, 0, img);
	cvReleaseImage(&tmp);
}

///<summary>
///Fonction pour dessiner une ligne.
///</summary>
///<param name ="img">Image sur laquelle dessiner.</param>
///<param name ="pt1">Point de départ.</param>
///<param name ="pt2">Point d'arrivée.</param>
///<param name ="color">Couleur de la ligne.</param>
void drawLine(IplImage * img, CvPoint pt1, CvPoint pt2, CvScalar color)
{
	IplImage* tmp = cvCloneImage(img);
	double opacity = 0.2;
	cvLine(tmp, pt1, pt2, color);
	cvAddWeighted(tmp, opacity, img, 1 - opacity, 0, img);
	cvReleaseImage(&tmp);
}

