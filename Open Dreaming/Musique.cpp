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
	listeMusique["bébé"] = 1;
	listeMusique["bébés"] = 1;

	//Dark
	listeMusique["sombre"] = 2;
	listeMusique["pleurs"] = 2;
	listeMusique["pleurer"] = 2;
	listeMusique["desespoir"] = 2;
	listeMusique["désespoir"] = 2;
	
	//Mort / Death
	listeMusique["deceder"] = 3;
	listeMusique["deces"] = 3;
	listeMusique["mort"] = 3;
	listeMusique["morte"] = 3;
	listeMusique["morts"] = 3;
	listeMusique["mortes"] = 3;
	listeMusique["mourir"] = 3;
	listeMusique["sacrifice"] = 3;
	listeMusique["sacrifices"] = 3;
	listeMusique["sacrifier"] = 3;
	listeMusique["tuer"] = 3;
	listeMusique["tuez-moi"] = 3;

	//Rêve / dream
	listeMusique["reve"] = 4;
	listeMusique["reves"] = 4;
	listeMusique["rever"] = 4;
	listeMusique["reveur"] = 4;
	listeMusique["rêveur"] = 4;
	listeMusique["songe"] = 4;
	listeMusique["songes"] = 4;
	listeMusique["dormir"] = 4;
	listeMusique["sommeil"] = 4;

	//Famille / familly
	listeMusique["famille"] = 5;
	listeMusique["familles"] = 5;
	listeMusique["pere"] = 5;
	listeMusique["père"] = 5;
	listeMusique["mere"] = 5;
	listeMusique["mère"] = 5;
	listeMusique["enfant"] = 5;
	listeMusique["enfants"] = 5;
	listeMusique["frère"] = 5;
	listeMusique["frere"] = 5;
	listeMusique["soeur"] = 5;

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
	listeMusique["révolte"] = 11;
	listeMusique["revolution"] = 11;
	listeMusique["révolution"] = 11;

	//Meteo
	listeMusique["meteo"] = 12;
	listeMusique["météo"] = 12;
	listeMusique["soleil"] = 12;
	listeMusique["nuage"] = 12;
	listeMusique["nuages"] = 12;
	listeMusique["pluie"] = 12;
	listeMusique["pleuvoir"] = 12;
	listeMusique["orage"] = 12;
	listeMusique["neige"] = 12;
	listeMusique["neiger"] = 12;
	listeMusique["ciel"] = 12;
	listeMusique["cieux"] = 12;

	//who
	listeMusique["qui"] = 13;

	//Volonté / Will
	listeMusique["volonte"] = 14;
	listeMusique["volonté"] = 14;
	listeMusique["continuer"] = 14;

	//education
	listeMusique["éducation"] = 15;
	listeMusique["education"] = 15;
	listeMusique["éduquer"] = 15;
	listeMusique["eduquer"] = 15;
	listeMusique["école"] = 15;
	listeMusique["ecole"] = 15;

	//food / nourriture
	listeMusique["nourriture"] = 16;
	listeMusique["nourrir"] = 16;

	//game / jeux video
	listeMusique["jeu"] = 17;
	listeMusique["jeux"] = 17;
	listeMusique["jouer"] = 17;

	//hope / espoir
	listeMusique["espoir"] = 18;
	listeMusique["espérer"] = 18;
	listeMusique["esperer"] = 18;

	//movie / films
	listeMusique["film"] = 19;
	listeMusique["filmer"] = 19;

	//music / musique
	listeMusique["musique"] = 20;
	listeMusique["écouter"] = 20;
	listeMusique["ecouter"] = 20;

	// night / nuit
	listeMusique["lune"] = 21;
	listeMusique["astre"] = 21;
	listeMusique["astres"] = 21;
	listeMusique["nuit"] = 21;

	//ocean
	listeMusique["ocean"] = 22;
	listeMusique["océan"] = 22;
	listeMusique["mer"] = 22;

	//religion
	listeMusique["religion"] = 23;
	listeMusique["église"] = 23;
	listeMusique["eglise"] = 23;
	listeMusique["prier"] = 23;
	listeMusique["prière"] = 23;
	listeMusique["priere"] = 23;

	//travel / voyage
	listeMusique["voyage"] = 24;
	listeMusique["voyages"] = 24;
	listeMusique["voyager"] = 24;
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

sf::Music * getMusique()
{
	return &musique;
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
		nomMusique = "dream" + to_string(generateNumber(1, 3)) + ".ogg";
		break;

	case 5:
		nomMusique = "family" + to_string(generateNumber(1, 1)) + ".ogg";
		break;

	case 6:
		nomMusique = "imagine.ogg";
		break;

	case 7:
		nomMusique = "joy" + to_string(generateNumber(1, 2)) + ".ogg";
		break;

	case 8:
		nomMusique = "love" + to_string(generateNumber(1, 3)) + ".ogg";
		break;

	case 9:
		nomMusique = "money" + to_string(generateNumber(1, 2)) + ".ogg";
		break;

	case 10:
		nomMusique = "queen" + to_string(generateNumber(1, 3)) + ".ogg";
		break;

	case 11:
		nomMusique = "revolution" + to_string(generateNumber(1, 1)) + ".ogg";
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

	case 15:
		nomMusique = "education.ogg";
		break;

	case 16:
		nomMusique = "food.ogg";
		break;

	case 17:
		nomMusique = "game" + to_string(generateNumber(1, 3)) + ".ogg";
		break;

	case 18:
		nomMusique = "hope1.ogg";
		break;

	case 19:
		nomMusique = "movie" + to_string(generateNumber(1, 2)) + ".ogg";
		break;

	case 20:
		nomMusique = "music1.ogg";
		break;

	case 21:
		nomMusique = "night" + to_string(generateNumber(1, 2)) + ".ogg";
		break;

	case 22:
		nomMusique = "ocean1.ogg";
		break;

	case 23:
		nomMusique = "religion.ogg";
		break;

	case 24:
		nomMusique = "travel" + to_string(generateNumber(1, 1)) + ".ogg";
		break;

	default:
		nomMusique = "default.ogg";
		break;
	}
	changerMusique(nomMusique);
}
