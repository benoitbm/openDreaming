#include "Parser.hpp"
queue<string> histoire; //Variable globale contenant les mots

///<summary>
///Fonction pour ouvrir la fenêtre de dialogue pour choisir un fichier.
///</summary>
OpenFileDialog::OpenFileDialog(void)
{
	this->DefaultExtension = 0;
	this->FileName = new TCHAR[MAX_PATH];
	this->Filter = 0;
	this->FilterIndex = 0;
	this->Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	this->InitialDir = 0;
	this->Owner = 0;
	this->Title = 0;
}

///<summary>
///Fonction pour afficher la fenêtre de dialogue pour choisir un fichier
///</summary>
bool OpenFileDialog::ShowDialog()
{
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = this->Owner;
	ofn.lpstrDefExt = this->DefaultExtension;
	ofn.lpstrFile = this->FileName;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = this->Filter;
	ofn.nFilterIndex = this->FilterIndex;
	ofn.lpstrInitialDir = this->InitialDir;
	ofn.lpstrTitle = this->Title;
	ofn.Flags = this->Flags;

	GetOpenFileName(&ofn);

	if (_tcslen(this->FileName) == 0) return false;

	return true;
}


///<summary>
///La fonction readFile permet de lire un fichier texte ouvert dans une fenêtre
///</summary>
void readFile()
{
	OpenFileDialog* OFD = new OpenFileDialog(); //On instancie une nouvelle classe pour ouvrir une fenêtre

	OFD->Filter = _T("Fichiers texte\0*.txt\0Tous les fichiers\0*.*\0";); //On rajoute le filtre .txt et tous les fichiers
	OFD->Title = _T("Chose the begin of the story..."); //Le titre lors de l'ouverture

	OFD->ShowDialog();

	string nomfichier = OFD->FileName;

	ifstream fichier;
	fichier.open(nomfichier);

	if (fichier.is_open()) //On teste si le fichier est bien ouvert (et que l'utilisateur ne tente pas d'ouvrir autre chose)
	{
		string mots = "";
		while (fichier >> mots) //On récupère chaque mot
			histoire.push(mots);
	}
	else
		return; //TODO Proposer à l'utilisateur d'ouvrir à nouveau son fichier

	fichier.close(); 
}

///<summary>
///La fonction recevoirPhrase() permet de récupérer la phrase actuelle du fichier.
///</summary>
///<returns> Renvoie une "queue" de strings. </returns>
queue<string> recevoirPhrase()
{
	if (histoire.empty()) //On teste s'il reste du contenu à envoyer
		return queue<string>(); // On renvoie une queue vide
	else
	{
		bool finPhrase = false;
		queue<string> Phrase;
		while (!finPhrase)
		{
			Phrase.push(histoire.front()); //On rajoute le premier mot de la file
			histoire.pop(); //Et on l'enlève

			string temp = Phrase.back();
			finPhrase = temp.at(temp.size() - 1) == '.';
		}
		return Phrase;
	}
}

///<summary>
///La fonction recevoirMot() permet de récupérer le mot actuel du fichier.
///</summary>
///<returns> Renvoie un string. </returns>
string recevoirMot()
{
	if (histoire.empty())
		return "";
	else
	{
		string mot = histoire.front();
		histoire.pop();
		return mot;
	}
}
