#include "Random.hpp"

///<summary>
///Cette fonction renvoie un nombre g�n�r� al�atoirement.
///</summary>
///<param name="min">Intervalle minimum inclus</param>
///<param name="max">Intervalle maximum inclus</param>
///<returns>Renvoie un entier g�n�r� al�atoirement.</returns>
int generateNumber(int min, int max)
{
	return rand() % (max + 1) + min;
}

///<summary>
///Cette fonction renvoie un nombre g�n�r� al�atoirement.
///</summary>
///<param name="min">Intervalle minimum inclus</param>
///<param name="max">Intervalle maximum exclus</param>
///<returns>Renvoie un float g�n�r� al�atoirement.</returns>
float generateNumber(float min, float max)
{
	return (rand() % int(max) + min)*1.0f;
}

///<summary>
///Cette fonction permet de renvoyer le r�sultat pour le choix entre afficher la phrase enti�re ou mot par mot.
///0 = Phrase, 1+ = Mot al�atoire
///</summary>
int determinerChoix()
{
	return generateNumber(0, 2);
}

///<summary>
///Fonction pour d�finir ce qu'on va faire avec le mot
///</summary>
int typeMot()
{
	return generateNumber(1, 5);
}

int typeForme()
{
	return generateNumber(1, 4);
}

int typePhrase()
{
	return 0;
}