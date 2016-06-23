#include "Musique.hpp"

sf::Music musique;

///<summary>
///Fonction pour charger une autre musique. Elle arrête la musique en cours.
///</summary>
///<param name="nomMusique">Nom de la musique (sans l'extension .wav)</param>
void chargerMusique(string nomMusique)
{
	arretMusique();
	if (!musique.openFromFile(adresse + nomMusique + ".wav"))
		cerr << "Erreur lors du chargement de la musique" << endl;
}

///<summary>
///Fonction pour changer de musique et de jouer la nouvelle musique.
///</summary>
///<param name="nomMusique">Nom de la musique (sans l'extension .wav)</param>
void changerMusique(string nomMusique)
{
	chargerMusique(nomMusique);
	jouerMusique();
}

void jouerMusique()
{
	musique.play();
}

void pauseMusique()
{
	musique.pause();
}

void arretMusique()
{
	musique.stop();
}
