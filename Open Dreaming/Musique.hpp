#pragma once
#ifndef MUSIQUE_HPP
#define MUSIQUE_HPP

#include <SFML\Audio.hpp>
#include <string>

#include "Random.hpp"

using namespace std;

const string adresse = "../Music/";

void chargerMusique(string nomMusique);
void changerMusique(string nomMusique);
void jouerMusique();
void pauseMusique();
void arretMusique();


#endif // !MUSIQUE_HPP
