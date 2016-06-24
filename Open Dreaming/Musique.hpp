#pragma once
#ifndef MUSIQUE_HPP
#define MUSIQUE_HPP

#include <SFML\Audio.hpp>
#include <string>
#include <map>

#include "Random.hpp"

using namespace std;

const string adresse = "../Music/";

void chargerMusique(string nomMusique);
void changerMusique(string nomMusique);
void jouerMusique();
void pauseMusique();
void arretMusique();
void musiqueMot(string mot);
void creerListe();
sf::Music * getMusique();


#endif // !MUSIQUE_HPP
