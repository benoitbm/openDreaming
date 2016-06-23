#include "Musique.hpp"

sf::Music musique;

//Lieu pour raccorder les mots-clés au type de musique (voir carnet notes références)
map<string, int> listeMusique;
void creerListe()
{
	//Birth/Naissance
	listeMusique["naitre"] = 1;
	listeMusique["naissance"] = 1;
	listeMusique["naissances"] = 1;
	listeMusique["bebe"] = 1;
	listeMusique["bebes"] = 1;

	//Dark
	listeMusique["sombre"] = 2;
	
	//Mort / Death
	listeMusique["deceder"] = 3;
	listeMusique["deces"] = 3;
	listeMusique["mort"] = 3;
	listeMusique["morte"] = 3;
	listeMusique["morts"] = 3;
	listeMusique["mortes"] = 3;
	listeMusique["mourir"] = 3;

	//Rêve / dream
	listeMusique["reve"] = 4;
	listeMusique["reves"] = 4;
	listeMusique["rever"] = 4;
	listeMusique["songe"] = 4;
	listeMusique["songes"] = 4;

	//Famille / familly
	listeMusique["famille"] = 5;
	listeMusique["familles"] = 5;

	//Paix / Imaginer
	listeMusique["imagine"] = 6;
	listeMusique["imaginer"] = 6;
	listeMusique["paix"] = 6;

	//Joie
	listeMusique["lumiere"] = 7;
	listeMusique["bonheur"] = 7;
	listeMusique["joie"] = 7;
	listeMusique["joyeux"] = 7;
	listeMusique["heureux"] = 7;
	listeMusique["heureuse"] = 7;
	listeMusique["heureuses"] = 7;

	//Amour
	listeMusique["aimer"] = 8;
	listeMusique["aime"] = 8;
	listeMusique["amour"] = 8;
	listeMusique["amant"] = 8;
	listeMusique["amants"] = 8;

	//Argent / Money
	listeMusique["argent"] = 9;

	//Queen
	listeMusique["roi"] = 10;
	listeMusique["rois"] = 10;
	listeMusique["reine"] = 10;
	listeMusique["reines"] = 10;
	listeMusique["royal"] = 10;
	listeMusique["royale"] = 10;
	listeMusique["royaux"] = 10;

	//Revolution
	listeMusique["revolte"] = 11;
	listeMusique["revolution"] = 11;

	//Meteo
	listeMusique["meteo"] = 12;
	listeMusique["soleil"] = 12;
	listeMusique["nuage"] = 12;
	listeMusique["nuages"] = 12;
	listeMusique["lune"] = 12;
	listeMusique["astre"] = 12;
	listeMusique["pluie"] = 12;
	listeMusique["pleuvoir"] = 12;
	listeMusique["orage"] = 12;
	listeMusique["neige"] = 12;
	listeMusique["neiger"] = 12;

	//who
	listeMusique["qui"] = 13;

	//Volonté / Will
	listeMusique["volonte"] = 14;
	listeMusique["continuer"] = 14;

}


///<summary>
///Fonction pour charger une autre musique. Elle arrête la musique en cours.
///</summary>
///<param name="nomMusique">Nom de la musique (pensez à rajouter l'extension)</param>
void chargerMusique(string nomMusique)
{
	arretMusique();
	if (!musique.openFromFile(adresse + nomMusique))
		cerr << "Erreur lors du chargement de la musique" << endl;
}

///<summary>
///Fonction pour changer de musique et de jouer la nouvelle musique.
///</summary>
///<param name="nomMusique">Nom de la musique (pensez à rajouter l'extension)</param>
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

///<summary>
///Fonction pour jouer la musique adaptée à un mot clé
///</summary>
///<param name = "mot">Mot clé de la recherche</param>
void musiqueMot(string mot)
{
	cerr << "Mot musique : " << mot << endl;
	int choix = listeMusique.find(mot)->second; //On récupère le type de musique
	string nomMusique = "";
	switch (choix)
	{
	case 1:
		nomMusique = "birth.ogg";
		break;

	case 2:
		nomMusique = "dark" + to_string(generateNumber(1, 2)) + ".ogg";
		break;
		
	case 3:
		nomMusique = "death" + to_string(generateNumber(1, 2)) + ".ogg";
		break;

	case 4:
		nomMusique = "dream" + to_string(generateNumber(1, 2)) + ".ogg";
		break;

	case 5:
		nomMusique = "family1.ogg";
		break;

	case 6:
		nomMusique = "imagine.ogg";
		break;

	case 7:
		nomMusique = "joy1.ogg";
		break;

	case 8:
		nomMusique = "love" + to_string(generateNumber(1, 3)) + ".ogg";
		break;

	case 9:
		nomMusique = "money" + to_string(generateNumber(1, 2)) + ".ogg";
		break;

	case 10:
		nomMusique = "queen1.ogg";
		break;

	case 11:
		nomMusique = "revolution1.ogg";
		break;

	case 12:
		nomMusique = "weather" + to_string(generateNumber(1, 2)) + ".ogg";
		break;

	case 13:
		nomMusique = "who.ogg";
		break;

	case 14:
		nomMusique = "will.ogg";
		break;

	default:
		cerr << "Choix non renseigne : " << choix << endl;
		break;
	}
	changerMusique(nomMusique);
}
