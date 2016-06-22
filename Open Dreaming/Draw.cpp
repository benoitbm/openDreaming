#include "Draw.hpp"

void drawMaison(IplImage* img, CvPoint pos, int size_x, int size_y, CvScalar color)
{
	int thickness = (rand() % 5) + 1;
	cvRectangle(img, cvPoint(pos.x - size_x, pos.y - size_y), cvPoint(pos.x + size_x, pos.y + size_y), color, thickness, 8, 0);
	cvLine(img, cvPoint(pos.x - size_x, pos.y - size_y), cvPoint(pos.x, pos.y - (2 * size_y)), color, thickness, 8, 0);
	cvLine(img, cvPoint(pos.x, pos.y - (2 * size_y)), cvPoint(pos.x + size_x, pos.y - size_y), color, thickness, 8, 0);
	cvRectangle(img, cvPoint(pos.x - size_x / 4, pos.y + size_y / 3), cvPoint(pos.x + size_x / 4, pos.y + size_y), color, thickness, 8, 0);
}

void drawPolySphere(IplImage* img, CvPoint pos, int nbPts, int size, CvScalar color)
{
	int thickness = (rand() % 2);
	
	CvPoint * pts = new CvPoint[nbPts];
	
	for (unsigned int i = 0; i < nbPts; ++i)
	{
		int random1 = (rand() % size) - size / 2;
		int random2 = (rand() % size) - size / 2;
		pts[i] = (cvPoint(cos((2*i*3.14159)/nbPts)*size+pos.x+random1, sin((2*i*3.14159)/nbPts)*size+pos.y+random2));
	}
	//int npts = Mat(contour).rows;

	std::cout << "Number of polygon vertices: " << nbPts << std::endl;

	// draw the polygon 
	int mode = rand() % 2 + 1;
	if(mode == 1)
		cvFillPoly(img, &pts, &nbPts, 1,
			// draw closed contour (i.e. joint end to start) 
		color,// colour RGB ordering (here = green) 
 		        // line thickness
		8, 0);
	else
		cvPolyLine(img, &pts, &nbPts, 1,
			true, 			// draw closed contour (i.e. joint end to start) 
			color,// colour RGB ordering (here = green) 
			thickness, 		        // line thickness
			8, 0);
	delete [] pts;
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
	cvRectangle(img, pt1, pt2, color);
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
	cvCircle(img, center, radius, color);
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
	cvLine(img, pt1, pt2, color);
}

