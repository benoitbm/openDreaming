#include "Random.hpp"

///<summary>
///Cette fonction renvoie un nombre généré aléatoirement.
///</summary>
///<param name="min">Intervalle minimum inclus</param>
///<param name="max">Intervalle maximum inclus</param>
///<returns>Renvoie un entier généré aléatoirement.</returns>
int generateNumber(int min, int max)
{
	return rand() % (max + 1) + min;
}

///<summary>
///Cette fonction renvoie un nombre généré aléatoirement.
///</summary>
///<param name="min">Intervalle minimum inclus</param>
///<param name="max">Intervalle maximum exclus</param>
///<returns>Renvoie un float généré aléatoirement.</returns>
float generateNumber(float min, float max)
{
	return (rand() % int(max) + min)*1.0f;
}

///<summary>
///Cette fonction permet de renvoyer le résultat pour le choix entre afficher la phrase entière ou mot par mot.
///0 = Phrase, 1+ = Mot aléatoire
///</summary>
int determinerChoix()
{
	return generateNumber(0, 2);
}

///<summary>
///Fonction pour définir ce qu'on va faire avec le mot
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