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

int determinerChoix()
{
	int temp = generateNumber(0, 2);
	cout << "Choix = " << temp << endl;
	return temp;
	//return generateNumber(0, 2);
}

int typeMot()
{
	return generateNumber(0, 2);
}

int typePhrase()
{
	return 0;
}