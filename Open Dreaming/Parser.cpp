#include "Parser.hpp"

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

	cout << "Fichier choisi : " + nomfichier << endl;

	ifstream fichier;
	fichier.open(nomfichier);

	queue<string> histoire;

	cout << "Fichier ouvert ?" << fichier.is_open() << endl;
	if (fichier.is_open()) //On teste si le fichier est bien ouvert (et que l'utilisateur ne tente pas d'ouvrir autre chose)
	{
		string mots = "";
		while (fichier >> mots) //On récupère chaque mot
			histoire.push(mots);
	}
	else
		return; //TODO Proposer à l'utilisateur d'ouvrir à nouveau son fichier

	while (!histoire.empty())
	{
		cout << histoire.front() << endl;
		cout << "Contenu : " << histoire.size() << endl << endl;
		histoire.pop();
	}

	fichier.close(); 
	system("pause");
}
