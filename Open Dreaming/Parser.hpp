#pragma once
#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream> //Pour lire les fichiers
#include <string>
#include <queue>

#include <Windows.h> //Utilis� pour la fen�tre d'exploration de fichier.
#include <Commdlg.h>
#include <tchar.h>

using namespace std;

class OpenFileDialog //Fonction Microsoft pour faire appara�tre une fen�tre pour choisir un fichier
{
	public:
		OpenFileDialog(void);

	TCHAR* DefaultExtension;
	TCHAR* FileName;
	TCHAR* Filter;
	int FilterIndex;
	int Flags;
	TCHAR* InitialDir;
	HWND Owner;
	TCHAR* Title;

	bool ShowDialog();
};

void readFile();

#endif